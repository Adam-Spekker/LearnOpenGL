/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mesh.cpp
 * Author: archghoul
 * 
 * Created on 24 March 2017, 20:09
 */

#include "Mesh.h"



Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures) 
          : vertices(vertices), indices(indices), textures(textures) {
    this->setupMesh();     
}

Mesh::Mesh(const Mesh& orig) {
}

Mesh::~Mesh() {
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    
    glBindVertexArray(VAO);
	
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), 
            &this->vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
            &this->indices[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (GLvoid*)0); 
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (GLvoid*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (GLvoid*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::Draw(Shader shader) {
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    for (GLuint i = 0; i < this->textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); ///activating textures 1by1
        
        std::stringstream ss;
        string number;
        TexType type = textures[i].type;
        string name = this->textures[i].typetxt[type];
        
        if(type == DIFFUSE)  /// swap later for enum
            ss << diffuseNr++;
        else if(type == SPECULAR)
            ss << specularNr++;
        number = ss.str();
        
        glUniform1f(glGetUniformLocation(shader.Program, ("material." +
                name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, this->textures[i].id);

		std::cout << "test1" << std::endl;

    }
    
    glActiveTexture(GL_TEXTURE0);
    
    
    ///actual draw
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
        
}