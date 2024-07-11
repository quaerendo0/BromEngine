#include "StagingBuffer.h"

#include "vulkan/vulkan.h"
#include <stdexcept>

Vulkan::StagingBuffer::StagingBuffer(const LogicalDevice &device, const std::vector<Vertex> &vertices)
    : AbstractBuffer{device, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, vertices, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT}
{
    void* data;
    vkMapMemory(device.getDevicePtr(), stagingBufferMemory, 0, _size, 0, &data);
    memcpy(data, vertices.data(), (size_t) _size);
    vkUnmapMemory(device.getDevicePtr(), stagingBufferMemory);
}

Vulkan::StagingBuffer::~StagingBuffer() {}