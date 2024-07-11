#pragma once

#include "vulkan/vulkan.h"

#include "ICommand.h"
#include "../CommandBuffer.h"
#include "../Buffers/DeviceIndexBuffer.h"
#include "../Buffers/DeviceVertexBuffer.h"

namespace Vulkan {
	template <class T>
	class DrawIndexedCommand : public ICommand {
	public:
		DrawIndexedCommand(CommandBuffer& buffer, const DeviceVertexBuffer<T>& vertexBuffer, const DeviceIndexBuffer<T>& indexBuffer)
		: buffer{buffer}, stagingBuffer{stagingBuffer}, indexBuffer{indexBuffer} {};

		void execute() const override {
            VkBuffer vertexBuffers[] = {vertexBuffer.getBufferHandle()};
            VkDeviceSize offsets[] = {0};
			vkCmdBindVertexBuffers(buffer.getBuffer(), 0, 1, vertexBuffers, offsets);
			vkCmdBindIndexBuffer(buffer.getBuffer(), indexBuffer.getBufferHandle(), 0, VK_INDEX_TYPE_UINT16);
			vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indexBuffer.elementCount()), 1, 0, 0, 0);
		};
	private:
		const DeviceVertexBuffer<T>& vertexBuffer;
		const DeviceIndexBuffer<T>& indexBuffer;
		CommandBuffer& buffer;
	};
}