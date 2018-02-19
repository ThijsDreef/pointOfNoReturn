#include <mingw.thread.h>
#include "rotateTransform.h"
#include "renderModule.h"
#include "basicScene.h"
#include "engine.h"
#include "orbitalCamera.h"

int main(int argc, char const *argv[])
{
  Engine engine(1/60.0f);
  Object * object = new Object({});
  object->addComponent(new RotateTransform(Vec3<float>(0, 0, -0.5f), Vec3<float>(1, 1, 1), Vec3<float>(0, 0, 0), "obj_hammer_triangle", {"initialShadingGroup", "Material.001"}, Vec3<float>(0, 0, 0), engine.getInput(), object));
  object->addComponent(new OrbitalCamera(-5, Vec3<bool>(true, false, true), Vec3<float>(-15, -90, 0), &object->getComponent<Transform>()->getRot(), &object->getComponent<Transform>()->getPos(), object));
  engine.start(new BasicScene
    (
      {
        object,
        new Object({new Transform(Vec3<float>(-2, 0, -2), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "wizard", {"Material.001", "initialShadingGroup"}, 0)}),
        new Object({new Transform(Vec3<float>(2, 0, -2), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "wizard", {"Material.001", "initialShadingGroup"}, 0)}),
        new Object({new Transform(Vec3<float>(2, 0, 2), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "wizard", {"Material.001", "initialShadingGroup"}, 0)}),
        new Object({new Transform(Vec3<float>(-2, 0, 2), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "wizard", {"Material.001", "initialShadingGroup"}, 0)})
      },
      {
        new RenderModule(engine.getGeoLib(), engine.getMatLib(), engine.getShaderManger())
      }
    ));
  return 0;
}
