#shader vertex
#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 color;

uniform mat4 modelTransformMatrix;
uniform mat4 projectionMatrix;

out vec3 u_Color;

void main()
{
	vec4 v = vec4(position, 1.0);
	vec4 newPosition = modelTransformMatrix * v;
	vec4 projectedPosition = projectionMatrix * newPosition;
	gl_Position = projectedPosition;
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