#pragma once

#include "../../Geometry/Vertex.h"
#include "../../LogicalDevice.h"
#include <vector>

namespace Vulkan {
class AbstractBuffer {
public:
  virtual ~AbstractBuffer();

  const VkBuffer &getBufferHandle() const { return bufferHandle; }
  VkDeviceSize size() const { return _size; }
  size_t elementCount() const { return _elementCount; }

protected:
  AbstractBuffer(const LogicalDevice &device, VkBufferUsageFlags usage,
                 VkDeviceSize size, size_t elementCount,
                 VkMemoryPropertyFlags properties);
  const LogicalDevice &device;

  VkBuffer bufferHandle;
  VkDeviceMemory bufferMemory;
  size_t _elementCount;
  VkDeviceSize _size;
};
} // namespace Vulkan