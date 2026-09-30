#version 430 core

layout (location = 0) in vec3 s_Pos;
layout (location = 1) in vec4 s_Color;
layout (location = 2) in vec4 TexAndMix;

out vec4 F_Color;

out vec2 TexCords;
out float TexIndex;
out float MixRatio;

uniform mat4 Proj;
uniform mat4 View;
uniform mat4 Model;

void main(){

gl_Position = Proj * View * Model * vec4(s_Pos, 1.0);

F_Color = s_Color;
TexCords = TexAndMix.xy;
TexIndex = TexAndMix.z;
MixRatio = TexAndMix.w;
	   }
