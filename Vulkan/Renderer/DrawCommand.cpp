#include "vulkan/vulkan.h"

#include "DrawCommand.h"

#include "CommandBuffer.h"

Vulkan::Command::Command(CommandBuffer &buffer) : buffer{buffer}
{
}

void Vulkan::Command::execute() const
{
    vkCmdDraw(buffer.getBuffer(), 3, 1, 0, 0);
}
