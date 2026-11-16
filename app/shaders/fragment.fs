#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform vec4 ourColor;
uniform sampler2D tekstura;
uniform float useTexture; 

void main() {
    vec4 texColor = texture(tekstura, TexCoord);
    FragColor = mix(ourColor, texColor, useTexture);
}