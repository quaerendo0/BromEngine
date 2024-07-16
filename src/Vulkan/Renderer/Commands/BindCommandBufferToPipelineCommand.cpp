#include "vulkan/vulkan.h"

#include "BindCommandBufferToPipelineCommand.h"

Vulkan::BindCommandBufferToPipelineCommand::BindCommandBufferToPipelineCommand(CommandBuffer &buffer,
                                                                               const GraphicsPipeline &pipeline)
    : pipeline{pipeline}, buffer{buffer} {}

void Vulkan::BindCommandBufferToPipelineCommand::enqueue() const {
  vkCmdBindPipeline(buffer.getBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.getPipeline());
}
