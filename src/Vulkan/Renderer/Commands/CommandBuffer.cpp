#include <stdexcept>

#include "CommandBuffer.h"

namespace Vulkan {
CommandBuffer::CommandBuffer(const LogicalDevice &device, const CommandPool &commandPool) {
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = commandPool.getCommandPool();
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = 1;

  if (vkAllocateCommandBuffers(device.getDevicePtr(), &allocInfo, &commandBuffer) != VK_SUCCESS) {
    throw std::runtime_error("failed to allocate command buffers!");
  }
}

CommandBuffer::~CommandBuffer() {}

void CommandBuffer::beginRecordingCommands() const {
  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = 0;                  // Optional
  beginInfo.pInheritanceInfo = nullptr; // Optional

  if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
    throw std::runtime_error("failed to begin recording command buffer!");
  }
}

void CommandBuffer::stopRecordingCommands() const {
  if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
    throw std::runtime_error("failed to record command buffer!");
  }
}

void CommandBuffer::recordCommandBuffer(const std::vector<std::unique_ptr<ICommand>> &commands) {
  beginRecordingCommands();
  for (const auto &command : commands) {
    command->enqueue();
  }
  stopRecordingCommands();
}

void CommandBuffer::resetCommandBuffer() const { vkResetCommandBuffer(commandBuffer, 0); }
} // namespace Vulkan