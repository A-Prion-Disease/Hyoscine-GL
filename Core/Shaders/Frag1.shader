#version 430 core

out vec4 FragColor;

in vec4 F_Color;
in vec2 TexCords;

in float TexIndex;
in float MixRatio;

uniform sampler2D uniTexture[2];

void main(){

int index = clamp(int(TexIndex + 0.5), 0, 1);

FragColor = mix(texture(uniTexture[index], TexCords), F_Color, MixRatio);

	   }
