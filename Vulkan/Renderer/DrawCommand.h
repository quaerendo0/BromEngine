#pragma once

namespace Vulkan {

	class CommandBuffer;

	class DrawCommand {
	public:
		DrawCommand(CommandBuffer& buffer);
		void execute() const;
	private:
		CommandBuffer& buffer;
	};
}