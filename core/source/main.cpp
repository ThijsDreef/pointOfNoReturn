#include <mingw.thread.h>
#include "rotateTransform.h"
#include "renderModule.h"
#include "basicScene.h"
#include "engine.h"
#include "orbitalCamera.h"
#include "aabbModule.h"
#include "characterResolver.h"

int main(int argc, char const *argv[])
{
  Engine engine(1/60.0f);
  Object * object = new Object({});
  object->addComponent(new RotateTransform(Vec3<float>(0, 0.5, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 0, 0), "wizard", {"initialShadingGroup", "Material.001"}, Vec3<float>(0, 0, 0), engine.getInput(), object));
  object->addComponent(new OrbitalCamera(-5, Vec3<bool>(false, false, true), Vec3<float>(-15, -90, 0), &object->getComponent<Transform>()->getRot(), &object->getComponent<Transform>()->getPos(), true, object));
  object->addComponent(new Aabb(object->getComponent<Transform>()->getPos(), Vec3<float>(1, 1, 1), new CharacterResolver(), "player", 0));

  Object * ground = new Object({new Transform(Vec3<float>(0, 0, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "cube", {"Material.001", "initialShadingGroup"}, 0)});
  ground->addComponent(new Aabb(ground->getComponent<Transform>()->getPos(), Vec3<float>(1, 1, 1), 0, "ground", 0));

  engine.start(new BasicScene
    (
      {
        object,
        new Object({new Transform(Vec3<float>(8, 2, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "wizard", {"Material.001", "initialShadingGroup"}, 0)}),
        new Object({new Transform(Vec3<float>(0, 1, 0), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "wizard", {"Material.001", "initialShadingGroup"}, 0)}),
        new Object({new Transform(Vec3<float>(0, 1, 8), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "wizard", {"Material.001", "initialShadingGroup"}, 0)}),
        new Object({new Transform(Vec3<float>(8, 1, 8), Vec3<float>(1, 1, 1), Vec3<float>(0, 90, 0), "wizard", {"Material.001", "initialShadingGroup"}, 0)}),
        ground

      },
      {
        new RenderModule(engine.getGeoLib(), engine.getMatLib(), engine.getShaderManger()),
        new AabbModule(32)
      }
    ));
  return 0;
}
