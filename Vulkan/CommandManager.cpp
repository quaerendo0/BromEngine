#include "CommandManager.h"

Vulkan::CommandManager::CommandManager(
	const LogicalDevice& device,
	const RenderPass& renderPass,
	const FrameBuffer& frameBuffer, 
	const SwapChain& swapChain,
	const GraphicsPipeline& graphicsPipeline)
	: device{ device }, 
	renderPass{ renderPass }, 
	frameBuffer{frameBuffer},
	swapChain{swapChain},
	graphicsPipeline{graphicsPipeline}
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

void Vulkan::CommandManager::beginRecordingCommands() const {
	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = 0; // Optional
	beginInfo.pInheritanceInfo = nullptr; // Optional

	if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to begin recording command buffer!");
	}
}

void Vulkan::CommandManager::bindCommandBufferToPipeline() {
	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline.getPipeline());
}

void Vulkan::CommandManager::startRenderPass(uint32_t imageIndex) {
	VkRenderPassBeginInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassInfo.renderPass = renderPass.getRenderPass();
	renderPassInfo.framebuffer = frameBuffer.getSwapChainFramebuffers().at(imageIndex);

	renderPassInfo.renderArea.offset = { 0, 0 };
	renderPassInfo.renderArea.extent = swapChain.getSwapChainExtent();

	VkClearValue clearColor = { { { 0.0f, 0.0f, 0.0f, 1.0f } } };
	renderPassInfo.clearValueCount = 1;
	renderPassInfo.pClearValues = &clearColor;
	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void Vulkan::CommandManager::setupAndInsertCommand() {
	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)swapChain.getSwapChainExtent().width;
	viewport.height = (float)swapChain.getSwapChainExtent().height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = swapChain.getSwapChainExtent();
	vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	vkCmdDraw(commandBuffer, 3, 1, 0, 0);
}

void Vulkan::CommandManager::stopRenderPass() const {
	vkCmdEndRenderPass(commandBuffer);
}

void Vulkan::CommandManager::stopRecordingCommands() {
	if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
		throw std::runtime_error("failed to record command buffer!");
	}
}

void Vulkan::CommandManager::initCommandBuffer(uint32_t imageIndex) {
	beginRecordingCommands();
	startRenderPass(imageIndex);
	bindCommandBufferToPipeline();
	setupAndInsertCommand();
	stopRenderPass();
	stopRecordingCommands();
}

void Vulkan::CommandManager::resetCommandBuffer() const
{
	vkResetCommandBuffer(commandBuffer, 0);
}
