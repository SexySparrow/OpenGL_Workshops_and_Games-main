#include "BowAndArrow.h"

#include <vector>
#include <iostream>
#include <Core/Engine.h>
#include <Laboratoare\Laborator3\Transform2D.h>
#include <random>
#include<sstream>
#include <ctime>

using namespace std;

BowAndArrow::BowAndArrow()
{
}

BowAndArrow::~BowAndArrow()
{
}

void BowAndArrow::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	// bow creation
	{
		vector<VertexFormat> vertices;
		vector<GLushort> indices;
		GLfloat arg;

		for (GLushort i = 0; i < NUM_TRIANGLES; i++)
		{
			arg = TWO_PI * i / NUM_TRIANGLES / 2 - TWO_PI / 4;

			vertices.emplace_back(glm::vec3(35 * cos(arg), 50 * sin(arg), 0), glm::vec3(0, 1, 0));
			indices.push_back(i);
		}

		// Create a new mesh from buffer data
		CreateMesh("bow", vertices, indices);
		meshes["bow"]->SetDrawMode(GL_LINE_LOOP);
	}
	//first balloon model
	{
		vector<VertexFormat> vertices;
		vector<GLushort> indices;
		GLfloat arg;

		vertices.emplace_back(glm::vec3(0, 0, 0), glm::vec3(1, 1, 0));
		for (GLushort i = 0; i < NUM_TRIANGLES; i++)
		{
			arg = TWO_PI * i / NUM_TRIANGLES;

			vertices.emplace_back(glm::vec3(15 * cos(arg), 25 * sin(arg), 0), glm::vec3(1, 1, 0));
			indices.push_back(i);
		}

		indices.push_back(NUM_TRIANGLES);
		indices.push_back(1);

		vertices.emplace_back(glm::vec3(0, -25, 0), glm::vec3(1, 1, 0));
		vertices.emplace_back(glm::vec3(4, -29, 0), glm::vec3(1, 1, 0));
		vertices.emplace_back(glm::vec3(-4, -29, 0), glm::vec3(1, 1, 0));
		indices.push_back(NUM_TRIANGLES + 1);
		indices.push_back(NUM_TRIANGLES + 2);
		indices.push_back(NUM_TRIANGLES + 3);

		// Create a new mesh from buffer data
		CreateMesh("balloon0", vertices, indices);
		meshes["balloon0"]->SetDrawMode(GL_TRIANGLE_FAN);
	}
	//second balloon model
	{
		vector<VertexFormat> vertices;
		vector<GLushort> indices;
		GLfloat arg;

		vertices.emplace_back(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
		for (GLushort i = 0; i < NUM_TRIANGLES; i++)
		{
			arg = TWO_PI * i / NUM_TRIANGLES;

			vertices.emplace_back(glm::vec3(15 * cos(arg), 25 * sin(arg), 0), glm::vec3(1, 0, 0));
			indices.push_back(i);
		}

		indices.push_back(NUM_TRIANGLES);
		indices.push_back(1);

		vertices.emplace_back(glm::vec3(0, -25, 0), glm::vec3(1, 0, 0));
		vertices.emplace_back(glm::vec3(4, -29, 0), glm::vec3(1, 0, 0));
		vertices.emplace_back(glm::vec3(-4, -29, 0), glm::vec3(1, 0, 0));
		indices.push_back(NUM_TRIANGLES + 1);
		indices.push_back(NUM_TRIANGLES + 2);
		indices.push_back(NUM_TRIANGLES + 3);

		// Create a new mesh from buffer data
		CreateMesh("balloon1", vertices, indices);
		meshes["balloon1"]->SetDrawMode(GL_TRIANGLE_FAN);
	}
	//first balloon hit model
	{
		vector<VertexFormat> vertices;
		vector<GLushort> indices;
		GLfloat arg;

		vertices.emplace_back(glm::vec3(0, 0, 0), glm::vec3(1, 1, 0));
		for (GLushort i = 0; i < NUM_TRIANGLES; i++)
		{
			arg = TWO_PI * i / NUM_TRIANGLES;

			vertices.emplace_back(glm::vec3(10 * cos(arg), 25 * sin(arg), 0), glm::vec3(1, 1, 0));
			indices.push_back(i);
		}

		indices.push_back(NUM_TRIANGLES);
		indices.push_back(1);

		vertices.emplace_back(glm::vec3(0, -25, 0), glm::vec3(1, 1, 0));
		vertices.emplace_back(glm::vec3(4, -29, 0), glm::vec3(1, 1, 0));
		vertices.emplace_back(glm::vec3(-4, -29, 0), glm::vec3(1, 1, 0));
		indices.push_back(NUM_TRIANGLES + 1);
		indices.push_back(NUM_TRIANGLES + 2);
		indices.push_back(NUM_TRIANGLES + 3);

		// Create a new mesh from buffer data
		CreateMesh("balloon0_hit", vertices, indices);
		meshes["balloon0_hit"]->SetDrawMode(GL_TRIANGLE_FAN);
	}
	//second balloon hit model
	{
		vector<VertexFormat> vertices;
		vector<GLushort> indices;
		GLfloat arg;

		vertices.emplace_back(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
		for (GLushort i = 0; i < NUM_TRIANGLES; i++)
		{
			arg = TWO_PI * i / NUM_TRIANGLES;

			vertices.emplace_back(glm::vec3(10 * cos(arg), 25 * sin(arg), 0), glm::vec3(1, 0, 0));
			indices.push_back(i);
		}

		indices.push_back(NUM_TRIANGLES);
		indices.push_back(1);

		vertices.emplace_back(glm::vec3(0, -25, 0), glm::vec3(1, 0, 0));
		vertices.emplace_back(glm::vec3(4, -29, 0), glm::vec3(1, 0, 0));
		vertices.emplace_back(glm::vec3(-4, -29, 0), glm::vec3(1, 0, 0));
		indices.push_back(NUM_TRIANGLES + 1);
		indices.push_back(NUM_TRIANGLES + 2);
		indices.push_back(NUM_TRIANGLES + 3);

		// Create a new mesh from buffer data
		CreateMesh("balloon1_hit", vertices, indices);
		meshes["balloon1_hit"]->SetDrawMode(GL_TRIANGLE_FAN);
	}
	//balloon tail
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(0, -29, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(5, -35, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(-5, -45, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(5, -55, 0), glm::vec3(1, 1, 1))
		};

		vector<unsigned short> indices =
		{
			0, 1,
			1, 2,
			2, 3,
			3, 4
		};
		CreateMesh("line", vertices, indices);
		meshes["line"]->SetDrawMode(GL_LINES);
	}

	//shuriken
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),

			VertexFormat(glm::vec3(0, -10, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(10, -10, 0), glm::vec3(1, 1, 1)),

			VertexFormat(glm::vec3(0, 10, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(-10, 10, 0), glm::vec3(1, 1, 1)),

			VertexFormat(glm::vec3(10, 0, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(10, 10, 0), glm::vec3(1, 1, 1)),

			VertexFormat(glm::vec3(-10, 0, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(-10, -10, 0), glm::vec3(1, 1, 1))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,	// indices for first triangle
			0, 3, 4,	// indices for second triangle
			0, 5, 6,	// etc.
			0, 7, 8
		};
		CreateMesh("shur", vertices, indices);
		meshes["shur"]->SetDrawMode(GL_TRIANGLE_FAN);
	}
	//arrow model
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(10, 0, 0), glm::vec3(1, 1, 1)),

			VertexFormat(glm::vec3(0, -5, 0), glm::vec3(1, 1, 1)),
			VertexFormat(glm::vec3(0, 5, 0), glm::vec3(1, 1, 1)),

			VertexFormat(glm::vec3(0, 2, 0), glm::vec3(132, 66, 0)),
			VertexFormat(glm::vec3(0, -2, 0), glm::vec3(132, 66, 0)),

			VertexFormat(glm::vec3(-50, 2, 0), glm::vec3(132, 66, 0)),
			VertexFormat(glm::vec3(-50, -2, 0), glm::vec3(132, 66, 0))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,	// indices for first triangle
			0, 1, 3,	// indices for second triangle
			4, 5, 7,	// etc.
			4, 6, 7
		};

		CreateMesh("arrow", vertices, indices);
		meshes["arrow"]->SetDrawMode(GL_TRIANGLE_FAN);
	}
	//player life model
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 10, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(5, 20, 0), glm::vec3(1, 0, 0)),

			VertexFormat(glm::vec3(10, 15, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(15, 20, 0), glm::vec3(1, 0, 0)),

			VertexFormat(glm::vec3(20, 10, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(10, 0, 0), glm::vec3(1, 0, 0))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,	// indices for first triangle
			2, 3, 4,	// indices for second triangle
			2, 4, 5,	// etc.
			2, 5, 0
		};

		CreateMesh("live", vertices, indices);
		meshes["live"]->SetDrawMode(GL_TRIANGLE_FAN);
	}
	//square used for power bar
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 10, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(10, 0, 0), glm::vec3(1, 0, 0)),

			VertexFormat(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0)),
			VertexFormat(glm::vec3(10, 10, 0), glm::vec3(1, 0, 0))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,	// indices for first triangle
			2, 1, 3,	// indices for second triangle
		};

		CreateMesh("power", vertices, indices);
		meshes["power"]->SetDrawMode(GL_TRIANGLE_FAN);
	}

	//start position for the bow
	translateY = resolution.y / 2;
	translateX = 50;
	//calling the initial dunctions to populate the balloons and shuriken arrays
	initBallons();
	initShurs();
}
//create all balloons
void BowAndArrow::initBallons()
{
	for (int i = 0; i < NUM_BALLONS; i++)
	{
		newBallon(i);
	}
}
//create all the shuriken
void BowAndArrow::initShurs()
{
	for (int i = 0; i < NUM_SHURS; i++)
	{
		newShur(i);
	}
}

void BowAndArrow::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

Mesh* BowAndArrow::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
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

void BowAndArrow::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glm::ivec2 resolution = window->GetResolution();

	// checks to be made if the player is still alive
	if (alive) {

		//increase the speed for the balloons and shurikens
		speedInc();
		//if the player is in the shoot mode increase arrow speed
		if (shootMode && arrowSpeedX < 800) {
			arrowSpeedX += 15;
		}

		{
			//animate the falling balloons
			fallingBalloons(deltaTimeSeconds);
			//and delete the ones that are offscreen
			RemoveBalloon(hitBallons);
		}
		//player life bar
		renderLives();

		{
			//move the bow up and down on the screen
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(translateX, translateY);
			modelMatrix *= Transform2D::Rotate(angularStep);
			RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);

			if (holstered)
			{
				//the arrow is holstered

				//render the power bar according to the arrow speed
				powerMatrix = glm::mat3(1);
				powerMatrix *= Transform2D::Translate(0, 0);
				powerMatrix *= Transform2D::Scale(arrowSpeedX / 3 - 100, 1);
				RenderMesh2D(meshes["power"], shaders["VertexColor"], powerMatrix);

				//and move the arrow with the bow
				arrowX = translateX;
				arrowY = translateY;
				arrowStep = angularStep;
				arrowMatrix = glm::mat3(1);
				arrowMatrix *= Transform2D::Translate(translateX, translateY);
				arrowMatrix *= Transform2D::Rotate(angularStep);
				arrowMatrix *= Transform2D::Translate(50, 0);
			}
			else
			{
				//the arrow is in the air
				arrowMatrix = glm::mat3(1);
				arrowX += arrowSpeedX * deltaTimeSeconds * abs(cos(arrowStep));
				arrowY += arrowSpeedX * deltaTimeSeconds * sin(arrowStep);
				arrowMatrix *= Transform2D::Translate(arrowX, arrowY);
				arrowMatrix *= Transform2D::Rotate(arrowStep);
				arrowMatrix *= Transform2D::Translate(50, 0);
				//so we check for collisions with other objects
				checkArrowCollision();
				//and delete the arrow if is off-screen
				checkOnScreen();
			}
			RenderMesh2D(meshes["arrow"], shaders["VertexColor"], arrowMatrix);

		}

		{
			//check to see if the balloons are on screen and move them up
			checkBallons(deltaTimeSeconds);
			//and the same for shurikens
			checkShurs(deltaTimeSeconds);
		}

		{
			//check to see if the player is hit by a shuriken
			checkIfHit(true);
		}
	}
	else
	{
		printf("GAME OVER\n");
		printf("Final Score: %d\n", SCORE);
		//exit(0);
	}
}

// render a number of lifes on the screen according to the current amount
void BowAndArrow::renderLives()
{
	glm::ivec2 resolution = window->GetResolution();

	if (shield) {
		glm::mat3 liveMatrix = glm::mat3(1);
		liveMatrix *= Transform2D::Translate(0, resolution.y - 30);
		RenderMesh2D(meshes["power"], liveMatrix, glm::vec3(1,1,0));
	}

	if (alive > 2)
	{
		glm::mat3 liveMatrix = glm::mat3(1);
		liveMatrix *= Transform2D::Translate(120, resolution.y - 30);
		RenderMesh2D(meshes["live"], shaders["VertexColor"], liveMatrix);
	}
	if (alive > 1)
	{
		glm::mat3 liveMatrix = glm::mat3(1);
		liveMatrix *= Transform2D::Translate(80, resolution.y - 30);
		RenderMesh2D(meshes["live"], shaders["VertexColor"], liveMatrix);
	}
	if (alive > 0)
	{
		glm::mat3 liveMatrix = glm::mat3(1);
		liveMatrix *= Transform2D::Translate(40, resolution.y - 30);
		RenderMesh2D(meshes["live"], shaders["VertexColor"], liveMatrix);
	}
}

//look for collisions with
void BowAndArrow::checkArrowCollision()
{
	for (int i = 0; i < NUM_BALLONS; i++)
	{
		//the balloons 
		checkIfHitBalloon(i);
	}
	//the shurikens
	checkIfHit(false);
}

bool BowAndArrow::insideBallon(double x, double y, double centx, double centy)
{
	//look if the arrow has hit one of the balloons 
	double val1 = x - centx;
	double val2 = y - centy;
	if ((val1 * val1 / 225) + (val2 * val2 / 900) <= 1.1)
		return true;
	return false;
}

void BowAndArrow::checkIfHitBalloon(int i)
{
	if (insideBallon(arrowX, arrowY, balloons[i].x, balloons[i].y)) {

		//place the hit balloon inside the falling balloons vector
		Ballon aux;
		aux.x = balloons[i].x;
		aux.y = balloons[i].y;
		aux.color = balloons[i].color;
		hitBallons.emplace_back(aux);

		//add or subtract from the score 
		if (balloons[i].color)
		{
			SCORE++;
		}
		else
		{
			SCORE--;
		}
		//print the updated score
		printf("SCORE: %d\n", SCORE);
		//and create a new balloon to replace the hit one
		newBallon(i);
	}
}

void BowAndArrow::fallingBalloons(int deltaTime)
{
	for (auto it = hitBallons.begin(); it != hitBallons.end(); ++it)
	{
		//animate the falling balloons
		hitMatrix = glm::mat3(1);
		it->y -= 10;
		hitMatrix *= Transform2D::Translate(it->x, it->y);

		if (it->color)
			RenderMesh2D(meshes["balloon1_hit"], shaders["VertexColor"], hitMatrix);
		else
			RenderMesh2D(meshes["balloon0_hit"], shaders["VertexColor"], hitMatrix);

		RenderMesh2D(meshes["line"], shaders["VertexColor"], hitMatrix);
	}
}


void BowAndArrow::RemoveBalloon(std::vector<BowAndArrow::Ballon>& allHitBalloons) {
	//erase all balloons that are no longer on the screen
	allHitBalloons.erase(
		std::remove_if(allHitBalloons.begin(), allHitBalloons.end(), [&](BowAndArrow::Ballon const& hitBalloon) {
			return hitBalloon.y < -50;
			}),
		allHitBalloons.end());
}

void BowAndArrow::checkOnScreen()
{
	//remove the arrow if it is offscreen
	glm::ivec2 resolution = window->GetResolution();
	if (arrowX > resolution.x + 50 || arrowY < -50 || arrowY >  resolution.y + 50)
	{
		holstered = true;
		arrowSpeedX = 300;
	}

}

void BowAndArrow::speedInc()
{
	//make the game harder if the score is increasing
	ballonSpeed = 100 + max(SCORE, 0) * 10;
	shurSpeed = 300 + max(SCORE, 0) * 10;
}

void BowAndArrow::checkIfHit(bool bow)
{
	// look if shurikens have colisions
	for (int i = 0; i < NUM_SHURS; i++)
	{
		//getthe collision type 
		bool cond = bow == true ? hitByShur(i) : shurArrowHit(i);
		if (cond) {
			if (bow) {
				

				//remove a life if it's a shuriken
				if (shurs[i].color)
					if (shurs[i].color == 1) {
						glClearColor(1, 1, 0, 0);
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						shield = 2;
					}
					else
					{
						//if the player is hit, turn the screen red
						glClearColor(1, 0, 0, 0);
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						if (shield)
							shield--;
						else
							alive--;
					}
				else // and add a life if it's a heart
				{
					alive = min(alive + 1, 3);
					glClearColor(0, 1, 0, 0);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				}

			}
			else
			{
				// if the arrow hits a shuriken add a point
				if (shurs[i].color)
				{
					SCORE++;
					printf("SCORE: %d\n", SCORE);
				}
				else // or a life if it's a heart
				{
					alive = min(alive + 1, 3);
					glClearColor(0, 1, 0, 0);
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				}
				//and turn the other object red to animate a hit
				shurMatrix = glm::mat3(1);
				shurMatrix *= Transform2D::Translate(shurs[i].x, shurs[i].y);
				RenderMesh2D(meshes["shur"], shurMatrix, glm::vec3(1, 0, 0));
			}
			newShur(i);
		}
	}
}
bool BowAndArrow::shurArrowHit(int i)
{
	//check if an arrow and a shuriken collided
	float x = shurs[i].x;
	float y = shurs[i].y;
	if (arrowX < x + 15 && arrowX > x - 15 && arrowY < y + 15 && arrowY > y - 15)
		return true;
	return false;
}

bool BowAndArrow::hitByShur(int i)
{
	//check if the player is hit by a shuriken
	if (shurs[i].x > 0 && shurs[i].x < 40 && shurs[i].y > translateY - 50 && shurs[i].y < translateY + 50)
		return true;
	return false;
}

void BowAndArrow::clearBallons()
{
	//remove all the offscreen balloons
	glm::ivec2 resolution = window->GetResolution();
	for (int i = 0; i < NUM_BALLONS; i++)
	{
		if (balloons[i].x > resolution.x + 85 || balloons[i].x < -100 || balloons[i].y > resolution.y + 100) {
			newBallon(i);
		}
	}
}

void BowAndArrow::clearShurs()
{
	//remove all the offscreen balloons
	glm::ivec2 resolution = window->GetResolution();
	for (int i = 0; i < NUM_SHURS; i++)
	{
		if (shurs[i].x < -100 || shurs[i].y > resolution.y + 100 || shurs[i].y < -50) {
			newShur(i);
		}
	}
}

void BowAndArrow::newBallon(int i) {
	//create a new ballon at a random  position and of a random type
	glm::ivec2 resolution = window->GetResolution();
	balloons[i].color = rand() % 2;
	balloons[i].x = rand() % (resolution.x - 200) + 150;
	balloons[i].y = -150 - rand() % 400;
	balloons[i].hit = false;
	balloons[i].wind = rand() % 2 ? -1 : 1;
}

void BowAndArrow::newShur(int i) {
	//create a new object(shuriken or life) at a random position
	glm::ivec2 resolution = window->GetResolution();
	shurs[i].y = rand() % (resolution.y - 20) + 10;
	shurs[i].x = resolution.x + 100 + rand() % 100;
	shurs[i].color = rand() % 15;
}

void BowAndArrow::checkShurs(float deltaTimeSeconds)
{
	//remove offscreen objects
	clearShurs();
	glm::ivec2 resolution = window->GetResolution();

	//and move the rest further left
	for (int i = 0; i < NUM_SHURS; i++)
	{
		if (shurs[i].x > resolution.x + 50) {
			if (rand() % 6 == 2) {
				shurMatrix = glm::mat3(1);
				shurs[i].x -= shurSpeed * deltaTimeSeconds;
				shurMatrix *= Transform2D::Translate(shurs[i].x, shurs[i].y);
				if (shurs[i].color)
					if (shurs[i].color == 1)
						RenderMesh2D(meshes["power"], shurMatrix, glm::vec3(1, 1, 0));
					else
						RenderMesh2D(meshes["shur"], shaders["VertexColor"], shurMatrix);
				else
					RenderMesh2D(meshes["live"], shurMatrix, glm::vec3(0, 1, 0));
			}
		}
		else
		{
			shurStep += deltaTimeSeconds;
			shurs[i].x -= shurSpeed * deltaTimeSeconds;
			shurMatrix = glm::mat3(1);
			shurMatrix *= Transform2D::Translate(shurs[i].x, shurs[i].y);


			if (shurs[i].color)
			{

				if (shurs[i].color == 1) {
					shurMatrix *= Transform2D::Rotate(shurStep * 2);
					RenderMesh2D(meshes["power"], shurMatrix, glm::vec3(1, 1, 0));
				}
				else {
					shurMatrix *= Transform2D::Rotate(shurStep);
					RenderMesh2D(meshes["shur"], shaders["VertexColor"], shurMatrix);
				}
			}
			else
				RenderMesh2D(meshes["live"], shurMatrix, glm::vec3(0, 1, 0));
		}
	}
}


void BowAndArrow::checkBallons(float deltaTimeSeconds)
{
	//remove offscreen ballons
	clearBallons();
	//and move the rest further up
	glm::ivec2 resolution = window->GetResolution();
	for (int i = 0; i < NUM_BALLONS; i++)
	{
		if (balloons[i].y <= -150) {
			//before moving a new ballon check a random number to make the ballons leave at different times
			if (rand() % 6 == 2) {
				ballonMatrix = glm::mat3(1);
				balloons[i].y += ballonSpeed * deltaTimeSeconds;
				ballonMatrix *= Transform2D::Translate(balloons[i].x, balloons[i].y);
				if (balloons[i].color)
					RenderMesh2D(meshes["balloon1"], shaders["VertexColor"], ballonMatrix);
				else
					RenderMesh2D(meshes["balloon0"], shaders["VertexColor"], ballonMatrix);
			}
		}
		else
		{
			ballonMatrix = glm::mat3(1);
			balloons[i].y += ballonSpeed * deltaTimeSeconds;
			if (balloons[i].x > resolution.x)
				balloons[i].wind *= -1;
			if (balloons[i].x < 0)
				balloons[i].wind *= -1;
			balloons[i].x += ballonSpeed / 2 * deltaTimeSeconds * balloons[i].wind;

			ballonMatrix *= Transform2D::Translate(balloons[i].x, balloons[i].y);

			if (balloons[i].color)
				RenderMesh2D(meshes["balloon1"], shaders["VertexColor"], ballonMatrix);
			else
				RenderMesh2D(meshes["balloon0"], shaders["VertexColor"], ballonMatrix);

			RenderMesh2D(meshes["line"], shaders["VertexColor"], ballonMatrix);
		}
	}
}

void BowAndArrow::FrameEnd()
{
	DrawCoordinatSystem();
}

void BowAndArrow::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_R && alive == 0)
	{
		alive = 3;
		initBallons();
		initShurs();
		SCORE = 0;
		holstered = true;
	}
}

void BowAndArrow::OnInputUpdate(float deltaTime, int mods) {

	float playerMoveSpeed = 200;
	glm::ivec2 resolution = window->GetResolution();
	//move the player up
	if (window->KeyHold(GLFW_KEY_W) && translateY < resolution.y - 50)
	{
		translateY += playerMoveSpeed * deltaTime;
	}
	//move the player down
	if (window->KeyHold(GLFW_KEY_S) && translateY - 50 > 0)
	{
		translateY -= playerMoveSpeed * deltaTime;
	}


}

void BowAndArrow::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void BowAndArrow::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	//angle the bow after the mouse
	double x = max(mouseX - (double)translateX, 0.001);
	double y = (double)window->GetResolution().y - mouseY - (double)translateY;

	angularStep = atan(y / x);
}

void BowAndArrow::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
	//on pressing the mouse button if an arrow is holstered enter shoot mode
	if (holstered) {
		shootMode = true;
	}

}

void BowAndArrow::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	//and on release, shoot the arrow 
	if (holstered && arrowSpeedX > 0) {
		shootMode = false;
		holstered = false;
	}
}

void BowAndArrow::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void BowAndArrow::OnWindowResize(int width, int height)
{
}
