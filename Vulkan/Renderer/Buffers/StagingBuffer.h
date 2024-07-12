#pragma once

#include <vector>
#include "../../LogicalDevice.h"
#include "../../Geometry/Vertex.h"
#include "AbstractBuffer.h"

namespace Vulkan
{
    class StagingBuffer : public AbstractBuffer {
    public:
        StagingBuffer(const LogicalDevice &device, const VkDeviceSize size, const size_t elementCount, const void *srcData);
        StagingBuffer(const LogicalDevice &device, const VkDeviceSize size, const size_t elementCount);
        virtual ~StagingBuffer();

        void acquireData(const void *srcData);

    private:
        void* mappedDataHandlerPtr = nullptr;
    };
}
