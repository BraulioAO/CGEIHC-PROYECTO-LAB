#pragma once
void LoadTextures(void);
unsigned int generateTextures(char*, bool);

//Texture
unsigned int	t_piso;
unsigned int	t_pisoLamina;
unsigned int	t_techo;
unsigned int	t_muroMarco;
unsigned int	t_muroFondo;
unsigned int	t_muroDerechoFondo;
unsigned int	t_puerta;
unsigned int	t_white;
unsigned int	t_yeso;
unsigned int	t_yesoBarda;
unsigned int	t_pizarron;
unsigned int	t_lamparaOn;
unsigned int	t_lamparaOff;
unsigned int	t_arranque;
unsigned int	t_arranque0;
unsigned int	t_arranque1;
unsigned int	t_arranque2;
unsigned int	t_arranque3;
unsigned int	t_arranque4;
unsigned int	t_arranque5;



unsigned int generateTextures(const char* filename, bool alfa)
{
	unsigned int textureID;	//Genera textura desde un archivo
	glGenTextures(1, &textureID);	//Genera un identificador
	glBindTexture(GL_TEXTURE_2D, textureID); //Tipo de textura que va a generar, 1D o 2D
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Prepara la textura, activa opcion de repetir
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Filtros para el redimencionamiento, tanto cuando se haga pequeña
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //o se haga mas grande
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);  //Lee el archivo
	if (data){
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //convierte la invormación en mapa de bits
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return textureID; //Regresa el identificador de la textura que se esta manejando
	}
	else{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

void LoadTextures()
{
	t_piso = generateTextures("Texturas/piso.jpg", 0); //El 1 indica que hay canal alfa, importante agregar
	t_pisoLamina = generateTextures("Texturas/pisoLamina.jpg", 0);
	t_techo = generateTextures("Texturas/techo.jpg", 0);
	t_white = generateTextures("Texturas/white.jpg", 0);
	t_muroFondo = generateTextures("Texturas/muroFondo.jpg", 0);
	t_muroDerechoFondo = generateTextures("Texturas/muroDerechoFondo.jpg", 0);
	t_puerta = generateTextures("Texturas/puerta.jpg", 0);
	t_muroMarco = generateTextures("Texturas/muroMarco.jpg", 0);
	t_yeso = generateTextures("Texturas/yeso.jpg", 0);
	t_yesoBarda = generateTextures("Texturas/yesoBarda.jpg", 0);
	t_pizarron = generateTextures("Texturas/pizarron.jpg", 0);
	t_lamparaOn = generateTextures("Texturas/lamparaOn.jpg", 0);
	t_lamparaOff = generateTextures("Texturas/lamparaOff2.jpg", 0);
	t_arranque1 = generateTextures("Texturas/Arranque/arranque0.jpg", 0);
	t_arranque1 = generateTextures("Texturas/Arranque/arranque1.jpg", 0);
	t_arranque2 = generateTextures("Texturas/Arranque/arranque2.jpg", 0);
	t_arranque3 = generateTextures("Texturas/Arranque/arranque3.jpg", 0);
	t_arranque4 = generateTextures("Texturas/Arranque/arranque4.jpg", 0);
	t_arranque5 = generateTextures("Texturas/Arranque/arranque5.jpg", 0);

	
}