cmake_minimum_required(VERSION 3.28)
project(BromEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp
        App.cpp
        App.h

        Logger/ILogger.h
        Logger/ILogger.h
        Logger/Logger.cpp
        Logger/Logger.h
        Logger/Logger.h

        Vulkan/Debug.cpp
        Vulkan/Debug.h
        Vulkan/Instance.cpp
        Vulkan/Instance.h
        Vulkan/LogicalDevice.cpp
        Vulkan/LogicalDevice.h
        Vulkan/PhysicalDevice.cpp
        Vulkan/PhysicalDevice.h
        Vulkan/PhysicalDeviceQueueFamilyIndexInfo.h
        Vulkan/Queue.cpp
        Vulkan/Queue.h
        Vulkan/Surface.cpp
        Vulkan/Surface.h
        Vulkan/SwapChainSupportDetails.h
        Vulkan/Window.cpp
        Vulkan/Window.h

        Vulkan/Renderer/CommandBuffer.cpp
        Vulkan/Renderer/CommandBuffer.h
        Vulkan/Renderer/CommandBufferInitInfo.h
        Vulkan/Renderer/CommandPool.cpp
        Vulkan/Renderer/CommandPool.h
        Vulkan/Renderer/FrameBuffer.cpp
        Vulkan/Renderer/FrameBuffer.h
        Vulkan/Renderer/GraphicsPipeline.cpp
        Vulkan/Renderer/GraphicsPipeline.h
        Vulkan/Renderer/Renderer.cpp
        Vulkan/Renderer/Renderer.h
        Vulkan/Renderer/RenderPass.cpp
        Vulkan/Renderer/RenderPass.h
        Vulkan/Renderer/SwapChain.cpp
        Vulkan/Renderer/SwapChain.h
        Vulkan/Renderer/DrawCommand.h
        Vulkan/Renderer/DrawCommand.cpp
        Vulkan/Renderer/VertexBuffer.h
        Vulkan/Renderer/VertexBuffer.cpp

        Vulkan/Geometry/Vertex.h
)

find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)