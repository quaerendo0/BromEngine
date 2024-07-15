#pragma once

#include "glm/glm.hpp"

namespace BromEngine {
class Camera {
public:
  glm::vec3 eyeLocation{2.0f, 2.0f, 2.0f};
  glm::vec3 looksAt{0.0f, 0.0f, 0.0f};
  glm::vec3 up{0.0f, 0.0f, 1.0f};
};
} // namespace BromEngine
