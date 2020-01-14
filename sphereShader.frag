#version 430

in Data
{
    vec3 Position;
    vec3 Normal;
    vec2 TexCoord;
} data;
in vec3 LightVector;
in vec3 CameraVector;

uniform sampler2D TexColor;
uniform sampler2D TexGrey;
uniform float textureOffset;

out vec4 FragColor;

float ambientReflectenceCoefficient = 0.25f;
vec3 ambientLightColor = vec3(0.3f);
float specularReflectenceCoefficient= 1.0f;
vec3 specularLightColor = vec3 (1.0f);
float SpecularExponent = 100;
float diffuseReflectenceCoefficient= 1.0f;
vec3 diffuseLightColor =vec3(1.0f);


void main()
{
    vec3 normalVector = gl_FrontFacing ? normalize(data.Normal) : normalize(-data.Normal);
    vec3 reflect = reflect(-LightVector, normalVector);

    vec3 ambient = ambientLightColor * ambientReflectenceCoefficient;
    vec3 diffuse = diffuseLightColor * diffuseReflectenceCoefficient * max(dot(normalVector, LightVector), 0);
    vec3 spec = specularLightColor * specularReflectenceCoefficient * pow(max(dot(CameraVector, reflect), 0), SpecularExponent);

    vec2 offset = vec2(mod(textureOffset +  data.TexCoord.x, 1), data.TexCoord.y);
    vec4 texColor = texture(TexColor, offset);
    vec4 color = vec4(ambient + diffuse + spec, 1.0) * texColor;

    FragColor = vec4(clamp(color.xyz, 0.0, 1.0), 1);
}
