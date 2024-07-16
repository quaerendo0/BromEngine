#pragma once

#include "../../LogicalDevice.h"
#include "../Commands/CommandPool.h"
#include "BasicBuffer.h"
#include "IBuffer.h"
#include <vector>

namespace Vulkan {
class IndexBuffer : IElementBuffer {
public:
  IndexBuffer(const LogicalDevice &device, const std::vector<uint16_t> &indices, const CommandPool &commandPool);
  virtual ~IndexBuffer();

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