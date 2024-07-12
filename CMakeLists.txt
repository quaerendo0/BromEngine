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

        Vulkan/Renderer/Commands/ICommand.h
        Vulkan/Renderer/Commands/DrawCommand.h
        Vulkan/Renderer/Commands/DrawCommand.cpp
        Vulkan/Renderer/Commands/DrawIndexedCommand.h
        Vulkan/Renderer/Commands/DrawIndexedCommand.cpp
        Vulkan/Renderer/Commands/StartRenderPassCommand.h
        Vulkan/Renderer/Commands/StartRenderPassCommand.cpp
        Vulkan/Renderer/Commands/BindCommandBufferToPipelineCommand.h
        Vulkan/Renderer/Commands/BindCommandBufferToPipelineCommand.cpp
        Vulkan/Renderer/Commands/SetupViewportScissorCommand.h
        Vulkan/Renderer/Commands/SetupViewportScissorCommand.cpp
        Vulkan/Renderer/Commands/StopRenderPassCommand.h
        Vulkan/Renderer/Commands/StopRenderPassCommand.cpp
        Vulkan/Renderer/Commands/CopyBufferCommand.h
        Vulkan/Renderer/Commands/CopyBufferCommand.cpp

        Vulkan/Renderer/Buffers/AbstractBuffer.h
        Vulkan/Renderer/Buffers/AbstractBuffer.cpp
        Vulkan/Renderer/Buffers/StagingBuffer.h
        Vulkan/Renderer/Buffers/StagingBuffer.cpp
        Vulkan/Renderer/Buffers/DeviceInternalBuffer.h
        Vulkan/Renderer/Buffers/DeviceInternalBuffer.cpp

        Vulkan/Renderer/CommandBuffer.cpp
        Vulkan/Renderer/CommandBuffer.h
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

        Vulkan/Geometry/Vertex.h
)

find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)