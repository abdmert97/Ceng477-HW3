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

out vec4 FragColor;


vec3 lightColor = vec3(0.3, 0.3, 0.3);
vec3 ambientReflectence = vec3(0.25f, 0.25f, 0.25f);
vec3 ambientColor = vec3(0.3f, 0.3f, 0.3f);
vec3 specularReflectence= vec3(1.0f, 1.0f, 1.0f);
vec3 specularColor = vec3 (1.0f, 1.0f, 1.0f);
vec3 diffuseReflectence= vec3(1.0f, 1.0f, 1.0);
vec3 diffuseColor =vec3(1.0f, 1.0f, 1.0f);
float SpecularExponent = 100;



void light(int lightIndex, vec3 position, vec3 norm, out vec3 ambient, out vec3 diffuse, out vec3 spec)
{

    vec3 n = normalize(norm);
    vec3 s = normalize(LightVector  - position);

    vec3 camera = CameraVector - position;
    vec3 light = LightVector   - position;
    vec3 h = normalize(camera + light);




    float cos_alpha = clamp(dot(n, h), 0, 1);
    float cos_theta = clamp(dot(n, light), 0, 1);


    // compute ambient component
    ambient = ambientColor * ambientReflectence;
    // compute diffuse component
    diffuse = diffuseColor * diffuseReflectence * cos_theta;
    // compute specular component
    spec = specularColor * specularReflectence * pow(cos_alpha, SpecularExponent);


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


    vec4 texColor = texture(Tex, data.TexCoord);
    vec4 color = vec4(ambientSum + diffuseSum, 1) * texColor + vec4(specSum, 1);
    color = vec4(clamp(color.xyz, 0.0, 1.0), 1);

    FragColor = color;
}
