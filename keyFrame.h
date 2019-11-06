#pragma once
//Keyframes
float	posX = 0.0f,
		posY = 0.0f,
		posZ = 0.0f,
		rotAvion = 0.0f;

float	incX = 0.0f,
		incY = 0.0f,
		incZ = 0.0f,
		rotInc = 0.0f;

int		abrirPuertaInc;

#define MAX_FRAMES 30
int i_max_steps = 90;
int i_curr_steps = 0;
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotAvion;
	int abrirPuerta;
	int frameIndex;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void){
	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;
	KeyFrame[FrameIndex].rotAvion = rotAvion;
	KeyFrame[FrameIndex].abrirPuerta = abrirPuerta;
	KeyFrame[FrameIndex].frameIndex = FrameIndex+1;
	FrameIndex++;
}

void resetElements(void){
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;
	rotAvion = KeyFrame[0].rotAvion;
	abrirPuerta = KeyFrame[0].abrirPuerta;
}

void interpolation(void)
{
	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	rotInc = (KeyFrame[playIndex + 1].rotAvion - KeyFrame[playIndex].rotAvion) / i_max_steps;
	abrirPuertaInc = KeyFrame[playIndex].abrirPuerta;
}

void saveFile(void) {
	KeyFrame[0].frameIndex = KeyFrame[FrameIndex-1].frameIndex;
	FILE *archivo;
	archivo = fopen("keyframe.txt", "wb+");
	if (archivo != NULL) {
		fwrite(KeyFrame, sizeof(KeyFrame), 1, archivo);
		fclose(archivo);
		printf("Archivo guardado\n");
	}
	else {
		printf("El archivo no existe o no se tiene permisos de lectura /escritura.\n");
	}
}


void openFile(void) {
	FILE *archivo;
	archivo = fopen("keyframe.txt", "rb");
	if (archivo != NULL) {
		fread(KeyFrame, sizeof(KeyFrame), 1, archivo);
		fclose(archivo);
		printf("Archivo cargado \n");
		FrameIndex = KeyFrame[0].frameIndex;
	}
	else {
		printf("El archivo no existe o no se tiene permisos de lectura /escritura.\n");
	}
}
/*
void mostrarDatos(void) {
	for (int i = 0; i < MAX_FRAMES; i++)
		printf("%d\n", KeyFrame[i].frameIndex);
	printf("no frame %d\n", FrameIndex);
}
*/