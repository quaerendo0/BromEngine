#pragma once

#include "../GraphicsPipeline.h"
#include "CommandBuffer.h"
#include "ICommand.h"


namespace Vulkan {
class BindDescriptorSetCommand : public ICommand {
public:
  BindDescriptorSetCommand(CommandBuffer &buffer, const GraphicsPipeline &graphicsPipeline,
                           const VkDescriptorSet &descriptorSet);
  void enqueue() const override;

private:
  const GraphicsPipeline &graphicsPipeline;
  const VkDescriptorSet &descriptorSet;
  CommandBuffer &buffer;
};
} // namespace Vulkan
