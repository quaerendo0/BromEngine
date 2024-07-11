#pragma once

#include "ICommand.h"
#include "../Buffers/AbstractBuffer.h"

namespace Vulkan {

	class CommandBuffer;

	class DrawCommand : public ICommand {
	public:
		DrawCommand(CommandBuffer& buffer, const AbstractBuffer& stagingBuffer);
		void execute() const override;
	private:
		const AbstractBuffer& stagingBuffer;
		CommandBuffer& buffer;
	};
}