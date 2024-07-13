#include "CopyBufferCommand.h"

Vulkan::CopyBufferCommand::CopyBufferCommand(CommandBuffer &buffer,
                                             const AbstractBuffer &srcBuffer,
                                             const AbstractBuffer &trgtBuffer)
    : buffer{buffer}, srcBuffer{srcBuffer}, trgtBuffer{trgtBuffer} {}

void Vulkan::CopyBufferCommand::execute() const {
  VkBufferCopy copyRegion{};
  copyRegion.size = trgtBuffer.size();
  vkCmdCopyBuffer(buffer.getBuffer(), srcBuffer.getBufferHandle(),
                  trgtBuffer.getBufferHandle(), 1, &copyRegion);
}
