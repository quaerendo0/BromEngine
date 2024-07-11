#include "vulkan/vulkan.h"

#include "StopRenderPassCommand.h"

Vulkan::StopRenderPassCommand::StopRenderPassCommand(CommandBuffer& buffer)
    : buffer{buffer}
{
}

void Vulkan::StopRenderPassCommand::execute() const
{
    vkCmdEndRenderPass(buffer.getBuffer());
}
