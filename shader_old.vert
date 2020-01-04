#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTex;

out Data
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoord;
} data;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main()
{
	data.Normal = normalize( NormalMatrix * VertexNormal );
	data.Position = vec3( ModelViewMatrix * vec4( VertexPosition, 1 ) );
	data.TexCoord = VertexTex;

	gl_Position = MVP * vec4( VertexPosition, 1);
}