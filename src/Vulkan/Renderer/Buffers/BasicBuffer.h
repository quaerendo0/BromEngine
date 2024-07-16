#pragma once

#include "../../LogicalDevice.h"
#include "IBuffer.h"
#include <vector>

namespace Vulkan {
class BasicBuffer : public IBuffer {
public:
  BasicBuffer(const LogicalDevice &device, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
              VkDeviceSize size);
  virtual ~BasicBuffer();

  const VkDeviceMemory &getBufferMemoryHandle() const { return bufferMemory; }
  const VkBuffer &getBufferHandle() const { return bufferHandle; }
  VkDeviceSize size() const { return _size; }

protected:
  const LogicalDevice &device;

  VkBuffer bufferHandle;
  VkDeviceMemory bufferMemory;
  VkDeviceSize _size;
};
} // namespace Vulkan