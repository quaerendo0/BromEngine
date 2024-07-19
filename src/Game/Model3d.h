#pragma once

#include "Geometry/Vertex.h"
#include <vector>

namespace BromEngine {
class Model3d {
public:
  Model3d(std::vector<Geometry::Vertex> vertices, std::vector<uint16_t> indices)
      : vertices{vertices}, indices{indices} {};
  ~Model3d() {};

  const std::vector<Geometry::Vertex> &getVertices() const { return vertices; }
  const std::vector<uint16_t> &getIndices() const { return indices; }

  float X = 0.0f;
  float Y = 0.0f;
  float Z = 0.0f;

  glm::vec3 frontNormalized{1.0f, 0.0f, 0.0f};
  glm::vec3 upNormalized{0.0f, 0.0f, 1.0f};

private:
  std::vector<Geometry::Vertex> vertices;
  std::vector<uint16_t> indices;
};
} // namespace BromEngine