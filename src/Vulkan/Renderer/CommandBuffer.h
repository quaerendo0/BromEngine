#pragma once

#include "../LogicalDevice.h"
#include "vulkan/vulkan.h"

#include "./Commands/ICommand.h"
#include "CommandPool.h"

namespace Vulkan {
class CommandBuffer {
public:
  CommandBuffer(const LogicalDevice &device, const CommandPool &commandPool);
  ~CommandBuffer();

  void recordCommandBuffer(const std::vector<std::unique_ptr<ICommand>> &commands);
  void resetCommandBuffer() const;

  const VkCommandBuffer &getBuffer() const noexcept { return commandBuffer; }

private:
  VkCommandBuffer commandBuffer;

  void beginRecordingCommands() const;
  void stopRecordingCommands() const;
};
} // namespace Vulkan