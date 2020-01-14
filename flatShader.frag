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



void light(int lightIndex, vec3 position, vec3 norm, out vec3 ambient, out vec3 diffuse, out vec3 spec)
{

    vec3 normalVector = normalize(norm);


    vec3 reflect = reflect(-LightVector, normalVector);

    float cos_alpha = max(dot(CameraVector, reflect), 0);
    float cos_theta = max(dot(normalVector, LightVector), 0);


    // compute ambient component
    ambient = ambientLightColor * ambientReflectenceCoefficient;
    // compute diffuse component
    diffuse = diffuseLightColor * diffuseReflectenceCoefficient * cos_theta;
    // compute specular component
    spec = specularLightColor * specularReflectenceCoefficient * pow(cos_alpha, SpecularExponent);


}

void main()
{

    vec3 ambientSum = vec3(0);
    vec3 diffuseSum = vec3(0);
    vec3 specSum = vec3(0);
    vec3 ambient, diffuse, spec;

    if (gl_FrontFacing)
    {

        light(0, data.Position, data.Normal, ambient, diffuse, spec);
        ambientSum += ambient;
        diffuseSum += diffuse;
        specSum += spec;

    }
    else
    {

        light(0, data.Position, -data.Normal, ambient, diffuse, spec);
        ambientSum += ambient;
        diffuseSum += diffuse;
        specSum += spec;

    }

    vec2 offset = vec2(mod(textureOffset +  data.TexCoord.x, 1), data.TexCoord.y);
    vec4 texColor = texture(TexColor, offset);
    vec4 color = vec4(ambientSum + diffuseSum + specSum, 1.0) * texColor;
    color = vec4(clamp(color.xyz, 0.0, 1.0), 1);

    FragColor = color;
}
