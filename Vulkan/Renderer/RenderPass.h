#pragma once

#include "SwapChain.h"

namespace Vulkan {
    class RenderPass {
    public:
        RenderPass(const SwapChain &swapChain, const LogicalDevice &logicalDevice);

        ~RenderPass();

        [[nodiscard]] const VkRenderPass &getRenderPass() const noexcept { return renderPass; };

    private:
        VkRenderPass renderPass;
        const LogicalDevice &logicalDevice;
    };
}
