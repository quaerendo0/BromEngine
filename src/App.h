#pragma once

#include "Game/Scene.h"
#include "Logger/Logger.h"
#include "Vulkan/VulkanApi.h"
#include "Window.h"

namespace BromEngine {

class App {
public:
  void run();

private:
  Log::Logger logger{};
  Window window{800, 600, logger};
  BromEngine::Scene scene{};
  Vulkan::VulkanApi rendererApi{window.getWindowPtr(), logger, scene};
};

} // namespace BromEngine