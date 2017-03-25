#define STB_IMAGE_IMPLEMENTATION    
#include "Surface.h"
#include "Shader.h"


Surface::Surface(GLuint cnt) {
	this->cnt = cnt;
	textures = new GLuint[cnt];
	glGenTextures(cnt, textures);
}

Surface::Surface(const Surface& orig) {
	this->cnt = orig.cnt;
	textures = new GLuint[cnt];
	glGenTextures(cnt, textures);
}


void Surface::setup(GLuint serial, const char* img) {
	int widthIMG, heightIMG, n;
	glBindTexture(GL_TEXTURE_2D, textures[serial]);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	///img load
	unsigned char* image = stbi_load(img, &widthIMG, &heightIMG, &n, 3);
        if (image == nullptr)
           std::cout<<stbi_failure_reason() <<std::endl;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthIMG, heightIMG, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);


	stbi_image_free(image);
}

void Surface::activate(GLuint serial, GLuint texUnit, GLuint uniform, GLuint shader) {
    glActiveTexture(texUnit);
    glBindTexture(GL_TEXTURE_2D, textures[serial]);
    GLchar uniName[20];
    if (uniform == 0) {
       sprintf(uniName,"material.diffuse"); 
       //std::cout<<"diff"<<std::endl;
       
    }
    else {
       sprintf(uniName,"material.specular");
       //std::cout<<"spec"<<std::endl;
    }
    glUniform1i(glGetUniformLocation(shader, uniName), uniform);
}



GLuint Surface::operator[](GLuint serial) const {
	if (serial < 0 || serial >= this->cnt) {
		std::cout << "outofrange" << std::endl;
		return textures[0];
	}
	else return textures[serial];

}










Surface::~Surface() {

	glDeleteTextures(cnt, textures);

	delete[] textures;
}




