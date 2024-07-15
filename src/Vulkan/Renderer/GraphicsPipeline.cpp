#include "GraphicsPipeline.h"

#include "VertexUtility.h"

namespace Vulkan {

static std::vector<char> readFile(const std::string &filename) {
  std::ifstream file(filename, std::ios::ate | std::ios::binary);

  if (!file.is_open()) {
    throw std::runtime_error("failed to open file!");
  }

  size_t fileSize = (size_t)file.tellg();
  std::vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);

  file.close();

  return buffer;
}

/* The one catch is that the size of the bytecode is specified in bytes, but the
 * bytecode pointer is a uint32_t pointer rather than a char pointer. Therefore
 * we will need to cast the pointer with reinterpret_cast as shown below. When
 * you perform a cast like this, you also need to ensure that the data satisfies
 * the alignment requirements of uint32_t. Lucky for us, the data is stored in
 * an std::vector where the default allocator already ensures that the data
 * satisfies the worst case alignment requirements.
 */
VkShaderModule createShaderModule(const std::vector<char> &code, VkDevice device) {
  VkShaderModuleCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = code.size();
  createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());
  VkShaderModule shaderModule;
  if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
    throw std::runtime_error("failed to create shader module!");
  }

  return shaderModule;
}

std::vector<VkPipelineShaderStageCreateInfo> createShaderStages(VkDevice device) {

  auto vertShaderCode = readFile("./shaders/vert.spv");
  auto fragShaderCode = readFile("./shaders/frag.spv");

  VkShaderModule vertShaderModule = createShaderModule(vertShaderCode, device);
  VkShaderModule fragShaderModule = createShaderModule(fragShaderCode, device);

  VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
  vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
  vertShaderStageInfo.module = vertShaderModule;
  vertShaderStageInfo.pName = "main";

  VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
  fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  fragShaderStageInfo.module = fragShaderModule;
  fragShaderStageInfo.pName = "main";

  std::vector<VkPipelineShaderStageCreateInfo> shaderStages{vertShaderStageInfo, fragShaderStageInfo};

  return shaderStages;
}

struct PipelineStateConfig {
  std::vector<VkDynamicState> dynamicStates{};
  VkPipelineDynamicStateCreateInfo dynamicState{};
};

PipelineStateConfig createDynamicState() {
  PipelineStateConfig config;

  config.dynamicStates = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};

  config.dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  config.dynamicState.dynamicStateCount = static_cast<uint32_t>(config.dynamicStates.size());
  config.dynamicState.pDynamicStates = config.dynamicStates.data();

  return config;
}

struct VertexConfig {
  VkVertexInputBindingDescription bindingDescription{};
  std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
  VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
};

VertexConfig createVertexConfig() {
  VertexConfig vertexConfig{};

  vertexConfig.bindingDescription = VertexUtilities::getBindingDescription();
  vertexConfig.attributeDescriptions = VertexUtilities::getAttributeDescriptions();

  vertexConfig.vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertexConfig.vertexInputInfo.vertexBindingDescriptionCount = 1;
  vertexConfig.vertexInputInfo.vertexAttributeDescriptionCount =
      static_cast<uint32_t>(vertexConfig.attributeDescriptions.size());
  vertexConfig.vertexInputInfo.pVertexBindingDescriptions = &vertexConfig.bindingDescription;
  vertexConfig.vertexInputInfo.pVertexAttributeDescriptions = vertexConfig.attributeDescriptions.data();

  return vertexConfig;
}

VkPipelineInputAssemblyStateCreateInfo getInputAssemblyConfig() {
  VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
  inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  inputAssembly.primitiveRestartEnable = VK_FALSE;

  return inputAssembly;
}

struct ViewportConfig {
  VkViewport viewport{};
  VkRect2D scissor{};
  VkPipelineViewportStateCreateInfo viewportState{};
};

ViewportConfig getViewportConfig(const VkExtent2D extent) {
  ViewportConfig viewportConfig{};
  viewportConfig.viewport.x = 0.0f;
  viewportConfig.viewport.y = 0.0f;
  viewportConfig.viewport.width = (float)extent.width;
  viewportConfig.viewport.height = (float)extent.height;
  viewportConfig.viewport.minDepth = 0.0f;
  viewportConfig.viewport.maxDepth = 1.0f;

  viewportConfig.scissor.offset = {0, 0};
  viewportConfig.scissor.extent = extent;

  viewportConfig.viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportConfig.viewportState.viewportCount = 1;
  viewportConfig.viewportState.pViewports = &viewportConfig.viewport;
  viewportConfig.viewportState.scissorCount = 1;
  viewportConfig.viewportState.pScissors = &viewportConfig.scissor;

  return viewportConfig;
}

VkPipelineRasterizationStateCreateInfo getRasterizerConfig() {
  VkPipelineRasterizationStateCreateInfo rasterizer{};
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;
  rasterizer.depthBiasConstantFactor = 0.0f; // Optional
  rasterizer.depthBiasClamp = 0.0f;          // Optional
  rasterizer.depthBiasSlopeFactor = 0.0f;    // Optional

  return rasterizer;
}

VkPipelineMultisampleStateCreateInfo getMultisamplingConfig() {
  VkPipelineMultisampleStateCreateInfo multisampling{};
  multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  multisampling.minSampleShading = 1.0f;          // Optional
  multisampling.pSampleMask = nullptr;            // Optional
  multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
  multisampling.alphaToOneEnable = VK_FALSE;      // Optional

  return multisampling;
}

struct ColorBlendConfig {
  VkPipelineColorBlendAttachmentState colorBlendAttachment{};
  VkPipelineColorBlendStateCreateInfo colorBlending{};
};

ColorBlendConfig getColorBlendingConfig() {
  ColorBlendConfig config{};

  config.colorBlendAttachment.colorWriteMask =
      VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  config.colorBlendAttachment.blendEnable = VK_FALSE;
  config.colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional
  config.colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  config.colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;             // Optional
  config.colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;  // Optional
  config.colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  config.colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;             // Optional

  config.colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  config.colorBlending.logicOpEnable = VK_FALSE;
  config.colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
  config.colorBlending.attachmentCount = 1;
  config.colorBlending.pAttachments = &config.colorBlendAttachment;
  config.colorBlending.blendConstants[0] = 0.0f; // Optional
  config.colorBlending.blendConstants[1] = 0.0f; // Optional
  config.colorBlending.blendConstants[2] = 0.0f; // Optional
  config.colorBlending.blendConstants[3] = 0.0f; // Optional

  return config;
}

VkPipelineLayoutCreateInfo getPipelineLayoutInfoConfig(const DescriptorSetLayout &descriptorSetLayout) {
  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 1;                             // Optional
  pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout.getLayout(); // Optional
  pipelineLayoutInfo.pushConstantRangeCount = 0;                     // Optional
  pipelineLayoutInfo.pPushConstantRanges = nullptr;                  // Optional

  return pipelineLayoutInfo;
}

GraphicsPipeline::GraphicsPipeline(const LogicalDevice &logicalDevice, const VkExtent2D swapChainExtent,
                                   const DescriptorSetLayout &descriptorSetLayout, const RenderPass &renderPass)
    : logicalDevice{logicalDevice} {
  const auto device = logicalDevice.getDevicePtr();

  const auto shaderStages = createShaderStages(device);
  const auto dynamicState = createDynamicState();
  const auto vertexInputInfo = createVertexConfig().vertexInputInfo;
  const auto inputAssembly = getInputAssemblyConfig();
  const auto viewportState = getViewportConfig(swapChainExtent);
  const auto rasterizer = getRasterizerConfig();
  const auto multisampling = getMultisamplingConfig();
  const auto colorBlending = getColorBlendingConfig();
  const auto pipelineLayoutInfo = getPipelineLayoutInfoConfig(descriptorSetLayout);

  if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
    throw std::runtime_error("failed to create pipeline layout!");
  }

  VkGraphicsPipelineCreateInfo pipelineInfo{};
  pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipelineInfo.stageCount = shaderStages.size();
  pipelineInfo.pStages = shaderStages.data();
  pipelineInfo.pVertexInputState = &vertexInputInfo;
  pipelineInfo.pInputAssemblyState = &inputAssembly;
  pipelineInfo.pViewportState = &viewportState.viewportState;
  pipelineInfo.pRasterizationState = &rasterizer;
  pipelineInfo.pMultisampleState = &multisampling;
  pipelineInfo.pDepthStencilState = nullptr; // Optional
  pipelineInfo.pColorBlendState = &colorBlending.colorBlending;
  pipelineInfo.pDynamicState = &dynamicState.dynamicState;
  pipelineInfo.layout = pipelineLayout;
  pipelineInfo.renderPass = renderPass.getRenderPass();
  pipelineInfo.subpass = 0;
  pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
  pipelineInfo.basePipelineIndex = -1;              // Optional

  if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
    throw std::runtime_error("failed to create graphics pipeline!");
  }

  // тута типа всё выпиливаем нахуй?
  vkDestroyShaderModule(device, shaderStages[0].module, nullptr);
  vkDestroyShaderModule(device, shaderStages[1].module, nullptr);
}

GraphicsPipeline::~GraphicsPipeline() {
  vkDestroyPipeline(logicalDevice.getDevicePtr(), graphicsPipeline, nullptr);
  vkDestroyPipelineLayout(logicalDevice.getDevicePtr(), pipelineLayout, nullptr);
}
} // namespace Vulkan