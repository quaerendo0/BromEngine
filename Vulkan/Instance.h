#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <memory>

#include "PhysicalDevice.h"
#include "LogicalDevice.h"

namespace Vulkan {

    class Instance {
    public:
        static const std::vector<const char *> validationLayers;

        explicit Instance(bool enableValidationLayers, const Log::ILogger &logger);

        ~Instance();

        [[nodiscard]] const VkInstance &getInstancePtr() const noexcept { return instance; }

    private:
        void createInstance(bool enableValidationLayers);

        VkInstance instance = nullptr;
        const Log::ILogger &logger;
    };

} // Vulkan