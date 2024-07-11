#pragma once
#include "vulkan/vulkan.h"
#include "../../LogicalDevice.h"
#include "AbstractBuffer.h"

namespace Vulkan {
    template<class T>
    class DeviceVertexBuffer : public AbstractBuffer
    {
    public:
        DeviceVertexBuffer(const LogicalDevice &device, const std::vector<T> &elements)
            : AbstractBuffer{
                device,
                VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                sizeof(elements[0]) * elements.size(),
                elements.size(),
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT} {};
        virtual ~DeviceVertexBuffer() {};
    };
}