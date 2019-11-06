/*---------------------------------------------------------------*/
/* -----------------   Proyecto Final ---------------------------*/
/*------------------       2020-1     ---------------------------*/
/*---------- Alumno:  Arrieta Ocampo Braulio Enrique   ----------*/
//#define STB_IMAGE_IMPLEMENTATION
#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "camera.h"
#include "Model.h"

// Other Libs
#include "SOIL2/SOIL2.h"

// settings
int abrirPuerta = 0;
#include "texturas.h"
#include "datosModelosPropios.h"
#include "keyFrame.h"
#include "init.h"


glm::vec3 estadoLuces;
float 	despPuerta = 0.0f;


void animate(void)
{

	if (estadoLuz == 1)
		estadoLuces = glm::vec3(1.0f, 1.0f, 1.0f);
	else
		estadoLuces = glm::vec3(0.0f, 0.0f, 0.0f);

	if (abrirPuerta == 1)
		if (despPuerta >= 3.75f)
			;
		else
			despPuerta += 0.125;
	else
		if (despPuerta <= 0.0f)
			;
		else
			despPuerta -= 0.125;

	if (estadoArranque == 0)
		t_arranque = t_arranque5;
	else
		t_arranque = t_arranque0;


	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;
			rotAvion += rotInc;
			abrirPuerta = abrirPuertaInc;

			i_curr_steps++;
		}

	}
	
}

void display(Shader shader, Shader shaderLamp, Model mesa, Model CPU, Model monitor, Model mouse, 
			Model keyboard, Model dispensador, Model silla, Model extintor, Model avion)
{
	//Lighting
	//float posLuzX = movLuzX;
	float posLuzX = 7.0f;
	glm::vec3 lightPosition0(posLuzX, 8.0f, -7.0f);
	glm::vec3 lightPosition1(posLuzX, 8.0f,  0.0f);
	glm::vec3 lightPosition2(posLuzX, 8.0f,  7.0f);
	glm::vec3 lightPosition3(-posLuzX, 8.0f, -7.0f);
	glm::vec3 lightPosition4(-posLuzX, 8.0f,  0.0f);
	glm::vec3 lightPosition5(-posLuzX, 8.0f,  7.0f);
	glm::vec3 lightPosition6(posLuzX-7.0f, 4.0f, 0.0f);
	glm::vec3 lightDirection(1.0f, -1.0f, -1.0f);  //Dirección de la luz ambiental


	shader.use();
	shader.setVec3("viewPos", camera.Position);

	//Luz direccional, fuente infinita
	shader.setVec3("dirLight.direction", lightDirection);  	// Se pasa la direccion de la fuente de luz direccional
	shader.setVec3("dirLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));	//AMBIENTAL, indica hacia que color tienden las caras menos iluminadas por la fuente de luz
	shader.setVec3("dirLight.diffuse", glm::vec3(0.2f, 0.2f, 0.2f));	//DIFUSA, indica el color que van a tomar las caras más iluminadas del objeto
	shader.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));	//ESPECULAR, se trata de simular un brillo que va a tener la superficie

	//Luz posicional
	float lin = 0.001f;
	float quad = 0.03f;
	shader.setVec3("pointLight[0].position", lightPosition0);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[0].diffuse", estadoLuces);
	shader.setVec3("pointLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[0].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[0].linear", lin);     //Distancia máxima
	shader.setFloat("pointLight[0].quadratic", quad);  //Distancia máxima

	shader.setVec3("pointLight[1].position", lightPosition1);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].diffuse", estadoLuces);
	shader.setVec3("pointLight[1].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[1].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[1].linear", lin);     //Distancia máxima
	shader.setFloat("pointLight[1].quadratic", quad);  //Distancia máxima

	shader.setVec3("pointLight[2].position", lightPosition2);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[2].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[2].diffuse", estadoLuces);
	shader.setVec3("pointLight[2].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[2].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[2].linear", lin);        //Distancia máxima
	shader.setFloat("pointLight[2].quadratic", quad);  //Distancia máxima

	shader.setVec3("pointLight[3].position", lightPosition3);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[3].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[3].diffuse", estadoLuces);
	shader.setVec3("pointLight[3].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[3].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[3].linear", lin);        //Distancia máxima
	shader.setFloat("pointLight[3].quadratic", quad);  //Distancia máxima

	shader.setVec3("pointLight[4].position", lightPosition4);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[4].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[4].diffuse", estadoLuces);
	shader.setVec3("pointLight[4].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[4].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[4].linear", lin);        //Distancia máxima
	shader.setFloat("pointLight[4].quadratic", quad);  //Distancia máxima

	shader.setVec3("pointLight[5].position", lightPosition5);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[5].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[5].diffuse", estadoLuces);
	shader.setVec3("pointLight[5].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[5].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[5].linear", lin);        //Distancia máxima
	shader.setFloat("pointLight[5].quadratic", quad);  //Distancia máxima

	shader.setVec3("pointLight[6].position", lightPosition6);  //Modifica la dirección de la luz posicional
	shader.setVec3("pointLight[6].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[6].diffuse", estadoLuces);
	shader.setVec3("pointLight[6].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[6].constant", 1.0f);    //Factor de atenuación, potencia de la fuente de luz muy grande
	shader.setFloat("pointLight[6].linear", lin);        //Distancia máxima
	shader.setFloat("pointLight[6].quadratic", quad);  //Distancia máxima

	shader.setFloat("material_shininess", 250.0f);

	// create transformations and Projection
	glm::mat4 temp = glm::mat4(1.0f);
	glm::mat4 origenHab = glm::mat4(1.0f);
	glm::mat4 origenMesa = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 150.0f);
	view = camera.GetViewMatrix();

	view = glm::scale(view, glm::vec3(2.0f, 2.0f, 2.0f));
//	view = glm::scale(view, glm::vec3(1.0f, 1.0f, 1.0f));

	// pass them to the shaders
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader.setMat4("projection", projection);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);


	//******************************************************************************************
	// MODELOS PROPIOS, A PARTIR DE CUBOS Y PLANOS

	/*----------------------------------------------------------*/
	/* ---- Shader sin efectos de luz, crea fuentes de luz ---- */
	/*----------------------------------------------------------*/
	glBindVertexArray(VAO);
	shaderLamp.use();	//
	/*
	//Se dibujan cubos amarillos para ubicar la posicion de las luces
	//Se reemplaza con las lámparas.
	//FUENTE DE LUZ POSICIONAL 0
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition0);
	shaderLamp.setMat4("projection", projection);
	shaderLamp.setMat4("view", view);
	shaderLamp.setMat4("model", model);
	shaderLamp.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//FUENTE DE LUZ POSICIONAL 1
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition1);
	shaderLamp.setMat4("projection", projection);
	shaderLamp.setMat4("view", view);
	shaderLamp.setMat4("model", model);
	shaderLamp.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//FUENTE DE LUZ POSICIONAL 2
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition2);
	shaderLamp.setMat4("projection", projection);
	shaderLamp.setMat4("view", view);
	shaderLamp.setMat4("model", model);
	shaderLamp.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//FUENTE DE LUZ POSICIONAL 3
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition3);
	shaderLamp.setMat4("projection", projection);
	shaderLamp.setMat4("view", view);
	shaderLamp.setMat4("model", model);
	shaderLamp.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//FUENTE DE LUZ POSICIONAL 4
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition4);
	shaderLamp.setMat4("projection", projection);
	shaderLamp.setMat4("view", view);
	shaderLamp.setMat4("model", model);
	shaderLamp.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	//FUENTE DE LUZ POSICIONAL 5
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition5);
	shaderLamp.setMat4("projection", projection);
	shaderLamp.setMat4("view", view);
	shaderLamp.setMat4("model", model);
	shaderLamp.setVec3("aColor", glm::vec3(1.0f, 1.0f, 0.0f));
	glDrawArrays(GL_QUADS, 0, 24);
	*/

	/*----------------------------------------------------------*/
	/* -------- Shader con efectos de luz y texturizado ------- */
	/*----------------------------------------------------------*/
	shader.use();  //Shader con los efectos de luz y texturizado
	//CUBO EN EL CENTRO
	
	/*model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(rotAvion), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(posX, posY, posZ));
	shader.setVec3("aColor", 1.0f, 0.0f, 0.0f);
	shader.setMat4("model", model);
	glBindTexture(GL_TEXTURE_2D, t_white);
	glDrawArrays(GL_QUADS, 0, 24);
	shader.setVec3("aColor", 1.0f, 1.0f, 1.0f);
	}*/
	//PISO
	origenHab = glm::mat4(1.0f);
	//origenHab = glm::translate(origenHab, glm::vec3(posX, 0.0f, 0.0f));
	model = glm::scale(origenHab, glm::vec3(28.0f, 1.0f, 28.0f));
	shader.setMat4("model", model);
	glBindTexture(GL_TEXTURE_2D, t_piso);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//PISO LÁMINA
	model = glm::translate(origenHab, glm::vec3(-1.0f, 0.01f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 28.0f));
	shader.setMat4("model", model);
	glBindTexture(GL_TEXTURE_2D, t_pisoLamina);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(6));

	//TECHO
	
	model = origenHab;
	model = glm::translate(model, glm::vec3(0.0f, 9.01f, 0.0f));
	model = glm::scale(model, glm::vec3(28.0f, 1.0f, 28.0f));
	shader.setMat4("model", model);
	glBindTexture(GL_TEXTURE_2D, t_techo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(12));
	

	//LAMPARAS
	temp = origenHab;
	if(estadoLuz == 1)
		glBindTexture(GL_TEXTURE_2D, t_lamparaOn); //Textura lampara
	else
		glBindTexture(GL_TEXTURE_2D, t_lamparaOff); //Textura lampara
	for (int i = 0; i < 3; i++) {
		temp = model = glm::translate(temp, glm::vec3(-7.0f, 9.0f, -7.0f + 7.0f*i)); //Posiciones lamparas izq
		model = glm::scale(model, glm::vec3(6.0f, 2.5f, 1.0f));
		shader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(30));
		temp = glm::translate(temp, glm::vec3(7.0f, -9.0f, +7.0f - 7.0f*i));

		temp = model = glm::translate(temp, glm::vec3(7.0f, 9.0f, -7.0f + 7.0f*i)); //Posiciones lamparas der
		model = glm::scale(model, glm::vec3(6.0f, 2.5f, 1.0f));
		shader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(30));
		temp = glm::translate(temp, glm::vec3(-7.0f, -9.0f, 7.0f - 7.0f*i));
	}


	//PARED FRONTAL
	temp = origenHab;
	for (int i = 0; i < 7;i++) {
		temp = glm::translate(temp, glm::vec3(-12.0f + 3.834f*i, 0.001f, -14.0f)); //Posicion de la pared
		//pared
		glBindTexture(GL_TEXTURE_2D, t_muroMarco); //Textura marcos
		temp = model = glm::translate(temp, glm::vec3(0.0f, 0.17f, 0.10f)); //parte 1-7
		model = glm::scale(model, glm::vec3(3.8f, 0.34f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 2.83f, 0.00f)); //parte 2-7
		model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 5.0f, 0.00f)); //parte 3-7
		model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 0.9f, 0.00f)); //parte 4-7
		model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(-1.95f, -4.4f, 0.00f)); //parte 5-7
		model = glm::scale(model, glm::vec3(0.1f, 9.0f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(3.9f, 0.00f, 0.00f)); //parte 6-7
		model = glm::scale(model, glm::vec3(0.1f, 9.0f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		glBindTexture(GL_TEXTURE_2D, t_muroFondo); //Textura fondo pared
		temp = model = glm::translate(temp, glm::vec3(-1.95f, 0.00f, -0.101f)); //parte 7-7
		model = glm::scale(model, glm::vec3(4.0f, 9.0f, 1.0f));
		shader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		temp = glm::translate(temp, glm::vec3(12.0f - 3.834f*i, -4.501f, 14.0f)); //Regresamos al origen
	}

	//PARED TRASERA
	temp = glm::rotate(temp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	for (int i = 0; i < 7;i++) {
		temp = glm::translate(temp, glm::vec3(12.0f - 3.834f*i, 0.001f, -14.0f)); //Posicion de la pared
		//pared
		glBindTexture(GL_TEXTURE_2D, t_muroMarco); //Textura marcos
		temp = model = glm::translate(temp, glm::vec3(0.0f, 0.17f, 0.10f)); //parte 1-7
		model = glm::scale(model, glm::vec3(3.8f, 0.34f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 2.83f, 0.00f)); //parte 2-7
		model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 5.0f, 0.00f)); //parte 3-7
		model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 0.9f, 0.00f)); //parte 4-7
		model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(-1.95f, -4.4f, 0.00f)); //parte 5-7
		model = glm::scale(model, glm::vec3(0.1f, 9.0f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(3.9f, 0.00f, 0.00f)); //parte 6-7
		model = glm::scale(model, glm::vec3(0.1f, 9.0f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		glBindTexture(GL_TEXTURE_2D, t_muroFondo); //Textura fondo pared
		temp = model = glm::translate(temp, glm::vec3(-1.95f, 0.00f, -0.101f)); //parte 7-7
		model = glm::scale(model, glm::vec3(4.0f, 9.0f, 1.0f));
		shader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		temp = glm::translate(temp, glm::vec3(-12.0f + 3.834f*i, -4.501f, 14.0f)); //Regresamos al origen
	}

	//PARED IZQUIERDA
	temp = origenHab;
	temp = glm::rotate(temp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	for (int i = 1; i < 7;i++) {
		temp = glm::translate(temp, glm::vec3(-12.0f + 4.0f*i, 0.001f, -14.0f)); //Posicion de la pared
		//pared
		glBindTexture(GL_TEXTURE_2D, t_muroMarco); //Textura marcos
		temp = model = glm::translate(temp, glm::vec3(0.0f, 0.17f, 0.10f)); //parte 1-7
		model = glm::scale(model, glm::vec3(3.8f, 0.34f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 2.83f, 0.00f)); //parte 2-7
		model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 5.0f, 0.00f)); //parte 3-7
		model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 0.9f, 0.00f)); //parte 4-7
		model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(-1.95f, -4.4f, 0.00f)); //parte 5-7
		model = glm::scale(model, glm::vec3(0.1f, 9.0f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(3.9f, 0.00f, 0.00f)); //parte 6-7
		model = glm::scale(model, glm::vec3(0.1f, 9.0f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		glBindTexture(GL_TEXTURE_2D, t_muroFondo); //Textura fondo pared
		temp = model = glm::translate(temp, glm::vec3(-1.95f, 0.00f, -0.101f)); //parte 7-7
		model = glm::scale(model, glm::vec3(4.0f, 9.0f, 1.0f));
		shader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		temp = glm::translate(temp, glm::vec3(12.0f - 4.0f*i, -4.501f, 14.0f)); //Regresamos al origen
	}
	temp = origenHab;
	temp = glm::translate(temp, glm::vec3(-12.001f, 0.001f, -13.90f)); //Posicion esquina frente-izq
	temp = model = glm::translate(temp, glm::vec3(-1.9f, 4.49f, 0.01f)); //Vija esquina
	model = glm::scale(model, glm::vec3(0.2f, 9.0f, 0.20f));
	shader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 48, 24);

	//PARED DERECHA
	glBindTexture(GL_TEXTURE_2D, t_yeso); //Textura yeso columna
	temp = origenHab;
	model = glm::translate(temp, glm::vec3(13.5, 4.5f, -13.7f)); //Posicion columna 1 de 3
	model = glm::scale(model, glm::vec3(1.0f, 9.0f, 0.5f));
	shader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 24, 24);

	temp = origenHab;
	temp = glm::rotate(temp, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	temp = glm::translate(temp, glm::vec3(0.5f, 0.0f, 0.0f));
	for (int i = 0; i < 2;i++) {
		temp = glm::translate(temp, glm::vec3(-12.0f + 4.0f*i, 0.0f, -13.99f)); //Posicion de la pared
		//pared
		glBindTexture(GL_TEXTURE_2D, t_muroMarco); //Textura marcos
		temp = model = glm::translate(temp, glm::vec3(0.0f, 0.17f, 0.10f)); //parte 1-7
		//model = glm::scale(model, glm::vec3(3.8f, 0.34f, 0.20f));
		//shader.setMat4("model", model);
		//glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 2.83f, 0.00f)); //parte 2-7
		model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 5.0f, 0.00f)); //parte 3-7
		model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 0.9f, 0.00f)); //parte 4-7
		model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(-1.95f, -2.95f, 0.00f)); //parte 5-7
		model = glm::scale(model, glm::vec3(0.1f, 6.1f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(3.9f, 0.00f, 0.00f)); //parte 6-7
		model = glm::scale(model, glm::vec3(0.1f, 6.1f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		glBindTexture(GL_TEXTURE_2D, t_muroDerechoFondo); //Textura fondo pared
		temp = model = glm::translate(temp, glm::vec3(-1.95f, -1.45f, -0.101f)); //parte 7-7
		model = glm::scale(model, glm::vec3(4.0f, 9.0f, 1.0f));
		shader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		temp = glm::translate(temp, glm::vec3(12.0f - 4.0f*i, -4.501f, 14.0f)); //Regresamos al origen
	}
	glBindTexture(GL_TEXTURE_2D, t_yeso); //Textura yeso columna
	temp = origenHab;
	model = glm::translate(temp, glm::vec3(13.5, 4.5f, -5.0f)); //Posicion columna 2 de 3
	model = glm::scale(model, glm::vec3(1.0f, 9.0f, 1.0f));
	shader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 24, 24);

	temp = origenHab;
	temp = glm::rotate(temp, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	temp = glm::translate(temp, glm::vec3(9.7f, 0.0f, 0.0f));
	for (int i = 0; i < 4;i++) {
		temp = glm::translate(temp, glm::vec3(-12.0f + 4.5f*i, 0.0f, -13.99f)); //Posicion de la pared
		//pared
		glBindTexture(GL_TEXTURE_2D, t_muroMarco); //Textura marcos
		temp = model = glm::translate(temp, glm::vec3(0.0f, 0.17f, 0.10f)); //parte 1-7
		//model = glm::scale(model, glm::vec3(4.3f, 0.34f, 0.20f));
		//shader.setMat4("model", model);
		//glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 2.83f, 0.00f)); //parte 2-7
		model = glm::scale(model, glm::vec3(4.3f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 5.0f, 0.00f)); //parte 3-7
		model = glm::scale(model, glm::vec3(4.3f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(0.0f, 0.9f, 0.00f)); //parte 4-7
		model = glm::scale(model, glm::vec3(4.3f, 0.20f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(-2.20f, -2.95f, 0.00f)); //parte 5-7
		model = glm::scale(model, glm::vec3(0.1f, 6.1f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		temp = model = glm::translate(temp, glm::vec3(4.3f, 0.00f, 0.00f)); //parte 6-7
		model = glm::scale(model, glm::vec3(0.1f, 6.1f, 0.20f));
		shader.setMat4("model", model);
		glDrawArrays(GL_QUADS, 48, 24);
		glBindTexture(GL_TEXTURE_2D, t_muroDerechoFondo); //Textura fondo pared
		temp = model = glm::translate(temp, glm::vec3(-2.20f, -1.45f, -0.101f)); //parte 7-7
		model = glm::scale(model, glm::vec3(4.5f, 9.0f, 1.0f));
		shader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		temp = glm::translate(temp, glm::vec3(12.0f - 4.5f*i, -4.501f, 14.0f)); //Regresamos al origen
	}
	glBindTexture(GL_TEXTURE_2D, t_yeso); //Textura yeso columna
	temp = origenHab;
	model = glm::translate(temp, glm::vec3(13.5, 4.5f, 13.5f)); //Posicion columna 3 de 3
	model = glm::scale(model, glm::vec3(1.0f, 9.0f, 1.0f));
	shader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 24, 24);

	glBindTexture(GL_TEXTURE_2D, t_yesoBarda); //Textura yeso barda
	temp = origenHab;
	model = glm::translate(temp, glm::vec3(13.5, 3.0f, 0.0f)); //Posicion bardita
	model = glm::scale(model, glm::vec3(0.999f, 0.5f, 28.0f));
	shader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 0, 24);


	//PUERTA
	temp = origenHab;
	temp = glm::rotate(temp, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	temp = glm::translate(temp, glm::vec3(-11.76f+despPuerta, 0.001f, -13.795f)); //Posicion de la pared
	//pared
	glBindTexture(GL_TEXTURE_2D, t_muroMarco); //Textura marcos
	temp = model = glm::translate(temp, glm::vec3(0.0f, 0.17f, 0.10f)); //parte 1-7
	model = glm::scale(model, glm::vec3(3.8f, 0.34f, 0.20f));
	shader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 48, 24);
	temp = model = glm::translate(temp, glm::vec3(0.0f, 2.83f, 0.00f)); //parte 2-7
	model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
	shader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 48, 24);
	temp = model = glm::translate(temp, glm::vec3(0.0f, 5.0f, 0.00f)); //parte 3-7
	model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
	shader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 48, 24);
	temp = model = glm::translate(temp, glm::vec3(0.0f, 0.9f, 0.00f)); //parte 4-7
	model = glm::scale(model, glm::vec3(3.8f, 0.20f, 0.20f));
	shader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 48, 24);
	temp = model = glm::translate(temp, glm::vec3(-1.95f, -4.4f, 0.00f)); //parte 5-7
	model = glm::scale(model, glm::vec3(0.1f, 9.0f, 0.20f));
	shader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 48, 24);
	temp = model = glm::translate(temp, glm::vec3(3.9f, 0.00f, 0.00f)); //parte 6-7
	model = glm::scale(model, glm::vec3(0.1f, 9.0f, 0.20f));
	shader.setMat4("model", model);
	glDrawArrays(GL_QUADS, 48, 24);
	glBindTexture(GL_TEXTURE_2D, t_puerta); //Textura fondo puerta
	temp = model = glm::translate(temp, glm::vec3(-1.95f, 0.00f, -0.101f)); //parte 7-7
	model = glm::scale(model, glm::vec3(4.0f, 9.0f, 1.0f));
	shader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
	temp = glm::translate(temp, glm::vec3(12.0f, -4.501f, 14.0f)); //Regresamos al origen


	//PIZARRON
	model = origenHab;
	model = glm::translate(model, glm::vec3(0, 5.0f, -13.77f)); //Posicion pizarron
	model = glm::scale(model, glm::vec3(8.0f, 4.0f, 1.0f));
	shader.setMat4("model", model);
	glBindTexture(GL_TEXTURE_2D, t_pizarron); //Textura pizarron
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(24));
		



	glBindVertexArray(0);

	//******************************************************************************************
	//MODELOS CARGADOS

	//MESAS LADO IZQUIERDO Y COMPUTADORAS Y SILLAS
	float aux;
	temp = origenHab;
	for (int i = 0; i < 3; i++) { //Dibuja 3 pares de mesas del lado izquierdo
		origenMesa = model = glm::translate(temp, glm::vec3(aux=-12.05f, 0.0f, -7.5f + 6.0f*i)); //mesa 1 de 3
		model = glm::scale(model, glm::vec3(0.875f, 1.0f, 1.5f));
		shader.setMat4("model", model);
		mesa.Draw(shader);
		//Computadora 1 de 3
		model = glm::translate(origenMesa, glm::vec3(0.55f, 2.11f, -0.75f)); //Monitor
		shader.setMat4("model", model);
		monitor.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(-0.95f, 2.11f, 0.25f)); //CPU
		shader.setMat4("model", model);
		CPU.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(0.3f, 2.11f, 0.2f)); //teclado
		shader.setMat4("model", model);
		keyboard.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(1.25f, 2.11f, 0.5f)); //raton
		shader.setMat4("model", model);
		mouse.Draw(shader);
		//arranque 1
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, t_arranque);
		temp = model = glm::translate(origenMesa, glm::vec3(0.55f, 2.95f, -0.74f));
		if (estadoArranque == 2) {
			glBindTexture(GL_TEXTURE_2D, t_arranque1); 
			model = glm::scale(model, glm::vec3(1.62f, 1.02f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
			glBindTexture(GL_TEXTURE_2D, t_arranque2);
			model = glm::translate(temp, glm::vec3(0.0f, -0.2f, 0.01f));
			model = glm::rotate(model, glm::radians(rotArr), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		}
		else {
			model = glm::scale(model, glm::vec3(1.62f, 1.02f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		}
		glBindVertexArray(0);
		//Silla 1 de 3
		model = glm::translate(origenMesa, glm::vec3(0.0f, 0.0f, 2.0f));
		shader.setMat4("model", model);
		silla.Draw(shader);

		origenMesa = model = glm::translate(origenMesa, glm::vec3(3.5f, 0.0f, 0.0f)); // mesa 2 de 3
		model = glm::scale(model, glm::vec3(0.875f, 1.0f, 1.5f));
		shader.setMat4("model", model);
		mesa.Draw(shader);
		//Computadora 2 de 3
		model = glm::translate(origenMesa, glm::vec3(0.55f, 2.11f, -0.75f)); //Monitor
		shader.setMat4("model", model);
		monitor.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(-0.95f, 2.11f, 0.25f)); //CPU
		shader.setMat4("model", model);
		CPU.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(0.3f, 2.11f, 0.2f)); //teclado
		shader.setMat4("model", model);
		keyboard.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(1.25f, 2.11f, 0.5f)); //raton
		shader.setMat4("model", model);
		mouse.Draw(shader);
		//arranque 2
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, t_arranque);
		temp = model = glm::translate(origenMesa, glm::vec3(0.55f, 2.95f, -0.74f));
		if (estadoArranque == 2) {
			glBindTexture(GL_TEXTURE_2D, t_arranque1);
			model = glm::scale(model, glm::vec3(1.62f, 1.02f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
			glBindTexture(GL_TEXTURE_2D, t_arranque2);
			model = glm::translate(temp, glm::vec3(0.0f, -0.2f, 0.01f));
			model = glm::rotate(model, glm::radians(rotArr), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		}
		else {
			model = glm::scale(model, glm::vec3(1.62f, 1.02f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		}
		glBindVertexArray(0);
		//Silla 2 de 3
		model = glm::translate(origenMesa, glm::vec3(0.0f, 0.0f, 2.0f));
		shader.setMat4("model", model);
		silla.Draw(shader);

		origenMesa = model = glm::translate(origenMesa, glm::vec3(3.5f, 0.0f, 0.0f)); // mesa 3 de 3
		model = glm::scale(model, glm::vec3(0.875f, 1.0f, 1.5f));
		shader.setMat4("model", model);
		mesa.Draw(shader);
		//Computadora 3 de 3
		model = glm::translate(origenMesa, glm::vec3(0.55f, 2.11f, -0.75f)); //Monitor
		shader.setMat4("model", model);
		monitor.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(-0.95f, 2.11f, 0.25f)); //CPU
		shader.setMat4("model", model);
		CPU.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(0.3f, 2.11f, 0.2f)); //teclado
		shader.setMat4("model", model);
		keyboard.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(1.25f, 2.11f, 0.5f)); //raton
		shader.setMat4("model", model);
		mouse.Draw(shader);
		//arranque 3
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, t_arranque);
		temp = model = glm::translate(origenMesa, glm::vec3(0.55f, 2.95f, -0.74f));
		if (estadoArranque == 2) {
			glBindTexture(GL_TEXTURE_2D, t_arranque1);
			model = glm::scale(model, glm::vec3(1.62f, 1.02f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
			glBindTexture(GL_TEXTURE_2D, t_arranque2);
			model = glm::translate(temp, glm::vec3(0.0f, -0.2f, 0.01f));
			model = glm::rotate(model, glm::radians(rotArr), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		}
		else {
			model = glm::scale(model, glm::vec3(1.62f, 1.02f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		}
		glBindVertexArray(0);
		//Silla 3 de 3
		model = glm::translate(origenMesa, glm::vec3(0.0f, 0.0f, 2.0f));
		shader.setMat4("model", model);
		silla.Draw(shader);

		temp = glm::translate(origenMesa, glm::vec3(-aux-7.0f, 0.0f, 7.5f - 6.0f*i)); //Regresamos al origen
	}



	//MESAS LADO DERECHO
	temp = origenHab;
	for (int i = 0; i < 3; i++) {  //Dibuja 3 pares de mesas del lado derecho
		origenMesa = model = glm::translate(temp, glm::vec3(aux=11.25f, 0.0f, -7.5f + 6.0f*i)); //mesa 1 de 3
		model = glm::scale(model, glm::vec3(0.875, 1.0f, 1.5f));
		shader.setMat4("model", model);
		mesa.Draw(shader);
		//Computadora 1 de 3
		model = glm::translate(origenMesa, glm::vec3(-0.55f, 2.11f, -0.75f)); //Monitor
		shader.setMat4("model", model);
		monitor.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(0.95f, 2.11f, 0.25f)); //CPU
		shader.setMat4("model", model);
		CPU.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(-0.8f, 2.11f, 0.2f)); //teclado
		shader.setMat4("model", model);
		keyboard.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(0.15f, 2.11f, 0.5f)); //raton
		shader.setMat4("model", model);
		mouse.Draw(shader);
		//arranque 1
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, t_arranque);
		temp = model = glm::translate(origenMesa, glm::vec3(-0.55f, 2.95f, -0.74f));
		if (estadoArranque == 2) {
			glBindTexture(GL_TEXTURE_2D, t_arranque1);
			model = glm::scale(model, glm::vec3(1.62f, 1.02f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
			glBindTexture(GL_TEXTURE_2D, t_arranque2);
			model = glm::translate(temp, glm::vec3(0.0f, -0.2f, 0.01f));
			model = glm::rotate(model, glm::radians(rotArr), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		}
		else {
			model = glm::scale(model, glm::vec3(1.62f, 1.02f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		}
		glBindVertexArray(0);
		//Silla 1 de 3
		model = glm::translate(origenMesa, glm::vec3(0.0f, 0.0f, 2.0f));
		shader.setMat4("model", model);
		silla.Draw(shader);

		origenMesa = model = glm::translate(origenMesa, glm::vec3(-3.5f, 0.0f, 0.0f)); //mesa 2 de 3
		model = glm::scale(model, glm::vec3(0.875, 1.0f, 1.5f));
		shader.setMat4("model", model);
		mesa.Draw(shader);
		//Computadora 2 de 3
		model = glm::translate(origenMesa, glm::vec3(-0.55f, 2.11f, -0.75f)); //Monitor
		shader.setMat4("model", model);
		monitor.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(0.95f, 2.11f, 0.25f)); //CPU
		shader.setMat4("model", model);
		CPU.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(-0.8f, 2.11f, 0.2f)); //teclado
		shader.setMat4("model", model);
		keyboard.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(0.15f, 2.11f, 0.5f)); //raton
		shader.setMat4("model", model);
		mouse.Draw(shader);
		//arranque 2
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, t_arranque);
		temp = model = glm::translate(origenMesa, glm::vec3(-0.55f, 2.95f, -0.74f));
		if (estadoArranque == 2) {
			glBindTexture(GL_TEXTURE_2D, t_arranque1);
			model = glm::scale(model, glm::vec3(1.62f, 1.02f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
			glBindTexture(GL_TEXTURE_2D, t_arranque2);
			model = glm::translate(temp, glm::vec3(0.0f, -0.2f, 0.01f));
			model = glm::rotate(model, glm::radians(rotArr), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		}
		else {
			model = glm::scale(model, glm::vec3(1.62f, 1.02f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		}
		glBindVertexArray(0);
		//Silla 2 de 3
		model = glm::translate(origenMesa, glm::vec3(0.0f, 0.0f, 2.0f));
		shader.setMat4("model", model);
		silla.Draw(shader);

		origenMesa = model = glm::translate(origenMesa, glm::vec3(-3.5f, 0.0f, 0.0f)); //mesa 2 de 3
		model = glm::scale(model, glm::vec3(0.875, 1.0f, 1.5f));
		shader.setMat4("model", model);
		mesa.Draw(shader);
		//Computadora 3 de 3
		model = glm::translate(origenMesa, glm::vec3(-0.55f, 2.11f, -0.75f)); //Monitor
		shader.setMat4("model", model);
		monitor.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(0.95f, 2.11f, 0.25f)); //CPU
		shader.setMat4("model", model);
		CPU.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(-0.8f, 2.11f, 0.2f)); //teclado
		shader.setMat4("model", model);
		keyboard.Draw(shader);
		model = glm::translate(origenMesa, glm::vec3(0.15f, 2.11f, 0.5f)); //raton
		shader.setMat4("model", model);
		mouse.Draw(shader);
		//arranque 3
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, t_arranque);
		temp = model = glm::translate(origenMesa, glm::vec3(-0.55f, 2.95f, -0.74f));
		if (estadoArranque == 2) {
			glBindTexture(GL_TEXTURE_2D, t_arranque1);
			model = glm::scale(model, glm::vec3(1.62f, 1.02f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
			glBindTexture(GL_TEXTURE_2D, t_arranque2);
			model = glm::translate(temp, glm::vec3(0.0f, -0.2f, 0.01f));
			model = glm::rotate(model, glm::radians(rotArr), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		}
		else {
			model = glm::scale(model, glm::vec3(1.62f, 1.02f, 1.0f));
			shader.setMat4("model", model);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, BUFFER_OFFSET(18));
		}
		glBindVertexArray(0);
		//Silla 3 de 3
		model = glm::translate(origenMesa, glm::vec3(0.0f, 0.0f, 2.0f));
		shader.setMat4("model", model);
		silla.Draw(shader);

		temp = glm::translate(origenMesa, glm::vec3(-aux+7.0f, 0.0f, 7.5f - 6.0f*i)); //Regresamos al origen
	}

	//DISPENSADOR
	model = origenHab;
	model = glm::rotate(temp, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -13.2f));
	shader.setMat4("model", model);
	dispensador.Draw(shader);

	//Extintor
	model = origenHab;
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(13.4f, 4.0f, -12.75f));
	model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
	shader.setMat4("model", model);
	extintor.Draw(shader);

	//Avion
	if (play) {
		glBindTexture(GL_TEXTURE_2D, t_white);
		model = origenHab;
		model = glm::translate(model, glm::vec3(-15.0f, 5.1f, 12.00f));
		model = glm::translate(model, glm::vec3(posZ, posY, -posX));
		model = glm::rotate(model, glm::radians(rotAvion), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.1f, 10.1f, 10.1f));
		shader.setMat4("model", model);
		avion.Draw(shader);
	}




	
}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWwindow* window = initWindow("Proyecto Final");

	//Mis funciones
	//Datos a utilizar
	LoadTextures();
	myData();
	glEnable(GL_DEPTH_TEST);

	
	Shader modelShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");
	// Load models
	Model mesaModel = ((char*)"Models/Mesa/mesa.obj");
	Model CPUModel = ((char*)"Models/Computadora/CPU.obj");
	Model monitorModel = ((char*)"Models/Computadora/monitor.obj");
	Model mouseModel = ((char*)"Models/Computadora/mouse.obj");
	Model keyboardModel = ((char*)"Models/Computadora/keyboard.obj");
	Model extintorModel = ((char*)"Models/Extintor/extintor.obj");
	Model dispensadorModel = ((char*)"Models/Dispensador/dispensador.obj");
	Model sillaModel = ((char*)"Models/Silla/silla.obj");
	Model avionModel = ((char*)"Models/avion.obj");

	

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0.0f;
		KeyFrame[i].posY = 0.0f;
		KeyFrame[i].posZ = 0.0f;
		KeyFrame[i].rotAvion = 0.0f;
		KeyFrame[i].abrirPuerta = 0;
	}
	openFile();

	double currentFrame;
	// render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
		// per-frame time logic
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		animate();

        // render
        // Backgound color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		display(modelShader, lampShader, mesaModel, CPUModel, monitorModel, mouseModel, keyboardModel, 
				dispensadorModel, sillaModel, extintorModel, avionModel);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

