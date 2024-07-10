#include "vulkan/vulkan.h"

#include "DrawCommand.h"

#include "CommandBuffer.h"

Vulkan::DrawCommand::DrawCommand(CommandBuffer& buffer, uint32_t vertexCount) : buffer{buffer}, vertexCount{vertexCount}
{
}

void Vulkan::DrawCommand::execute() const
{
    vkCmdDraw(buffer.getBuffer(), vertexCount, 1, 0, 0);
}
