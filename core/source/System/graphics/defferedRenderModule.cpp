#include "System/Graphics/defferedRenderModule.h"
#define _USE_MATH_DEFINES

DefferedRenderModule::DefferedRenderModule(GeometryLib * geo, MaterialLib * mat, ShaderManager * shader, int width, int height) : renderFbo(Fbo(width, height)), shadowFbo(Fbo(width, height))
{
  glGenVertexArrays(1, &defaultVao);
  glGenVertexArrays(1, &instancedVao);

  glBindVertexArray(defaultVao);
  w = width;
  h = height;
  geoLib = geo;
  matLib = mat;
  shaderManager = shader;
  shaderManager->createShaderProgram("shaders/defferedStandard.vert", "shaders/defferedStandard.frag", "deffered");
  shaderManager->createShaderProgram("shaders/standard.vert", "shaders/standard.frag", "standard");
  shaderManager->createShaderProgram("shaders/defferedFinish.vert", "shaders/defferedFinish.frag", "deffered-finish");
  shaderManager->createShaderProgram("shaders/directionalLight.vert", "shaders/directionalLight.frag", "directionalLight");
  shaderManager->createShaderProgram("shaders/defferedInstanced.vert", "shaders/defferedInstanced.frag", "defferedInstanced");
  shaderManager->createShaderProgram("shaders/directionalLightInstanced.vert", "shaders/directionalLightInstanced.frag", "directionalLightInstanced");


  glEnable(GL_CULL_FACE);
  geoLib->setUpBuffer();
  matLib->setUpBuffer();
  setUpFormat();
  setUpInstancedFormat();
  projection.perspectiveView(45, width / (float)height, 0.01, 100.0);
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
  glBindVertexArray(defaultVao);
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

void DefferedRenderModule::setUpInstancedFormat() 
{
  glBindVertexArray(instancedVao);

  glEnableVertexAttribArray(0);
  glVertexAttribFormat(0, 3, GL_FLOAT, false,  0); // position
  glVertexAttribBinding(0, 0); // position -> stream 0

  glEnableVertexAttribArray(1);
  glVertexAttribFormat(1, 3, GL_FLOAT, false, 12); // normal
  glVertexAttribBinding(1, 0); // normal   -> stream 0
  
  glEnableVertexAttribArray(2);
  glVertexAttribFormat(2, 2, GL_FLOAT, false, 24); // texcoord
  glVertexAttribBinding(2, 0); // texcoord -> stream 0

  glEnableVertexAttribArray(3);
  glVertexAttribFormat(3, 4, GL_FLOAT, false, 0);
  glVertexAttribBinding(3, 1);

  glEnableVertexAttribArray(4);
  glVertexAttribFormat(4, 4, GL_FLOAT, false, 16);
  glVertexAttribBinding(4, 1);

  glEnableVertexAttribArray(5);
  glVertexAttribFormat(5, 4, GL_FLOAT, false, 32);
  glVertexAttribBinding(5, 1);

  glEnableVertexAttribArray(6);
  glVertexAttribFormat(6, 4, GL_FLOAT, false, 48);
  glVertexAttribBinding(6, 1);

  glVertexBindingDivisor(1, 1);

}

void DefferedRenderModule::updatePerspective(int width, int height, int fov, float near, float far)
{
  projection.perspectiveView(fov, (float)width/(float)height, near, far);
}

void DefferedRenderModule::addObject(Object * object)
{
  Transform *  transObj = object->getComponent<Transform>();
  if (transObj && transObj->shouldRender)
  {
    transObj->added();
    transforms.push_back(transObj);
  }
  Camera * cam = object->getComponent<Camera>();
  if (cam) cam->setMatrix(&camera);

  InstancedTransform * itObj = object->getComponent<InstancedTransform>();
  if (itObj) instancedTransforms.push_back(itObj);
}

Matrix<float> * DefferedRenderModule::getCameraMatrix()
{
  return &camera;
}

void DefferedRenderModule::bindInstance()
{
  glBindVertexArray(instancedVao);
}

void DefferedRenderModule::bindDefault()
{
  glBindVertexArray(defaultVao);
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

  for (unsigned int i = 0; i < instancedTransforms.size(); i++)
    instancedTransforms[i]->prepareBuffer(camera, projection);

  //primary render loop
  glCullFace(GL_BACK);

  glUseProgram(shaderManager->getShader("deffered"));
  bindDefault();
  drawGeometry(renderList, true);

  glUseProgram(shaderManager->getShader("defferedInstanced"));  
  bindInstance();
  glUniformMatrix4fv(shaderManager->uniformLocation("defferedInstanced", "p"), 1, false, &projection.multiplyByMatrix(camera).matrix[0]);
  drawInstanced();

  //shadow map rendering
  Vec3<float> directionalLight(0.5, 2, 1);

  //shadow matrix setup
  Matrix<float> lightPerspective;
  Matrix<float> lightMatrix;
  Matrix<float> lightViewMatrix;
  lightPerspective.orthographicView(20, 20, -20, 20);
  lightViewMatrix.lookAt(directionalLight, Vec3<float>(), Vec3<float>(0, 1, 0));
  lightMatrix = lightPerspective.multiplyByMatrix(lightViewMatrix);

  //draw shadow map
  shadowFbo.bind();
  glViewport(0, 0, 4096, 4096);
  glCullFace(GL_FRONT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(shaderManager->getShader("directionalLight"));
  glUniformMatrix4fv(shaderManager->uniformLocation("directionalLight", "uLightVP"), 1, false, &lightMatrix.matrix[0]);

  bindDefault();
  drawGeometry(renderList, false);

  glUseProgram(shaderManager->getShader("directionalLightInstanced"));  
  glUniformMatrix4fv(shaderManager->uniformLocation("directionalLightInstanced", "uLightVP"), 1, false, &lightMatrix.matrix[0]);

  bindInstance();
  drawInstanced();

  // draw one screen aligned quad
  bindDefault();
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

void DefferedRenderModule::drawInstanced()
{
  for (unsigned int i = 0; i < instancedTransforms.size(); i++)
  {
    glBindVertexBuffer(0, geoLib->getGeoBufferId(), 0, 32);
    glBindVertexBuffer(1, instancedTransforms[i]->getBufferId(), 0, 64);
    for (unsigned int j = 0; j < geoLib->getTotalGroups(instancedTransforms[i]->getModel()); j++) {
      std::vector<unsigned int> indice = geoLib->getIndice(instancedTransforms[i]->getModel(), j);
      glDrawElementsInstanced(GL_TRIANGLES, indice.size(), GL_UNSIGNED_INT, &indice[0], instancedTransforms[0]->getTransformSize());
    }
  }
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
        if (!materials && !renderList[i][j].second->castShadow) break; 
      }
      std::vector<unsigned int> indice = geoLib->getIndice(renderList[i][j].second->model, renderList[i][j].first);
      glDrawElements(GL_TRIANGLES, indice.size(), GL_UNSIGNED_INT, &indice[0]);
    }
  }
}