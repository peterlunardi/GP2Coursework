#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	bool CollisionChecker(glm::vec3, float, glm::vec3, float);
	void drawGame();
	void UpdatePositions();
	void CheckCollisions();

	Display _gameDisplay; //the window we set up with SDL
	GameState _gameState; //the current state of the game, is it running?
	Mesh shipMesh; //the mesh for our spaceship
	Mesh asteroidMesh; //the meshes of the asteroids
	Mesh asteroidMesh2;
	Mesh asteroidMesh3;
	Mesh bulletMesh; //mesh of the projectile
	Camera myCamera; //reference to the main camera

	//the textures of our various meshes
	Texture shipTexture; 
	Texture asteroidTexture;
	Texture bulletTexture;

	Shader shader; //our shader
	Audio audioDevice; //reference to our audio handler

	float counter; //incremented per frame to move objects
	float counter2; //incremented per frame to move our projectile
	float shipPos; //stores the x position of the ship, the player can move this
	float bulletPosX; //the coordinates of our projectile
	float bulletPosY;
	float bulletSpeed; //controls how quickly the bullet fires
	bool bulletFlying; //tells us if the bullet is in flight or not

	//these check if an asteroid has been hit,
	//use these so we dont check for collisions with something thats been hit
	bool asteroid1hit;
	bool asteroid2hit;
	bool asteroid3hit;

	//these unsigned integers are set when we load in specific sounds
	unsigned int shoot;
	unsigned int explosion;
	unsigned int background;

};

