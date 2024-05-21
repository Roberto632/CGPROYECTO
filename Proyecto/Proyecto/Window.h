#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }

	//animacion tirolesa
	GLfloat movTP() { return movZ; }
	GLfloat movTB() { return movZ1; }

	//animacion jetpack
	GLfloat animJP() { return movJP; }

	//Animaciones Gumball
	GLfloat getmovArana() { return movArana; }
	GLfloat getr1() { return r1; }
	GLfloat getjuego() { return juego; }

	//para cambiar de dia a noche

	GLfloat getCambioNoche() { return cambiaNoche; }

	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;

	bool movZ = false;
	bool movZ1 = false;

	bool movJP = false;

	//Animaciones Gumball
	bool juego = false;
	bool movArana;
	bool r1 = false;

	//variable para cambiar de dia noche 
	GLfloat cambiaNoche; 
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

