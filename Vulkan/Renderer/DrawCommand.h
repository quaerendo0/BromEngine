#pragma once

namespace Vulkan {

	class CommandBuffer;

	class DrawCommand {
	public:
		DrawCommand(CommandBuffer& buffer, uint32_t vertexCount);
		void execute() const;
	private:
		uint32_t vertexCount;
		CommandBuffer& buffer;
	};
}