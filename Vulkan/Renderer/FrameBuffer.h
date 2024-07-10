#pragma once

#include "../LogicalDevice.h"
#include "SwapChain.h"
#include "RenderPass.h"
#include <stdexcept>

namespace Vulkan {
	class FrameBuffer {
	public:
		FrameBuffer(const SwapChain &swapchain, const RenderPass &renderPass, const LogicalDevice &device);
		~FrameBuffer();

		const std::vector<VkFramebuffer>& getSwapChainFramebuffers() const noexcept { return swapChainFramebuffers; }

	private:
		std::vector<VkFramebuffer> swapChainFramebuffers;
		const LogicalDevice& device;
	};
}