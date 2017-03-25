/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mesh.h
 * Author: archghoul
 *
 * Created on 24 March 2017, 20:09
 */



#ifndef MESH_H
#define MESH_H

#include "top_header.h"
#include "Shader.h"

enum TexType {DIFFUSE = 0, SPECULAR = 1};

using std::vector;
using std::string;       

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    GLuint id; 
    TexType type;
    
    static const char* typetxt[];
};
const char* Texture::typetxt[] = {"texture_diffuse", "texture_specular"};


class Mesh {
public:
    ///Mesh data
    vector<Vertex> vertices;
    vector<GLuint> indices;
    vector<Texture> textures;
    
    ///public functions   
    Mesh(vector<Vertex> vertices, vector<GLuint> indices,
        vector<Texture> textures);
    void Draw(Shader shader);
    
    Mesh(const Mesh& orig);
    virtual ~Mesh();
private:
    
   
    ///render
    GLuint VAO, VBO, EBO;

    ///private functions
    void setupMesh();

};



#endif /* MESH_H */

