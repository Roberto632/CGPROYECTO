
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
Model pizzeria;
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

//lamp
Model lamp;

//sign
Model sign;


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
//variables para le movimiento auto
GLfloat moviemientoAutoPhineas;
GLfloat giroAutoPhienas;
//>>>>>>> 96256336d13de02933bd449444bf4c16d1a55335


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
SpotLight spotLights[MAX_SPOT_LIGHTS];

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
	pizzeria = Model();
	pizzeria.LoadModel("Models/Daniel/pizzeria/pizzaParlor.obj");

	snow = Model();
	snow.LoadModel("Models/Daniel/snow/snow.obj");

	puffleC = Model();
	puffleC.LoadModel("Models/Daniel/puffle/puffleC.obj");

	puffleG = Model();
	puffleG.LoadModel("Models/Daniel/puffle/puffleG.obj");

	puffleO = Model();
	puffleO.LoadModel("Models/Daniel/puffle/puffleO.obj");

	puffleR = Model();
	puffleR.LoadModel("Models/Daniel/puffle/puffleR.obj");

	zipB = Model();
	zipB.LoadModel("Models/Daniel/zip/zipB.obj");

	zipC = Model();
	zipC.LoadModel("Models/Daniel/zip/zipC.obj");

	zipC1 = Model();
	zipC1.LoadModel("Models/Daniel/zip/zipC1.obj");

	tree = Model();
	tree.LoadModel("Models/Daniel/tree/tree.obj");

	sensei = Model();
	sensei.LoadModel("Models/Daniel/sensei/bodyS.obj");

	beard = Model();
	beard.LoadModel("Models/Daniel/sensei/beardS.obj");

	wingL = Model();
	wingL.LoadModel("Models/Daniel/sensei/wingLS.obj");

	wingR = Model();
	wingR.LoadModel("Models/Daniel/sensei/wingRS.obj");

	lamp= Model();
	lamp.LoadModel("Models/Daniel/lamp/lampCP.obj");

	sign = Model();
	sign.LoadModel("Models/Daniel/sign/sign.obj");



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

	ArbolFP_M = Model();
	ArbolFP_M.LoadModel("Models/Roberto/arbolFinal.obj");

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
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		-6.0f, 1.5f, 1.5f,
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
	spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	//se crean mas luces puntuales y spotlight 

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana


	//obtener el tiempo de incio
	inicio = clock();
	while (!mainWindow.getShouldClose())
	{
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
		shaderList[0].SetSpotLights(spotLights, spotLightCount);


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
			}
			else {
				mcz = 0.0;
			}
		}

		if (mainWindow.getjuego()) {

			rotJuego += 0.001 * glfwGetTime();
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

		/*model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(-30.0f, -2.5f, -45.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Vidrios2_M.RenderModel();
		glDisable(GL_BLEND);*/


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
		model = glm::translate(model, glm::vec3(57.0f + max, 1.9f + may, 127.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Spider_M.RenderModel();

		//Carro
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.5f, 2.0f, 2.0f));
		model = glm::translate(model, posic + glm::vec3(mcz, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::translate(model, glm::vec3(25, -0.1f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		SkateG_M.RenderModel();

		//---------- Universo de Club Penguin O> ----------//

		//pizzeria
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-400.0f, 0.0f, 250.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pizzeria.RenderModel();

		//snow
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-350.0f, 0.0f, 240.0f));
		model = glm::scale(model, glm::vec3(27.0f, 0.0f, 20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		snow.RenderModel();

		//puffles
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-250.0f, -0.5f, 100.0f));
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
		model = glm::translate(model, glm::vec3(-250.0f, -0.5f, 70.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puffleR.RenderModel();

		//tirolesa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, 0.0f, 100.0f));
		model = glm::scale(model, glm::vec3(12.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		zipB.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, 0.0f, 100.0f));
		model = glm::scale(model, glm::vec3(9.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		zipC.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, 0.0f, 100.0f));
		model = glm::scale(model, glm::vec3(9.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		zipC1.RenderModel();

		//outside

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-350.0f, 0.0f, 300.0f));
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		lamp.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, 0.0f, 90.0f));
		model = glm::scale(model, glm::vec3(7.0f, 7.0f, 7.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sign.RenderModel();





		//forest club penguin
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, -1.0f, 20.0f));
		model = glm::scale(model, glm::vec3(15.0f, 17.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-600.0f, -1.0f, 20.0f));
		model = glm::scale(model, glm::vec3(10.0f, 15.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-600.0f, -1.0f, 450.0f));
		model = glm::scale(model, glm::vec3(10.0f, 12.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, -1.0f, 450.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		//m�s �rboles

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, -1.0f, 200.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, -1.0f, 450.0f));
		model = glm::scale(model, glm::vec3(10.0f, 20.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-189.0f, -1.0f, 341.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-400.0f, -1.0f, 359.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		tree.RenderModel();

		//sensei
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, 0.0f, 320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sensei.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, 0.0f, 320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		beard.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, 0.0f, 320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		wingL.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-100.0f, 0.0f, 320.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
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