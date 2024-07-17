#include "UniformBuffer.h"

Vulkan::UniformBuffer::UniformBuffer(const LogicalDevice &device, VkDeviceSize size, bool a) : device{device} {
  if (!a) {
    uniformBuffer =
        std::make_unique<BasicBuffer>(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, size);
  } else {
    uniformBuffer = std::make_unique<BasicBuffer>(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                                  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, size);
  }
  vkMapMemory(device.getDevicePtr(), uniformBuffer->getBufferMemoryHandle(), 0, size, 0, &mappedDataHandlerPtr);
}

Vulkan::UniformBuffer::~UniformBuffer() {
  vkUnmapMemory(device.getDevicePtr(), uniformBuffer->getBufferMemoryHandle());
}

void Vulkan::UniformBuffer::acquireData(const void *srcData) const {
  memcpy(mappedDataHandlerPtr, srcData, uniformBuffer->size());
}
