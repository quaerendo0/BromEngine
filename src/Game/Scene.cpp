#include "Scene.h"

namespace BromEngine {

Scene::Scene() {

  const std::vector<Geometry::Vertex> vertices = {{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
                                                  {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
                                                  {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
                                                  {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}};

  const std::vector<uint16_t> indices = {0, 1, 2, 2, 3, 0};
  models.push_back(Model3d{vertices, indices});
  // models.push_back(Model3d{vertices, indices});
  models[0].X = 0.0f;
  models[0].Y = 0.0f;

  /*
    models[1].X = 0.0f;
    models[1].Y = 0.0f;*/
};
} // namespace BromEngine