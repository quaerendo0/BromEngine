#pragma once

#include "vulkan/vulkan.h"
#include "../../LogicalDevice.h"
#include "AbstractBuffer.h"

namespace Vulkan {

    enum InternalMemoryType {
        VertexBuffer,
        IndexBuffer
    };

    class DeviceInternalBuffer : public AbstractBuffer
    {
    public:
        DeviceInternalBuffer(const LogicalDevice &device, InternalMemoryType type, VkDeviceSize size, size_t elementCount);
        virtual ~DeviceInternalBuffer();
    };
}