#pragma once

#include "ICommand.h"
#include "../Buffers/StagingBuffer.h"
#include "../GraphicsPipeline.h"
#include "../CommandBuffer.h"

namespace Vulkan {

	class CommandBuffer;

	class BindCommandBufferToPipelineCommand : public ICommand {
	public:
		BindCommandBufferToPipelineCommand(CommandBuffer& buffer, const GraphicsPipeline &pipeline);
		void execute() const override;
	private:
		const GraphicsPipeline &pipeline;
		CommandBuffer& buffer;
	};
}