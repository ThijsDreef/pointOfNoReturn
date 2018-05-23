#include "fbo.h"
#include <iostream>
Fbo::Fbo(int width, int height)
{
  w = width;
  h = height;
  glGenFramebuffers(1, &id);
  glBindFramebuffer(GL_FRAMEBUFFER, id);
}

Fbo::~Fbo()
{

}

void Fbo::attachDepth()
{
  bind();
  glGenRenderbuffers(1, &renderBufferId);
  glBindRenderbuffer(GL_RENDERBUFFER, renderBufferId);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBufferId);
}

unsigned int Fbo::getDepth()
{
  return renderBufferId;
}

unsigned int Fbo::getTextureIndex(unsigned int attachment)
{
  return textures[attachment].getId();
}

void Fbo::attach(unsigned int internal, unsigned int format, unsigned int dataType, unsigned int bindingPoint)
{
  bind();
  textures.push_back(Texture(w, h, internal, format, GL_NEAREST, dataType, 0, "fboTexture"));
  bindingPoints.push_back(bindingPoint);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + bindingPoint, GL_TEXTURE_2D, textures[textures.size() - 1].getId(), 0);
  attachments.push_back(GL_COLOR_ATTACHMENT0 + bindingPoint);
  glDrawBuffers(attachments.size(), &attachments[0]);
}

void Fbo::attach(Texture * texture, unsigned int bindingPoint)
{
  textures.push_back(*texture);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + bindingPoint, GL_TEXTURE_2D, textures[textures.size() - 1].getId(), 0);
  attachments.push_back(GL_COLOR_ATTACHMENT0 + bindingPoint);
  glDrawBuffers(attachments.size(), &attachments[0]);
}

void Fbo::bind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void Fbo::prepareDraw()
{
  for (unsigned int i = 0; i < textures.size(); i++)
  {
    textures[i].bind(bindingPoints[i]);
  }

}
