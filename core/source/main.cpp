#include <mingw.thread.h>
#include "rotateTransform.h"
#include "renderModule.h"
#include "scene.h"
#include "engine.h"
#include "orbitalCamera.h"
#include "defferedRenderModule.h"
#include <iostream>
#include "octree.h"
int main(int argc, char const *argv[])
{
  Engine engine(1/60.0f, 1920, 1080);
  Object * object = new Object({});
  object->addComponent(new RotateTransform(Vec3<float>(0, 1.8, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 0, 0), "bunny", {"initialShadingGroup"}, engine.getInput(), object));
  object->addComponent(new OrbitalCamera(-8, Vec3<bool>(false, false, true), Vec3<float>(-15, 0, 0), &object->getComponent<RotateTransform>()->rotation, &object->getComponent<Transform>()->getPos(), true, object));

  Object * box = new Object({});
  box->addComponent(new Transform(Vec3<float>(0, 0, 0), Vec3<float>(3, 1, 3), Vec3<float>(0, 0, 0), "cube", {"Material.001", "initialShadingGroup"}, box));

  engine.start(new Scene
    (
      {
        object,
        box
      },
      {
        new DefferedRenderModule(engine.getGeoLib(), engine.getMatLib(), engine.getShaderManger(), engine.getWidth(), engine.getHeight())
      }
    ));
  return 0;
}
