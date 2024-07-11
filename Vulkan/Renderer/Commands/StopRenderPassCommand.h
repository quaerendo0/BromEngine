#pragma once

#include "ICommand.h"
#include "../Buffers/StagingBuffer.h"
#include "../CommandBuffer.h"

namespace Vulkan {

	class CommandBuffer;

	class StopRenderPassCommand : public ICommand {
	public:
		StopRenderPassCommand(CommandBuffer& buffer);
		void execute() const override;
	private:
		CommandBuffer& buffer;
	};
}