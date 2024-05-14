/*
Práctica 7: Iluminación 1
*/
//para cargar imagen
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

//para iluminación
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

//modelos del univero de phineas  ferb models
Model Inator_M;
Model EdiDodu_M;
Model House_M;
Model Banco_M;

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


//función de calculo de normales por promedio de vértices 
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
	/*Cámara se usa el comando: glm::lookAt(vector de posición, vector de orientación, vector up));
	En la clase Camera se reciben 5 datos:
	glm::vec3 vector de posición,
	glm::vec3 vector up,
	GlFloat yaw rotación para girar hacia la derecha e izquierda
	GlFloat pitch rotación para inclinar hacia arriba y abajo
	GlFloat velocidad de desplazamiento,
	GlFloat velocidad de vuelta o de giro
	Se usa el Mouse y las teclas WASD y su posición inicial está en 0,0,1 y ve hacia 0,0,-1.
	*/
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

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

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");

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

	//modelos del univero de phineas y ferb 
	Inator_M = Model();
	Inator_M.LoadModel("Models/Roberto/inator.obj");

	EdiDodu_M = Model();
	EdiDodu_M.LoadModel("Models/Roberto/EdoDufusFinal.obj");

	House_M = Model();
	House_M.LoadModel("Models/Roberto/casaFinal2PhienasFerb.obj");

	Banco_M = Model();
	Banco_M.LoadModel("Models/Roberto/bancoText.obj");

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
	skyboxFacesAmanecer.push_back("Textures/Skybox/leftAmanecer.tga");
	skyboxFacesAmanecer.push_back("Textures/Skybox/downAmanecer.tga");
	skyboxFacesAmanecer.push_back("Textures/Skybox/upAmanecer.tga");
	skyboxFacesAmanecer.push_back("Textures/Skybox/backAmanecer.tga");
	skyboxFacesAmanecer.push_back("Textures/Skybox/frontAmanecer.tga");

	skyboxAmanecer = Skybox(skyboxFacesAmanecer);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
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

		//Para apagar el pollo
		if (periodoUso <= 5.0) {
			skyboxDia.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else if (periodoUso <= 10.0) {
			skyboxTarde.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else if (periodoUso <= 15.0) {
			skyboxNoche.DrawSkybox(camera.calculateViewMatrix(), projection);
		}
		else if (periodoUso <= 20.0) {
			skyboxAmanecer.DrawSkybox(camera.calculateViewMatrix(), projection);
		}

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		//sirve para que en tiempo de ejecución (dentro del while) se cambien propiedades de la luz
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//Instancia del coche 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex(), 0.5f, -3.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Kitt_M.RenderModel();

		//Llanta delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(7.0f, -0.5f, 8.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		color = glm::vec3(0.5f, 0.5f, 0.5f);//llanta con color gris
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.5f, -0.5f, 8.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(7.0f, -0.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();

		//Llanta trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.5f, -0.5f, 1.5f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Llanta_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 6.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Blackhawk_M.RenderModel();


		//Árboles Gumball
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
		model = glm::translate(model, glm::vec3(60.0f, 4.2f, 90.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Spider_M.RenderModel();

		//Carro
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.5f, 2.0f, 2.0f));
		model = glm::translate(model, glm::vec3(180.0f, 0.0f, 50.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Car_M.RenderModel();

		/////////////////////////////////////////////////////////Univero de phienas y ferb
		//edificio
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-285.0f, 2.0f, -285.0f));
		model = glm::scale(model, glm::vec3(15.0f, 20.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		EdiDodu_M.RenderModel();

		//casa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(75.0f, -14.5f, -260.0f));
		//model = glm::rotate(model, glm::radians(-165.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		House_M.RenderModel();


		//invento
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, 1.0f, -100.0f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Inator_M.RenderModel();

		//Banco de parque
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, -2.0f, -50.0f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		//Banco de parque
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(140.0f, -2.0f, -100.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		//Banco de parque
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, -2.0f, -100.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		//Banco de parque
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.0f, -2.0f, -150.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		//Agave ¿qué sucede si lo renderizan antes del coche y el helicóptero?
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
		if (periodoUso <= 20.0) {
			fin = clock();
			periodoUso = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
			printf("\nPeriodo usado del cpu %f segundos", periodoUso);
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
