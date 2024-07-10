#include "Debug.h"

namespace Vulkan {

    VkBool32 debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                           VkDebugUtilsMessageTypeFlagsEXT messageType,
                           const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData) {
        const auto logger = static_cast<Log::ILogger *>(pUserData);
        switch (messageSeverity) {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                logger->logError("validation layer: " + std::string(pCallbackData->pMessage));
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                logger->logWarning("validation layer: " + std::string(pCallbackData->pMessage));
                break;
            default:
                logger->logInfo("validation layer: " + std::string(pCallbackData->pMessage));
        }

        return VK_FALSE;
    }

    VkResult createDebugUtilsMessengerExt(VkInstance instance,
                                          const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
                                          const VkAllocationCallbacks *pAllocator,
                                          VkDebugUtilsMessengerEXT *pDebugMessenger) {
        const auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,
                                                                                     "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void destroyDebugUtilsMessengerExt(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
                                       const VkAllocationCallbacks *pAllocator) {
        const auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance,
                                                                                      "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }

    Debug::Debug(bool enableValidationLayers, const Instance &instance, const Log::ILogger &logger)
            : referenceInstance{instance} {
        if (!enableValidationLayers) return;

        const auto createInfo = populateDebugMessengerCreateInfo(logger);
        if (createDebugUtilsMessengerExt(instance.getInstancePtr(), &createInfo, nullptr, &debugMessenger) !=
            VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }

    Debug::~Debug() {
        destroyDebugUtilsMessengerExt(referenceInstance.getInstancePtr(), debugMessenger, nullptr);
    }

    VkDebugUtilsMessengerCreateInfoEXT Debug::populateDebugMessengerCreateInfo(const Log::ILogger &logger) {
        VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = debugCallback;
        createInfo.pUserData = const_cast<Log::ILogger *>(&logger);
        return createInfo;
    }
}