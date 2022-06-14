#ifndef SCENESKYBOX_HPP
#define SCENESKYBOX_HPP

#include "../common/shader.hpp"

#include "../shapes/includeShapes.hpp"
#include "../common/texture.hpp"
#include "../common/objloader.hpp"
#include <glm.hpp>

class sceneSkyBox
{
private:
    Shader shaderSkybox;
    Shader shaderEnv;
    Shader shaderBezier;
    GLuint vaoHandle;

    BezierHair hair;
    flatPlaneTemplate floor;
    cubeTemplate cube;
    cubeTemplate cube1;
    cubeTemplate cube2;
    GLuint texture;
	GLuint floorTexture;
    unsigned int diffuseMap;
    unsigned int normalMap;
    skyBox world;

    GLuint vertexbuffer;
	GLuint uvbuffer;
    unsigned int susanVBO;
	unsigned int susanVBOuv;
	unsigned int susanVBOnorm;
    unsigned int susanVAO;
    unsigned int VAO, VBO, EBO;

    std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
    
    glm::vec3 lightPos = glm::vec3(1.5f, 1.0f, 0.3f);


    void setMatrices();
    void compileAndLinkShader();
    unsigned int loadTexture(char const * path){
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat 
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }
public:
    sceneSkyBox();
    glm::vec3 move = glm::vec3(0.0f,0.0f,0.0f);
    void initScene();
    void render();
    void render(glm::mat4, glm::mat4, glm::mat4, glm::vec3);

};

#endif