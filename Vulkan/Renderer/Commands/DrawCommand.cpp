#include "DrawCommand.h"

#include "vulkan/vulkan.h"
#include "../CommandBuffer.h"

Vulkan::DrawCommand::DrawCommand(CommandBuffer& buffer, const AbstractBuffer& stagingBuffer)
    : buffer{buffer}, stagingBuffer{stagingBuffer}
{
}

void Vulkan::DrawCommand::execute() const
{
    VkBuffer stagingBuffers[] = {stagingBuffer.getBufferHandle()};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(buffer.getBuffer(), 0, 1, stagingBuffers, offsets);
    vkCmdDraw(buffer.getBuffer(), stagingBuffer.elementCount(), 1, 0, 0);
}
