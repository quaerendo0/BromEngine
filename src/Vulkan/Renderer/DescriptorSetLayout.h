#pragma once

#include "vulkan/vulkan.h"

#include "../LogicalDevice.h"

namespace Vulkan {
class DescriptorSetLayout {
public:
  DescriptorSetLayout(const LogicalDevice &device);
  ~DescriptorSetLayout();

  const VkDescriptorSetLayout &getLayout() const { return descriptorSetLayout; };

private:
  const LogicalDevice &device;
  VkDescriptorSetLayout descriptorSetLayout;
};

} // namespace Vulkan
