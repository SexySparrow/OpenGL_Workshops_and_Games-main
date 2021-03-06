#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

/* Taste utilizare
	
	Pentru deplasarea modelului se folosesc W, A, S, D, Q, E;
	Culoarea se schimba la apasarea lui F, iar modelul se schimba apasand pe T.
*/
Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;

		Mesh* mesh2 = new Mesh("teapot");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh2->GetMeshID()] = mesh2;

		Mesh* mesh3 = new Mesh("sphere");
		mesh3->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh3->GetMeshID()] = mesh3;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	

	if (changeColor) {
		glClearColor(1, 0.5f, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	else
	{
		// sets the clear color for the color buffer
		glClearColor(0, 0, 0, 1);

		// clears the color buffer (using the previously set color) and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	if (renderTeaPot)
		RenderMesh(meshes["teapot"], glm::vec3(x, y, z));
	else
		RenderMesh(meshes["sphere"], glm::vec3(x, y, z));

}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	if (!moveMode && window->KeyHold(GLFW_KEY_W)) {
		z -= 0.2f;
	}
	if (!moveMode && window->KeyHold(GLFW_KEY_S)) {
		z += 0.2f;
	}
	if (!moveMode && window->KeyHold(GLFW_KEY_A)) {
		x -= 0.2f;
	}
	if (!moveMode && window->KeyHold(GLFW_KEY_D)) {
		x += 0.2f;
	}

	if (!moveMode && window->KeyHold(GLFW_KEY_Q)) {
		y -= 0.2f;
	}
	if (!moveMode && window->KeyHold(GLFW_KEY_E)) {
		y += 0.2f;
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		changeColor = !changeColor;
	}

	if (key == GLFW_KEY_T) {
		renderTeaPot = !renderTeaPot;
	}

	if (key == GLFW_KEY_LEFT_CONTROL) {
		moveMode = true;
	}

	if (moveMode && window->KeyHold(GLFW_KEY_UP)) {
		z -= 1;
	}
	if (moveMode && window->KeyHold(GLFW_KEY_DOWN)) {
		z += 1;
	}
	if (moveMode && window->KeyHold(GLFW_KEY_LEFT)) {
		x -= 1;
	}
	if (moveMode && window->KeyHold(GLFW_KEY_RIGHT)) {
		x += 1;
	}

	if (moveMode && window->KeyHold(GLFW_KEY_Q)) {
		y -= 0.2f;
	}
	if (moveMode && window->KeyHold(GLFW_KEY_E)) {
		y += 0.2f;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event

	if (key == GLFW_KEY_LEFT_CONTROL) {
		moveMode = false;
	}
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
