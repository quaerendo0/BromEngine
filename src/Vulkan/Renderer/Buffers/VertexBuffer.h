#pragma once

#include "../../../Game/Geometry/Vertex.h"
#include "../../LogicalDevice.h"
#include "../CommandPool.h"
#include "BasicBuffer.h"
#include <vector>

namespace Vulkan {
class VertexBuffer {
public:
  VertexBuffer(const LogicalDevice &device, const std::vector<BromEngine::Geometry::Vertex> &vertices,
               const CommandPool &commandPool);
  virtual ~VertexBuffer();

  const VkDeviceMemory &getBufferMemoryHandle() const { return inMemoryBuffer->getBufferMemoryHandle(); }
  const VkBuffer &getBufferHandle() const { return inMemoryBuffer->getBufferHandle(); }
  VkDeviceSize size() const { return stagingBuffer->size(); }
  size_t getElementsCount() const { return elementsCount; };

private:
  void *mappedDataHandlerPtr = nullptr;
  std::unique_ptr<BasicBuffer> stagingBuffer;
  std::unique_ptr<BasicBuffer> inMemoryBuffer;
  size_t elementsCount = 0;
};
} // namespace Vulkan