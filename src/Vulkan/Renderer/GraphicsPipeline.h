#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

#include "../LogicalDevice.h"
#include "DescriptorSetLayout.h"
#include "RenderPass.h"
#include "SwapChain.h"

namespace Vulkan {

class GraphicsPipeline {
public:
  GraphicsPipeline(const LogicalDevice &logicalDevice, const VkExtent2D swapChainExtent,
                   const DescriptorSetLayout &descriptorSetLayout, const RenderPass &renderPass);
  ~GraphicsPipeline();

  const VkPipeline &getPipeline() const noexcept { return graphicsPipeline; }
  const VkPipelineLayout &getPipelineLayout() const noexcept { return pipelineLayout; }

private:
  VkPipelineLayout pipelineLayout = nullptr;
  VkPipeline graphicsPipeline = nullptr;
  const LogicalDevice &logicalDevice;
};

} // namespace Vulkan