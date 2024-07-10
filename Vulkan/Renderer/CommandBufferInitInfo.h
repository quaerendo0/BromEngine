#pragma once

#include <vector>

#include "RenderPass.h"
#include "FrameBuffer.h"
#include "GraphicsPipeline.h"
#include "SwapChain.h"
#include "DrawCommand.h"
#include "VertexBuffer.h"

namespace Vulkan {

    struct CommandBufferInitInfo {
        uint32_t imageIndex;
        const RenderPass& renderPass;
        const FrameBuffer &frameBuffer;
        const GraphicsPipeline &pipeline;
        const SwapChain &swapChain;
        std::vector<DrawCommand> commands;
        const VertexBuffer& vertexBuffer;
    };
}