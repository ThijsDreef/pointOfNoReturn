#include "System/Physics/collider.h"
#include "Game/Object/rotateTransform.h"
#include "System/Graphics/renderModule.h"
#include "System/Engine/scene.h"
#include "System/Engine/engine.h"
#include "System/Engine/EngineObjects/orbitalCamera.h"
#include "System/Graphics/defferedRenderModule.h"
#include "System/Physics/collisionModule.h"
#include "System/Physics/octree.h"
#include "System/Engine/EngineObjects/fpsCamera.h"
#include <iostream>

int main(int argc, char const *argv[])
{
  Engine engine(1/60.0f, 1920, 1080);
  if (GLEW_ARB_bindless_texture) std::cout << "PogChamp\n";
  engine.getInput()->setMouseLock(true);
  Object * camera = new Object({});
  camera->addComponent(new FpsCamera(engine.getInput(), camera));
  Object * object = new Object({});
  object->addComponent(new RotateTransform(Vec3<float>(0, 1.8, 0), Vec3<float>(1.5, 1.5, 1.5), Vec3<float>(0, 0, 0), "sponza", {"None"}, engine.getInput(), object));
  // object->addComponent(new OrbitalCamera(-18, Vec3<bool>(false, false, true), Vec3<float>(0, 0, 0), &object->getComponent<RotateTransform>()->rotation, &object->getComponent<Transform>()->getPos(), true, object));
  Object * box = new Object({});
  box->addComponent(new Transform(Vec3<float>(0, 0, 0), Vec3<float>(10, 0.1, 10), Vec3<float>(0, 0, 0), "cube", {"Material.001", "initialShadingGroup"}, box));
  // box->getComponent<Transform>()->castShadow = false;

  Object * instanced = new Object({});

  std::vector<Object*> objects;

  InstancedTransform * it = new InstancedTransform(instanced);
  for (int x = -10; x < 10; x++) {
    for (int y = 2; y < 10; y++) {
      for (int z = -10; z < 10; z++) {
        Object * o = new Object({});
        o->addComponent(new RotateTransform(Vec3<float>(x, 1.8 + y, z), Vec3<float>(0.2, 0.2, 0.2), Vec3<float>(0, 90, 0), "cube", {"initialShadingGroup"}, engine.getInput(), o));
        objects.push_back(o);
        it->addToInstance(o->getComponent<Transform>());
      }
    }
  }
  instanced->addComponent(it);
  // objects.push_back(instanced);
  objects.push_back(object);
  objects.push_back(camera);
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
