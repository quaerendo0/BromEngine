#pragma once

#include "vulkan/vulkan.h"
#include "LogicalDevice.h"
#include <stdexcept>
#include "RenderPass.h"
#include "FrameBuffer.h"
#include "GraphicsPipeline.h"

namespace Vulkan {
	class CommandManager {
	public:
		CommandManager(
			const LogicalDevice &device,
			const RenderPass& renderPass,
			const FrameBuffer &frameBuffer,
			const SwapChain &swapChain,
			const GraphicsPipeline& graphicsPipeline);

		~CommandManager();

		void initCommandBuffer(uint32_t imageIndex);
		void resetCommandBuffer();

	private:

		void beginRecordingCommands() const;
		void bindCommandBufferToPipeline();
		void startRenderPass(uint32_t imageIndex);
		void setupAndInsertCommand();
		void stopRenderPass() const;
		void stopRecordingCommands();

		VkCommandPool commandPool;
		VkCommandBuffer commandBuffer;

		const LogicalDevice &device;
		const FrameBuffer& frameBuffer;
		const SwapChain& swapChain;
		const RenderPass &renderPass;
		const GraphicsPipeline& graphicsPipeline;
	};
}