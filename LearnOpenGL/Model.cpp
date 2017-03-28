/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Model.cpp
 * Author: archghoul
 * 
 * Created on 24 March 2017, 22:25
 */

#include "Model.h"


Model::Model(const Model& orig) {
}

Model::~Model() {
}

void Model::Draw(Shader shader) {
	for (GLint i = 0; i < this->meshes.size(); i++) {
		this->meshes[i].Draw(shader);
              //  std::cout<< meshes[i].textures.size() << std::endl;
                
	}
}

void Model::loadModel(string path) {
	Assimp::Importer import;

	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}

	this->directory = path.substr(0, path.find_last_of('/'));

	this->processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	///Processing node meshes
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
            //std::cout << node->mNumMeshes << std::endl;
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                
                
              // std::cout << mesha.textures[0].id << std::endl;
		this->meshes.push_back(Mesh(this->processMesh(mesh, scene)));
               // std::cout << this->meshes[i].textures[0].id << std::endl;
               
	}
	///Processing for children
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		this->processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
        
	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		
                Vertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vector;
			vector.x = mesh->mTextureCoords[0][i].x;
			vector.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vector;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
        
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
           // std::cout<<"\ndiff:";
            vector<Texture> diffuseMaps = this->loadMaterialTextures(material,
                                      aiTextureType_DIFFUSE, DIFFUSE);
            textures.insert(textures.end(), 
                    diffuseMaps.begin(), diffuseMaps.end());
           //std::cout<<"\nspec:"; 
            vector<Texture> specularMaps = this->loadMaterialTextures(material,
                                      aiTextureType_SPECULAR, SPECULAR);
            textures.insert(textures.end(),
                    specularMaps.begin(), specularMaps.end());
            
           //std::cout<<textures.size()<<std::endl;  
        }
        //std::cout << textures[0].id << "!";
        
        
        return Mesh(vertices, indices, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                                        TexType typeName) {
    vector<Texture> textures;
    
    
    for(GLuint i = 0; i < mat->GetTextureCount(type); i++) {
        //std::cout<< i <<" ";
        aiString str;
        mat->GetTexture(type, i, &str);
        GLboolean skip = false;
        for(GLuint j = 0; j < textures_loaded.size(); j++) {
            if (std::strcmp(textures_loaded[j].path.C_Str(), str.C_Str()) == 0 ) {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if(!skip) {  
        
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
            this->textures_loaded.push_back(texture);
        }
    }
    return textures;
}



GLint TextureFromFile(const char* path, string directory)
{
     //Generate texture ID and load texture data 
    string filename = string(path);
    filename = directory + '/' + filename;
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width,height;
    //unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    
    unsigned char* image = stbi_load(filename.c_str(), &width, &height, 0, 3);
        if (image == nullptr)
           std::cout<<stbi_failure_reason() <<std::endl;
    
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);	

    // Parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    //SOIL_free_image_data(image);
    stbi_image_free(image);
    return textureID;
}