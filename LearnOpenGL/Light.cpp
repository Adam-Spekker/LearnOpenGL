/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Light.cpp
 * Author: archghoul
 * 
 * Created on 29 March 2017, 12:30
 */

#include "Light.h"


void Light::setUni(Shader shader) {
    GLchar tmp[32];
    
    snprintf(tmp, sizeof tmp, "%s.ambient", name );
    GLint lightAmbientLoc = glGetUniformLocation(shader.Program, tmp);
    snprintf(tmp, sizeof tmp, "%s.diffuse", name );
    GLint lightDiffuseLoc = glGetUniformLocation(shader.Program, tmp);
    snprintf(tmp, sizeof tmp, "%s.specular", name );
    GLint lightSpecularLoc = glGetUniformLocation(shader.Program, tmp); 
    
    glUniform3f(lightAmbientLoc, Ambient.x, Ambient.y, Ambient.z);
    glUniform3f(lightDiffuseLoc, Diffuse.x, Diffuse.y, Diffuse.z);
    glUniform3f(lightSpecularLoc, Specular.x, Specular.y, Specular.z);       
}

void DirLight::setUni(Shader shader) {
    
    Light::setUni(shader);
    
    GLchar tmp[32];
    
    snprintf(tmp, sizeof tmp, "%s.direction", name );
    GLuint dirLightDirLoc = glGetUniformLocation(shader.Program, tmp);
    glUniform3f(dirLightDirLoc, Direction.x, Direction.y, Direction.z);
                       
}

void PointLight::setUni(Shader shader) {
    
    Light::setUni(shader);
    
    GLchar tmp[32];
    
    GLuint pointLightPosLoc = glGetUniformLocation(shader.Program, tmp);
    glUniform3f(pointLightPosLoc, Position.x, Position.y, Position.z);

    ///Fade x,y,z coordinates respectively : constant, linear, quadratic 

    GLuint pointLightFadeLoc = glGetUniformLocation(shader.Program,
            strcat(name, ".position"));
    glUniform3f(pointLightFadeLoc, Fade.x, Fade.y, Fade.z);

}

void SpotLight::setUni(Shader shader) {
    
    Light::setUni(shader);
    
    GLchar tmp[32];
    
    snprintf(tmp, sizeof tmp, "%s.direction", name );
    GLuint spotLightDirLoc = glGetUniformLocation(shader.Program, tmp);
    snprintf(tmp, sizeof tmp, "%s.position", name );
    GLuint spotLightPosLoc = glGetUniformLocation(shader.Program, tmp);
    snprintf(tmp, sizeof tmp, "%s.cutOff", name );
    GLuint spotLightCutOffLoc = glGetUniformLocation(shader.Program, tmp);
    
    
    glUniform3f(spotLightDirLoc, Direction.x, Direction.y, Direction.z);
    glUniform3f(spotLightDirLoc, Position.x, Position.y, Position.z);
    glUniform2f(spotLightCutOffLoc, CutOff, OuterCutOff);
                       
}