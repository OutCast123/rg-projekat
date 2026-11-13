#version 330 core

layout (location = 0) in vec3 aPos;

uniform vec2 offSet;

void main() {
    gl_Position = vec4(aPos.x + offSet.x,aPos.y+offSet.y,aPos.z, 1.0);
}