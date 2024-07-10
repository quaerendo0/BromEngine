#include "vulkan/vulkan.h"

#include "DrawCommand.h"

#include "CommandBuffer.h"

Vulkan::DrawCommand::DrawCommand(CommandBuffer &buffer) : buffer{buffer}
{
}

void Vulkan::DrawCommand::execute() const
{
    vkCmdDraw(buffer.getBuffer(), 3, 1, 0, 0);
}
