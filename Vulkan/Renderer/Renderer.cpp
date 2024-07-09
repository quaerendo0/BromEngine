#include "Renderer.h"

namespace Vulkan {

    Renderer::Renderer(const LogicalDevice &device, const Surface &surface, GLFWwindow *window, const Log::ILogger &logger)
        : device{device}
    {
        swapChain = new SwapChain{device, surface, window, logger};
        renderPass = new RenderPass{*swapChain, device};
        graphicsPipeline = new GraphicsPipeline{device, *swapChain, *renderPass};
        frameBuffer = new FrameBuffer{ *swapChain, *renderPass, device };
        frameManager = new FrameManager{ device, *renderPass, *frameBuffer, *swapChain, *graphicsPipeline };
    }

    Renderer::~Renderer()
    {
        delete frameManager;
        delete frameBuffer; // swapchain clean framebuffer?
        delete graphicsPipeline;
        delete renderPass;
        delete swapChain;
    }

    void Renderer::drawFrame()
    {
        frameManager->drawFrame();
    }
}