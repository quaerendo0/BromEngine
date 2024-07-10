#pragma once

#include "Vulkan/Window.h"
#include "Logger/Logger.h"

namespace BromEngine {

    class App {
    public:
        void run();

    private:
        Log::Logger logger{};
        Vulkan::Window window{800, 600, logger};
    };

}