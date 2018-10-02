#include <mingw.thread.h>
#include "System/Physics/collider.h"
#include "Game/Object/rotateTransform.h"
#include "System/Graphics/renderModule.h"
#include "System/Engine/scene.h"
#include "System/Engine/engine.h"
#include "System/Engine/EngineObjects/orbitalCamera.h"
#include "System/Graphics/defferedRenderModule.h"
#include "System/Physics/collisionModule.h"
#include "System/Physics/octree.h"
#include <iostream>

int main(int argc, char const *argv[])
{
  Engine engine(1/60.0f, 1920, 1080);
  engine.getInput()->setMouseLock(true);
  Object * object = new Object({});
  object->addComponent(new RotateTransform(Vec3<float>(0, 1.8, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 0, 0), "bunny", {"initialShadingGroup"}, engine.getInput(), object));
  object->addComponent(new OrbitalCamera(-18, Vec3<bool>(false, false, true), Vec3<float>(-15, 0, 0), &object->getComponent<RotateTransform>()->rotation, &object->getComponent<Transform>()->getPos(), true, object));
  Object * box = new Object({});
  box->addComponent(new Transform(Vec3<float>(0, 0, 0), Vec3<float>(10, 1, 10), Vec3<float>(0, 0, 0), "cube", {"Material.001", "initialShadingGroup"}, box));
  box->getComponent<Transform>()->castShadow = false;

  Object * instanced = new Object({});

  std::vector<Object*> objects;

  InstancedTransform * it = new InstancedTransform(instanced);
  for (int x = -5; x < 5; x++) {
    for (int y = 0; y < 5; y++) {
      for (int z = -5; z < 5; z++) {
        Object * o = new Object({});
        o->addComponent(new RotateTransform(Vec3<float>(x, 1.8 + y * 1.8, z), Vec3<float>(1, 1, 1), Vec3<float>(0, 0, 0), "bunny", {"initialShadingGroup"}, engine.getInput(), o));
        objects.push_back(o);
        it->addToInstance(o->getComponent<Transform>());
      }
    }
  }
  instanced->addComponent(it);
  objects.push_back(instanced);
  objects.push_back(object);
  objects.push_back(box);

  engine.start(new Scene
    (
      objects,
      {
        new DefferedRenderModule(engine.getGeoLib(), engine.getMatLib(), engine.getShaderManger(), engine.getWidth(), engine.getHeight()),
        new CollisionModule(50, 4)
      }
    ));
  return 0;
}
