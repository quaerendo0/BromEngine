#include "VulkanApi.h"

Vulkan::VulkanApi::VulkanApi(GLFWwindow *window, const Log::ILogger &logger, const BromEngine::Scene &scene)
    : logger{logger}, scene{scene} {
  instance = std::make_unique<Instance>(true, logger);
  debug = std::make_unique<Debug>(enableValidationLayers, *instance, logger);
  surface = std::make_unique<Surface>(instance->getInstancePtr(), window);
  physicalDevice = std::make_unique<PhysicalDevice>(instance->getInstancePtr(), surface->getSurface(), logger);
  logicalDevice = std::make_unique<LogicalDevice>(*physicalDevice, Instance::validationLayers, enableValidationLayers);
  renderer = std::make_unique<Renderer>(*logicalDevice, *surface, window, logger, scene);
}

void Vulkan::VulkanApi::drawFrame() { renderer->drawFrame(); }

void Vulkan::VulkanApi::handleResize() { renderer->handleOuterFrameResize(); }

void Vulkan::VulkanApi::waitIdle() { vkDeviceWaitIdle(logicalDevice->getDevicePtr()); }
