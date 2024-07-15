#include "BasicBuffer.h"

#include "vulkan/vulkan.h"
#include <stdexcept>

uint32_t findMemoryType(VkPhysicalDevice device, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(device, &memProperties);

  for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
    if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
      return i;
    }
  }

  throw std::runtime_error("failed to find suitable memory type!");
}

Vulkan::BasicBuffer::BasicBuffer(const LogicalDevice &device, VkBufferUsageFlags usage,
                                 VkMemoryPropertyFlags properties, VkDeviceSize size)
    : device{device} {
  _size = size;

  VkBufferCreateInfo bufferInfo{};
  bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bufferInfo.size = _size;
  bufferInfo.usage = usage;
  bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if (vkCreateBuffer(device.getDevicePtr(), &bufferInfo, nullptr, &bufferHandle) != VK_SUCCESS) {
    throw std::runtime_error("failed to create vertex buffer!");
  }

  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements(device.getDevicePtr(), bufferHandle, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = findMemoryType(device.getParentPhysicalDevice().getPhysicalDevicePtr(),
                                             memRequirements.memoryTypeBits, properties);

  if (vkAllocateMemory(device.getDevicePtr(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
    throw std::runtime_error("failed to allocate vertex buffer memory!");
  }

  vkBindBufferMemory(device.getDevicePtr(), bufferHandle, bufferMemory, 0);
}

Vulkan::BasicBuffer::~BasicBuffer() {
  vkDestroyBuffer(device.getDevicePtr(), bufferHandle, nullptr);
  vkFreeMemory(device.getDevicePtr(), bufferMemory, nullptr);
}