#pragma once

#include <vector>
#include "../LogicalDevice.h"
#include "../Geometry/Vertex.h"

namespace Vulkan
{
    class VertexBuffer {
    public:
        VertexBuffer(const LogicalDevice &device, const std::vector<Vertex> &vertices);
        ~VertexBuffer();

        const VkBuffer &getBufferHandle() const { return vertexBuffer; }
        uint32_t size() const { return _size; }

    private:
        const LogicalDevice &device;

        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t _size;
    };
}
