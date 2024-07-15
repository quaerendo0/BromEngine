#pragma once

#include "../CommandBuffer.h"
#include "../GraphicsPipeline.h"
#include "ICommand.h"

namespace Vulkan {

class CommandBuffer;

class BindCommandBufferToPipelineCommand : public ICommand {
public:
  BindCommandBufferToPipelineCommand(CommandBuffer &buffer, const GraphicsPipeline &pipeline);
  void enqueue() const override;

private:
  const GraphicsPipeline &pipeline;
  CommandBuffer &buffer;
};
} // namespace Vulkan