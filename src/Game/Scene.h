#pragma once

#include "Camera.h"
#include "Model3d.h"

namespace BromEngine {
class Scene {
public:
  Scene();

  Scene(const Scene &) = delete;
  Scene &operator=(const Scene &) = delete;

  const std::vector<Model3d> &getModels() const { return models; }
  std::vector<Model3d> &getModelsChange() { return models; }
  const Camera &getCamera() const { return camera; }

private:
  std::vector<Model3d> models;
  Camera camera{};
};
} // namespace BromEngine
