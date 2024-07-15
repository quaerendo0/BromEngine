#pragma once

#include "Camera.h"
#include "Model3d.h"

namespace BromEngine {
class Scene {
public:
  Scene();
  const std::vector<Model3d> &getModels() const { return models; }
  const Camera &getCamera() const { return camera; }

private:
  std::vector<Model3d> models;
  Camera camera{};
};
} // namespace BromEngine
