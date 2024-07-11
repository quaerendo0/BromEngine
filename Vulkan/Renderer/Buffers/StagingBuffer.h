#pragma once

#include <vector>
#include "../../LogicalDevice.h"
#include "../../Geometry/Vertex.h"
#include "AbstractBuffer.h"

namespace Vulkan
{
    template<class T>
    class StagingBuffer : public AbstractBuffer {
    public:
        StagingBuffer(const LogicalDevice &device, const std::vector<T> &elements)
        : AbstractBuffer{
            device,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            sizeof(elements[0]) * elements.size(),
            elements.size(),
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT}
        {
            void* data;
            vkMapMemory(device.getDevicePtr(), stagingBufferMemory, 0, _size, 0, &data);
            memcpy(data, elements.data(), (size_t) _size);
            vkUnmapMemory(device.getDevicePtr(), stagingBufferMemory);
        }

        virtual ~StagingBuffer() {};
    };
}
