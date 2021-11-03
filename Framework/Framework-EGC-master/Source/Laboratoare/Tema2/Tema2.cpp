#include "Tema2.h"
#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Laboratoare/Laborator4/Transform3D.h"
#include "Core/Managers/ResourcePath.h"
#include "Laboratoare/Laborator3/Transform2D.h"
#include "Laboratoare/Laborator5/LabCamera.h"


Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("plane");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "platform.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("wall");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "wall.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("lamps");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "lamps.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	
	{
		Mesh* mesh = new Mesh("city");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "city.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("player");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "ship.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("skull_up");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "skull_up.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("skull_down");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "skull_down.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("GameOver");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "GameOver.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(1, 0, 0)),

			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(1, 1, 0), glm::vec3(1, 0, 0))
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2,	// indices for first triangle
			2, 1, 3,	// indices for second triangle
		};

		CreateMesh("fuel", vertices, indices);
		meshes["fuel"]->SetDrawMode(GL_TRIANGLE_FAN);
	}

	{
		std::vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 10, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(5, 20, 0), glm::vec3(1, 1, 1)),

			VertexFormat(glm::vec3(10, 15, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(15, 20, 0), glm::vec3(1, 1, 1)),

			VertexFormat(glm::vec3(20, 10, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(10, 0, 0), glm::vec3(1, 1, 1))
		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2,	// indices for first triangle
			2, 3, 4,	// indices for second triangle
			2, 4, 5,	// etc.
			2, 5, 0
		};

		CreateMesh("life", vertices, indices);
		meshes["life"]->SetDrawMode(GL_TRIANGLE_FAN);
	}

	{
		Shader* shader = new Shader("Tema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader* shader = new Shader("Player");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Noise/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/Noise/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	alive = 3;
	fuel = 100;
	camera = new TEMA2::Camera();
	camera->Set(glm::vec3(0, 3.3f, 5), glm::vec3(0, 0.5f, 0), glm::vec3(0, 0.5f, 0));
	camera->MoveForward(-5.5f);
	camera->TranslateUpword(2.5f);
	projectionMatrix = glm::perspective(RADIANS(70), window->props.aspectRatio, 0.01f, 200.0f);
	InitLanes();
	InitLamps();
	InitStartArea();
	translateY = 0.5;
	translateZ = -2;
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	if (alive)
	{
		{
			glm::ivec2 resolution = window->GetResolution();


			glm::mat3 fuel_mat3 = glm::mat3(1);
			fuel_mat3 *= Transform2D::Translate(-3.5f, -1.8f);
			fuel_mat3 *= Transform2D::Scale(fuel * 7 / 100, 1);
			SimpleScene::RenderMesh2D(meshes["fuel"], fuel_mat3, glm::vec3(1, 1, 1));

			fuel_mat3 = glm::mat3(1);
			fuel_mat3 *= Transform2D::Translate(-3.5f, -1.8f);
			fuel_mat3 *= Transform2D::Scale(10, 1);
			SimpleScene::RenderMesh2D(meshes["fuel"], fuel_mat3, glm::vec3(0, 0, 0));
		}
		{
			glm::mat4 wallMat = glm::mat4(1);
			wallMat *= Transform3D::Translate(0, 0, 3);
			RenderMesh(meshes["wall"], shaders["VertexNormal"], wallMat);
		}
		{
			glm::mat4 cityMat = glm::mat4(1);
			cityMat *= Transform3D::Translate(0, 0, -150);
			RenderMesh(meshes["city"], shaders["VertexNormal"], cityMat);
		}
	}

	if(speed_lock)
	{
		speed_lock--;
		platformSpeed = 200;
		if (!speed_lock)
			platformSpeed = 100;
	}

	renderLives();
	index++;
	int platformFrames = 30 - (platformSpeed / 10);
	if (index % platformFrames == 0 && alive)
	{
		index = 0;
		CreatePanels();

	}
	fuel -= 0.1f;

	CheckAlive();

	if (alive)
	{
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(translateX, translateY, 2);
		RenderSimpleMesh(meshes["player"], shaders["Player"], modelMatrix, glm::vec3(0, 1, 2), GetClosestLight(glm::vec3(translateX, translateY, 2)));

		MovePanels();
		MoveLamps();
		RemovePlatformAllLanes();
		Gravity();
	}
	else
	{
		DeadUpdate();
	}
}

glm::vec3 Tema2::GetClosestLight(glm::vec3 pos)
{
	float min = FLT_MAX;
	int index = 0;
	
	for (int i = 0; i < 5; ++i)
	{
		float dis = sqrtf(dot(lampPos[i] - pos, lampPos[i] - pos));

		if (dis < min)
		{
			min = dis;
			index = i;
		}
			
	}

	return lampPos[index];
}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem();
}

void Tema2::CheckAlive()
{
	if (translateY < -10)
	{
		fuel = 0;
		translateY = 10;
		alive = false;
		return;
	}
	if (fuel <= 0 && alive > 1)
	{
		alive = std::max(alive - 1, 0);
		fuel = 100;
	}

}

void Tema2::InitLanes()
{
	for (int i = 0; i < 5; ++i)
	{
		std::vector<Panel*> lane;
		Panel* p = new Panel(i);
		lane.push_back(p);
		all_Lanes.push_back(lane);
	}
}

void Tema2::InitLamps()
{
	for (int i = 0; i < 5; i++)
	{
		lampPos[i] = glm::vec3(0, 5, i * -20);
	}
}


//create starting platforms
void Tema2::InitStartArea()
{

	for (int i = 0; i > -50; i -= 4)
	{
		Panel* p = new Panel(2, i);
		all_Lanes[2].push_back(p);
		p = new Panel(1, i);
		all_Lanes[2].push_back(p);
		p = new Panel(3, i);
		all_Lanes[2].push_back(p);
	}
}
//create new platforms
void Tema2::CreatePanels()
{
	for (int i = 0; i < 5; ++i)
	{
		if (gap[i] || rand() % 3)
		{
			Panel* p = new Panel(i);
			all_Lanes[i].push_back(p);
			gap[i] = false;
		}
		else
			gap[i] = true;
	}
}

void Tema2::MoveLamps()
{
	for (int i = 0; i < 5; i++)
	{
		glm::mat4 lampsPos = glm::mat4(1);
		lampPos[i].z += platformSpeed * static_cast<float>(2) / 1000;

		if (lampPos[i].z >= 3)
			lampPos[i].z = -100;
		lampsPos *= Transform3D::Translate(lampPos[i].x, lampPos[i].y, lampPos[i].z);
		RenderMesh(meshes["lamps"], shaders["VertexNormal"], lampsPos);
	}
}



// move the platforms
void Tema2::MovePanels()
{
	for (int i = 0; i < 5; ++i)
	{
		for (auto p : all_Lanes[i])
		{
			p->z += platformSpeed * static_cast<float>(2) / 1000;
			panelMatrix = glm::mat4(1);
			panelMatrix *= Transform3D::Translate(p->x, p->y, p->z);
			RenderSimpleMesh(meshes["plane"], shaders["Tema2"], panelMatrix, p->color, GetClosestLight(glm::vec3(p->x, p->y, p->z)));
		}
	}
	CheckCollision();
}
//clear all lanes
void Tema2::RemovePlatformAllLanes()
{
	for (int i = 0; i < 5; ++i) {
		RemovePlatform(all_Lanes[i]);
	}
}

//clear offscreen platforms off one lane
void Tema2::RemovePlatform(std::vector<Panel*>& offScreen) {
	offScreen.erase(
		std::remove_if(offScreen.begin(), offScreen.end(), [&](Panel* const& offScreenPanel) {
			return offScreenPanel->z > 15;
			}),
		offScreen.end());
}

void Tema2::Gravity()
{
	if (onPlatform)
		translateY = std::max(translateY + speed_Y, 0.5f);
	else
		translateY += speed_Y;
	speed_Y = std::max(speed_Y - 0.15f, -0.2f);
}

void Tema2::CheckCollision()
{
	bool check = false;
	for (int i = 0; i < 5; ++i)
	{
		for (auto p : all_Lanes[i])
		{
			if (p->IsOnPanel(translateX, translateZ) && translateY <= 0.5f && translateY > 0)
			{
				//change the color if the landed platform
				p->color = glm::vec3(1, 0, 1);
				//and activate the power
				p->PanelPower(&fuel, &alive, &speed_lock);
				//mark the ship as being on a platform
				check = true;
				break;
			}
			//else
			//{
				//p->ResetColor();
			//}
		}
	}
	onPlatform = check;
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	float playerMoveSpeed = 10;
	glm::ivec2 resolution = window->GetResolution();
	//move right
	if (window->KeyHold(GLFW_KEY_D) && translateX < 12)
	{
		translateX += playerMoveSpeed * deltaTime;
	}
	//move left
	if (window->KeyHold(GLFW_KEY_A) && translateX > -12)
	{
		translateX -= playerMoveSpeed * deltaTime;
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	//move faster
	if (key == GLFW_KEY_W && platformSpeed < 200 && !speed_lock)
	{
		platformSpeed += 20;
	}
	//move slower
	if (key == GLFW_KEY_S && platformSpeed > 100 && !speed_lock)
	{
		platformSpeed -= 20;
	}
	//press space to jump
	if (key == GLFW_KEY_SPACE && onPlatform)
	{
		speed_Y = 1.5f;
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
//show the lives on screen
void Tema2::renderLives()
{
	glm::ivec2 resolution = window->GetResolution();

	if (alive > 2)
	{
		glm::mat3 liveMatrix = glm::mat3(1);
		liveMatrix *= Transform2D::Translate(0.5f, -0.5f);
		liveMatrix *= Transform2D::Scale(0.01f, 0.01f);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], liveMatrix);
	}
	if (alive > 1)
	{
		glm::mat3 liveMatrix = glm::mat3(1);
		liveMatrix *= Transform2D::Translate(0, -0.5f);
		liveMatrix *= Transform2D::Scale(0.01f, 0.01f);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], liveMatrix);
	}
	if (alive > 0)
	{
		glm::mat3 liveMatrix = glm::mat3(1);
		liveMatrix *= Transform2D::Translate(-0.5f, -0.5f);
		liveMatrix *= Transform2D::Scale(0.01f, 0.01f);
		RenderMesh2D(meshes["life"], shaders["VertexColor"], liveMatrix);
	}
}
void Tema2::DeadUpdate()
{
	for (int i = 0; i < 7; ++i)
	{

		glm::mat3 fuel_mat3 = glm::mat3(1);
		fuel_mat3 *= Transform2D::Translate(i - 3, 3);
		fuel_mat3 *= Transform2D::Scale(0.1f, fuel / 4);
		RenderMesh2D(meshes["fuel"], fuel_mat3, glm::vec3(1, 0, 0));
	}

	if (fuel < -20)
	{
		// make the screen red
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// move the skull forward
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0, -5, -14 - (fuel + 20));
		modelMatrix *= Transform3D::Scale(1, 1, 0.2f);
		SimpleScene::RenderMesh(meshes["skull_up"], shaders["VertexNormal"], modelMatrix);
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0, -4 - index / 10 % 2, -14 - (fuel + 20));
		SimpleScene::RenderMesh(meshes["skull_down"], shaders["VertexNormal"], modelMatrix);

		//diplay game over text
		if (fuel < -37)
		{
			modelMatrix = glm::mat4(1);
			modelMatrix *= Transform3D::Translate(0, -15, -50);
			RenderMesh(meshes["GameOver"], shaders["VertexNormal"], modelMatrix);
		}
		
	}
	else
	{
		//make the skull laugh
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0, -5, -14);
		SimpleScene::RenderMesh(meshes["skull_up"], shaders["VertexNormal"], modelMatrix);
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(0, -4 - index / 10 % 2, -14);
		SimpleScene::RenderMesh(meshes["skull_down"], shaders["VertexNormal"], modelMatrix);
	}
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix_param, const glm::vec3& color, const glm::vec3& lightPosition)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	GLint obj_color = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(obj_color, 1, glm::value_ptr(color));

	// TODO : get shader location for uniform mat4 "Model"
	GLint modelL = glGetUniformLocation(shader->GetProgramID(), "Model");
	glUniformMatrix4fv(modelL, 1, GL_FALSE, glm::value_ptr(modelMatrix_param));

	GLint viewL = glGetUniformLocation(shader->GetProgramID(), "View");

	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(viewL, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));


	if (shader == shaders["Player"])
	{
		GLint cur_time = glGetUniformLocation(shader->program, "time");
		glUniform1f(cur_time, (GLfloat)Engine::GetElapsedTime());
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

Mesh* Tema2::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);

	// TODO: Send vertices data into the VBO buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data
	// It will be learned later, when GLSL shaders will be introduced
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// TODO: Unbind the VAO
	glBindVertexArray(0);
	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}