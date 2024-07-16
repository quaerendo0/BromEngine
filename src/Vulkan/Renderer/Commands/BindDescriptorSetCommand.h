#pragma once

#include "../GraphicsPipeline.h"
#include "CommandBuffer.h"
#include "ICommand.h"

namespace Vulkan {
class BindDescriptorSetCommand : public ICommand {
public:
  BindDescriptorSetCommand(CommandBuffer &buffer, const GraphicsPipeline &graphicsPipeline,
                           const VkDescriptorSet &descriptorSet, const std::vector<uint32_t> &dynamicOffsets)
      : graphicsPipeline{graphicsPipeline}, descriptorSet{descriptorSet}, buffer{buffer},
        dynamicOffsets{dynamicOffsets} {};

  void enqueue() const {
    vkCmdBindDescriptorSets(buffer.getBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline.getPipelineLayout(),
                            0, 1, &descriptorSet, dynamicOffsets.size(), dynamicOffsets.data());
  }

private:
  const GraphicsPipeline &graphicsPipeline;
  const VkDescriptorSet &descriptorSet;
  CommandBuffer &buffer;
  const std::vector<uint32_t> &dynamicOffsets;
};
} // namespace Vulkan
