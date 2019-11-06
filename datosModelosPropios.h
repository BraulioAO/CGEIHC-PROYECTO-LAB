#pragma once
GLuint VBO, VAO, EBO;
#define BUFFER_OFFSET(i) ((void*)(i*sizeof(float)))

void myData(){
	float vertices[] = {  
		// positions			// normals				//texture coords
		//	Cubo misma Textura por lado
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  0.0f,	//V0 - Frontal
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  0.0f,	//V1
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  1.0f,	//V5
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  1.0f,	//V4

		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  0.0f,	//V3
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  1.0f,	//V7
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  1.0f,	//V6

		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  0.0f,	//V3 - Izquierda
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f,  0.0f,	//V0
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f,  1.0f,	//V4
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  1.0f,	//V7
		
		 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  0.0f,	//V1 - Derecha
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f,  0.0f,	//V2
		 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f,  1.0f,	//V6
		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  1.0f,	//V5		 

		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  0.0f,	//V4 - Superior
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  1.0f,	//V5
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  1.0f,	//V6
		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  0.0f,	//V7

		-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  0.0f,	//V0 - Inferior
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  0.0f,	//V1
		 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  1.0f,	//V2
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  1.0f,	//V3
		//	Cubo para columnas pared
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  0.0f,	//V0 - Frontal
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  0.0f,	//V1
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  1.0f,	//V5
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  1.0f,	//V4

		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  0.0f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  0.0f,	//V3
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  1.0f,	//V7
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  1.0f,	//V6

		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.6f,  0.0f,	//V3 - Izquierda
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  0.0f,	//V0
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  1.0f,	//V4
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.6f,  1.0f,	//V7

		 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  0.0f,	//V1 - Derecha
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	0.6f,  0.0f,	//V2
		 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	0.6f,  1.0f,	//V6
		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  1.0f,	//V5		 

		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  0.0f,	//V4 - Superior
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  0.0f,	//V5
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  1.0f,	//V6
		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  1.0f,	//V7

		-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  0.0f,	//V0 - Inferior
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  0.0f,	//V1
		 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  1.0f,	//V2
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  1.0f,	//V3
		//	Cubo diferente Textura por lado
		-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.5015f,  0.6653f,	//V0 - Frontal
		 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.7497f,  0.6653f,	//V1
		 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.7497f,  0.3347f,	//V5
		-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.5015f,  0.3347f,	//V4

		 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0000f,  0.6653f,	//V2 - Trasera
		-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.2482f,  0.6653f,	//V3
		-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.2482f,  0.3347f,	//V7
		 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0000f,  0.3347f,	//V6

		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.2503f,  0.6653f,	//V3 - Izquierda
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	0.4985f,  0.6653f,	//V0
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	0.2503f,  0.3347f,	//V4
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.4985f,  0.3347f,	//V7

		 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.7518f,  0.6653f,	//V1 - Derecha
		 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0000f,  0.6653f,	//V2
		 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0000f,  0.3347f,	//V6
		 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.7518f,  0.3347f,	//V5		 

		-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.5015f,  0.3307f,	//V4 - Superior
		 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.7497f,  0.3307f,	//V5
		 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.7497f,  0.0000f,	//V6
		-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.5015f,  0.0000f,	//V7

		-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.5015f,  0.6693f,	//V0 - Inferior
		 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.7497f,  0.6693f,	//V1
		 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.7497f,  1.0000f,	//V2
		-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.5015f,  1.0000f,	//V3
		// PISO
		-0.5f,  0.0f,  0.5f,	 0.0f,  1.0f,  0.0f,	00.0f,  0.0f,	//V4 --Superior
		 0.5f,  0.0f,  0.5f,	 0.0f,  1.0f,  0.0f,	14.0f,  0.0f,	//V5
		 0.5f,  0.0f, -0.5f,	 0.0f,  1.0f,  0.0f,	14.0f,  14.0f,	//V6
		-0.5f,  0.0f, -0.5f,	 0.0f,  1.0f,  0.0f,	00.0f,  14.0f,	//V7
		// PISO LAMINA
		-0.5f,  0.0f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  0.0f,	//V4 --Superior
		 0.5f,  0.0f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  0.0f,	//V5
		 0.5f,  0.0f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  14.0f,	//V6
		-0.5f,  0.0f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  14.0f,	//V7

		// TECHO
		-0.5f,  0.0f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  0.0f,	//V0 - Inferior
		 0.5f,  0.0f,  0.5f,	 0.0f, -1.0f,  0.0f,	4.0f,  0.0f,	//V1
		 0.5f,  0.0f, -0.5f,	 0.0f, -1.0f,  0.0f,	4.0f,  4.0f,	//V2
		-0.5f,  0.0f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  4.0f,	//V3
		// PARED
		-0.5f, -0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	0.0f,  0.0f,	//V0 - Frontal
		 0.5f, -0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	1.0f,  0.0f,	//V1
		 0.5f,  0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	1.0f,  1.0f,	//V5
		-0.5f,  0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	0.0f,  1.0f,	//V4
		//PIZARRON
		-0.5f, -0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	0.0f,  0.0f,	//V0 - Frontal
		 0.5f, -0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	1.0f,  0.0f,	//V1
		 0.5f,  0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	1.0f,  1.0f,	//V5
		-0.5f,  0.5f,  0.0f,	 0.0f,  0.0f,  1.0f,	0.0f,  1.0f,	//V4
		//LAMPARAS
		-0.5f, 0.0f,  0.5f,		 0.0f, -1.0f,  0.0f,	0.0f,  0.0f,	//V0 - Inferior
		 0.5f, 0.0f,  0.5f,		 0.0f, -1.0f,  0.0f,	1.0f,  0.0f,	//V1
		 0.5f, 0.0f, -0.5f,		 0.0f, -1.0f,  0.0f,	1.0f,  1.0f,	//V2
		-0.5f, 0.0f, -0.5f,		 0.0f, -1.0f,  0.0f,	0.0f,  1.0f,	//V3
	};

	unsigned int indices[] = {
		//PISO
		72, 73, 75, // first triangle
		73, 74, 75,  // second triangle
		//PISO LAMINA
		76, 77, 79, // first triangle
		77, 78, 79,  // second triangle
		//TECHO
		80, 81, 83, // first triangle
		81, 82, 83,  // second triangle
		//PARED		
		84, 85, 87, // first triangle
		85, 86, 87,  // second triangle
		//PIZARRON
		88, 89, 91, // first triangle
		89, 90, 91,  // second triangle
		//LAMPARA
		92, 93, 95, // first triangle
		93, 94, 95,  // second triangle

	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}