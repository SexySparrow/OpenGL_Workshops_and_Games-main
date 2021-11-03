#pragma once
#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#define TWO_PI			(6.28318530718f)
#define NUM_TRIANGLES	(50)
#define NUM_BALLONS     (20)
#define NUM_SHURS       (10)

class BowAndArrow : public SimpleScene
{



	public:
		BowAndArrow();
		~BowAndArrow();

		void Init() override;

		void initBallons();

		void initShurs();

		typedef struct Ballon
		{
			float x, y;
			int color;
			int wind;
			bool hit;

			Ballon() {}

			Ballon(float x, float y, bool color)
			{
				this->x = x;
				this->y = y;
				this->color = color;
			}
		};

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void renderLives();
		void checkArrowCollision();
		bool insideBallon(double x, double y, double centx, double centy);
		void checkIfHitBalloon(int i);
		void fallingBalloons(int deltaTime);
		void RemoveBalloon(std::vector<BowAndArrow::Ballon>& pets);
		void checkOnScreen();
		void arrowMove(int deltaTime);
		void speedInc();
		void speedInc(int deltaTime);
		void checkIfHit(bool bow);
		bool shurArrowHit(int i);
		bool hitByShur(int i);
		void clearBallons();
		void clearShurs();
		void newBallon(int i);
		void newShur(int i);
		void checkBallons(float deltaTimeSeconds);
		void checkShurs(float deltaTimeSeconds);
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
		Ballon balloons[NUM_BALLONS], shurs[NUM_SHURS];
		std::vector<Ballon> hitBallons;

	protected:
		glm::mat3 modelMatrix = glm::mat3(1), ballonMatrix = glm::mat3(1), shurMatrix = glm::mat3(1), arrowMatrix = glm::mat3(1), hitMatrix = glm::mat3(1), powerMatrix = glm::mat3(1);
		float translateX, translateY, arrowX, arrowY;
		float scaleX, scaleY;
		float angularStep, shurStep, arrowStep;
		GLboolean moveRight;
		int currentBallons = 0;
		float ballonSpeed = 100, shurSpeed = 300;
		int alive = 3;
		float arrowSpeedX = 200, arrowSpeedY;
		bool holstered = true;
		bool shootMode = false;
		float gRotate = 1;
		int SCORE = 0;
		int shield = false;
};

