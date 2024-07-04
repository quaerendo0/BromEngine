#pragma once

#include "SwapChain.h"
#include "RenderPass.h"
#include "LogicalDevice.h"
#include <stdexcept>

namespace Vulkan {
	class FrameBuffer {
	public:
		FrameBuffer(const SwapChain &swapchain, const RenderPass &renderPass, const LogicalDevice &device);
		~FrameBuffer();

	private:
		std::vector<VkFramebuffer> swapChainFramebuffers;
		const LogicalDevice& device;
	};
}