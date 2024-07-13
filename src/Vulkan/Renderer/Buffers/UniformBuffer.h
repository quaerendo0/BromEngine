#pragma once

#include "../UniformBufferObject.h"
#include "AbstractBuffer.h"

namespace Vulkan {
class UniformBuffer : public AbstractBuffer {
public:
  UniformBuffer(const LogicalDevice &device);
  virtual ~UniformBuffer();

  void acquireData(const void *srcData);

private:
  void *mappedDataHandlerPtr = nullptr;
};
} // namespace Vulkan