#include "vulkan/vulkan.h"

#include "StopRenderPassCommand.h"

Vulkan::StopRenderPassCommand::StopRenderPassCommand(CommandBuffer &buffer) : buffer{buffer} {}

void Vulkan::StopRenderPassCommand::enqueue() const { vkCmdEndRenderPass(buffer.getBuffer()); }
