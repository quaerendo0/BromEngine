#pragma once

#include <vector>
#include "../../LogicalDevice.h"
#include "../../Geometry/Vertex.h"
#include "AbstractBuffer.h"

namespace Vulkan
{
    class StagingBuffer : public AbstractBuffer {
    public:
        StagingBuffer(const LogicalDevice &device, const std::vector<Vertex> &vertices);
        virtual ~StagingBuffer();
    };
}
