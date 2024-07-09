#include "../LogicalDevice.h"

#include "SwapChain.h"
#include "RenderPass.h"
#include "GraphicsPipeline.h"
#include "FrameBuffer.h"
#include "CommandManager.h"
#include "FrameManager.h"

namespace Vulkan {
    class Renderer
    {
    public:
        Renderer(const LogicalDevice &device, const Surface &surface, GLFWwindow *window, const Log::ILogger &logger);
        ~Renderer();

		void drawFrame();
    private:
        const LogicalDevice &device;

        SwapChain *swapChain = nullptr;
        RenderPass *renderPass = nullptr;
        GraphicsPipeline *graphicsPipeline = nullptr;
        FrameBuffer* frameBuffer = nullptr;
        CommandManager* commandManager = nullptr;
        FrameManager* frameManager = nullptr;
    };

}