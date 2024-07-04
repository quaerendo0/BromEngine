#include "CommandManager.h"

Vulkan::CommandManager::CommandManager(const LogicalDevice& device, const RenderPass& renderPass, const FrameBuffer& frameBuffer, const SwapChain& swapChain)
	: device{ device }, renderPass{ renderPass }, frameBuffer{frameBuffer}, swapChain{swapChain}
{
	auto queueFamilyIndices = device.getParentPhysicalDevice().getDeviceQueueFamiliesInfo();

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

	if (vkCreateCommandPool(device.getDevicePtr(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create command pool!");
	}

	VkCommandBufferAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = 1;

	if (vkAllocateCommandBuffers(device.getDevicePtr(), &allocInfo, &commandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}
}

Vulkan::CommandManager::~CommandManager() {
	vkDestroyCommandPool(device.getDevicePtr(), commandPool, nullptr);
}