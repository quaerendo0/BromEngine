#pragma once

#include "../LogicalDevice.h"
#include "RenderPass.h"
#include "SwapChain.h"
#include <fstream>
#include <string>
#include <vector>
#include <vulkan/vulkan_core.h>

namespace Vulkan {

class GraphicsPipeline {
public:
  GraphicsPipeline(const LogicalDevice &logicalDevice, const VkExtent2D swapChainExtent, const RenderPass &renderPass);
  ~GraphicsPipeline();

  const VkPipeline &getPipeline() const noexcept { return graphicsPipeline; }

private:
  VkPipelineLayout pipelineLayout = nullptr;
  VkPipeline graphicsPipeline = nullptr;
  const LogicalDevice &logicalDevice;
};

} // namespace Vulkan