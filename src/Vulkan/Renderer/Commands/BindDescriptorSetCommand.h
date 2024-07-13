#pragma once

#include "../CommandBuffer.h"
#include "../GraphicsPipeline.h"
#include "ICommand.h"


namespace Vulkan {
class BindDescriptorSetCommand : public ICommand {
public:
  BindDescriptorSetCommand(CommandBuffer &buffer, const GraphicsPipeline &graphicsPipeline,
                           const VkDescriptorSet &descriptorSet);
  void execute() const override;

private:
  const GraphicsPipeline &graphicsPipeline;
  const VkDescriptorSet &descriptorSet;
  CommandBuffer &buffer;
};
} // namespace Vulkan
