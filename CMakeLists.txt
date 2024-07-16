cmake_minimum_required(VERSION 3.28)
project(BromEngine)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}

./src/App.cpp
./src/App.h
./src/main.cpp
./src/Game/Camera.h
./src/Game/Model3d.cpp
./src/Game/Model3d.h
./src/Game/Scene.cpp
./src/Game/Scene.h
./src/Game/Geometry/Vertex.h
./src/Logger/ILogger.h
./src/Logger/Logger.cpp
./src/Logger/Logger.h
./src/Shaders/compile.ps1
./src/Shaders/frag.spv
./src/Shaders/shader.frag
./src/Shaders/shader.vert
./src/Vulkan/Debug.cpp
./src/Vulkan/Debug.h
./src/Vulkan/Instance.cpp
./src/Vulkan/Instance.h
./src/Vulkan/LogicalDevice.cpp
./src/Vulkan/LogicalDevice.h
./src/Vulkan/PhysicalDevice.cpp
./src/Vulkan/PhysicalDevice.h
./src/Vulkan/PhysicalDeviceQueueFamilyIndexInfo.h
./src/Vulkan/Queue.cpp
./src/Vulkan/Queue.h
./src/Vulkan/Surface.cpp
./src/Vulkan/Surface.h
./src/Vulkan/SwapChainSupportDetails.h
./src/Vulkan/Window.cpp
./src/Vulkan/Window.h
./src/Vulkan/Renderer/Frame.cpp
./src/Vulkan/Renderer/Frame.h
./src/Vulkan/Renderer/FrameBuffer.cpp
./src/Vulkan/Renderer/FrameBuffer.h
./src/Vulkan/Renderer/GraphicsPipeline.cpp
./src/Vulkan/Renderer/GraphicsPipeline.h
./src/Vulkan/Renderer/Renderer.cpp
./src/Vulkan/Renderer/Renderer.h
./src/Vulkan/Renderer/RenderPass.cpp
./src/Vulkan/Renderer/RenderPass.h
./src/Vulkan/Renderer/SwapChain.cpp
./src/Vulkan/Renderer/SwapChain.h
./src/Vulkan/Renderer/UniformBufferObject.h
./src/Vulkan/Renderer/VertexUtility.h
./src/Vulkan/Renderer/Vulkan3dModelWrapper.cpp
./src/Vulkan/Renderer/Vulkan3dModelWrapper.h
./src/Vulkan/Renderer/Buffers/BasicBuffer.cpp
./src/Vulkan/Renderer/Buffers/BasicBuffer.h
./src/Vulkan/Renderer/Buffers/IBuffer.h
./src/Vulkan/Renderer/Buffers/IndexBuffer.cpp
./src/Vulkan/Renderer/Buffers/IndexBuffer.h
./src/Vulkan/Renderer/Buffers/UniformBuffer.cpp
./src/Vulkan/Renderer/Buffers/UniformBuffer.h
./src/Vulkan/Renderer/Buffers/VertexBuffer.cpp
./src/Vulkan/Renderer/Buffers/VertexBuffer.h
./src/Vulkan/Renderer/Commands/BindCommandBufferToPipelineCommand.cpp
./src/Vulkan/Renderer/Commands/BindCommandBufferToPipelineCommand.h
./src/Vulkan/Renderer/Commands/BindDescriptorSetCommand.cpp
./src/Vulkan/Renderer/Commands/BindDescriptorSetCommand.h
./src/Vulkan/Renderer/Commands/CommandBuffer.cpp
./src/Vulkan/Renderer/Commands/CommandBuffer.h
./src/Vulkan/Renderer/Commands/CommandPool.cpp
./src/Vulkan/Renderer/Commands/CommandPool.h
./src/Vulkan/Renderer/Commands/CopyBufferCommand.cpp
./src/Vulkan/Renderer/Commands/CopyBufferCommand.h
./src/Vulkan/Renderer/Commands/DrawCommand.h
./src/Vulkan/Renderer/Commands/DrawIndexedCommand.h
./src/Vulkan/Renderer/Commands/ICommand.h
./src/Vulkan/Renderer/Commands/SetupViewportScissorCommand.cpp
./src/Vulkan/Renderer/Commands/SetupViewportScissorCommand.h
./src/Vulkan/Renderer/Commands/StartRenderPassCommand.cpp
./src/Vulkan/Renderer/Commands/StartRenderPassCommand.h
./src/Vulkan/Renderer/Commands/StopRenderPassCommand.cpp
./src/Vulkan/Renderer/Commands/StopRenderPassCommand.h
./src/Vulkan/Renderer/Descriptors/DescriptorManager.cpp
./src/Vulkan/Renderer/Descriptors/DescriptorManager.h
./src/Vulkan/Renderer/Descriptors/DescriptorsData.h
./src/Vulkan/Renderer/Descriptors/DescriptorSetLayout.cpp
./src/Vulkan/Renderer/Descriptors/DescriptorSetLayout.h


)

find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)