#pragma once

#include "vulkan/vulkan.h"
#include "../LogicalDevice.h"
#include "SwapChain.h"
#include "CommandPool.h"
#include "CommandBuffer.h"

namespace Vulkan {
	class FrameManager {
	public:
		FrameManager(
			const LogicalDevice& device,
			const RenderPass& renderPass,
			const FrameBuffer& frameBuffer,
			const SwapChain& swapChain,
			const GraphicsPipeline& graphicsPipeline);
		~FrameManager();

		void drawFrame();

	private:
		VkSemaphore imageAvailableSemaphore; // VkSemaphore - only GPU waits for GPU, CPU is not locked
		VkSemaphore renderFinishedSemaphore;
		VkFence inFlightFence; // fence - makes CPU wait for GPU


		const LogicalDevice& device;
		const RenderPass& renderPass;
		const FrameBuffer& frameBuffer;
		const SwapChain& swapChain;
		const GraphicsPipeline& graphicsPipeline;

		CommandPool* commandPool;
		CommandBuffer* commandBuffer;
	};
}