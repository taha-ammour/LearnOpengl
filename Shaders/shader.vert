#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

uniform mat4 Model;
uniform mat4 Projection;
uniform mat4 View;

out vec4 Vcol;
out vec2 TexCoord;
out vec3 Normal;
out vec3 fragPos;


void main()
{

	gl_Position = Projection * View * Model * vec4(pos, 1.0);

	Vcol= vec4(clamp(pos,0.0,1.0),1.0);
	TexCoord = tex;

	Normal = mat3(transpose(inverse(Model))) * norm;
	fragPos = (Model * vec4(pos, 1.0)).xyz;
}