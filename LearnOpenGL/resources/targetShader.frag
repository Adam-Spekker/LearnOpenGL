#version 330 core

struct Material {
    	//vec3 ambient;
    	//vec3 diffuse;
      sampler2D diffuse;
      sampler2D specular;
    	//vec3 specular;
        float shine;
    };

struct DirLight {
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct PointLight {
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float constant;
  float linear;
  float quadratic;

};
#define MAX_NR_POINT_LIGHTS 4 /// get input uniform for actual number 


struct SpotLight {
      vec3 position;
      vec3 direction;

      vec3 ambient;
      vec3 diffuse;
      vec3 specular;

      float constant;
      float linear;
      float quadratic;

      float cutoff;
      float outerCutoff;
};

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 FragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

    in vec3 Normal;
    in vec3 FragPos;
    in vec2 TexCoords;

    uniform Material material;
    uniform DirLight dirLight;
    uniform SpotLight spotLight;

    uniform PointLight pointLights[MAX_NR_POINT_LIGHTS];

    uniform vec3 cameraPos;

    out vec4 color;

void main() {
        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(cameraPos - FragPos);

        //dir
        vec3 result = CalcDirLight(dirLight, norm, viewDir);

        //point
        for (int i = 0; i < MAX_NR_POINT_LIGHTS; i++) {
            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
        }      

        //spot
        result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

         //Output
        color = vec4(result, 1.0f);

    }

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
        vec3 lightDir = normalize(-light.direction);
        //diff shade
        float diff = max(dot(normal, lightDir), 0.0);
        //specular shade
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir),0.0),
            material.shine);
        //combine
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,
            TexCoords));
        vec3 specular = light.specular * spec * vec3(texture(material.specular,
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
        float attenuation = 1.0f / (light.constant + light.linear * distance +
        light.quadratic * (distance * distance));
        // Combine results
        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,
            TexCoords));
        vec3 specular = light.specular * spec * vec3(texture(material.specular,
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
        float epsilon = light.cutoff - light.outerCutoff;
        float intensity = clamp ((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

        //vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,
            TexCoords));
        vec3 specular = light.specular * spec * vec3(texture(material.specular,
            TexCoords));
        vec3 ambient = vec3(0.0f);

        diffuse *= intensity;
        specular *= intensity;

        return (ambient + diffuse + specular);


}
