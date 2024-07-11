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
        VkDeviceSize size() const { return _size; }
        size_t elementCount() const { return _elementCount; }

    protected:
        AbstractBuffer(
            const LogicalDevice &device,
            VkBufferUsageFlags usage,
            VkDeviceSize size,
            size_t elementCount,
            VkMemoryPropertyFlags properties);
        const LogicalDevice &device;

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        size_t _elementCount;
        VkDeviceSize _size;
    };
}