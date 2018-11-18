#version 410 core
in vec2 vtexCoord;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedo;
uniform sampler2D ssao;

out vec4 color;
void main()
{
    vec3 Position = vec3(10.0);
    vec3 Color = vec3(0.3,0.5,1.0);
    float Linear = 1.0;
    float Quadratic = 1.0;
    float Radius =1.0;
    // retrieve data from gbuffer
    vec3 FragPos = texture(position, vtexCoord).rgb;
    vec3 Normal = texture(normal, vtexCoord).rgb;
    vec3 Diffuse = texture(albedo, vtexCoord).rgb;
    float AmbientOcclusion = texture(ssao, vtexCoord).r;

    // blinn-phong (in view-space)
    vec3 lighting  = Diffuse * AmbientOcclusion;
    vec3 viewDir  = normalize(-FragPos); // viewpos is (0.0.0) in view-space
    // diffuse
    vec3 lightDir = normalize(Position - FragPos);
    vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * Color;
    // specular
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(Normal, halfwayDir), 0.0), 8.0);
    vec3 specular = Color * spec;
    // attenuation
    float dist = length(Position - FragPos);
    float attenuation = 1.0 / (1.0 + Linear * dist + Quadratic * dist * dist);
    diffuse  *= attenuation;
    specular *= attenuation;
    lighting += diffuse + specular;

    color = vec4(lighting, 1.0);
}
