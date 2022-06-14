#include "engine.hpp"

/*static void GLClearError(){
	while(glGetError() != GL_NO_ERROR);
}
static void GLCheckError(){
	while(GLenum error = glGetError()){
		std::cout<<"[OpenGL Error]("<<error<<")"<<std::endl;
	}
}*/

void engine::init(){
    if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		//getchar();
		exit(1);
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    engine::window = glfwCreateWindow( 1024, 768, "Skrobisz Pawlik 3ID14A", NULL, NULL);
	if(engine::window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		//getchar();
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(engine::window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		fprintf(stderr, "Failed to initialize GLAD\n");
		glfwTerminate();
		exit(1);
	}

    // Ensure we can capture the escape key being pressed below
	glfwSetInputMode(engine::window, GLFW_STICKY_KEYS, GL_TRUE);
	// Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(engine::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(engine::window, 1024/2, 768/2);
	glfwSwapInterval(1);
    // Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    scenenumber = 1;
	
	skyboxScene.initScene();
}

void engine::run(){
	do{
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		sceneChoice = getSceneChoice();

		skyboxScene.render(MVP,ProjectionMatrix, ModelMatrix, getcameraposition());

		computeMatricesFromInputs(engine::window);
		glfwSwapBuffers(engine::window);
		glfwPollEvents();

	}while(glfwGetKey(engine::window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(engine::window) == 0 );
}