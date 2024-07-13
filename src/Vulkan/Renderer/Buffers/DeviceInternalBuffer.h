#pragma once

#include "../../LogicalDevice.h"
#include "AbstractBuffer.h"
#include "vulkan/vulkan.h"

namespace Vulkan {

enum InternalMemoryType { VertexBuffer, IndexBuffer };

class DeviceInternalBuffer : public AbstractBuffer {
public:
  DeviceInternalBuffer(const LogicalDevice &device, InternalMemoryType type, VkDeviceSize size, size_t elementCount);
  virtual ~DeviceInternalBuffer();
};
} // namespace Vulkan