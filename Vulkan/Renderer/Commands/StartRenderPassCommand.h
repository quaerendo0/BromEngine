#pragma once

#include "ICommand.h"
#include "../Buffers/StagingBuffer.h"
#include "../RenderPass.h"
#include "../FrameBuffer.h"
#include "../CommandBuffer.h"

namespace Vulkan {

	class CommandBuffer;

	class StartRenderPassCommand : public ICommand {
	public:
		StartRenderPassCommand(
			CommandBuffer& buffer,
			uint32_t imageIndex,
			const RenderPass& renderPass,
			const FrameBuffer &frameBuffer,
			const VkExtent2D &extent);
		void execute() const override;
	private:
		uint32_t imageIndex;
		const RenderPass& renderPass;
		const FrameBuffer &frameBuffer;
		const VkExtent2D &extent;
		CommandBuffer& buffer;
	};
}