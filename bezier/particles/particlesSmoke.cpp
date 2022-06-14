// Include GLFW
//extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
using namespace glm;

#include "particlesSmoke.hpp"


#define MAX_PART 100 // Liczba cząstek
// Odstęp (sekundy) między aktywacjami kolejnych cząstek:
#define ACTIVATE_TIME 0.05
// Losowanie liczby w zakresie 0..1:
#define F_RAND() ((float)rand()/RAND_MAX)

ParticleSmoke::ParticleSmoke() {

    particlePool.resize(MAX_PART);
    activate();
    // Ustawienie koloru:
    float grey = F_RAND()*0.8f + 0.2f;
    r = grey;
    g = grey;
    b = grey;
    // Pozostałe parametry:
    active = false;
    size = F_RAND() * 5.0f +0.5f; // Rozmiar
    delta = glfwGetTime();
}

void ParticleSmoke::loadTexture(GLuint mytex){
	this->texture = mytex;
}

void ParticleSmoke::activate() {
    life = 1.0f; // Pełnia życia (dla 0 cząstka ginie)
    fade = 0.05f + F_RAND()*0.4f; // Tempo umierania (1/sekunda)
    // Początkowa pozycja cząstki (emiter punktowy):
    x = F_RAND()*10.0f;
    z = F_RAND()*10.0f;
    y = 10.0f;
    x = y = z = 0.0f;
    // Wektor ruchu - losowo z użyciem SFERYCZNEGO układu:
    float fi = M_PI/6; // 45 stopni w górę
    float psi = F_RAND() * (M_PI); // 0-360 stopni wokół osi Y
    float rr = F_RAND() * 12 + 16; // Długość wektora ruchu
    // Przeliczenie na układ kartezjański:
    xi = rr * cos(fi) * cos(psi);
    yi = rr * sin(fi);
    zi = rr * cos(fi) * cos(psi);
    
    // Wektor grawitacji:
    xg = zg = 0;
    //zg = 1;
    yg = -10; // Grawitacja "tradycyjna" w dół
    quadVA = 0;
}


void ParticleSmoke::live(float tt) {

    // Przesunięcie cząstki zgodnie z wektorem ruchu:
    x += xi * tt;
    y += yi * tt;
    z += zi * tt;
    // Modyfikacja wektora ruchu przez wektor grawitacji:
    xi += xg * tt;
    yi += yg * tt;
    zi += zg * tt;
    // Zabranie życia:
    life -= fade * tt;
    // Jeżeli cząstka "umarła", reaktywacja:
        /* code */
    
    //if(life <= 0.0f) activate();
    for (auto& particle : particlePool)
	{
        /*particle.Position.x = particle.Position.x+=xi * tt;
        particle.Position.y = particle.Position.y+=yi * tt;
        particle.Position.z = particle.Position.z+=zi * tt;*/
        particle.Position.x += particle.Velocity.x * 0.4f;
        particle.Position.y += particle.Velocity.y;
        particle.Position.z += particle.Velocity.z * 0.4f;
        deltaTime = glfwGetTime();
        if(deltaTime - delta > ACTIVATE_TIME) 
        if (particle.LifeRemaining <= 0.0f)
		{
            delta = glfwGetTime();
			particle.Active = false;

            activate();

            particle.Active = true;
            particle.Position = glm::vec3(0.0f,-0.5f,0.0f);
            //particle.Position = glm::vec3(x,y,z);
            particle.Rotation = F_RAND() * 2.0f * glm::pi<float>();

            // Velocity
            particle.Velocity = glm::vec3(xi*tt,yi*tt,zi*tt);

            // Color
            float grey = F_RAND()*0.6f + 0.2f;
            particle.Color = glm::vec4(grey,grey,grey,1.0f);

            particle.LifeTime = 1.0f;
            particle.LifeRemaining = 1.0f;
            particle.SizeBegin = F_RAND()*0.3f + 0.1f;
            particle.SizeEnd = F_RAND()*0.1f + 0.1f;

			continue;
		}
        particle.LifeRemaining -= tt*2;
    }
    

}

void ParticleSmoke::draw(Shader prog, glm::mat4 direction){
    if (!quadVA)
	{
    float position[]={
        x, y,z,//0
        x+size/2, y,z,//1
        x+size/2, y+size/2,z,//2
        x+size/2, y+size/2,z,//2
        x, y+size/2,z,//3
        x, y,z//0
    };
    center = {size/3, size/3};
    
    float uvposition[]={
        0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
    };


    glGenBuffers(1, &quadVA);
	glBindBuffer(GL_ARRAY_BUFFER, quadVA);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

    glGenBuffers(1, &quadUV);
	glBindBuffer(GL_ARRAY_BUFFER, quadUV);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvposition), uvposition, GL_STATIC_DRAW);
    
    }
    prog.use();
    for (auto& particle : particlePool)
	{
		if (!particle.Active)
			continue;
        prog.use();
        float alpha = particle.LifeRemaining;
        //glm::vec4 color = glm::vec4(particle.Color.r,particle.Color.g,particle.Color.b,0.3f);
        prog.setVec4("Color", vec4(particle.Color.r,particle.Color.g,particle.Color.b,alpha));
        prog.setVec3("Position",particle.Position);
        prog.setMat4("direction",direction);
        prog.setVec2("center",center);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glUniform1i(texture, 0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, quadUV);
        glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, quadVA);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

        glDrawArrays(GL_TRIANGLES, 0, 2*3);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }


    
    /*
    prog.use();
    prog.setUniform("Color", vec4(r,g,b,life));
    prog.setUniform("Position",vec3(x,y,z));
    //glDrawArrays(GL_POINTS, 0, 4);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, quadVA);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 2*3);
    glDisableVertexAttribArray(0);*/
}