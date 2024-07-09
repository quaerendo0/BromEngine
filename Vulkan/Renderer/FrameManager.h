#pragma once

#include "vulkan/vulkan.h"
#include "../LogicalDevice.h"
#include "SwapChain.h"
#include "CommandManager.h"

namespace Vulkan {
	class FrameManager {
	public:
		FrameManager(const LogicalDevice& logicalDevice, const SwapChain& swapChain, CommandManager& commandManager);
		~FrameManager();

		void drawFrame();

	private:
		VkSemaphore imageAvailableSemaphore; // VkSemaphore - only GPU waits for GPU, CPU is not locked
		VkSemaphore renderFinishedSemaphore;
		VkFence inFlightFence; // fence - makes CPU wait for GPU

		const LogicalDevice& logicalDevice;
		const SwapChain& swapChain;
		CommandManager& commandManager;
	};
}