#pragma once

#include "../Buffers/StagingBuffer.h"
#include "../CommandBuffer.h"
#include "../GraphicsPipeline.h"
#include "ICommand.h"

namespace Vulkan {

class CommandBuffer;

class BindCommandBufferToPipelineCommand : public ICommand {
public:
  BindCommandBufferToPipelineCommand(CommandBuffer &buffer,
                                     const GraphicsPipeline &pipeline);
  void execute() const override;

private:
  const GraphicsPipeline &pipeline;
  CommandBuffer &buffer;
};
} // namespace Vulkan