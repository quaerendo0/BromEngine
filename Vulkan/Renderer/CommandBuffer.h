#pragma once

#include "vulkan/vulkan.h"
#include "../LogicalDevice.h"

#include "CommandPool.h"
#include "CommandBufferInitInfo.h"
#include "VertexBuffer.h"

namespace Vulkan {
    class CommandBuffer
    {
    public:
        CommandBuffer(const LogicalDevice &device, const CommandPool &commandPool);
        ~CommandBuffer();

		void recordCommandBuffer(const CommandBufferInitInfo& info);
		void resetCommandBuffer() const;

        const VkCommandBuffer &getBuffer() const noexcept { return commandBuffer; }

    private:
        VkCommandBuffer commandBuffer;

		void beginRecordingCommands() const;
		void bindCommandBufferToPipeline(const GraphicsPipeline &pipeline);
        void bindVertexBuffer(const VertexBuffer& vertexBuffer);
		void startRenderPass(
            uint32_t imageIndex,
            const RenderPass& renderPass,
            const FrameBuffer &frameBuffer,
            const VkExtent2D &extent);
		void setupViewportScissor(const VkExtent2D &extent);
		void stopRenderPass() const;
		void stopRecordingCommands() const;
    };
}