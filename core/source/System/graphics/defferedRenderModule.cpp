#include "System/Graphics/defferedRenderModule.h"
#define _USE_MATH_DEFINES

DefferedRenderModule::DefferedRenderModule(GeometryLib * geo, MaterialLib * mat, ShaderManager * shader, int width, int height) : renderFbo(Fbo(width, height)), shadowFbo(Fbo(width, height))
{
  w = width;
  h = height;
  geoLib = geo;
  matLib = mat;
  shaderManager = shader;
  shaderManager->createShaderProgram("shaders/defferedStandard.vert", "shaders/defferedStandard.frag", "deffered");
  shaderManager->createShaderProgram("shaders/standard.vert", "shaders/standard.frag", "standard");
  shaderManager->createShaderProgram("shaders/defferedFinish.vert", "shaders/defferedFinish.frag", "deffered-finish");
  shaderManager->createShaderProgram("shaders/directionalLight.vert", "shaders/directionalLight.frag", "directionalLight");
  glEnable(GL_CULL_FACE);
  geoLib->setUpBuffer();
  matLib->setUpBuffer();
  setUpFormat();
  projection.perspectiveView(60, width / (float)height, 0.01, 100.0);
  camera.translateMatrix(Vec3<float>(0, 0, -2));
  renderFbo.bind();
  renderFbo.attach(GL_RGBA16F, GL_RGBA, GL_FLOAT, 0);
  renderFbo.attach(GL_RGB16F, GL_RGB, GL_FLOAT, 1);
  renderFbo.attach(GL_RGB16F, GL_RGB, GL_FLOAT, 2);
  renderFbo.attachDepth(w, h);
  shadowFbo.bind();
  shadowFbo.attachDepth(4096, 4096);
}

DefferedRenderModule::~DefferedRenderModule()
{

}

void DefferedRenderModule::setUpFormat()
{
  // stream, buffer, offset, stride
  glBindVertexBuffer(0, geoLib->getGeoBufferId(), 0, 32);
  glEnableVertexAttribArray(0);
  glVertexAttribFormat(0, 3, GL_FLOAT, false,  0); // position
  glVertexAttribBinding(0, 0); // position -> stream 0
  glEnableVertexAttribArray(1);
  glVertexAttribFormat(1, 3, GL_FLOAT, false, 12); // normal
  glVertexAttribBinding(1, 0); // normal   -> stream 0
  glEnableVertexAttribArray(2);
  glVertexAttribFormat(2, 2, GL_FLOAT, false, 24); // texcoord
  glVertexAttribBinding(2, 0); // texcoord -> stream 0
}

void DefferedRenderModule::updatePerspective(int width, int height, int fov, float near, float far)
{
  projection.perspectiveView(fov, (float)width/(float)height, near, far);
}

void DefferedRenderModule::addObject(Object * object)
{
  Transform *  transObj = object->getComponent<Transform>();
  if (transObj)
  {
    transObj->added();
    transforms.push_back(transObj);
  }
  Camera * cam = object->getComponent<Camera>();
  if (cam)
    cam->setMatrix(&camera);
}

Matrix<float> * DefferedRenderModule::getCameraMatrix()
{
  return &camera;
}

void DefferedRenderModule::update()
{
  //TODO: add a way to cull objects


  //bind fbo
  renderFbo.bind();
  glViewport(0, 0, w, h);

  //bind the fbo textures to the gldrawTarget
  renderFbo.prepareDraw();
  //clear the fbo
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //buffer the matrices
  matBufferer.setBuffer(transforms, camera, projection);
  //bind the buffer base to binding 1 hard bound in shader
  glUseProgram(shaderManager->getShader("deffered"));
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, matBufferer.getBufferId());

  //prepare vector used for rendering
  std::vector<std::vector<std::pair<unsigned int, Transform*>>> renderList;
  for (unsigned int i = 0; i < transforms.size(); i++)
  {
    if (transforms[i]->isDead())
    {
      transforms[i]->setRemoved();
      transforms.erase(transforms.begin() + i);
    }
    for (unsigned int j = 0; j < transforms[i]->materials.size(); j++)
    {
      if (j >= geoLib->getTotalGroups(transforms[i]->model)) break;
      unsigned int materialId = matLib->getMaterialId(transforms[i]->materials[j]);
      //nested if to for to increase renderlist size to needed material index
      if (materialId >= renderList.size()) for (unsigned int i = renderList.size(); i <= materialId; i++) renderList.push_back(std::vector<std::pair<unsigned int, Transform*>>());
      renderList[materialId].push_back(std::pair<unsigned int, Transform*>(j, transforms[i]));
    }
  }

  //primary render loop
  glCullFace(GL_BACK);

  drawGeometry(renderList, true);

  //shadow map rendering
  Vec3<float> directionalLight(0, -8, -4);

  //shadow matrix setup
  Matrix<float> lightMatrix;
  Matrix<float> temp;
  lightMatrix.orthographicView(4, 4, 0.01, 20);
  temp.translateMatrix(Vec3<float>(0, -8, -4));
  temp = temp.multiplyByMatrix(temp.rotation(directionalLight));
  lightMatrix = lightMatrix.multiplyByMatrix(temp);

  //draw shadow map
  shadowFbo.bind();
  glViewport(0, 0, 4096, 4096);
  glCullFace(GL_BACK);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(shaderManager->getShader("directionalLight"));
  glUniformMatrix4fv(shaderManager->uniformLocation("directionalLight", "uLightVP"), 1, false, &lightMatrix.matrix[0]);
  drawGeometry(renderList, false);

  // draw one screen aligned quad
  glCullFace(GL_BACK);
  glViewport(0, 0, w, h);

  glUseProgram(shaderManager->getShader("deffered-finish"));
  glUniformMatrix4fv(shaderManager->uniformLocation("deffered-finish", "uLightVP"), 1, false, &lightMatrix.matrix[0]);
  glUniform3f(shaderManager->uniformLocation("deffered-finish", "directionalLight"), directionalLight[0], directionalLight[1], directionalLight[2]);
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, shadowFbo.getDepth());
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  std::vector<unsigned int> indice = geoLib->getIndice("quad", 0);
  glDrawElements(GL_TRIANGLES, indice.size(), GL_UNSIGNED_INT, &indice[0]);
}

void DefferedRenderModule::drawGeometry(std::vector<std::vector<std::pair<unsigned int, Transform*>>> & renderList, bool materials)
{
  for (unsigned int i = 0; i < renderList.size(); i++)
  {
    if (materials) glBindBufferRange(GL_UNIFORM_BUFFER, 0, matLib->matBuffer.getBufferId(), i * sizeof(Material), sizeof(Material));
    unsigned int bufferIndex = -1;
    for (unsigned int j = 0; j < renderList[i].size(); j++)
    {
      if (bufferIndex != renderList[i][j].second->bufferIndex)
      {
        bufferIndex = renderList[i][j].second->bufferIndex;
        glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 1, matBufferer.getBufferId(), bufferIndex * sizeof(MatrixBufferObject), sizeof(MatrixBufferObject));
      }
      std::vector<unsigned int> indice = geoLib->getIndice(renderList[i][j].second->model, renderList[i][j].first);
      glDrawElements(GL_TRIANGLES, indice.size(), GL_UNSIGNED_INT, &indice[0]);
    }
  }
}
