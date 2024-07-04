cmake_minimum_required(VERSION 3.28)
project(BromEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp
        App.cpp
        App.h
        App.h
        Vulkan/Window.cpp
        Vulkan/Window.h
        Vulkan/PhysicalDevice.cpp
        Vulkan/PhysicalDevice.h
        Vulkan/Instance.cpp
        Vulkan/Instance.h
        Vulkan/Debug.cpp
        Vulkan/Debug.h
        Vulkan/LogicalDevice.cpp
        Vulkan/LogicalDevice.h
        Vulkan/LogicalDevice.h
        Vulkan/LogicalDevice.cpp
        Vulkan/Surface.cpp
        Vulkan/Surface.h
        Logger/ILogger.h
        Logger/ILogger.h
        Logger/Logger.cpp
        Logger/Logger.h
        Logger/Logger.h
        Vulkan/Queue.cpp
        Vulkan/Queue.h
        Vulkan/PhysicalDeviceQueueFamilyIndexInfo.h
        Vulkan/SwapChainSupportDetails.h
        Vulkan/SwapChain.cpp
        Vulkan/SwapChain.h
        Vulkan/GraphicsPipeline.cpp
        Vulkan/GraphicsPipeline.h
        Vulkan/RenderPass.cpp
        Vulkan/RenderPass.h
        Vulkan/FrameBuffer.cpp
        Vulkan/FrameBuffer.h)

find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)