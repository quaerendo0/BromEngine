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
		static constexpr int MAX_FRAMES_IN_FLIGHT = 2;
    	uint32_t currentFrame = 0;

		const LogicalDevice& device;
		const RenderPass& renderPass;
		const FrameBuffer& frameBuffer;
		const SwapChain& swapChain;
		const GraphicsPipeline& graphicsPipeline;

		CommandPool* commandPool;

		std::vector<VkSemaphore> imageAvailableSemaphores{MAX_FRAMES_IN_FLIGHT}; // VkSemaphore - only GPU waits for GPU, CPU is not locked
		std::vector<VkSemaphore> renderFinishedSemaphores{MAX_FRAMES_IN_FLIGHT};
		std::vector<VkFence> inFlightFences{MAX_FRAMES_IN_FLIGHT}; // fence - makes CPU wait for GPU
		std::vector<CommandBuffer*> commandBuffers{MAX_FRAMES_IN_FLIGHT};
	};
}