#pragma once

#include "vulkan/vulkan.h"

#include "ICommand.h"
#include "../CommandBuffer.h"
#include "../Buffers/DeviceIndexBuffer.h"
#include "../Buffers/DeviceVertexBuffer.h"

namespace Vulkan {
	template <class T1, class T2>
	class DrawIndexedCommand : public ICommand {
	public:
		DrawIndexedCommand(CommandBuffer& buffer, const DeviceVertexBuffer<T1>& vertexBuffer, const DeviceIndexBuffer<T2>& indexBuffer)
		: buffer{buffer}, vertexBuffer{vertexBuffer}, indexBuffer{indexBuffer} {};

		void execute() const override {
            VkBuffer vertexBuffers[] = {vertexBuffer.getBufferHandle()};
            VkDeviceSize offsets[] = {0};
			vkCmdBindVertexBuffers(buffer.getBuffer(), 0, 1, vertexBuffers, offsets);
			vkCmdBindIndexBuffer(buffer.getBuffer(), indexBuffer.getBufferHandle(), 0, VK_INDEX_TYPE_UINT16);
			vkCmdDrawIndexed(buffer.getBuffer(), static_cast<uint32_t>(indexBuffer.elementCount()), 1, 0, 0, 0);
		};
	private:
		const DeviceVertexBuffer<T1>& vertexBuffer;
		const DeviceIndexBuffer<T2>& indexBuffer;
		CommandBuffer& buffer;
	};
}