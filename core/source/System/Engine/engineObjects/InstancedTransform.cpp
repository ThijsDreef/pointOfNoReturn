#include "System/Engine/EngineObjects/InstancedTransform.h"

InstancedTransform::InstancedTransform(Object * object) : Component(object), matrixBuffer("matrices", GL_ARRAY_BUFFER)
{

}

InstancedTransform::~InstancedTransform() 
{

}

void InstancedTransform::addToInstance(Transform * t) 
{
    t->shouldRender = false;
    instances.push_back(t);
}

void InstancedTransform::prepareBuffer(Matrix<float> & view, Matrix<float> & p) 
{
    for (unsigned int i = 0; i < instances.size(); i++) 
    {
        MatrixBufferObject o = instances[i]->getBuffer(view, p);
        if (i >= bufferData.size()) bufferData.push_back(o.modelView);
        else bufferData[i] = (o.modelView);
    }
    matrixBuffer.bufferData(sizeof(float) * 16 * bufferData.size(), &bufferData[0].matrix[0], GL_STATIC_DRAW);
}

std::string & InstancedTransform::getModel() 
{
    return instances[0]->model;
}

unsigned int InstancedTransform::getBufferId() 
{
    return matrixBuffer.getBufferId();
}

unsigned int InstancedTransform::getTransformSize() 
{
    return instances.size();
}