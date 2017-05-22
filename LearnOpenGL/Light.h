/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Light.h
 * Author: archghoul
 *
 * Created on 29 March 2017, 12:30
 */

#ifndef LIGHT_H
#define LIGHT_H

#include "top_header.h"
#include "Shader.h"
#include "Camera.h"

enum LightType {DIR =0, POINT = 1, SPOT = 2};


class Light {
    glm::vec3 Ambient;
    glm::vec3 Diffuse;
    glm::vec3 Specular;
    
protected:
    LightType flag;
    GLuint ID;
    GLchar name[16];
    
public:
    Light(glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f),
            glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f),
                glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f) ): 
                    Ambient(ambient), Diffuse(diffuse), Specular(specular) {}
                    
    void setAmbient(glm::vec3 amb) {Ambient = amb;}
    void setDiffuse(glm::vec3 diff) {Diffuse = diff;}
    void setSpecular(glm::vec3 spec) {Specular = spec;}      
    
    glm::vec3 getAmbient() { return Ambient;}
    glm::vec3 getDiffuse() { return Diffuse;}
    glm::vec3 getSpecular() { return Specular;}
    
    void setID(GLuint id) { 
        ID = id; 
        snprintf(name, sizeof name, "lights[%d]", id );
    }
    
    
    const GLchar* getName();
    
    virtual void setUni(Shader shader);
    
   // virtual void move(glm::vec3);
            
    virtual ~Light() {}

};

class DirLight : public Light {
    glm::vec3 Direction;
    
public:
    DirLight(GLuint id, glm::vec3 dir = glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f),
                    glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f),
                        glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f)) : 
                            Direction(dir),Light(ambient, diffuse, specular) {                            
                                flag = DIR;
                            } 
                        
    
    
 
    void setDir(glm::vec3 dir) { Direction = dir;}
    glm::vec3 getDir() {return Direction;}
    
    void setUni(Shader shader);
    ~DirLight() {}
        
};

class PointLight : public Light {
    glm::vec3 Position;    
    glm::vec3 Fade;
    
public: 
    PointLight(glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f),
                glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f),
                    glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f),
                        glm::vec3 pos = glm::vec3(1.0f, 1.0f, 1.0f),
                            glm::vec3 fade = glm::vec3(1.0f, 0.09f, 0.032f)) : 
                                Light(ambient, diffuse, specular), 
                                Position(pos), Fade(fade) {
                                        flag = POINT;
                                }
                            
                            
    void setPosition(glm::vec3 pos) { Position = pos; }
    glm::vec3 getPosition() { return Position; }
    
    void setFade(glm::vec3 fade) { Fade = fade; }
    void setFade(GLfloat c, GLfloat l, GLfloat q) { Fade = glm::vec3(c,l,q); }
    glm::vec3 getFade() { return Fade; }
    
    void setUni(Shader shader);
     ~PointLight() {}
};

class SpotLight : public Light {
    glm::vec3 Position;
    glm::vec3 Direction;
    glm::vec2 CutOff;
public:
    //SpotLight();
    void setup(Shader shader);
    
    SpotLight(glm::vec3 ambient = glm::vec3(0.1f, 0.1f, 0.1f),
                glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f),
                    glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f),
                        glm::vec3 pos = glm::vec3(1.0f, 1.0f, 1.0f),
                            glm::vec3 dir = glm::vec3(1.0f, 0.09f, 0.032f),
                                glm::vec2 cutoff = glm::vec2(12.0f, 14.0f)) : 
                                    Light(ambient, diffuse, specular), 
                                    Position(pos), Direction(dir),
                                    CutOff(cutoff) {
                                        flag = POINT;
                                    }
    
    void setDir(glm::vec3 dir) { Direction = dir;}
    glm::vec3 getDir() { return Direction; }
    
    void setPosition(glm::vec3 pos) { Position = pos; }
    glm::vec3 getPosition() { return Position; }
    
    void setCutOff(glm::vec2 cutoff) { CutOff = cutoff; }
    glm::vec2 getCutOff() { return CutOff; }
    
    void setUni(Shader shader);
    
    
    
    
    
     ~SpotLight() {}
};



#endif /* LIGHT_H */
