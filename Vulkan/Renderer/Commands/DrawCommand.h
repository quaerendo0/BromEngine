#pragma once

#include "ICommand.h"
#include "../Buffers/StagingBuffer.h"

namespace Vulkan {

	class CommandBuffer;

	class DrawCommand : public ICommand {
	public:
		DrawCommand(CommandBuffer& buffer, const StagingBuffer& stagingBuffer);
		void execute() const override;
	private:
		const StagingBuffer& stagingBuffer;
		CommandBuffer& buffer;
	};
}