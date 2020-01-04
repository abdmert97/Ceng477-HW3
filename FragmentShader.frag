#version 430

in Data
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoord;
} data;

out vec4 FragColor;

uniform vec3 lightPosition ;
vec3 lightColor = vec3(1,0.3,0.3);
vec3 ambientReflectence = vec3(0.25f ,0.25f , 0.25f);
vec3 ambientColor = vec3( 0.3f , 0.3f, 0.3f) ;
vec3 specularReflectence= vec3( 1.0f, 1.0f ,1.0f);
vec3 specularColor = vec3 ( 1.0f, 1.0f ,1.0f);
vec3 diffuseReflectence= vec3(  1.0f, 1.0f ,1.0);
vec3 diffuseColor =vec3(1.0f, 1.0f ,1.0f );

vec4 DiffuseReflectance =vec4 ( 1.0f, 1.0f ,1.0f,1.0f );
vec4 DiffuseColor =vec4 ( 1.0f, 1.0f ,1.0f,1.0f );
float SpecularExponent = 200;
uniform sampler2D Tex;



void light( int lightIndex, vec3 position, vec3 norm, out vec3 ambient, out vec3 diffuse, out vec3 spec )
{

	vec3 n = normalize( norm );
	vec3 s = normalize( lightPosition  - position );
	vec3 v = normalize( -position );
	vec3 r = reflect( -s, n );

	ambient = ambientColor ;
	float sDotN = max( dot( s, n ), 0.0 );
	diffuse = diffuseReflectence * sDotN;


	spec = specularReflectence* pow( max( dot(r,v) , 0.0 ), SpecularExponent );

}

void main()
{

	vec3 ambientSum = vec3(0);
	vec3 diffuseSum = vec3(0);
	vec3 specSum = vec3(0);
	vec3 ambient, diffuse, spec;

	if ( gl_FrontFacing )
	{

		light( 0, data.Position, data.Normal, ambient, diffuse, spec );
		ambientSum += ambient;
		diffuseSum += diffuse;
		specSum += spec;

	}
	else
	{

		light( 0, data.Position, -data.Normal, ambient, diffuse, spec );
		ambientSum += ambient;
		diffuseSum += diffuse;
		specSum += spec;

	}


	vec4 texColor = texture(Tex, data.TexCoord);
    vec4 color = vec4( ambientSum + diffuseSum, 1 ) * texColor + vec4( specSum, 1 );
    color = vec4(clamp(color.xyz,0.0,1.0),1);

	FragColor = color ;
}
