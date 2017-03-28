#define GLM_FORCE_RADIANS

#include "main.h"


  GLfloat deltaTime = 0.0f;   // time between lat frame and current frame
  GLfloat lastFrame = 0.0f;   // time of last frame;

  GLfloat lastX = 400, lastY = 300;
  
  glm::vec3 lightPos(1.0f, 1.0f, -1.0f);
  
 // Camera cam(0,0,0, 0,1,0,0,0);
  Camera cam;


glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f, 0.2f, 2.0f),
        glm::vec3( 2.3f, -1.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3( 0.0f, 0.0f, -3.0f)
};





int main() {

	
	///init opengl
	GLFWwindow* window = setGL(WIDTH, HEIGHT);
		if (!window) {
			std::cout << "exiting" << std::endl;
			return -1;
		}
        
        
        ///mouse lock
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
	///set callback functions
	glfwSetKeyCallback(window, key_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        
        


	//vsync on
	glfwSwapInterval(1);

	//depth test on
	glEnable(GL_DEPTH_TEST);

	//teal background color
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	


        
        Model nano("./resources/nano/nanosuit.obj");
        Model maya("./resources/maya/maya.obj");
        Model mask("./resources/mask/VMask.obj");
        Model st("./resources/st/Stormtrooper.obj");

		Model sphere("./resources/sphere.obj");
        
       // std::cout <<"tina";
       // Model tina("./resources/tina/tina.obj");

	Shader lightingShader("./resources/VShader.vs", "./resources/targetShader.frag");
        
        Shader lampShader("./resources/VShader.vs", "./resources/lampShader.frag");
        
	
	///main loop
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
                pointLightPositions[0] =  glm::vec3(lightPos.x, lightPos.y+2, lightPos.z);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                GLfloat currentFrame = glfwGetTime();
                deltaTime = currentFrame - lastFrame;
                lastFrame = currentFrame;
                
                lightingShader.Use();
                
                do_movement(cam, deltaTime);              

		glm::mat4 model;  
                glm::mat4 view;
		glm::mat4 projection;
                
                view  = cam.GetViewMatrix();  
		projection = glm::perspective(glm::radians(FOV) , 
                       GLfloat(WIDTH) / GLfloat(HEIGHT), 0.1f, 100.0f);
                
                ///Transformation matrices
		GLuint modelLoc = glGetUniformLocation(lightingShader.Program, 
                        "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		GLuint viewLoc = glGetUniformLocation(lightingShader.Program, 
                        "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		GLuint projectionLoc = glGetUniformLocation(lightingShader.Program, 
                        "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, 
                        glm::value_ptr(projection));
                
                ///Camera Position
                GLint cameraPosLoc = glGetUniformLocation(lightingShader.Program, 
                        "cameraPos");
                glUniform3f(cameraPosLoc, cam.Position.x, cam.Position.y, 
                        cam.Position.z);
                
////////                
////////                ///Material             
                GLint matShineLoc = glGetUniformLocation(lightingShader.Program, 
                        "material.shine");             
                glUniform1f(matShineLoc, 32.0f);
////////                
                  //  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

                ///Dir light
                GLuint dirLightDirLoc = glGetUniformLocation(lightingShader.Program,
                        "dirLight.direction");
                glUniform3f(dirLightDirLoc, 3.0f, -3.0f, -4.0f);

                
                GLint dirLightAmbientLoc = glGetUniformLocation(lightingShader.Program,
                        "dirLight.ambient");
                GLint dirLightDiffuseLoc = glGetUniformLocation(lightingShader.Program,
                        "dirLight.diffuse");
                GLint dirLightSpecularLoc = glGetUniformLocation(lightingShader.Program,
                        "dirLight.specular");        
                glUniform3f(dirLightAmbientLoc, 0.06f, 0.06f, 0.06f);
                glUniform3f(dirLightDiffuseLoc, 0.2f, 0.2f, 0.2f);
                glUniform3f(dirLightSpecularLoc, 1.0f, 1.0f, 1.0f);       
                       
                
                
                
                ///Point Lights
//           
                int n = 4; /// making dynamic class later 
                GLuint pointLightPosLoc[4]; 
                GLint pointLightAmbientLoc[4];
                GLint pointLightDiffuseLoc[4];
                GLint pointLightSpecularLoc[4];
                
                GLchar uniName[30];
                
                for (int i = 0; i < n; i++) {                   
                    sprintf(uniName,"pointLights[%d]", i); 
                    std::string str = std::string(uniName) + ".position";
                    
                    pointLightPosLoc[i] = glGetUniformLocation(lightingShader.Program,
                            str.c_str());
                    glUniform3f(pointLightPosLoc[i], 
                                pointLightPositions[i].x, 
                                pointLightPositions[i].y,
                                pointLightPositions[i].z);

                    //std::cout << str.c_str() << " 1\n";
                    
                    str = std::string(uniName) + ".constant";
                    glUniform1f(glGetUniformLocation(lightingShader.Program, 
                            str.c_str()), 1.0f);
                    str = std::string(uniName) + ".linear";
                    glUniform1f(glGetUniformLocation(lightingShader.Program, 
                            str.c_str()), 0.08f);
                    str = std::string(uniName) + ".quadratic";
                    glUniform1f(glGetUniformLocation(lightingShader.Program, 
                            str.c_str()), 0.022f);
                    
                    str = std::string(uniName) + ".ambient";
                    pointLightAmbientLoc[i] = glGetUniformLocation(lightingShader.Program,
                            str.c_str());
                    str = std::string(uniName) + ".diffuse";
                    pointLightDiffuseLoc[i] = glGetUniformLocation(lightingShader.Program,
                            str.c_str());
                    str = std::string(uniName) + ".specular";
                    pointLightSpecularLoc[i] = glGetUniformLocation(lightingShader.Program,
                            str.c_str());        
                    glUniform3f(pointLightAmbientLoc[i], 0.02f, 0.02f, 0.02f);
                    glUniform3f(pointLightDiffuseLoc[i], 0.5f, 0.5f, 0.5f);
                    glUniform3f(pointLightSpecularLoc[i], 1.0f, 1.0f, 1.0f);
                }
            
                
                GLint spotLightPosLoc = glGetUniformLocation(lightingShader.Program, 
                        "spotLight.position");
                GLint spotLightDirLoc = glGetUniformLocation(lightingShader.Program,
                        "spotLight.direction");
                glUniform3f(spotLightPosLoc, cam.Position.x, cam.Position.y,
                        cam.Position.z );
                glUniform3f(spotLightDirLoc, cam.Front.x, cam.Front.y, cam.Front.z);
                
                GLint spotLightAmbientLoc = glGetUniformLocation(lightingShader.Program,
                        "spotLight.ambient");
                GLint spotLightDiffuseLoc = glGetUniformLocation(lightingShader.Program,
                        "spotLight.diffuse");
                GLint spotLightSpecularLoc = glGetUniformLocation(lightingShader.Program,
                        "spotLight.specular");
				
				GLuint spotLightOn = switch_spotlight();
				GLfloat diffBase = spotLightOn * 0.5f;
				GLfloat specBase = spotLightOn * 1.0f;

                glUniform3f(spotLightAmbientLoc,  0.0f, 0.0f, 0.0f);
                glUniform3f(spotLightDiffuseLoc, diffBase, diffBase, diffBase);
                glUniform3f(spotLightSpecularLoc, specBase, specBase, specBase);
                
                ///Attenuation on request
                
                ///CutOff
                glUniform1f(glGetUniformLocation(lightingShader.Program, 
                        "spotLight.cutoff"), glm::cos(glm::radians(12.5f)));
                glUniform1f(glGetUniformLocation(lightingShader.Program, 
                        "spotLight.outerCutoff"), glm::cos(glm::radians(14.5f)));
               
                
                
                
			model = glm::mat4();
                model = glm::translate(model, glm::vec3(1.5f, -1.0f, -3.0f));
                model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                
                
                nano.Draw(lightingShader);
                
                
                
                model = glm::mat4(); 
                model = glm::translate(model, glm::vec3(1.5, 1.83f, -2.97f));
                model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                mask.Draw(lightingShader);
                
                
                model = glm::mat4(); 
                model = glm::translate(model, glm::vec3(1.5, -1.0f, 3.0f));
                model = glm::rotate(model, glm::radians(180.0f), 
                        glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::scale(model, glm::vec3(0.9f, 0.9f, 0.9f));
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                st.Draw(lightingShader);
                
                
				
				
                
                
				
                
                
              
		           
                
         
                lightPos.x = ((sin(currentFrame))) *10 +1;   
                lightPos.y = ((sin(currentFrame))) + 0.5;
                lightPos.z = ((cos(currentFrame))) *2 -3;
                
                lampShader.Use();

				
                
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		projectionLoc = glGetUniformLocation(lampShader.Program, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


				model = glm::mat4();
				model = glm::translate(model, glm::vec3(0.5, -1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(10.9f, 0.01f, 10.9f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
				sphere.Draw(lampShader);




               for (int i = 0; i < 4; i++) {
					model = glm::mat4();
                
					model = glm::translate(model, pointLightPositions[i]);
					model = glm::scale(model, glm::vec3(0.2f));
					glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                
					sphere.Draw(lampShader);
               }
                



		glfwSwapBuffers(window);
	}
	glfwTerminate();
	
	return 0;
	
}


GLFWwindow* setGL(GLuint width, GLuint height) {
	
	///GLFW init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	///Window init
	GLFWwindow* window = glfwCreateWindow(width, height, "FPS", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to open new window" << std::endl;		
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	///GLEW init
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed  GlewInit() " << std::endl;
		return nullptr;
	}
	
	///viewport INIT
	int fBuffWidth, fBuffHeight;
	glfwGetFramebufferSize(window, &fBuffWidth, &fBuffHeight);

	
	
	glfwSetWindowShouldClose(window, GL_FALSE);
	return window;
}


void do_movement(Camera& cam, GLfloat deltaTime) {
   
    if(keys[GLFW_KEY_W])
        cam.ProcessKeyboard( FORWARD, deltaTime);
    
    if(keys[GLFW_KEY_S])
        cam.ProcessKeyboard( BACKWARD, deltaTime);
    
    if(keys[GLFW_KEY_A])
       cam.ProcessKeyboard( LEFT, deltaTime);
    
     if(keys[GLFW_KEY_D])
        cam.ProcessKeyboard( RIGHT, deltaTime);
    
}

GLuint switch_spotlight() {

	if (keys[GLFW_KEY_F])
		return 1;
	else
		return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//set glfw to close window in next iteration	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;

}


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {

            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

        lastX = xpos;
        lastY = ypos;

        cam.ProcessMouseMovement(xoffset, yoffset);
}

