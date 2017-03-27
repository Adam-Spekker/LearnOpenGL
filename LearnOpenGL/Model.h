/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Model.h
 * Author: archghoul
 *
 * Created on 24 March 2017, 22:25
 */

#ifndef MODEL_H
#define MODEL_H

#include "top_header.h"
#include "Shader.h"
#include "Mesh.h"

class Model {
public:
	Model(GLchar* path) {
		this->loadModel(path);
	}

    Model(const Model& orig);

	void Draw(Shader shader);


    virtual ~Model();

private:
	///Data
	vector<Mesh> meshes;
	string directory;
	
	///Inner Functions
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTexture type, string typeName);

};

#endif /* MODEL_H */


