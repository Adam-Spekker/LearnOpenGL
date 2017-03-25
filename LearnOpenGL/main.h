
#include "top_header.h"
#include "Shader.h"
#include "Frame.h"
#include "Surface.h"


#include "Camera.h"

///global variables
const GLuint WIDTH = 1200;
const GLuint HEIGHT = 600;

 GLfloat FOV = 50.0f;

 bool keys[1024];
 bool firstMouse = true;

///declarations
GLFWwindow* setGL(GLuint width, GLuint height ); ///window dimensions /also viewport dimensions


void do_movement(Camera& cam, GLfloat deltaTime);

GLuint switch_spotlight();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

