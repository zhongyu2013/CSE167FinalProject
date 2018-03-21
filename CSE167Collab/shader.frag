#version 330 core
// This is a sample fragment shader.

// Inputs to the fragment shader are the outputs of the same name from the vertex shader.
// Note that you do not have access to the vertex shader's default output, gl_Position.
in float sampleExtraOutput;
in vec3 mycolor;
in vec3 Texture;
// You can output many things. The first vec4 type output determines the color of the fragment
//out vec4 color;
uniform sampler2D dTexture;
uniform sampler2D shadowMap;

struct Material {
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
    float shininess;
    float flag;
    float shadow_s;
};

struct DirLight {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
/*struct SpotLight{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
}*/
struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 4

in vec3 FragPos;
in float intensity;
//in vec3 Normal;

out vec4 fuckcolor;
in vec4 fragposlight;
uniform vec3 viewPos;
uniform vec3 lightP;
uniform DirLight dirLight;
uniform PointLight pointLights;
uniform SpotLight spotLight;
uniform Material material;
uniform int flag;
uniform int count;
uniform vec3 lid;
//uniform vec3 lid;
// Function prototypes

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    
    float shadow = 0.0f;
    vec3 norm = normalize(mycolor);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 lightcolor = vec3 (1.0);
    vec3 temp_color = norm;
    
    vec3 result;

    float intensity;
    vec3 lightDirection = normalize(lid-FragPos);
    intensity = max(dot(lightDirection,norm),0.0f);//diff
    if(material.flag==0){
        temp_color = norm;
    }
    if(material.flag==1){
        if (intensity > 0.95)
            temp_color = vec3(0.5,1.0,0.5);
        else if (intensity > 0.5)
            temp_color = vec3(0.3,0.6,0.3);
        else if (intensity > 0.2)
            temp_color = vec3(0.2,0.4,0.2);
        else
            temp_color = vec3(0.1,0.2,0.1);
    }
    if(material.flag==2){
        temp_color = vec3(1.0);
    }
        vec3 ambient = 0.2*temp_color;
        vec3 diffuse = intensity*lightcolor;
        vec3 reflection = reflect(-lightDirection, norm);
        float spec = 0.0f;
        vec3 midwaydir = normalize(lightDirection+ viewDir);
        //spec = pow(max(dot(norm,midwaydir),0.0f),64.0f);
        vec3 specular = spec*lightcolor;
        //cal shadow
    if(material.shadow_s==1){
        float bias = max(0.05 * (1.0 - dot(norm, lightDirection)), 0.005);
        vec3 project = fragposlight.xyz/fragposlight.w;
        project = project*0.5+0.5;
    
        float closestD = texture(shadowMap,project.xy).r;
        float currentD = project.z;
        shadow = currentD-bias>closestD ? 1.0 : 0.0;
        if(project.z>1.0)
            shadow = 0.0f;
    }
    
        result = (ambient+(1.0-shadow)*(diffuse+specular))*temp_color;

   
    // Phase 3: Spot light
    
    // Color everything a hot pink color. An alpha of 1.0f means it is not transparent.
    fuckcolor = vec4(result, sampleExtraOutput);
}
// Calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{

    vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Combine results
    vec3 ambient = light.ambient * material.diffuse;
    vec3 diffuse = light.diffuse * diff *material.diffuse;
    vec3 specular = light.specular * spec *material.specular;
    return (ambient + diffuse + specular);
}

// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Combine results
    vec3 ambient = light.ambient * material.diffuse;
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    vec3 specular = light.specular * spec *material.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // Combine results
    vec3 ambient = light.ambient * material.diffuse;
    vec3 diffuse = light.diffuse * diff *material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}
