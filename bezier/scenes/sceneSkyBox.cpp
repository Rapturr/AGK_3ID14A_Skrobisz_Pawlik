#include "sceneSkyBox.hpp"

sceneSkyBox::sceneSkyBox(){}

void sceneSkyBox::initScene(){
    // Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);

	// Enable blendin
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glColorMask(0, 0, 0, 0);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  

	GLuint vaoHandle;
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

    compileAndLinkShader();


	diffuseMap = loadTexture("assets/Brick_Wall.jpg");
	normalMap = loadTexture("assets/Brick_Wall_NORMAL.jpg");
	texture = loadTexture("assets/goblin.png");
	
	
	hair.initScene(&shaderBezier);
	hair.move();
	shaderBezier.unlink();
/*
	world.scale(30,30,30);
	world.loadTexture();
	world.prep();

	cube.loadTexture("assets/Brick_Wall.jpg");
	cube.setNormal(diffuseMap,normalMap);
	cube.prep();
*/

	/*cube1.loadTexture("assets/Brick_Wall.jpg");
	cube1.prep();*/
	

	bool res = loadOBJ("assets/goblin.obj", vertices, uvs, normals);
	
	
	if(res){
		glGenVertexArrays(1, &susanVAO);
		glGenBuffers(1, &susanVBO);
		glBindVertexArray(susanVAO);
		glBindBuffer(GL_ARRAY_BUFFER, susanVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(glm::vec3), (void*)0);
		glGenBuffers(1, &susanVBO);
		glBindVertexArray(susanVAO);
		glBindBuffer(GL_ARRAY_BUFFER, susanVBO);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0 * sizeof(glm::vec2), (void*)2);
		
		glBindVertexArray(0);
/*
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);\\
		glGenBuffers(1, &EBO);
	
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), 
					&indices[0], GL_STATIC_DRAW);

		// vertex positions
		glEnableVertexAttribArray(0);	
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);	
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glEnableVertexAttribArray(2);	
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
*/
		/*glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
		*/
	}
	
	
	/*
	cube2.loadTexture(Texture);
	cube2.move(2.0f,-1.0f,3.0f);
	cube2.prep();

	floor.scale(9,0.1,9);
	floor.move(-7,-1,0);
	floor.loadTexture(floorTexture);
	floor.prep();*/

}

void sceneSkyBox::compileAndLinkShader(){
	shaderBezier.LoadShaders("shaders/bezcurve.vs","shaders/bezcurve.fs", "shaders/bezcurve.tcs", "shaders/bezcurve.tes");
	shaderSkybox.LoadShaders("shaders/skybox.vs", "shaders/skybox.fs");
	shaderEnv.LoadShaders("shaders/Lighting.vs", "shaders/Lighting.fs");

}
void sceneSkyBox::render(){}
void sceneSkyBox::render(glm::mat4 MVP, glm::mat4 projection, glm::mat4 model, glm::vec3 pos){
    // Clear the screen
	//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Use our shader
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColorMask(1,1,1,1);

	shaderBezier.use();
	hair.setwind(pos);
	hair.draw(MVP,&shaderBezier);
	shaderBezier.unlink();
	
	/*shaderSkybox.use();
	shaderSkybox.setMat4("MVP", MVP);
	shaderSkybox.setVec3("pos", pos);
	shaderSkybox.setInt("myTextureSampler",0);
	shaderSkybox.setBool("skybox", true);
	world.draw();
	shaderSkybox.unlink();*/
	

	shaderEnv.use();
	shaderEnv.setMat4("MVP", MVP);
	shaderEnv.setInt("myTextureSampler",0);
	shaderEnv.setInt("oswietlenie",0);     
	shaderEnv.setInt("oswietlenie",3); 
	shaderEnv.setVec3("pos", glm::vec3(1.0f,0.0f,1.0f));
	shaderEnv.setVec3("pos", glm::vec3(0.5f,-0.5f,-0.4f));
	shaderEnv.setVec3("lightPos", glm::vec3(1.5f,-1.0f,2.4f));
	shaderEnv.setVec3("lightDir",glm::vec3(1.4f,-1.9f,2.3f));
	shaderEnv.setBool("setcolor",true);

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(susanVAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	
}