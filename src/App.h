#pragma once

#include "Logger/Logger.h"
#include "Vulkan/Window.h"

namespace BromEngine {

class App {
public:
  void run();

private:
  Log::Logger logger{};
  Vulkan::Window window{800, 600, logger};
};

} // namespace BromEngine