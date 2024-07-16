#include "CopyBufferCommand.h"

Vulkan::CopyBufferCommand::CopyBufferCommand(CommandBuffer &buffer, const BasicBuffer &srcBuffer,
                                             const BasicBuffer &trgtBuffer)
    : srcBuffer{srcBuffer}, trgtBuffer{trgtBuffer}, buffer{buffer} {}

void Vulkan::CopyBufferCommand::enqueue() const {
  VkBufferCopy copyRegion{};
  copyRegion.size = trgtBuffer.size();
  vkCmdCopyBuffer(buffer.getBuffer(), srcBuffer.getBufferHandle(), trgtBuffer.getBufferHandle(), 1, &copyRegion);
}
