#pragma once

#include <glm/glm.hpp>

namespace BromEngine {
namespace Geometry {
struct GlobalSpaceSettings {
  static const glm::vec3 Front;
  static const glm::vec3 Up;
  static const glm::vec3 Left;
};

const glm::vec3 GlobalSpaceSettings::Front = {1.0f, 0.0f, 0.0f};
const glm::vec3 GlobalSpaceSettings::Up = {0.0f, 0.0f, 1.0f};
const glm::vec3 GlobalSpaceSettings::Left = {0.0f, 1.0f, 0.0f};
} // namespace Geometry
} // namespace BromEngine
