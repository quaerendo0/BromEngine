#pragma once

#include "vulkan/vulkan.h"

#include "../Buffers/IndexBuffer.h"
#include "../Buffers/VertexBuffer.h"
#include "../CommandBuffer.h"
#include "ICommand.h"

namespace Vulkan {
class DrawIndexedCommand : public ICommand {
public:
  DrawIndexedCommand(CommandBuffer &buffer, const VertexBuffer &vertexBuffer, const IndexBuffer &indexBuffer)
      : buffer{buffer}, vertexBuffer{vertexBuffer}, indexBuffer{indexBuffer} {};

  void enqueue() const override {
    VkBuffer vertexBuffers[] = {vertexBuffer.getBufferHandle()};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(buffer.getBuffer(), 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(buffer.getBuffer(), indexBuffer.getBufferHandle(), 0, VK_INDEX_TYPE_UINT16);
    vkCmdDrawIndexed(buffer.getBuffer(), static_cast<uint32_t>(indexBuffer.getElementsCount()), 1, 0, 0, 0);
  };

private:
  CommandBuffer &buffer;
  const VertexBuffer &vertexBuffer;
  const IndexBuffer &indexBuffer;
};
} // namespace Vulkan