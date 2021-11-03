#pragma once
#include "../../../Visual Studio/Panel.h"
#include "Component/SimpleScene.h"
#include "Laboratoare/Laborator7/Laborator7.h"
#include "LabCamera.h"

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void InitStartArea();
	void InitLamps();
	void Init() override;

private:
	void FrameStart() override;
	void MoveLamps();
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;
	void CheckAlive();
	void InitLanes();
	void CreatePanels();
	void MovePanels();
	void RemovePlatformAllLanes();
	void RemovePlatform(std::vector<Panel*>& offScreen);
	void Gravity();
	void CheckCollision();

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void renderLives();
	void DeadUpdate();
	void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
	Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices,
	                 const std::vector<unsigned short>& indices);
	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix_param, const glm::vec3& color, const glm::vec3& lightPosition);
	glm::vec3 GetClosestLight(glm::vec3 pos);

protected:
	glm::mat4 modelMatrix, panelMatrix;
	float translateX = 0, translateY = 0, translateZ = 0;
	int platformSpeed = 100;
	bool onPlatform = false;
	std::vector<std::vector<Panel*>> all_Lanes;
	glm::vec3 lampPos[5];
	long long index = 0;
	float speed_Y = -0.2;
	TEMA2::Camera* camera;
	glm::mat4 projectionMatrix, lampMatrix;
	bool gap[5];
	int alive = 3, speed_lock = 0;
	float fuel = 100;
};

