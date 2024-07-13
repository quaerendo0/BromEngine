#pragma once

#include "vulkan/vulkan.h"

#include "../Buffers/DeviceInternalBuffer.h"
#include "../CommandBuffer.h"
#include "ICommand.h"

namespace Vulkan {
class DrawIndexedCommand : public ICommand {
public:
  DrawIndexedCommand(CommandBuffer &buffer,
                     const DeviceInternalBuffer &vertexBuffer,
                     const DeviceInternalBuffer &indexBuffer)
      : vertexBuffer{vertexBuffer}, buffer{buffer}, indexBuffer{indexBuffer} {};

  void execute() const override {
    VkBuffer vertexBuffers[] = {vertexBuffer.getBufferHandle()};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(buffer.getBuffer(), 0, 1, vertexBuffers, offsets);
    vkCmdBindIndexBuffer(buffer.getBuffer(), indexBuffer.getBufferHandle(), 0,
                         VK_INDEX_TYPE_UINT16);
    vkCmdDrawIndexed(buffer.getBuffer(),
                     static_cast<uint32_t>(indexBuffer.elementCount()), 1, 0, 0,
                     0);
  };

private:
  const DeviceInternalBuffer &vertexBuffer;
  const DeviceInternalBuffer &indexBuffer;
  CommandBuffer &buffer;
};
} // namespace Vulkan