#include "DeviceInternalBuffer.h"

namespace Vulkan {

const VkBufferUsageFlags getFlagsFromType(const InternalMemoryType type) {
  VkBufferUsageFlags flag = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
  switch (type) {
  case InternalMemoryType::VertexBuffer:
    flag = flag | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    break;
  case InternalMemoryType::IndexBuffer:
    flag = flag | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
    break;
  default:
    break;
  }
  return flag;
}

DeviceInternalBuffer::DeviceInternalBuffer(const LogicalDevice &device,
                                           InternalMemoryType type,
                                           VkDeviceSize size,
                                           size_t elementCount)
    : AbstractBuffer{device, getFlagsFromType(type), size, elementCount,
                     VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT} {}

DeviceInternalBuffer::~DeviceInternalBuffer() {}
} // namespace Vulkan