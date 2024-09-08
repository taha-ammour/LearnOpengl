#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

uniform mat4 Model;
uniform mat4 Projection;
uniform mat4 View;

out vec4 Vcol;
out vec2 TexCoord;

void main()
{

	gl_Position = Projection * View * Model * vec4(pos, 1.0);

	Vcol= vec4(clamp(pos,0.0,1.0),1.0);
	TexCoord = tex;
}