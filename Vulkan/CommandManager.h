#pragma once

#include "vulkan/vulkan.h"
#include "LogicalDevice.h"
#include <stdexcept>
#include "RenderPass.h"
#include "FrameBuffer.h"

namespace Vulkan {
	class CommandManager {
	public:
		CommandManager(const LogicalDevice &device, const RenderPass& renderPass, const FrameBuffer &frameBuffer, const SwapChain &swapChain);
		~CommandManager();

		void recordCommandBuffer() {
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags = 0; // Optional
			beginInfo.pInheritanceInfo = nullptr; // Optional

			if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
				throw std::runtime_error("failed to begin recording command buffer!");
			}
		}

		void startRenderPass(uint32_t imageIndex) {
			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = renderPass.getRenderPass();
			renderPassInfo.framebuffer = frameBuffer.getSwapChainFramebuffers().at(imageIndex);

			renderPassInfo.renderArea.offset = { 0, 0 };
			renderPassInfo.renderArea.extent = swapChain.getSwapChainExtent();

			VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
			renderPassInfo.clearValueCount = 1;
			renderPassInfo.pClearValues = &clearColor;
			vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		}

	private:
		VkCommandPool commandPool;
		VkCommandBuffer commandBuffer;

		const LogicalDevice &device;
		const FrameBuffer& frameBuffer;
		const SwapChain& swapChain;
		const RenderPass &renderPass;
	};
}