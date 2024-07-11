#pragma once

#include "vulkan/vulkan.h"
#include "../LogicalDevice.h"

#include "CommandPool.h"
#include "./Commands/ICommand.h"

namespace Vulkan {
    class CommandBuffer
    {
    public:
        CommandBuffer(const LogicalDevice &device, const CommandPool &commandPool);
        ~CommandBuffer();

		void recordCommandBuffer(const std::vector<std::unique_ptr<ICommand>> &commands);
		void resetCommandBuffer() const;

        const VkCommandBuffer &getBuffer() const noexcept { return commandBuffer; }

    private:
        VkCommandBuffer commandBuffer;

		void beginRecordingCommands() const;
		void stopRecordingCommands() const;
    };
}