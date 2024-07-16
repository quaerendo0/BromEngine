#include "UniformBuffer.h"

Vulkan::UniformBuffer::UniformBuffer(const LogicalDevice &device, VkDeviceSize size)
    : BasicBuffer{device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, size} {
  vkMapMemory(device.getDevicePtr(), bufferMemory, 0, size, 0, &mappedDataHandlerPtr);
}

Vulkan::UniformBuffer::~UniformBuffer() { vkUnmapMemory(device.getDevicePtr(), bufferMemory); }

void Vulkan::UniformBuffer::acquireData(const void *srcData) const {
  memcpy(mappedDataHandlerPtr, srcData, (size_t)_size);
}
