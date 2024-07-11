#pragma once
#include "vulkan/vulkan.h"
#include "../../LogicalDevice.h"
#include "AbstractBuffer.h"

namespace Vulkan {
    class DeviceVertexBuffer : public AbstractBuffer
    {
    public:
        DeviceVertexBuffer(const LogicalDevice &device, const std::vector<Vertex> &vertices)
            : AbstractBuffer{device, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, vertices, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT} {};
        virtual ~DeviceVertexBuffer() {};
    };
}