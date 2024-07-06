#pragma once

#include <vulkan/vulkan.h>

namespace Vulkan {
    class Queue {
    public:
        Queue(const VkDevice &device, uint32_t queueFamily);

        [[nodiscard]] const VkQueue& getQueue() const { return queue; }

    private:

        VkQueue queue = nullptr;
    };
}