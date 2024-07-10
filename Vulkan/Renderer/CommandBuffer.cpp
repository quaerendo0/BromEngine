#include <stdexcept>

#include "CommandBuffer.h"

namespace Vulkan {
    CommandBuffer::CommandBuffer(const LogicalDevice &device, const CommandPool &commandPool)
    {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool.getCommandPool();
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;

        if (vkAllocateCommandBuffers(device.getDevicePtr(), &allocInfo, &commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }
    }

    CommandBuffer::~CommandBuffer()
    {
    }

    void CommandBuffer::beginRecordingCommands() const {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0; // Optional
        beginInfo.pInheritanceInfo = nullptr; // Optional

        if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }
    }

    void CommandBuffer::bindCommandBufferToPipeline(const GraphicsPipeline &pipeline) {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.getPipeline());
    }

    void CommandBuffer::startRenderPass(
        uint32_t imageIndex,
        const RenderPass& renderPass,
        const FrameBuffer &frameBuffer,
        const VkExtent2D &extent)
    {
        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = renderPass.getRenderPass();
        renderPassInfo.framebuffer = frameBuffer.getSwapChainFramebuffers().at(imageIndex);

        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = extent;

        VkClearValue clearColor = { { { 0.0f, 0.0f, 0.0f, 1.0f } } };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;
        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    }

    void CommandBuffer::setupViewportScissor(const VkExtent2D &extent) {
        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)extent.width;
        viewport.height = (float)extent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = extent;
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
    }

    void CommandBuffer::stopRenderPass() const {
        vkCmdEndRenderPass(commandBuffer);
    }

    void CommandBuffer::stopRecordingCommands() const {
        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
    }

    void CommandBuffer::initCommandBuffer(const CommandBufferInitInfo& info)
    {
        beginRecordingCommands();
        startRenderPass(info.imageIndex, info.renderPass, info.frameBuffer, info.swapChain.getSwapChainExtent());
        bindCommandBufferToPipeline(info.pipeline);
        setupViewportScissor(info.swapChain.getSwapChainExtent());
        for (const DrawCommand& command : info.commands) {
            command.execute();
        }
        stopRenderPass();
        stopRecordingCommands();
    }

    void CommandBuffer::resetCommandBuffer() const
    {
        vkResetCommandBuffer(commandBuffer, 0);
    }
}