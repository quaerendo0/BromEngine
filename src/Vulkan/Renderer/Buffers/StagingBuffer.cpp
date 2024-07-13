#include "StagingBuffer.h"

Vulkan::StagingBuffer::StagingBuffer(const LogicalDevice &device,
                                     const VkDeviceSize size,
                                     const size_t elementCount,
                                     const void *srcData)
    : AbstractBuffer{device, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, size,
                     elementCount,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                         VK_MEMORY_PROPERTY_HOST_COHERENT_BIT} {
  acquireData(srcData);
}

Vulkan::StagingBuffer::StagingBuffer(const LogicalDevice &device,
                                     const VkDeviceSize size,
                                     const size_t elementCount)
    : AbstractBuffer{device, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, size,
                     elementCount,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                         VK_MEMORY_PROPERTY_HOST_COHERENT_BIT} {}

Vulkan::StagingBuffer::~StagingBuffer() {}

void Vulkan::StagingBuffer::acquireData(const void *srcData) {
  vkMapMemory(device.getDevicePtr(), bufferMemory, 0, _size, 0,
              &mappedDataHandlerPtr);
  memcpy(mappedDataHandlerPtr, srcData, (size_t)_size);
  vkUnmapMemory(device.getDevicePtr(), bufferMemory);
}
