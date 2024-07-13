cmake_minimum_required(VERSION 3.28)
project(BromEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp
        src/App.cpp
        src/App.h

        src/Logger/ILogger.h
        src/Logger/ILogger.h
        src/Logger/Logger.cpp
        src/Logger/Logger.h
        src/Logger/Logger.h

        src/Vulkan/Debug.cpp
        src/Vulkan/Debug.h
        src/Vulkan/Instance.cpp
        src/Vulkan/Instance.h
        src/Vulkan/LogicalDevice.cpp
        src/Vulkan/LogicalDevice.h
        src/Vulkan/PhysicalDevice.cpp
        src/Vulkan/PhysicalDevice.h
        src/Vulkan/PhysicalDeviceQueueFamilyIndexInfo.h
        src/Vulkan/Queue.cpp
        src/Vulkan/Queue.h
        src/Vulkan/Surface.cpp
        src/Vulkan/Surface.h
        src/Vulkan/SwapChainSupportDetails.h
        src/Vulkan/Window.cpp
        src/Vulkan/Window.h

        src/Vulkan/Renderer/Commands/ICommand.h
        src/Vulkan/Renderer/Commands/DrawCommand.h
        src/Vulkan/Renderer/Commands/DrawCommand.cpp
        src/Vulkan/Renderer/Commands/DrawIndexedCommand.h
        src/Vulkan/Renderer/Commands/DrawIndexedCommand.cpp
        src/Vulkan/Renderer/Commands/StartRenderPassCommand.h
        src/Vulkan/Renderer/Commands/StartRenderPassCommand.cpp
        src/Vulkan/Renderer/Commands/BindCommandBufferToPipelineCommand.h
        src/Vulkan/Renderer/Commands/BindCommandBufferToPipelineCommand.cpp
        src/Vulkan/Renderer/Commands/SetupViewportScissorCommand.h
        src/Vulkan/Renderer/Commands/SetupViewportScissorCommand.cpp
        src/Vulkan/Renderer/Commands/StopRenderPassCommand.h
        src/Vulkan/Renderer/Commands/StopRenderPassCommand.cpp
        src/Vulkan/Renderer/Commands/CopyBufferCommand.h
        src/Vulkan/Renderer/Commands/CopyBufferCommand.cpp

        src/Vulkan/Renderer/Buffers/AbstractBuffer.h
        src/Vulkan/Renderer/Buffers/AbstractBuffer.cpp
        src/Vulkan/Renderer/Buffers/StagingBuffer.h
        src/Vulkan/Renderer/Buffers/StagingBuffer.cpp
        src/Vulkan/Renderer/Buffers/DeviceInternalBuffer.h
        src/Vulkan/Renderer/Buffers/DeviceInternalBuffer.cpp

        src/Vulkan/Renderer/CommandBuffer.cpp
        src/Vulkan/Renderer/CommandBuffer.h
        src/Vulkan/Renderer/CommandPool.cpp
        src/Vulkan/Renderer/CommandPool.h
        src/Vulkan/Renderer/FrameBuffer.cpp
        src/Vulkan/Renderer/FrameBuffer.h
        src/Vulkan/Renderer/GraphicsPipeline.cpp
        src/Vulkan/Renderer/GraphicsPipeline.h
        src/Vulkan/Renderer/Renderer.cpp
        src/Vulkan/Renderer/Renderer.h
        src/Vulkan/Renderer/RenderPass.cpp
        src/Vulkan/Renderer/RenderPass.h
        src/Vulkan/Renderer/SwapChain.cpp
        src/Vulkan/Renderer/SwapChain.h

        src/Vulkan/Geometry/Vertex.h
)

find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)