#version 450

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 uMVP;
uniform vec4 uRect;

out vec4 vRect;

void main() {
    gl_Position = uMVP * vec4(aPos, 1.0f);
    vRect = vec4(aPos, 1.0f);
}