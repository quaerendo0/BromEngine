#pragma once

#include "vulkan/vulkan.h"

#include "../LogicalDevice.h"
#include "Buffers/UniformBuffer.h"
#include "DescriptorSetLayout.h"

namespace Vulkan {
class DescriptorManager {
public:
  DescriptorManager(const LogicalDevice &device, const DescriptorSetLayout &descriptorSetLayout,
                    const std::vector<UniformBuffer *> uniformBuffers);
  ~DescriptorManager();

  const std::vector<VkDescriptorSet> &getDescriptorSets() const { return descriptorSets; }

private:
  const LogicalDevice &device;
  VkDescriptorPool descriptorPool;
  std::vector<VkDescriptorSet> descriptorSets;
};

} // namespace Vulkan
