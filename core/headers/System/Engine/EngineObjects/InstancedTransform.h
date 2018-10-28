#ifndef INSTANCEDTRANSFORM__
#define INSTANCEDTRANSFORM__
#include "System/Engine/EngineObjects/component.h"
#include "System/Engine/EngineObjects/transform.h"
#include "System/Graphics/Resources/buffer.h"



class InstancedTransform : public Component
{
private:
    std::vector<Transform*> instances;
    Buffer matrixBuffer;
    
    std::vector<Matrix<float>> bufferData;
public:
    std::string & getModel();
    InstancedTransform(Object * object);
    ~InstancedTransform();
    void addToInstance(Transform * t);
    void prepareBuffer(Matrix<float> & view, Matrix<float> & p);
    unsigned int getBufferId();
    unsigned int getTransformSize();

};

#endif