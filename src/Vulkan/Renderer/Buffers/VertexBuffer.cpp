#include "VertexBuffer.h"
#include "../Commands/CommandBuffer.h"
#include "../Commands/CopyBufferCommand.h"

Vulkan::VertexBuffer::VertexBuffer(const LogicalDevice &device,
                                   const std::vector<BromEngine::Geometry::Vertex> &vertices,
                                   const CommandPool &commandPool)
    : elementsCount{vertices.size()} {
  const auto size = sizeof(BromEngine::Geometry::Vertex) * vertices.size();
  stagingBuffer =
      std::make_unique<BasicBuffer>(device, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, size);

  vkMapMemory(device.getDevicePtr(), stagingBuffer->getBufferMemoryHandle(), 0, size, 0, &mappedDataHandlerPtr);
  memcpy(mappedDataHandlerPtr, vertices.data(), (size_t)size);
  vkUnmapMemory(device.getDevicePtr(), stagingBuffer->getBufferMemoryHandle());

  inMemoryBuffer =
      std::make_unique<BasicBuffer>(device, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, size);

  CommandBuffer tempCopyCommandBuffer{device, commandPool};
  std::vector<std::unique_ptr<ICommand>> commands{};
  commands.push_back(std::make_unique<CopyBufferCommand>(tempCopyCommandBuffer, *stagingBuffer, *inMemoryBuffer));
  tempCopyCommandBuffer.recordCommandBuffer(commands);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &tempCopyCommandBuffer.getBuffer();

  vkQueueSubmit(device.getGraphicsQueue().getQueue(), 1, &submitInfo, VK_NULL_HANDLE);
  vkQueueWaitIdle(device.getGraphicsQueue().getQueue());

  vkFreeCommandBuffers(device.getDevicePtr(), commandPool.getCommandPool(), 1, &tempCopyCommandBuffer.getBuffer());
}

Vulkan::VertexBuffer::~VertexBuffer() {}
