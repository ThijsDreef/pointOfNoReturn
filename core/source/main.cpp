#include <mingw.thread.h>
#include "rotateTransform.h"
#include "renderModule.h"
#include "basicScene.h"
#include "engine.h"
#include "orbitalCamera.h"
#include "aabbModule.h"
#include "characterResolver.h"
#include "characterController.h"
#include <iostream>

int main(int argc, char const *argv[])
{
  Engine engine(1/60.0f);
  Object * object = new Object({});
  object->addComponent(new RotateTransform(Vec3<float>(1, 2, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 0, 0), "wizard", {"initialShadingGroup", "Material.001"}, engine.getInput(), object));
  object->addComponent(new OrbitalCamera(-5, Vec3<bool>(false, false, true), Vec3<float>(-15, 0, 0), &object->getComponent<RotateTransform>()->rotation, &object->getComponent<Transform>()->getPos(), true, object));
  object->addComponent(new Aabb(object->getComponent<Transform>()->getPos(), Vec3<float>(1, 1.4, 1), new CharacterResolver(), "player", object));
  // object->addComponent(new CharacterController(&object->getComponent<Aabb>()->velocity, &object->getComponent<Transform>()->getRot(), Vec3<float>(0.1, 0.3, 0.1), 4, engine.getInput(), object));

  // Object * box = new Object({new Transform(Vec3<float>(0, 1, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 0, 0), "cube", {"Material.001", "initialShadingGroup"}, 0)});
  // box->addComponent(new Aabb(box->getComponent<Transform>()->getPos(), Vec3<float>(1, 1, 1), 0, "ground", box));
  // Object * ground = new Object({new Transform(Vec3<float>(0, -1.0, 0), Vec3<float>(10, 1, 10), Vec3<float>(0, 0, 0), "cube", {"Material.001", "initialShadingGroup"}, 0)});
  // ground->addComponent(new Aabb(ground->getComponent<Transform>()->getPos(), Vec3<float>(10, 1, 10), 0, "ground", ground));
  engine.start(new BasicScene
    (
      {
        object
      },
      {
        new RenderModule(engine.getGeoLib(), engine.getMatLib(), engine.getShaderManger())
      }
    ));
  return 0;
}
