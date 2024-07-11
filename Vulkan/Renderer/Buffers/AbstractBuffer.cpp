#include "AbstractBuffer.h"

#include "vulkan/vulkan.h"
#include <stdexcept>

uint32_t findMemoryType(VkPhysicalDevice device, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(device, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

Vulkan::AbstractBuffer::AbstractBuffer(const LogicalDevice &device, VkBufferUsageFlags usage, const std::vector<Vertex> &vertices, VkMemoryPropertyFlags properties)
    : device{device}
{
    _size = sizeof(vertices[0]) * vertices.size();
    _vertexCount = vertices.size();

    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = _size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device.getDevicePtr(), &bufferInfo, nullptr, &stagingBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create vertex buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device.getDevicePtr(), stagingBuffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(
        device.getParentPhysicalDevice().getPhysicalDevicePtr(),
        memRequirements.memoryTypeBits,
        properties);

    if (vkAllocateMemory(device.getDevicePtr(), &allocInfo, nullptr, &stagingBufferMemory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate vertex buffer memory!");
    }

    vkBindBufferMemory(device.getDevicePtr(), stagingBuffer, stagingBufferMemory, 0);
}

Vulkan::AbstractBuffer::~AbstractBuffer()
{
    vkDestroyBuffer(device.getDevicePtr(), stagingBuffer, nullptr);
    vkFreeMemory(device.getDevicePtr(), stagingBufferMemory, nullptr);
}