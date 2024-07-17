#pragma once

#include <stdexcept>

#include "glm/glm.hpp"
#include "vulkan/vulkan.h"

#include "../../LogicalDevice.h"
#include "../Buffers/IBuffer.h"

namespace Vulkan {
struct Mvp {
  glm::mat4 projection;
  glm::mat4 view;
};

struct MvpPerModel {
  glm::mat4 model; // glm::translate * glm::rotate
};

class DescriptorSetMeme {
public:
  DescriptorSetMeme(const LogicalDevice &device, uint32_t modelsCount, const IBuffer &buffer, const IBuffer &buffer2)
      : device{device} {
    initPool(device);
    initCameraDescriptorSetLayout(device);
    allocateDescriptorSets(device);
    bindCameraUboToDescriptorSet(device, modelsCount, buffer, buffer2);
  }

  ~DescriptorSetMeme() {
    for (size_t i = 0; i < totalSets; i++) {
      vkDestroyDescriptorSetLayout(device.getDevicePtr(), descriptorSetLayouts.at(i), nullptr);
    }

    vkDestroyDescriptorPool(device.getDevicePtr(), descriptorPool, nullptr);
  }

  const std::vector<VkDescriptorSetLayout> &getDescriptorSetLayouts() const { return descriptorSetLayouts; }

  const std::vector<VkDescriptorSet> &getDescriptorSets() const { return descriptorSets; }

private:
  const uint32_t totalSets = 1;
  const uint32_t totalPools = 1;
  const uint32_t totalMaxUboDescriptors = 10;
  const uint32_t totalMaxDynamicUboDescriptors = 10;

  const LogicalDevice &device;

  std::vector<VkDescriptorSetLayout> descriptorSetLayouts{totalSets};
  std::vector<VkDescriptorSet> descriptorSets{totalSets};
  VkDescriptorPool descriptorPool;

  void initPool(const LogicalDevice &device) {

    VkDescriptorPoolSize maxUboDescriptorsCount{};
    maxUboDescriptorsCount.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    maxUboDescriptorsCount.descriptorCount = totalMaxUboDescriptors;

    VkDescriptorPoolSize maxDynamicUboDescriptorsCount{};
    maxDynamicUboDescriptorsCount.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    maxDynamicUboDescriptorsCount.descriptorCount = totalMaxDynamicUboDescriptors;

    VkDescriptorPoolSize poolSizes[2] = {maxUboDescriptorsCount, maxDynamicUboDescriptorsCount};

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = 2;
    poolInfo.pPoolSizes = poolSizes;
    poolInfo.maxSets = totalSets;

    if (vkCreateDescriptorPool(device.getDevicePtr(), &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
      throw std::runtime_error("failed to create descriptor pool!");
    }
  }

  void initCameraDescriptorSetLayout(const LogicalDevice &device) {
    VkDescriptorSetLayoutBinding cameraLayoutBinding{};
    cameraLayoutBinding.binding = 0;
    cameraLayoutBinding.descriptorCount = 1; // 1 if fixed size OR dynamic, n for for fixed sized array
    cameraLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    cameraLayoutBinding.pImmutableSamplers = nullptr;
    cameraLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT; // which shader stage can access this

    VkDescriptorSetLayoutBinding perModelTransformBinding{};
    perModelTransformBinding.binding = 1;
    perModelTransformBinding.descriptorCount = 1; // 1 if fixed size OR dynamic, n for for fixed sized array
    perModelTransformBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    perModelTransformBinding.pImmutableSamplers = nullptr;
    perModelTransformBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT; // which shader stage can access this

    VkDescriptorSetLayoutBinding bindings[] = {cameraLayoutBinding, perModelTransformBinding};
    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 2;
    layoutInfo.pBindings = bindings;

    if (vkCreateDescriptorSetLayout(device.getDevicePtr(), &layoutInfo, nullptr, &descriptorSetLayouts[0]) !=
        VK_SUCCESS) {
      throw std::runtime_error("failed to create descriptor set layout!");
    }
  }

  void allocateDescriptorSets(const LogicalDevice &device) {
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = totalSets;
    allocInfo.pSetLayouts = descriptorSetLayouts.data();

    if (vkAllocateDescriptorSets(device.getDevicePtr(), &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
      throw std::runtime_error("failed to allocate descriptor sets!");
    }
  }

  void bindCameraUboToDescriptorSet(const LogicalDevice &device, uint32_t modelsCount, const IBuffer &buffer,
                                    const IBuffer &buffer2) {
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = buffer.getBufferHandle();
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(Mvp::projection) + sizeof(Mvp::view);
    VkWriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = descriptorSets[0];
    descriptorWrite.dstBinding = 0;
    descriptorWrite.dstArrayElement = 0;
    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrite.descriptorCount = 1;
    descriptorWrite.pBufferInfo = &bufferInfo;

    vkUpdateDescriptorSets(device.getDevicePtr(), 1, &descriptorWrite, 0, nullptr);

    VkDescriptorBufferInfo bufferInfo2{};
    bufferInfo2.buffer = buffer2.getBufferHandle();
    bufferInfo2.offset = 0;
    bufferInfo2.range = sizeof(MvpPerModel);

    VkWriteDescriptorSet descriptorWrite2{};
    descriptorWrite2.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite2.dstSet = descriptorSets[0];
    descriptorWrite2.dstBinding = 1;
    descriptorWrite2.dstArrayElement = 0;
    descriptorWrite2.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
    descriptorWrite2.descriptorCount = 1;
    descriptorWrite2.pBufferInfo = &bufferInfo2;

    vkUpdateDescriptorSets(device.getDevicePtr(), 1, &descriptorWrite2, 0, nullptr);
  }
};

} // namespace Vulkan