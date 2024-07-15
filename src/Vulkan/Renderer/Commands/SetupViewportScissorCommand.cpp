#include "vulkan/vulkan.h"

#include "SetupViewportScissorCommand.h"

Vulkan::SetupViewportScissorCommand::SetupViewportScissorCommand(CommandBuffer &buffer, const VkExtent2D &extent)
    : buffer{buffer}, extent{extent} {}

void Vulkan::SetupViewportScissorCommand::enqueue() const {
  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = (float)extent.width;
  viewport.height = (float)extent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  vkCmdSetViewport(buffer.getBuffer(), 0, 1, &viewport);

  VkRect2D scissor{};
  scissor.offset = {0, 0};
  scissor.extent = extent;
  vkCmdSetScissor(buffer.getBuffer(), 0, 1, &scissor);
}
