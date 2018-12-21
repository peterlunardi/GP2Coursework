#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>

//All my objects transforms
Transform transform;
Transform transform1;
Transform transform2;
Transform transform3;
Transform transform4;

MainGame::MainGame()
{
	_gameState = GameState::PLAY; //Play the game
	Display* _gameDisplay = new Display(); //new display

	/*
	Mesh* mesh1();
	Mesh* mesh2();
	Shader* shader();
	Audio* audioDevice();
	*/
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();
	gameLoop();

}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay(); //initialise our display

	//load all of our models
	shipMesh.loadModel("..\\res\\f.obj");
	asteroidMesh.loadModel("..\\res\\rock2.obj");
	asteroidMesh2.loadModel("..\\res\\rock2.obj");
	asteroidMesh3.loadModel("..\\res\\rock2.obj");
	bulletMesh.loadModel("..\\res\\projectile.obj");

	//load all of our textures
	shipTexture.init("..\\res\\ship.jpg");
	asteroidTexture.init("..\\res\\rocktex.jpg");
	bulletTexture.init("..\\res\\bullet.jpg");

	//initialise our shader
	shader.init("..\\res\\shader"); //new shader

	//load all of our audio files
	shoot = audioDevice.loadSound("..\\res\\shoot.wav");
	explosion = audioDevice.loadSound("..\\res\\boom.wav");
	background = audioDevice.loadSound("..\\res\\bg.wav");

	//initialise the camera, filling in parameters for fov, aspect ratio etc..
	myCamera.initCamera(glm::vec3(0, 0, -6), 70.0f,
						(float)_gameDisplay.getWidth() / _gameDisplay.getHeight(),
						0.01f, 1000.0f);

	//setting certain variables to do with the movement of objects
	counter = 0.0f; //slowly rotates asteroids
	bulletPosX = shipPos; //our bullet is at our ships location
	bulletPosY = -2;

	asteroid1hit = false;
	asteroid2hit = false;
	asteroid3hit = false;

	audioDevice.playSound(background);
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		UpdatePositions(); //updates the positions of all our meshes
		processInput(); //handles player input
		drawGame(); //draws to the screen
		CheckCollisions(); //is our projectile colliding with any of the asteroids?
	}
}

void MainGame::CheckCollisions()
{
	if (CollisionChecker(bulletMesh.GetSpherePos(), bulletMesh.GetSphere(), asteroidMesh.GetSpherePos(), asteroidMesh.GetSphere()) && asteroid1hit == false)
	{
		audioDevice.playSound(explosion); //play the explosion sound since they are colliding
		asteroidMesh.~Mesh(); //destroys the mesh when collided with a projectile
		bulletFlying = false; //the bullet is reloaded
		counter2 = 0;
		asteroid1hit = true;
	}
	if (CollisionChecker(bulletMesh.GetSpherePos(), bulletMesh.GetSphere(), asteroidMesh2.GetSpherePos(), asteroidMesh2.GetSphere()) && asteroid2hit == false)
	{
		audioDevice.playSound(explosion); //play the explosion sound since they are colliding
		asteroidMesh2.~Mesh();
		bulletFlying = false;
		counter2 = 0;
		asteroid2hit = true;
	}
	if (CollisionChecker(bulletMesh.GetSpherePos(), bulletMesh.GetSphere(), asteroidMesh3.GetSpherePos(), asteroidMesh3.GetSphere()) && asteroid3hit == false)
	{
		audioDevice.playSound(explosion); //play the explosion sound since they are colliding
		asteroidMesh3.~Mesh();
		bulletFlying = false;
		counter2 = 0;
		asteroid3hit = true;
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym)
			{
			case SDLK_RIGHT:
				shipPos = shipPos - 0.1f; //ship moves to the right by altering the ships position variable every frame the key is held down
				break;
			case SDLK_LEFT:
				shipPos = shipPos + 0.1f;
				break;
			case SDLK_SPACE:
				if (bulletFlying == false)
				{
					audioDevice.playSound(shoot); //if we press space and our bullet isnt travelling, play shoot sound
				}
				bulletFlying = !bulletFlying; //this lets us reload the bullet
				break;
			}
		}
	}

}

bool MainGame::CollisionChecker(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float colDistance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + 
									(m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + 
									(m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z)); //calculates the distance between the two colliders being checked

	if (colDistance < (m1Rad + m2Rad)) //is the distance less than the 2 radii added together??  if yes, they are colliding!!
	{
		
		return true;
	}
	else
	{
		return false;
	}
}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f); //sets the colour of the screen

	shader.Bind(); //binds our shader
	shader.Update(transform, myCamera); //updates the shader with our new transform positions
	shipTexture.Bind(0); //binds our chosen texture
	shipMesh.draw(); //draws the mesh

	shader.Update(transform1, myCamera);
	asteroidTexture.Bind(0);
	asteroidMesh.draw();

	shader.Update(transform2, myCamera);
	asteroidTexture.Bind(0);
	asteroidMesh2.draw();

	shader.Update(transform3, myCamera);
	asteroidTexture.Bind(0);
	asteroidMesh3.draw();

	shader.Update(transform4, myCamera);
	bulletTexture.Bind(0);
	bulletMesh.draw();

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}

void MainGame::UpdatePositions()
{
	//where do we want our objects to appear on screen, how big? are they moving?
	transform.SetPos(glm::vec3(shipPos, -2, 0));
	transform.SetRot(glm::vec3(80, 0, 0));
	transform.SetScale(glm::vec3(0.02f, 0.02f, 0.02f));
	shipMesh.setSphereData(*transform.GetPos(), 0.3f);

	transform1.SetPos(glm::vec3(0, 2, 0));
	transform1.SetRot(glm::vec3(counter, counter, counter));
	transform1.SetScale(glm::vec3(0.08f, 0.08f, 0.08f));
	asteroidMesh.setSphereData(*transform1.GetPos(), 0.4f);

	transform2.SetPos(glm::vec3(2, 2, 0));
	transform2.SetRot(glm::vec3(counter, counter, counter));
	transform2.SetScale(glm::vec3(0.08f, 0.08f, 0.08f));
	asteroidMesh2.setSphereData(*transform2.GetPos(), 0.4f);

	transform3.SetPos(glm::vec3(-2, 2, 0));
	transform3.SetRot(glm::vec3(counter, counter, counter));
	transform3.SetScale(glm::vec3(0.08f, 0.08f, 0.08f));
	asteroidMesh3.setSphereData(*transform3.GetPos(), 0.4f);

	transform4.SetPos(glm::vec3(bulletPosX, bulletPosY + counter2, 0));
	transform4.SetRot(glm::vec3(0, 0, 0));
	transform4.SetScale(glm::vec3(0.003f, 0.003f, 0.003f));
	bulletMesh.setSphereData(*transform4.GetPos(), 0.1f);

	counter = counter + 0.0001f; //slowly rotates objects
	counter2 = counter2 + bulletSpeed; //used to make the bullet fly forwards

	if (bulletFlying)
	{
		bulletSpeed = 0.001;
	}

	if (bulletFlying == false)
	{
		bulletSpeed = 0;
		bulletPosX = shipPos;
		bulletPosY = -2;
		counter2 = 0;
	}
}
