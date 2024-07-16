#include "IndexBuffer.h"
#include "../Commands/CommandBuffer.h"
#include "../Commands/CopyBufferCommand.h"
#include "../Commands/ICommand.h"

Vulkan::IndexBuffer::IndexBuffer(const LogicalDevice &device, const std::vector<uint16_t> &indices,
                                 const CommandPool &commandPool)
    : elementsCount{indices.size()} {
  const auto size = sizeof(uint16_t) * indices.size();
  stagingBuffer =
      std::make_unique<BasicBuffer>(device, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, size);

  vkMapMemory(device.getDevicePtr(), stagingBuffer->getBufferMemoryHandle(), 0, size, 0, &mappedDataHandlerPtr);
  memcpy(mappedDataHandlerPtr, indices.data(), (size_t)size);
  vkUnmapMemory(device.getDevicePtr(), stagingBuffer->getBufferMemoryHandle());

  inMemoryBuffer =
      std::make_unique<BasicBuffer>(device, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                                    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, size);

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

Vulkan::IndexBuffer::~IndexBuffer() {}
