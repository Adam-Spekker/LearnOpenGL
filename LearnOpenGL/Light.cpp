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

void DirLight::setup(Shader shader) {
    GLuint dirLightDirLoc = glGetUniformLocation(shader.Program, 
             "dirLight.direction");
    glUniform3f(dirLightDirLoc, Direction.x, Direction.y, Direction.z);
     
    GLint dirLightAmbientLoc = glGetUniformLocation(lightingShader.Program,
            "dirLight.ambient");
    GLint dirLightDiffuseLoc = glGetUniformLocation(lightingShader.Program,
            "dirLight.diffuse");
    GLint dirLightSpecularLoc = glGetUniformLocation(lightingShader.Program,
            "dirLight.specular"); 
    
    glm::vec3& ambient = this->getAmbient();
    glm::vec3& diff = this->getDiffuse();
    glm::vec3& spec = this->getSpecular();
    
    glUniform3f(dirLightAmbientLoc, ambient.x, ambient.y, ambient.z);
    glUniform3f(dirLightDiffuseLoc, diff.x, diff.y, diff.z);
    glUniform3f(dirLightSpecularLoc, spec.x, spec.y, spec.z);       
                       
}

void PointLight::setup(Shader shader) {
    
    
    GLuint pointLightPosLoc; 
    GLuint pointLightAmbientLoc;
    GLuint pointLightDiffuseLoc;
    GLuint pointLightSpecularLoc;
                
        GLchar uniName[30];
                
        sprintf(uniName,"pointLights[%d]", id); 
               
        std::string str = std::string(uniName) + ".position";

        pointLightPosLoc = glGetUniformLocation(shader.Program, str.c_str());
        glUniform3f(pointLightPosLoc, Position.x, Position.y, Position.z);

        //std::cout << str.c_str() << " 1\n";

        str = std::string(uniName) + ".constant";
        glUniform1f(glGetUniformLocation(shader.Program, str.c_str()), Fade.x);
        str = std::string(uniName) + ".linear";
        glUniform1f(glGetUniformLocation(shader.Program, str.c_str()), Fade.y);
        str = std::string(uniName) + ".quadratic";
        glUniform1f(glGetUniformLocation(shader.Program, str.c_str()), Fade.z);

        
        str = std::string(uniName) + ".ambient";
        pointLightAmbientLoc = glGetUniformLocation(shader.Program, str.c_str());
        str = std::string(uniName) + ".diffuse";
        pointLightDiffuseLoc = glGetUniformLocation(shader.Program, str.c_str());
        str = std::string(uniName) + ".specular";
        pointLightSpecularLoc = glGetUniformLocation(shader.Program, str.c_str());        
        
        glm::vec3& ambient = this->getAmbient();
        glm::vec3& diff = this->getDiffuse();
        glm::vec3& spec = this->getSpecular();

        glUniform3f(pointLightAmbientLoc, ambient.x, ambient.y, ambient.z);
        glUniform3f(pointLightDiffuseLoc, diff.x, diff.y, diff.z);
        glUniform3f(pointLightSpecularLoc, spec.x, spec.y, spec.z);       
}