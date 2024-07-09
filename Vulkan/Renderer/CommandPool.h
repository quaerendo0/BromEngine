#pragma once

#include <stdexcept>

#include "vulkan/vulkan.h"

#include "../LogicalDevice.h"
#include "RenderPass.h"
#include "FrameBuffer.h"
#include "GraphicsPipeline.h"

namespace Vulkan {
	class CommandPool {
	public:
		CommandPool(const LogicalDevice &device);

		~CommandPool();

		void initCommandBuffer(uint32_t imageIndex);
		void resetCommandBuffer() const;

		const VkCommandPool& getCommandPool() const { return commandPool; }

	private:

		VkCommandPool commandPool;
		const LogicalDevice &device;
	};
}