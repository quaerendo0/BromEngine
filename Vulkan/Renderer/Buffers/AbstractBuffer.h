#pragma once

#include <vector>
#include "../../LogicalDevice.h"
#include "../../Geometry/Vertex.h"

namespace Vulkan
{
    class AbstractBuffer {
    public:
        virtual ~AbstractBuffer();

        const VkBuffer &getBufferHandle() const { return stagingBuffer; }
        uint32_t size() const { return _size; }
        VkDeviceSize vertexCount() const { return _vertexCount; }

    protected:
        AbstractBuffer(const LogicalDevice &device, VkBufferUsageFlags usage, const std::vector<Vertex> &vertices, VkMemoryPropertyFlags properties);
        const LogicalDevice &device;

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        uint32_t _vertexCount;
        VkDeviceSize _size;
    };
}