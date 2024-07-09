#pragma once

#include <vulkan/vulkan_core.h>
#include "GLFW/glfw3.h"

#include "../PhysicalDevice.h"
#include "../Surface.h"
#include "../LogicalDevice.h"
#include "../SwapChainSupportDetails.h"

namespace Vulkan {
    class SwapChain {
    public:
        SwapChain(const Vulkan::LogicalDevice &logicalDevice, const Surface &surface, GLFWwindow *window,
                  const Log::ILogger &logger);

        ~SwapChain();

        // Pich suitable surface format, preferred SRGB alpha, otherwise first that is available.
        // Surface format - what color scheme (RGB/SRGB) and how many bits are used for color
        // For example, B8G8R8A8 - r, g, b, alpha channel - 8 bits for each
        // If collection is empty or not found suitable, returns undefined format.
        static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

        // Picks presentation mode, preferred "mailbox", otherwise FIFO
        // How images are pushed to view, immediate/FIFO/relaxed fifo/mailbox (images in queue replaced)
        static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

        // Gets current swapchain image "extent"
        // Extent - width + height, but they may not correspond to pixels
        static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities, GLFWwindow *window);

        [[nodiscard]] const VkExtent2D &getSwapChainExtent() const noexcept { return swapChainExtent; }

        [[nodiscard]] const VkFormat &getSwapChainImageFormat() const noexcept { return swapChainImageFormat; }

        [[nodiscard]] const std::vector<VkImageView>& getSwapChainImageViews() const noexcept { return swapChainImageViews; }

        [[nodiscard]] const VkSwapchainKHR& getSwapChain() const noexcept { return swapChain; }

    private:
        VkSwapchainKHR swapChain;
        const LogicalDevice &logicalDevice;

        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;

        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;

        uint32_t initializeSwapChain(const LogicalDevice &logicalDevice, const Surface &surface, GLFWwindow *window,
                                     const Log::ILogger &logger);

        void initializeImageViews(uint32_t imageCount, const Log::ILogger &logger);
    };
}