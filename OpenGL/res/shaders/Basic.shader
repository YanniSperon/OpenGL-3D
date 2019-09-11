#shader vertex
#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 color;

uniform mat4 MVP;

out vec3 u_Color;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	u_Color = color;
}

#shader fragment
#version 430

out vec4 color;
in vec3 u_Color;

void main()
{
	color = vec4(u_Color, 1.0);
}