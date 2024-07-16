#pragma once

#include "../Buffers/VertexBuffer.h"
#include "CommandBuffer.h"
#include "ICommand.h"

namespace Vulkan {

class CommandBuffer;

class DrawCommand : public ICommand {
public:
  DrawCommand(CommandBuffer &buffer, const VertexBuffer &vertexBuffer) : buffer{buffer}, vertexBuffer{vertexBuffer} {};
  void enqueue() const override {
    VkBuffer stagingBuffers[] = {vertexBuffer.getBufferHandle()};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(buffer.getBuffer(), 0, 1, stagingBuffers, offsets);
    vkCmdDraw(buffer.getBuffer(), vertexBuffer.getElementsCount(), 1, 0, 0);
  };

private:
  CommandBuffer &buffer;
  const VertexBuffer &vertexBuffer;
};
} // namespace Vulkan