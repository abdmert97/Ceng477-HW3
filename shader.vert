#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTex;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;

uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 NormalMatrix;
uniform mat4 MVP;

out Data
{
    vec3 Position;
    vec3 Normal;
    vec2 TexCoord;
} data;


out vec3 LightVector;// Vector from Vertex to Light;
out vec3 CameraVector;// Vector from Vertex to Camera;

void main()
{

    data.Normal = vec3(normalize(vec3(NormalMatrix * vec4(VertexNormal, 0))));
    data.Position = vec3(ViewMatrix * vec4(VertexPosition, 1));
    data.TexCoord = vec2(VertexTex.x, VertexTex.y);

    CameraVector = normalize(vec3(ViewMatrix * vec4(cameraPosition - data.Position, 0)));
    LightVector = normalize(vec3(ViewMatrix * vec4(lightPosition - data.Position, 0)));

    gl_Position = ProjectionMatrix * vec4(VertexPosition, 1);
}