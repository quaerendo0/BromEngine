#include "../../Game/Model3d.h"
#include "Buffers/IndexBuffer.h"
#include "Buffers/VertexBuffer.h"


namespace Vulkan {
class Vulkan3dModelWrapper {
public:
  Vulkan3dModelWrapper(const LogicalDevice &device, const BromEngine::Model3d &model);

private:
  std::unique_ptr<VertexBuffer> vertexBuffer;
  std::unique_ptr<IndexBuffer> idnexBuffer;
};
} // namespace Vulkan