#include "Surface.h"

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <stdexcept>

Surface::~Surface() {
    vkDestroySurfaceKHR(referenceInstance, surface, nullptr);
}

Surface::Surface(const VkInstance &instance, GLFWwindow *window) : referenceInstance{instance} {
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}
