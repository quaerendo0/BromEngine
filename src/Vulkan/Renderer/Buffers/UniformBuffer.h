#pragma once

#include "../UniformBufferObject.h"
#include "BasicBuffer.h"

namespace Vulkan {
class UniformBuffer : public BasicBuffer {
public:
  UniformBuffer(const LogicalDevice &device, VkDeviceSize size);
  virtual ~UniformBuffer();

  void acquireData(const void *srcData) const;

private:
  void *mappedDataHandlerPtr = nullptr;
};
} // namespace Vulkan