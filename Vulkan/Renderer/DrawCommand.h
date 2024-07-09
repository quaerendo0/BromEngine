#pragma once

namespace Vulkan {

	class CommandBuffer;

	class Command {
	public:
		Command(CommandBuffer& buffer);
		void execute() const;
	private:
		CommandBuffer& buffer;
	};
}