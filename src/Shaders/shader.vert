#version 450

layout (binding = 0) uniform UboView
{
	mat4 projection;
	mat4 view;
} uboView;

layout (binding = 1) uniform UboInstance
{
	mat4 model;
} uboInstance;

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

void main() {
    gl_Position = uboView.projection * uboView.view * (uboInstance.model * vec4(inPosition, 0.0, 1.0));
    fragColor = inColor;
}