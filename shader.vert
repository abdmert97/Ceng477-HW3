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

uniform sampler2D TexColor;
uniform sampler2D TexGrey;
uniform float textureOffset;

uniform float heightFactor;
uniform float imageWidth;
uniform float imageHeight;

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
    vec4 texColor = texture(TexGrey, vec2(mod(textureOffset+ VertexTex.x, 1.0), VertexTex.y));
    vec3 newPosition = VertexPosition;
    newPosition.y = heightFactor * texColor.x;


    vec3 adjacentVertex1 = newPosition + vec3(-1, 0, 0);
    vec3 adjacentVertex2 = newPosition + vec3(-1, 0, 1);
    vec3 adjacentVertex3 = newPosition + vec3(0, 0, 1);
    vec3 adjacentVertex4 = newPosition + vec3(1, 0, 0);
    vec3 adjacentVertex5 = newPosition + vec3(1, 0, -1);
    vec3 adjacentVertex6 = newPosition + vec3(0, 0, -1);

    vec4 texColor1 = texture(TexGrey, vec2(mod(textureOffset+1-(adjacentVertex1.x)/imageWidth, 1.0), 1- (adjacentVertex1.z)/imageHeight));
    vec4 texColor2 = texture(TexGrey, vec2(mod(textureOffset+1-(adjacentVertex2.x)/imageWidth, 1.0), 1- (adjacentVertex2.z)/imageHeight));
    vec4 texColor3 = texture(TexGrey, vec2(mod(textureOffset+1-(adjacentVertex3.x)/imageWidth, 1.0), 1- (adjacentVertex3.z)/imageHeight));
    vec4 texColor4 = texture(TexGrey, vec2(mod(textureOffset+1-(adjacentVertex4.x)/imageWidth, 1.0), 1- (adjacentVertex4.z)/imageHeight));
    vec4 texColor5 = texture(TexGrey, vec2(mod(textureOffset+1-(adjacentVertex5.x)/imageWidth, 1.0), 1- (adjacentVertex5.z)/imageHeight));
    vec4 texColor6 = texture(TexGrey, vec2(mod(textureOffset+1-(adjacentVertex6.x)/imageWidth, 1.0), 1- (adjacentVertex6.z)/imageHeight));

    adjacentVertex1.y = heightFactor * texColor1.x;
    adjacentVertex2.y = heightFactor * texColor2.x;
    adjacentVertex3.y = heightFactor * texColor3.x;
    adjacentVertex4.y = heightFactor * texColor4.x;
    adjacentVertex5.y = heightFactor * texColor5.x;
    adjacentVertex6.y = heightFactor * texColor6.x;

    vec3 normal1 = cross((adjacentVertex1 - newPosition), (newPosition - adjacentVertex2));
    vec3 normal2 = cross((adjacentVertex2 - newPosition), (newPosition - adjacentVertex3));
    vec3 normal3 = cross((adjacentVertex3 - newPosition), (newPosition - adjacentVertex4));
    vec3 normal4 = cross((adjacentVertex4 - newPosition), (newPosition - adjacentVertex5));
    vec3 normal5 = cross((adjacentVertex5 - newPosition), (newPosition - adjacentVertex6));
    vec3 normal6 = cross((adjacentVertex6 - newPosition), (newPosition - adjacentVertex1));

    vec3 averageNormal = normalize(normal1 + normal2 + normal3 + normal4 + normal5 + normal6);

    data.Normal = vec3(normalize(vec3(NormalMatrix * vec4(averageNormal, 0))));
    data.Position = vec3(ViewMatrix * vec4(newPosition, 1));
    data.TexCoord = vec2(VertexTex.x, VertexTex.y);

    CameraVector = normalize(cameraPosition - data.Position);
    LightVector = normalize(lightPosition - data.Position);


    gl_Position = MVP* vec4(newPosition, 1);
}