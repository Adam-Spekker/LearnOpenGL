
#include "top_header.h"

class Frame {    //EBO version will be inherited
	GLuint cnt;
        GLuint* vCnt;
	GLuint* VBO;
	GLuint* VAO;
		
public:

	Frame(GLuint);
	Frame(const Frame& );

	void init(GLuint);
	void setup(GLuint, GLuint, GLuint, GLfloat*);
        void draw(GLuint);
        void pick(GLuint);
        
	GLuint operator[](GLuint) const;
		
	~Frame();
};