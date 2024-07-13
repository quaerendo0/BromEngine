#include "CommandPool.h"

Vulkan::CommandPool::CommandPool(const LogicalDevice &device) : device{device} {
  auto queueFamilyIndices =
      device.getParentPhysicalDevice().getDeviceQueueFamiliesInfo();

  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

  if (vkCreateCommandPool(device.getDevicePtr(), &poolInfo, nullptr,
                          &commandPool) != VK_SUCCESS) {
    throw std::runtime_error("failed to create command pool!");
  }
}

Vulkan::CommandPool::~CommandPool() {
  vkDestroyCommandPool(device.getDevicePtr(), commandPool, nullptr);
}