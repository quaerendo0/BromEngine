#include "BindDescriptorSetCommand.h"

namespace Vulkan {
BindDescriptorSetCommand::BindDescriptorSetCommand(CommandBuffer &buffer, const GraphicsPipeline &graphicsPipeline,
                                                   const VkDescriptorSet &descriptorSet)
    : graphicsPipeline{graphicsPipeline}, descriptorSet{descriptorSet}, buffer{buffer} {}

void BindDescriptorSetCommand::enqueue() const {
  vkCmdBindDescriptorSets(buffer.getBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline.getPipelineLayout(), 0,
                          1, &descriptorSet, 0, nullptr);
}
} // namespace Vulkan
