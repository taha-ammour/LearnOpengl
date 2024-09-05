#version 330

layout (location = 0) in vec3 pos;

uniform mat4 Model;
uniform mat4 Projection;

out vec4 Vcol;

void main()
{

	gl_Position = Projection * Model * vec4(pos, 1.0);

	Vcol= vec4(clamp(pos,0.0,1.0),1.0);
}