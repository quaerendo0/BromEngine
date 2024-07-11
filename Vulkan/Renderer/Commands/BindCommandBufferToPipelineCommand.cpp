#include "vulkan/vulkan.h"

#include "BindCommandBufferToPipelineCommand.h"

Vulkan::BindCommandBufferToPipelineCommand::BindCommandBufferToPipelineCommand(CommandBuffer& buffer, const GraphicsPipeline &pipeline)
    : buffer{buffer}, pipeline{pipeline}
{
}

void Vulkan::BindCommandBufferToPipelineCommand::execute() const
{
    vkCmdBindPipeline(buffer.getBuffer(), VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.getPipeline());
}
