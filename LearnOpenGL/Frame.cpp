#include "Frame.h"

Frame::Frame(GLuint cnt) {
	this->cnt = cnt;
	init(this->cnt);
}


Frame::Frame(const Frame& orig) {
	this->cnt = orig.cnt;
	init(this->cnt);
}


void Frame::init(GLuint cnt) {
        vCnt = new GLuint[cnt];
	VBO = new GLuint[cnt];
	VAO = new GLuint[cnt];
	glGenVertexArrays(cnt, VAO);
	glGenBuffers(cnt, VBO);

}
void Frame::pick(GLuint serial) {
    
}

void Frame::draw(GLuint serial) {
            glBindVertexArray(VAO[serial]);
            glDrawArrays(GL_TRIANGLES, 0, vCnt[serial]);

            glBindVertexArray(0);
    
}

void Frame::setup(GLuint serial, GLuint size, GLuint attribCnt, GLfloat* vertices) { //min 5 attrib/vertex x,y,z pos & x,y tex whatever after
	glBindVertexArray(VAO[serial]);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO[serial]);
        
        vCnt[serial] = GLuint(size/attribCnt);
	
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, attribCnt * sizeof(GLfloat),
                (GLvoid*)0); 
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, attribCnt * sizeof(GLfloat),
                (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, attribCnt * sizeof(GLfloat),
                (GLvoid*)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

}

GLuint Frame::operator[](GLuint serial) const {
	if (serial < 0 || serial >= this->cnt) {
		std::cout << "outofrange" << std::endl;
		return VAO[0];
	}
	else return VAO[serial];
	
}


Frame::~Frame() {
	glDeleteVertexArrays(cnt, VAO);
	glDeleteBuffers(cnt, VBO);
        delete[] vCnt;
	delete[] VBO;
	delete[] VAO;
}