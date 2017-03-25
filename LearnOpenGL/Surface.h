#include "top_header.h"


class Surface {
	GLuint* textures;
	GLuint cnt;

public:
	Surface(GLuint);
	Surface(const Surface&);

	
	void setup(GLuint, const char* );
        void activate(GLuint, GLuint, GLuint, GLuint );
       // void deactivate(GLuint);
        
	GLuint operator[](GLuint) const;


	~Surface();


};