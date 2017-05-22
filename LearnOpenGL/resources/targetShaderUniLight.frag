#version 330 core

#define MAX_NR_LIGHTS 6 /// get input uniform for actual number 
#define POINT 1;
#define DIR 2;
#define SPOT 3;

struct Material {
    	//vec3 ambient;
    	//vec3 diffuse;
      sampler2D texture_diffuse1;
      sampler2D texture_specular1;
    	//vec3 specular;
      float shine;
    };

struct Light {
      vec3 position;
      vec3 direction;

      vec3 ambient;
      vec3 diffuse;
      vec3 specular;

      vec2 cutOff;
      int flag;
};




vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(Light light, vec3 normal, vec3 FragPos, vec3 viewDir);
vec3 CalcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

    in vec3 Normal;
    in vec3 FragPos;
    in vec2 TexCoords;

    uniform Material material;

    uniform Light lights[MAX_NR_LIGHTS];

    uniform vec3 cameraPos;

    out vec4 color;

void main() {
        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(cameraPos - FragPos);

   
      

        //lights
        for (int i = 0; i < MAX_NR_LIGHTS; i++) {
            if (lights[i].flag == POINT)
                result += CalcPointLight(lights[i], norm, FragPos, viewDir);
            else if (lights[i].flag > POINT)
                result += CalcSpotLight(lights[i], norm, FragPos, viewDir);
            else 
                result += CalcDirLight(lights[i], norm, viewDir);
  
        }      

         //Output
        color = vec4(result, 1.0f);

    }

vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir) {
        vec3 lightDir = normalize(-light.direction);
        //diff shade
        float diff = max(dot(normal, lightDir), 0.0);
        //specular shade
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir),0.0),
            material.shine);
        //combine
        vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1,
            TexCoords));
        vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1,
            TexCoords));
        return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
        vec3 lightDir = normalize(light.position - fragPos);
        // Diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        // Specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shine);
        // Attenuation
        float distance = length(light.position - fragPos);
        float attenuation = 1.0f / (light.dir.x + light.dir.y * distance +
        light.dir.z * (distance * distance));
        // Combine results
        vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1,
            TexCoords));
        vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1,
            TexCoords));
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
        return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
        vec3 lightDir = normalize(light.position - fragPos);
        //diff
        float diff = max(dot(normal, lightDir), 0.0);
        //spec
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shine);
        
        //spot 
        float theta = dot(lightDir, normalize(-light.direction));
        float epsilon = light.cutOff.x - light.cutOff.y;
        float intensity = clamp ((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

        //vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse1, TexCoords));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse1,
            TexCoords));
        vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1,
            TexCoords));
        vec3 ambient = vec3(0.0f);

        diffuse *= intensity;
        specular *= intensity;

        return (ambient + diffuse + specular);


}
