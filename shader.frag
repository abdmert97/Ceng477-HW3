#version 430

in Data
{
    vec3 Position;
    vec3 Normal;
    vec2 TexCoord;
} data;

in vec3 LightVector;
in vec3 CameraVector;

uniform sampler2D Tex;
uniform float textureOffset;

out vec4 FragColor;


vec3 ambientReflectenceCoefficient = vec3(0.25f);
vec3 ambientLightColor = vec3(0.3f);
vec3 specularReflectenceCoefficient= vec3(1.0f);
vec3 specularLightColor = vec3 (1.0f);
float SpecularExponent = 100;
vec3 diffuseReflectenceCoefficient= vec3(1.0f);
vec3 diffuseLightColor =vec3(1.0f);



void light(int lightIndex, vec3 position, vec3 norm, out vec3 ambient, out vec3 diffuse, out vec3 spec)
{

    vec3 n = normalize(norm);
    vec3 s = normalize(LightVector  - position);

    vec3 camera = CameraVector;
    vec3 light = LightVector  ;
    vec3 h = normalize(camera + light);




    float cos_alpha = clamp(dot(n, h), 0, 1);
    float cos_theta = clamp(dot(n, light), 0, 1);


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

    vec2 offset = vec2(mod(textureOffset +  data.TexCoord.x,1),data.TexCoord.y);
    vec4 texColor = texture(Tex, offset);
    vec4 color = vec4(ambientSum + diffuseSum, 1.0) * texColor + vec4(specSum, 1);
    color = vec4(clamp(color.xyz, 0.0, 1.0), 1);

    FragColor = color;
}
