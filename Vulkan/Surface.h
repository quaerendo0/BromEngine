#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

class Surface {
public:
    Surface(const VkInstance &instance, GLFWwindow *window);

    [[nodiscard]] const VkSurfaceKHR &getSurface() const { return surface; }

    ~Surface();

private:
    VkSurfaceKHR surface;
    const VkInstance &referenceInstance;
};
