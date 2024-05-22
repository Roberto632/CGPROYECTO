
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminaci�n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

//para obtener el tiempo del sistema.
#include "time.h"

//Para archivos de audio
//#include<iostream>
//#include "../Externals/includes/irrKlang.h"
//
//using namespace irrklang;

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;

//parque la mexicana
Texture sueloMexicana;
Texture mosaicoSuelo;
Texture asfalto;
Texture mosaico;
Texture pisoSkate;


//modelos del universo de club penguin
//pizzeria
Model pizzeria;
Model doorP;
Model windowP;

//objetos de club penguin
Model pizza;
Model seat;
Model tableCP;
Model oven;
Model bar;

Model smoke; //está en la carpeta del horno

//outside
Model snow;

//puffles
Model puffleC;
Model puffleO;
Model puffleG;
Model puffleR;

//tirolesa
Model zipB;
Model zipC;
Model zipC1;

//arbol
Model tree;

//sensei
Model sensei;
Model beard;
Model wingL;
Model wingR;
Model lamp;
Model sign;
Model benchP;
Model jetpack;
Model jukebox;
Model skateparkC;
Model bush;
Model puffito;




//modelos del universo del gumball y elementos complementarios
Model Kitt_M;
Model Llanta_M;
Model Blackhawk_M;
Model Arbol_M;
Model Arbusto_M;
Model Juego1_M;
Model Juego2_M;
Model Juego31_M;
Model Juego32_M;
Model Juego33_M;
Model Juego34_M;
Model Puestos_M;
Model Darwin_M;
Model Flor_M;
Model Leslie_M;
Model Spider_M;
Model Light_M;
Model Car_M;
Model RF_M;
Model SkateG_M;
Model Vidrios_M;
Model Vidrios2_M;

//Variables Gumball
GLfloat may = 0.0f;
GLfloat max = 0.0f;
GLfloat mcx = 0.0f;
GLfloat mcz = 0.0f;
GLfloat rc = 0.0f;
GLfloat rotJuego = 0.0f;
GLfloat rotR = 0.0f;
glm::vec3 posic(-180.0f, 0.5f, -180.0f);
bool r1 = false;
bool r2 = false;
bool r3 = false;
bool r4 = false;
//<<<<<<< HEAD
//=======

//variables club penguin
GLfloat t1 = 0.0f;
GLfloat t2 = 0.0f;
GLfloat t3 = 0.0f;
GLfloat t4 = 0.0f;

GLfloat jpt1 = 0.0f;
GLfloat jpt2 = 0.0f;
GLfloat jpfs = 0.0f;
GLfloat jpr1 = 0.0f;

GLfloat smT = 0.0f;
GLfloat smT1 = 0.0f;
GLfloat smS = 0.0f;

GLfloat ar1 = 0.0f;
GLfloat pf1 = 0.0f;
GLfloat pf2 = 0.0f;

glm::vec3 posAv(0.0f, -2.0f, -10.0f);

//modelos del univero de phineas  ferb models
Model Inator_M;
Model EdiDodu_M;
Model House_M;
Model Banco_M;
Model Ballony_M;
Model Bambu_M;
//MODLEO AUTO PPHINEAS Y FERB
Model AutoCarcas_M;
Model llanaDD_M;
Model llanaDI_M;
Model llanaTD_M;
Model llanaTI_M;
Model ArbolFP_M;
Model PuenteFP_M;
Model CarritoPF_M;
Model LlantasPF_M;
Model poste_M;
Model lampara_M;
Model perry_M;
//variables para le movimiento auto
GLfloat moviemientoAutoPhineas;
GLfloat giroAutoPhienas;

GLfloat movimientoCajaMadera = 0.0f;
GLfloat movimientoCajaMaderaOffset = 0.3f;
GLfloat rotarLlantasCajaMadera = 0.0f;
GLfloat rotarLlantasCajaMaderaOffset = 5.0f;
bool avanzaCajaMadera = true;
//>>>>>>> 96256336d13de02933bd449444bf4c16d1a55335
Model nave_M;
GLfloat movimientoNave = 0.0f;
GLfloat movimientoNaveOffset = 0.7f;
GLfloat movimientoNaveAlto = 0.0f;
GLfloat movimientoNaveAltoOffset = 0.3f;
GLfloat rotarNave = 0.0f;
GLfloat rotarNaveOffset = 5.0f;
bool avanzarNave = true;

//skyboxs para cada perio del dia: dia, tarde, noche, amanecer
Skybox skyboxDia;
Skybox skyboxTarde;
Skybox skyboxNoche;
Skybox skyboxAmanecer;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

//variable para el tiempo, se utilizara para medir el tiempo de noche a dia de mejor manera
clock_t inicio, fin;
GLdouble periodoUso;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
PointLight pointLightsJ[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

SpotLight spotLightsInator[MAX_SPOT_LIGHTS];

//para las luciernagas
PointLight pointLightsLuciernagas[MAX_POINT_LIGHTS];
PointLight pointLightsLuciernagas1[MAX_POINT_LIGHTS];
PointLight pointLightsLuciernagas2[MAX_POINT_LIGHTS];
PointLight pointLightsLuciernagas3[MAX_POINT_LIGHTS];
PointLight pointLightsLuciernagas4[MAX_POINT_LIGHTS];
PointLight pointLightsLuciernagas5[MAX_POINT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//funci�n de calculo de normales por promedio de v�rtices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	/*C�mara se usa el comando: glm::lookAt(vector de posici�n, vector de orientaci�n, vector up));
	En la clase Camera se reciben 5 datos:
	glm::vec3 vector de posici�n,
	glm::vec3 vector up,
	GlFloat yaw rotaci�n para girar hacia la derecha e izquierda
	GlFloat pitch rotaci�n para inclinar hacia arriba y abajo
	GlFloat velocidad de desplazamiento,
	GlFloat velocidad de vuelta o de giro
	Se usa el Mouse y las teclas WASD y su posici�n inicial est� en 0,0,1 y ve hacia 0,0,-1.
	*/
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.9f, 0.5f);//0.9->0.3 velocidad de desplazamienot

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();


	//la mexicana textura de suelos
	sueloMexicana = Texture("Textures/sueloMexicana.tga");
	sueloMexicana.LoadTextureA();
	mosaicoSuelo = Texture("Textures/sueloMosaico.tga");
	mosaicoSuelo.LoadTextureA();
	asfalto = Texture("Textures/asfalto.tga");
	asfalto.LoadTextureA();
	mosaico = Texture("Textures/pisoBanio.tga");
	mosaico.LoadTextureA();
	pisoSkate = Texture("Textures/pisoSkate.tga");
	pisoSkate.LoadTextureA();


	//club penguin

	//pizzeria
	pizzeria = Model();
	pizzeria.LoadModel("Models/Daniel/pizzeria/pizzaParlor.obj");

	doorP = Model();
	doorP.LoadModel("Models/Daniel/pizzeria/doorP.obj");

	windowP = Model();
	windowP.LoadModel("Models/Daniel/pizzeria/windowP.obj");

	//objetos
	pizza = Model();
	pizza.LoadModel("Models/Daniel/pizza/pizza.obj");

	seat = Model();
	seat.LoadModel("Models/Daniel/seat/seat.obj");

	tableCP = Model();
	tableCP.LoadModel("Models/Daniel/table/table.obj");

	oven = Model();
	oven.LoadModel("Models/Daniel/oven/oven.obj");

	bar = Model();
	bar.LoadModel("Models/Daniel/bar/bar.obj");

	//outside
	snow = Model();
	snow.LoadModel("Models/Daniel/snow/snow.obj");

	//puffles
	puffleC = Model();
	puffleC.LoadModel("Models/Daniel/puffle/puffleC.obj");

	puffleG = Model();
	puffleG.LoadModel("Models/Daniel/puffle/puffleG.obj");

	puffleO = Model();
	puffleO.LoadModel("Models/Daniel/puffle/puffleO.obj");

	puffleR = Model();
	puffleR.LoadModel("Models/Daniel/puffle/puffleR.obj");

	//tirolesa
	zipB = Model();
	zipB.LoadModel("Models/Daniel/zip/zipB.obj");

	zipC = Model();
	zipC.LoadModel("Models/Daniel/zip/zipC.obj");

	zipC1 = Model();
	zipC1.LoadModel("Models/Daniel/zip/zipC1.obj");

	//arbol
	tree = Model();
	tree.LoadModel("Models/Daniel/tree/tree.obj");

	//avatar
	sensei = Model();
	sensei.LoadModel("Models/Daniel/sensei/bodyS.obj");

	beard = Model();
	beard.LoadModel("Models/Daniel/sensei/beardS.obj");

	wingL = Model();
	wingL.LoadModel("Models/Daniel/sensei/wingLS.obj");

	wingR = Model();
	wingR.LoadModel("Models/Daniel/sensei/wingRS.obj");

	//luminaria
	lamp = Model();
	lamp.LoadModel("Models/Daniel/lamp/lampCP.obj");

	//letrero
	sign = Model();
	sign.LoadModel("Models/Daniel/sign/sign.obj");

	benchP = Model();
	benchP.LoadModel("Models/Daniel/parkBench/benchP.obj");

	jetpack = Model();
	jetpack.LoadModel("Models/Daniel/jetpack/jetpack.obj");

	smoke = Model();
	smoke.LoadModel("Models/Daniel/oven/smoke.obj");

	jukebox = Model();
	jukebox.LoadModel("Models/Daniel/jukebox/jukebox.obj");

	skateparkC = Model();
	skateparkC.LoadModel("Models/Daniel/skatepark/skatepark.obj");

	bush = Model();
	bush.LoadModel("Models/Daniel/bush/bush.obj");

	puffito = Model();
	puffito.LoadModel("Models/Daniel/bush/puffito.obj");


	//----- end club penguin univrse -----



	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");

	//Modelos Gumball
	Arbol_M = Model();
	Arbol_M.LoadModel("Models/Alberto/arbol.obj");
	Arbusto_M = Model();
	Arbusto_M.LoadModel("Models/Alberto/arbusto.obj");
	Juego1_M = Model();
	Juego1_M.LoadModel("Models/Alberto/Juego1.obj");
	Juego2_M = Model();
	Juego2_M.LoadModel("Models/Alberto/Juego2.obj");
	Juego31_M = Model();
	Juego31_M.LoadModel("Models/Alberto/Juego31.obj");
	Juego32_M = Model();
	Juego32_M.LoadModel("Models/Alberto/Juego32.obj");
	Juego33_M = Model();
	Juego33_M.LoadModel("Models/Alberto/Juego33.obj");
	Juego34_M = Model();
	Juego34_M.LoadModel("Models/Alberto/Juego34.obj");

	Puestos_M = Model();
	Puestos_M.LoadModel("Models/Alberto/puestos.obj");

	Darwin_M = Model();
	Darwin_M.LoadModel("Models/Alberto/darwin.obj");

	Flor_M = Model();
	Flor_M.LoadModel("Models/Alberto/flor.obj");

	Leslie_M = Model();
	Leslie_M.LoadModel("Models/Alberto/leslie.obj");

	Spider_M = Model();
	Spider_M.LoadModel("Models/Alberto/spider.obj");

	Light_M = Model();
	Light_M.LoadModel("Models/Alberto/light.obj");

	Car_M = Model();
	Car_M.LoadModel("Models/Alberto/car.obj");

	RF_M = Model();
	RF_M.LoadModel("Models/Alberto/rf.obj");

	SkateG_M = Model();
	SkateG_M.LoadModel("Models/Alberto/SkateP.obj");

	Vidrios_M = Model();
	Vidrios_M.LoadModel("Models/Alberto/Cristales.obj");

	Vidrios2_M = Model();
	Vidrios2_M.LoadModel("Models/Alberto/Cristales2.obj");

	//modelos del univero de phineas y ferb 
	Inator_M = Model();
	Inator_M.LoadModel("Models/Roberto/inator.obj");

	EdiDodu_M = Model();
	EdiDodu_M.LoadModel("Models/Roberto/EdoDufusFinal.obj");

	House_M = Model();
	House_M.LoadModel("Models/Roberto/casaFinal2PhienasFerb.obj");

	Banco_M = Model();
	Banco_M.LoadModel("Models/Roberto/bancoText.obj");

	Ballony_M = Model();
	Ballony_M.LoadModel("Models/Roberto/ballonyFinal.obj");

	Bambu_M = Model();
	Bambu_M.LoadModel("Models/Roberto/bambufinal.obj");


	AutoCarcas_M = Model();
	AutoCarcas_M.LoadModel("Models/Roberto/autoCarcasaPF.obj");

	llanaDD_M = Model();
	llanaDD_M.LoadModel("Models/Roberto/llanataDD.obj");

	llanaTD_M = Model();
	llanaTD_M.LoadModel("Models/Roberto/llanataTD.obj");

	llanaDI_M = Model();
	llanaDI_M.LoadModel("Models/Roberto/llantaID.obj");

	llanaTI_M = Model();
	llanaTI_M.LoadModel("Models/Roberto/llanataTI.obj");


	poste_M = Model();
	poste_M.LoadModel("Models/Roberto/postePF.obj");

	ArbolFP_M = Model();
	ArbolFP_M.LoadModel("Models/Roberto/arbolFinal.obj");

	PuenteFP_M = Model();
	PuenteFP_M.LoadModel("Models/Roberto/aPuenteF.obj");


	CarritoPF_M = Model();
	CarritoPF_M.LoadModel("Models/Roberto/CajaFP.obj");

	LlantasPF_M = Model();
	LlantasPF_M.LoadModel("Models/Roberto/LlantaPF.obj");

	lampara_M = Model();
	lampara_M.LoadModel("Models/Roberto/lamparaTextura.obj");

	perry_M = Model();
	perry_M.LoadModel("Models/Roberto/PERRYFINAL.obj");


	nave_M = Model();
	nave_M.LoadModel("Models/Roberto/NavePF.obj");
	//se cargan nuestras skybox
	//dia
	std::vector<std::string> skyboxFacesDia;

	skyboxFacesDia.push_back("Textures/Skybox/rightDia.tga");
	skyboxFacesDia.push_back("Textures/Skybox/leftDia.tga");
	skyboxFacesDia.push_back("Textures/Skybox/downDia.tga");
	skyboxFacesDia.push_back("Textures/Skybox/upDia.tga");
	skyboxFacesDia.push_back("Textures/Skybox/backDia.tga");
	skyboxFacesDia.push_back("Textures/Skybox/frontDia.tga");

	skyboxDia = Skybox(skyboxFacesDia);

	//tarde
	std::vector<std::string> skyboxFacesTarde;

	skyboxFacesTarde.push_back("Textures/Skybox/rightAtardecer.tga");
	skyboxFacesTarde.push_back("Textures/Skybox/leftAtardecer.tga");
	skyboxFacesTarde.push_back("Textures/Skybox/downTarde.tga");
	skyboxFacesTarde.push_back("Textures/Skybox/upAtardecer.tga");
	skyboxFacesTarde.push_back("Textures/Skybox/backAtardecer.tga");
	skyboxFacesTarde.push_back("Textures/Skybox/frontAtardecer.tga");

	skyboxTarde = Skybox(skyboxFacesTarde);

	//noche
	std::vector<std::string> skyboxFacesNoche;

	skyboxFacesNoche.push_back("Textures/Skybox/rightNoche.tga");
	skyboxFacesNoche.push_back("Textures/Skybox/leftNoche.tga");
	skyboxFacesNoche.push_back("Textures/Skybox/downNoche.tga");
	skyboxFacesNoche.push_back("Textures/Skybox/upNoche.tga");
	skyboxFacesNoche.push_back("Textures/Skybox/backNoche.tga");
	skyboxFacesNoche.push_back("Textures/Skybox/frontNoche.tga");

	skyboxNoche = Skybox(skyboxFacesNoche);

	//amanecer
	std::vector<std::string> skyboxFacesAmanecer;

	skyboxFacesAmanecer.push_back("Textures/Skybox/rightAmanecer.tga");
	skyboxFacesAmanecer.push_back("Textures/Skybox/leftAmancer.tga");
	skyboxFacesAmanecer.push_back("Textures/Skybox/downAmanecer.tga");
	skyboxFacesAmanecer.push_back("Textures/Skybox/upAmanecer.tga");
	skyboxFacesAmanecer.push_back("Textures/Skybox/backAmanecer.tga");
	skyboxFacesAmanecer.push_back("Textures/Skybox/frontAmanecer.tga");

	skyboxAmanecer = Skybox(skyboxFacesAmanecer);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaraci�n de primer luz puntual
	//luz luminaria club penguin
	pointLights[0] = PointLight(1.0f, 1.0f, 0.0f,
		1.0f, 1.0f,
		-300.0f, 35.0f, 320.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int pointLightCountJ = 0;
	//luz jetpack
	pointLights[1] = PointLight(1.0f, 0.0f, 0.0f,
		1.0f, 2.0f,
		-118.0f, 5.0f, 95.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(1.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		-50.0f, 10.5f, -200.0f,
		5.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		30.0f);
	spotLightCount++;

	spotLights[2] = SpotLight(1.0f, 1.0f, 1.0f,  //Color
		1.0f, 2.0f,
		135.0f, 40.0f, 258.0, //Posición
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,  //limite
		30.0f); //Angulo
	spotLightCount++;

	spotLights[3] = SpotLight(1.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		-50.0f, 10.5f, -200.0f,
		5.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		30.0f);
	spotLightCount++;

	//se crean mas luces puntuales y spotlight 
	unsigned int spotLightCountInator = 0;
	//linterna
	spotLightsInator[0] = SpotLight(0.0f, 1.0f, 1.0f, //color
		1.0f, 2.0f,
		0.0f, 0.0f, 0.0f,//posición de la luz
		1.0f, 0.65f, 0.0f,//direccion
		0.1f, 0.0f, 0.0f, //para limitar
		20.0f); //apertura 
	spotLightCountInator++;

	//contador de luces puntuales
	unsigned int pointLightCountLuciernagas = 0;
	//Declaración de primer luz puntual
	pointLightsLuciernagas[0] = PointLight(1.0f, 1.0f, 1.0f,
		0.9f, 0.9f,//0.0f, 1.0f
		0.0f, 0.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCountLuciernagas++;


	unsigned int pointLightCountLuciernagas1 = 0;
	//Declaración de primer luz puntual
	pointLightsLuciernagas1[0] = PointLight(1.0f, 1.0f, 1.0f,
		0.9f, 0.9f,//0.0f, 1.0f
		0.0f, 0.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCountLuciernagas1++;

	unsigned int pointLightCountLuciernagas2 = 0;
	//Declaración de primer luz puntual
	pointLightsLuciernagas2[0] = PointLight(1.0f, 1.0f, 1.0f,
		0.9f, 0.9f,//0.0f, 1.0f
		0.0f, 0.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCountLuciernagas2++;

	unsigned int pointLightCountLuciernagas3 = 0;
	//Declaración de primer luz puntual
	pointLightsLuciernagas3[0] = PointLight(1.0f, 1.0f, 1.0f,
		0.9f, 0.9f,//0.0f, 1.0f
		0.0f, 0.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCountLuciernagas3++;

	unsigned int pointLightCountLuciernagas4 = 0;
	//Declaración de primer luz puntual
	pointLightsLuciernagas4[0] = PointLight(1.0f, 1.0f, 1.0f,
		0.9f, 0.9f,//0.0f, 1.0f
		0.0f, 0.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCountLuciernagas4++;

	unsigned int pointLightCountLuciernagas5 = 0;
	//Declaración de primer luz puntual
	pointLightsLuciernagas5[0] = PointLight(1.0f, 1.0f, 1.0f,
		0.9f, 0.9f,//0.0f, 1.0f
		0.0f, 0.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCountLuciernagas5++;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana

	//Audio
	//ISoundEngine* engine = createIrrKlangDevice();


	//obtener el tiempo de incio
	inicio = clock();
	while (!mainWindow.getShouldClose())
	{
		//engine->play2D("media/TheHappySong.mp3", true);

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//comentamos esta para ver que desaparece el skybox
		//ademas implementamos lo de la tarde 

		//PARA DAR LA ILUCION DE TIEMPO DIA A NOCHE
		// por el momento solo esta a 5 segundos para comprobar que funcione de manmera adecuada 
		if (periodoUso <= 75.0) {
			skyboxDia.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else if (periodoUso <= 150.0) {
			skyboxTarde.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else if (periodoUso <= 225.0) {
			skyboxNoche.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else if (periodoUso <= 300.0) {
			skyboxAmanecer.DrawSkybox(camera.calculateViewMatrix(), projection);
		}

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la c�mara de tipo flash
		//sirve para que en tiempo de ejecuci�n (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);


		//Animaciones Gumball
		//Animaci�n Ara�a
		if (mainWindow.getmovArana()) {
			may = abs(3 * sin(3*glfwGetTime()));
			if (max < 60.0) {
				max += 0.0005 * glfwGetTime();
			}
			else {
				max = 0.0;
			}
		}
		else {
			may = 0.0f;
			max = 0.0f;
		}

		//Animaci�n Carro
		if (mainWindow.getr1()) {
			rotR += 0.1 * glfwGetTime();
			if (mcz < 500.0) {
				mcz += 0.005 * glfwGetTime();
				mcx += 0.0075 * glfwGetTime();
			}
			else {
				mcz = 0.0;
				mcx = 0.0;
			}
		}

		if (mainWindow.getjuego()) {

			rotJuego += 0.001 * glfwGetTime();
		}

		//animacion tirolesa
		if (mainWindow.movTP()) {
			if (t1 < 75.0) {
				t1 += 0.001 * glfwGetTime();
				t2 -= 0.00035 * glfwGetTime();
			}
			else {
				t1 = 0.0;
				t2 = 0.0;
			}
		}
		if (mainWindow.movTB()) {
			if (t3 < 75.0) {
				t3 += 0.001 * glfwGetTime();
				t4 -= 0.00035 * glfwGetTime();
			}
			else {
				t3 = 0.0;
				t4 = 0.0;
			}
		}
		//animacion jetpack
		if (mainWindow.animJP()) {

			r1 = true;
		}
		if (r1) {
			jpt1 += 0.005 * glfwGetTime();
			smS = 5.0;
			smT = 0.0;
			smT1 = 0.0;
			if (jpt1 > 70.0) {
				r2 = true;
				r1 = false;
			}
		}
		if (r2) {
			jpt2 += 0.0025 * glfwGetTime();
			jpt1 = 70.0;
			jpfs = 7*sin(6*glfwGetTime());
			jpr1 = -90.0;
			smT = 4.0;
			smT1 = 3.0;
			if (jpt2 > 300.0) {
				r2 = false;
				r1 = true;
				jpt1 = 0.0f;
				jpt2 = 0.0f;
				jpr1 = 0.0f;
			}
		}

		if (mainWindow.animAr()) {

			//ar1 = 2 * sin(15 * glfwGetTime());
			
			if (pf1 < 6.0) {
				ar1 = 2 * sin(15 * glfwGetTime());
				pf1 += 0.0005 * glfwGetTime();
			}
			else {
				pf1 = 0.0;
				ar1 = 0.0;
			}
		}
		



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		//pasto la mexicana
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(70.0f, 1.0f, 50.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		sueloMexicana.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//suelo mosaico la mexicana 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -470.0f));
		model = glm::scale(model, glm::vec3(70.0f, 1.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		mosaicoSuelo.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//asfalto 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -380.0f));
		model = glm::scale(model, glm::vec3(70.0f, 1.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		asfalto.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//asfalto 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -260.0f));
		model = glm::scale(model, glm::vec3(70.0f, 1.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		asfalto.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//asfalto 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(670.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		asfalto.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//asfalto 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-670.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		asfalto.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();


		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(200.0f, 0.0f, -110.0f));
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 7.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(401.0f, 0.0f, -110.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 7.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(403.0f, 0.0f, -110.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 7.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(405.0f, 0.0f, -110.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 6.9f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(407.0f, 0.0f, -110.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 6.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(409.0f, 0.0f, -110.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 6.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(411.0f, 0.0f, -110.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 5.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 9.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-401.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 8.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-403.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 8.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-405.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 8.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-407.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 8.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();


		////////////////////////////////
		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-409.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-411.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 7.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-413.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 7.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-415.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 7.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-417.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 7.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-419.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 6.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();


		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-421.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 6.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();


		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-423.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 6.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-425.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 5.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-427.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 5.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-429.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 4.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso skatepark 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-431.0f, 0.0f, -95.0f));
		model = glm::scale(model, glm::vec3(0.1f, 1.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoSkate.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//piso baño 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(500.0f, 0.0f, 400.0f));
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		mosaico.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		
		//�rboles Gumball
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(45.0f, -0.15f, 45.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(20.0f, -0.15f, 10.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(30.0f, -0.15f, 20.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.15f, 40.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(40.0f, -0.15f, 0.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(35.0f, -0.15f, 15.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(25.0f, -0.15f, 30.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(45.0f, -0.15f, 35.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(15.0f, -0.15f, 15.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(5.0f, -0.15f, 25.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(10.0f, -0.15f, 33.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(5.0f, -0.15f, 5.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(12.0f, -0.15f, 13.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(18.0f, -0.15f, 3.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(3.0f, -0.15f, 1.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(33.0f, -0.15f, 23.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(8.0f, -0.15f, 8.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(5.0f, -0.15f, 35.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(25.0f, -0.15f, 14.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(10.0f, -0.15f, 29.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(12.0f, -0.15f, 22.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.15f, 25.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.15f, 19.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(1.0f, -0.15f, 14.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.15f, 10.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(5.0f, -0.15f, 21.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(33.0f, -0.15f, 10.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(39.0f, -0.15f, 19.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(35.0f, -0.15f, 30.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 7.0f, 6.0f));
		model = glm::translate(model, glm::vec3(41.0f, -0.15f, 23.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_M.RenderModel();






		//Arbustos Gumball
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(50.0f, -0.3f, 5.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(20.0f, -0.3f, 5.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(60.0f, -0.3f, 5.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(10.0f, -0.3f, 5.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(5.0f, -0.3f, 10.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(15.0f, -0.3f, 12.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(26.0f, -0.3f, 8.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(37.0f, -0.3f, 13.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(48.0f, -0.3f, 10.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(8.0f, -0.3f, 20.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(13.0f, -0.3f, 23.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(20.0f, -0.3f, 18.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(30.0f, -0.3f, 21.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(48.0f, -0.3f, 25.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(1.0f, -0.3f, 29.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(18.0f, -0.3f, 30.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(30.0f, -0.3f, 33.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(48.0f, -0.3f, 31.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(55.0f, -0.3f, 32.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(3.0f, -0.3f, 42.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(18.0f, -0.3f, 45.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(27.0f, -0.3f, 46.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(35.0f, -0.3f, 43.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(50.0f, -0.3f, 44.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbusto_M.RenderModel();





		//Juegos
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		model = glm::translate(model, glm::vec3(45.0f, -0.3f, 45.0));
		model = glm::rotate(model, glm::radians(rotJuego), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Juego1_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::translate(model, glm::vec3(50.0f, -0.3f, 35.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Juego2_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(25.0f, 2.9f, 30.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Juego31_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(25.0f, 2.9f, 30.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Juego32_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(25.0f, 2.9f, 30.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Juego33_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(25.0f, 2.9f, 30.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Juego34_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-30.0f, -2.5f, -45.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puestos_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-30.0f, -2.5f, -45.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Vidrios_M.RenderModel();
		glDisable(GL_BLEND);

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-30.0f, -2.5f, -45.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Vidrios2_M.RenderModel();
		glDisable(GL_BLEND);


		//Flores
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(5.0f, -1.21f, 10.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(10.0f, -1.21f, 12.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(15.0f, -1.21f, 13.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(20.0f, -1.21f, 9.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(25.0f, -1.21f, 11.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(37.0f, -1.21f, 9.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(45.0f, -1.21f, 12.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(50.0f, -1.21f, 10.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(3.0f, -1.21f, 23.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(8.0f, -1.21f, 22.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(15.0f, -1.21f, 25.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(25.0f, -1.21f, 24.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(35.0f, -1.21f, 21.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(40.0f, -1.21f, 26.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(55.0f, -1.21f, 27.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(1.0f, -1.21f, 34.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(8.0f, -1.21f, 35.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(16.0f, -1.21f, 37.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(28.0f, -1.21f, 38.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(33.0f, -1.21f, 40.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(46.0f, -1.21f, 34.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::translate(model, glm::vec3(54.0f, -1.21f, 36.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Flor_M.RenderModel();



		//Lights
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::translate(model, glm::vec3(42.0f, -0.15f, 43.0));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Light_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::translate(model, glm::vec3(18.0f, -0.15f, 43.0));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Light_M.RenderModel();

		//Personajes
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::translate(model, glm::vec3(20.0f, 0.7f, 30.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Darwin_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::translate(model, glm::vec3(50.0f, 1.2f, 35.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Leslie_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::translate(model, glm::vec3(57.0f + max, 0.2f + may, 117.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Spider_M.RenderModel();
		
		//Carro
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.5f, 2.0f, 2.0f));
		model = glm::translate(model, posic + glm::vec3(mcz, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		spotLights[1].SetPos(glm::vec3(-260.0 + mcx, 4.0f, -357.0f));
		spotLights[3].SetPos(glm::vec3(-260.0 + mcx, 4.0f, -363.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Car_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.5f, 2.0f, 2.0f));
		model = glm::translate(model, glm::vec3(-180.0f + mcz, 0.5f, -177.5f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotR), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RF_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.5f, 2.0f, 2.0f));
		model = glm::translate(model, glm::vec3(-187.0f + mcz, 0.5f, -177.5f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotR), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RF_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.5f, 2.0f, 2.0f));
		model = glm::translate(model, glm::vec3(-180.0f + mcz, 0.5f, -182.5f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotR), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RF_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.5f, 2.0f, 2.0f));
		model = glm::translate(model, glm::vec3(-187.0f + mcz, 0.5f, -182.5f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotR), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RF_M.RenderModel();

		//Skatepart
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::translate(model, glm::vec3(25, -0.1f, -10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SkateG_M.RenderModel();
		
		//---------- Universo de Club Penguin O> ----------//

		//pizzeria
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-350.0f, 0.0f, 350.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pizzeria.RenderModel();

		//ventana1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-325.5f, 7.0f, 322.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		windowP.RenderModel();
		glDisable(GL_BLEND);

		//ventana2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-374.5f, 7.0f, 322.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		windowP.RenderModel();
		glDisable(GL_BLEND);

		//ventana3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-374.5f, 7.0f, 378.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		windowP.RenderModel();
		glDisable(GL_BLEND);

		//ventana4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-350.0f, 7.0f, 378.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		windowP.RenderModel();
		glDisable(GL_BLEND);

		//ventana5
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-325.5f, 7.1f, 378.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		windowP.RenderModel();
		glDisable(GL_BLEND);

		//puerta1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-361.5f, 1.75f, 323.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		doorP.RenderModel();
		glDisable(GL_BLEND);

		//puerta2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-338.5f, 1.75f, 323.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		doorP.RenderModel();
		glDisable(GL_BLEND);

		//pizza
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-335.0f, 10.5f, 367.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pizza.RenderModel();

		//mesa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-335.0f, 2.0f, 367.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tableCP.RenderModel();

		//butacas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-324.0f, 2.0f, 367.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		seat.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-346.0f, 2.0f, 367.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		seat.RenderModel();

		//horno
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-376.0f, 2.0f, 350.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		oven.RenderModel();

		//barra
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-360.0f, 2.0f, 345.0f));
		model = glm::scale(model, glm::vec3(12.0f, 13.0f, 12.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bar.RenderModel();

		//snow
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-350.0f, 0.0f, 240.0f));
		model = glm::scale(model, glm::vec3(27.0f, 0.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		snow.RenderModel();

		//puffles
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-245.0f, -0.5f, 100.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puffleC.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250.0f, -0.5f, 90.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puffleG.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250.0f, -0.5f, 80.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puffleO.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-245.0f, -0.5f, 70.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puffleR.RenderModel();

		//tirolesa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, 0.0f, 60.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		zipB.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f + t1, 0.0f + t2, 60.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		zipC.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f + t3, 0.0f + t4, 60.0f));
		model = glm::scale(model, glm::vec3(12.0f, 12.0f, 12.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		zipC1.RenderModel();

		//outside

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.0f, 0.0f, 320.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lamp.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, 0.0f, 20.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sign.RenderModel();

		//bancas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-500.0f, 0.0f, 190.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		benchP.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 0.0f, 200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		benchP.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-370.0f, 0.0f, 90.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		benchP.RenderModel();
		//end bancas

		//jetpack
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f - jpt2, 0.0f + jpt1 + jpfs, 100.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(jpr1), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		jetpack.RenderModel();

		pointLights[1].setPosition(-120.0f - jpt2, -1.0f + jpt1 + jpfs, 100.0f);

		//humo1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-118.0f - jpt2 + smT1, -5.0f + jpt1 + jpfs + smT, 98.0f));
		model = glm::scale(model, glm::vec3(0.0f + smS, 0.0f + smS, 0.0f + smS));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(jpr1), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		smoke.RenderModel();

		//humo2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-118.0f - jpt2 + smT1, -5.0f + jpt1 + jpfs + smT, 102.0f));
		model = glm::scale(model, glm::vec3(0.0f + smS, 0.0f + smS, 0.0f + smS));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(jpr1), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		smoke.RenderModel();

		//rockola
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-400.0f, 0.0f, 90.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		jukebox.RenderModel();

		//skatepark
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -80.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		skateparkC.RenderModel();

		//arbustos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 0.0f, 35.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bush.RenderModel();

		//arbustos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 0.0f, 85.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bush.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-400.0f, 0.0f, 20.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(ar1), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		bush.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-400.0f, 0.0f, 20.0f));
		model = glm::scale(model, glm::vec3(pf1, pf1, pf1));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puffito.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-405.0f, 3.0f, 20.0f));
		model = glm::scale(model, glm::vec3(pf1, pf1, pf1));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puffito.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-395.0f, 2.0f, 20.0f));
		model = glm::scale(model, glm::vec3(pf1, pf1, pf1));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puffito.RenderModel();

		//forest club penguin	

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-600.0f, -1.0f, 20.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-600.0f, -1.0f, 450.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-500.0f, -1.0f, 450.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-400.0f, -1.0f, 450.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.0f, -1.0f, 450.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, -1.0f, 450.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, -1.0f, 450.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, -1.0f, 200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-189.0f, -1.0f, 341.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-460.0f, -1.0f, 359.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-410.0f, -1.0f, 215.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-450.0f, -1.0f, 182.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-380.0f, -1.0f, 252.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-403.0f, -1.0f, 50.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-210.0f, -1.0f, 270.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-500.0f, -1.0f, 120.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-400.0f, -1.0f, 300.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-606.0f, -1.0f, 290.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-450.0f, -1.0f, 202.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, -1.0f, 210.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-600.0f, -1.0f, 380.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-600.0f, -1.0f, 335.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-550.0f, -1.0f, 380.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, -1.0f, 240.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-220.0f, -1.0f, 308.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250.0f, -1.0f, 200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.0f, -1.0f, 230.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, -1.0f, 308.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, -1.0f, 248.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		//sensei
		model = glm::mat4(1.0);
		model = glm::translate(model, posAv + camera.getCameraDirection() + camera.getCameraPosition());
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sensei.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, posAv + camera.getCameraDirection() + camera.getCameraPosition());
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		beard.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, posAv + camera.getCameraDirection() + camera.getCameraPosition());
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		wingL.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, posAv + camera.getCameraDirection() + camera.getCameraPosition());
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		wingR.RenderModel();
		
		///////////////////////////////////////////Univero de phienas y ferb/////////////////////////////////////////////////////////////////////
		
		//movimeinto automovil

		//Auto
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(650.0f, 0.0f, -395.0f));
		model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AutoCarcas_M.RenderModel();

		//llanata delantare derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-5.0f, 1.8f, 10.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanaDD_M.RenderModel();

		//llantta delanntera izquiera
		model = modelaux;
		model = glm::translate(model, glm::vec3(5.0f, 1.8f, 10.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanaDI_M.RenderModel();

		//llanta trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-5.0f, 1.8f, -6.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanaTD_M.RenderModel();

		//llanta trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(5.0f, 1.8f, -6.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanaTI_M.RenderModel();

		//////////////////////////////////////////////////////////////////////////////


		if (avanzarNave) {
			if (movimientoNave >= -633.0f) {
				movimientoNave -= movimientoNaveOffset * deltaTime;
				rotarNave += rotarNaveOffset * deltaTime;
			}
			else {
				avanzarNave = !avanzarNave;
			}
		}
		else {
			if (movimientoNave <= 233.0f) {

				movimientoNave += movimientoNaveOffset * deltaTime;
				rotarNave += rotarNaveOffset * deltaTime;
			}
			else {
				avanzarNave = !avanzarNave;
			}
		}

		//nave
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(400.0f, 100.0f, -400.0f));
		model = glm::translate(model, glm::vec3(movimientoNave, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotarLlantasCajaMadera * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		nave_M.RenderModel();

		

		if (avanzaCajaMadera) {
			if (movimientoCajaMadera >= -433.0f) {
				movimientoCajaMadera -= movimientoCajaMaderaOffset * deltaTime;
				rotarLlantasCajaMadera -= rotarLlantasCajaMaderaOffset * deltaTime;
			}
			else {
				avanzaCajaMadera = !avanzaCajaMadera;
			}
		}
		else {
			if (movimientoCajaMadera < -230) {

				movimientoCajaMadera += movimientoCajaMaderaOffset * deltaTime;
				rotarLlantasCajaMadera += rotarLlantasCajaMaderaOffset * deltaTime;//para que no giren las llantas
			}
			else {
				avanzaCajaMadera = !avanzaCajaMadera;
			}
		}

		//CARRITO DE MADERA 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-499.7f, 96.0f, movimientoCajaMadera));//-433   230
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.12f, 0.1f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CarritoPF_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(2.7f, -0.05f, 3.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, rotarLlantasCajaMadera * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantasPF_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.7f, -0.05f, 3.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, rotarLlantasCajaMadera * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantasPF_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(2.7f, -0.05f, -3.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, rotarLlantasCajaMadera * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantasPF_M.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.7f, -0.05f, -3.0f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		model = glm::rotate(model, rotarLlantasCajaMadera * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantasPF_M.RenderModel();

		if (avanzarNave) {
			if (movimientoNave >= -633.0f) {
				movimientoNave -= movimientoNaveOffset * deltaTime;
				rotarNave += rotarNaveOffset * deltaTime;
			}
			else {
				avanzarNave = !avanzarNave;
			}
		}
		else {
			if (movimientoNave <= 233.0f) {

				movimientoNave += movimientoNaveOffset * deltaTime;
				rotarNave += rotarNaveOffset * deltaTime;
			}
			else {
				avanzarNave = !avanzarNave;
			}
		}

		//nave
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(400.0f, 100.0f, -400.0f));
		model = glm::translate(model, glm::vec3(movimientoNave, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotarLlantasCajaMadera * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		nave_M.RenderModel();
		//////////////////////////////////////////////////////////////////////////////

		//edificio
		//YA TIENE LA CAPACIDAD D MOSTRAR LA TRANSPARENCIA DE LOS CRISTALES 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-385.0f, 2.0f, -485.0f));
		model = glm::scale(model, glm::vec3(15.0f, 20.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		EdiDodu_M.RenderModel();
		glDisable(GL_BLEND);

		//casa
		//YA TIENE LA CAPACIDAD D MOSTRAR LA TRANSPARENCIA DE LOS CRISTALES 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(75.0f, -14.5f, -480.0f));
		//model = glm::rotate(model, glm::radians(-165.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		House_M.RenderModel();
		glDisable(GL_BLEND);

		//ballony
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-360.0f, 1.0f, -485.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ballony_M.RenderModel();

		//invento
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(480.0f, 1.0f, -100.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Inator_M.RenderModel();

		if (mainWindow.getApagarIna() == 1.0f) {
			spotLightsInator[0].SetPos(glm::vec3(490.0f, 43.0f, -98.0f));
			shaderList[0].SetSpotLights(spotLightsInator, spotLightCountInator);
		}
		else {
			shaderList[0].SetSpotLights(spotLightsInator, spotLightCountInator - 1);
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
		}

		//Banco de parque
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(480.0f, -2.0f, -50.0f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		//Banco de parque
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(540.0f, -2.0f, -100.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		//Banco de parque
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(420.0f, -2.0f, -100.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		//Banco de parque
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(480.0f, -2.0f, -150.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();


		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(600.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(550.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(500.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(450.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(400.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(350.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(300.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();


		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(250.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(200.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();


		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();



		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-600.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-550.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-500.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-450.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-400.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-350.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();


		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();


		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();

		//ARBOL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, -320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ArbolFP_M.RenderModel();


		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(460.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(490.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();


		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(520.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();


		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(550.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();


		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(580.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(610.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(640.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(670.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//////////////////

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(580.0f, 0.0f, -150.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(610.0f, 0.0f, -150.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(640.0f, 0.0f, -150.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(670.0f, 0.0f, -150.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//////////////////

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(580.0f, 0.0f, -100.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(610.0f, 0.0f, -100.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(640.0f, 0.0f, -100.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(670.0f, 0.0f, -100.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//////////////////

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(580.0f, 0.0f, -50.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(610.0f, 0.0f, -50.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(640.0f, 0.0f, -50.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//bambu
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(670.0f, 0.0f, -50.0f));
		model = glm::scale(model, glm::vec3(11.0f, 11.0f, 11.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bambu_M.RenderModel();

		//puente
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-500.0f, -2.0f, -300.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PuenteFP_M.RenderModel();

		////////////////////////////////////////////////////////////////////////////////////////
		
		//poste
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 31.0f, -500.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		poste_M.RenderModel();

		//poste
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-240.0f, 31.0f, -500.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		poste_M.RenderModel();

		//poste
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-380.0f, 31.0f, -500.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		poste_M.RenderModel();


		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(400.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();

		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(350.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();

		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(300.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();

		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(250.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();


		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(200.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();

		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();

		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();


		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(50.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();


		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();
		/////


		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-400.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();

		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-350.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();

		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-300.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();

		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();


		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-200.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();

		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();

		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();


		//lampara
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 0.0f, -200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lampara_M.RenderModel();

		//perry
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(400.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		perry_M.RenderModel();

		//////////////////////////////////////////////////////////////////////////////////////
		
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		
		//Agave �qu� sucede si lo renderizan antes del coche y el helic�ptero?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();
		glDisable(GL_BLEND);


		//pero necesitammos realizar un reset al periodo de uso para poder realizar un cambio entre
		//dia, tarde, noche, amanecer
		if (periodoUso <= 300.0) {
			fin = clock();
			periodoUso = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
			//para vererificar que si se realiza el reset de manera adecuada
			//printf("\nPeriodo usado del cpu %f segundos", periodoUso);
		}
		else {
			inicio = clock();
			periodoUso = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
		}


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}