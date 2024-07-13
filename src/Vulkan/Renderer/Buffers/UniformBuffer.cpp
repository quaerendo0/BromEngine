#include "UniformBuffer.h"

Vulkan::UniformBuffer::UniformBuffer(const LogicalDevice &device)
    : AbstractBuffer{device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, sizeof(UniformBufferObject), 1,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT} {
  vkMapMemory(device.getDevicePtr(), bufferMemory, 0, _size, 0, &mappedDataHandlerPtr);
}

Vulkan::UniformBuffer::~UniformBuffer() { vkUnmapMemory(device.getDevicePtr(), bufferMemory); }

void Vulkan::UniformBuffer::acquireData(const void *srcData) const {
  memcpy(mappedDataHandlerPtr, srcData, (size_t)_size);
}
