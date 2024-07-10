#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <vulkan/vulkan_core.h>
#include "../LogicalDevice.h"
#include "SwapChain.h"
#include "RenderPass.h"

namespace Vulkan {

    class GraphicsPipeline {
    public:
        GraphicsPipeline(const LogicalDevice &logicalDevice, const VkExtent2D swapChainExtent, const RenderPass &renderPass);
        ~GraphicsPipeline();

        const VkPipeline& getPipeline() const noexcept { return graphicsPipeline;  }

    private:
        VkPipelineLayout pipelineLayout = nullptr;
        VkPipeline graphicsPipeline = nullptr;
        const LogicalDevice &logicalDevice;
    };

}