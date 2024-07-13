#include "DescriptorManager.h"
#include <stdexcept>

namespace Vulkan {

DescriptorManager::DescriptorManager(const LogicalDevice &device, const DescriptorSetLayout &descriptorSetLayout,
                                     const std::vector<UniformBuffer *> uniformBuffers)
    : device{device} {
  const auto setAmount = uniformBuffers.size();
  VkDescriptorPoolSize poolSize{};
  poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  poolSize.descriptorCount = static_cast<uint32_t>(setAmount);

  VkDescriptorPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  poolInfo.poolSizeCount = 1;
  poolInfo.pPoolSizes = &poolSize;
  poolInfo.maxSets = static_cast<uint32_t>(setAmount);

  if (vkCreateDescriptorPool(device.getDevicePtr(), &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
    throw std::runtime_error("failed to create descriptor pool!");
  }

  std::vector<VkDescriptorSetLayout> layouts{2, descriptorSetLayout.getLayout()};

  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptorPool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(setAmount);
  allocInfo.pSetLayouts = layouts.data();

  descriptorSets.resize(setAmount);
  if (vkAllocateDescriptorSets(device.getDevicePtr(), &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  for (size_t i = 0; i < setAmount; i++) {
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = uniformBuffers[i]->getBufferHandle();
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(UniformBufferObject);

    VkWriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = descriptorSets[i];
    descriptorWrite.dstBinding = 0;
    descriptorWrite.dstArrayElement = 0;
    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrite.descriptorCount = 1;
    descriptorWrite.pBufferInfo = &bufferInfo;

    vkUpdateDescriptorSets(device.getDevicePtr(), 1, &descriptorWrite, 0, nullptr);
  }
}

DescriptorManager::~DescriptorManager() { vkDestroyDescriptorPool(device.getDevicePtr(), descriptorPool, nullptr); }
} // namespace Vulkan