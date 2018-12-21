#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0))
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct Sphere
{
public:

	Sphere() {}

	glm::vec3 position;
	float radius;

	Sphere(const glm::vec3& pos, float rad)
	{
		this->position = pos;
		this->radius = rad;
	}

	//getters
	glm::vec3* GetPos() { return &position; }
	float* GetRad() { return &radius; }

	//setters
	void SetPosition(glm::vec3& pos) { this->position = pos; }
	void SetRadius(float& rad) { this->radius = rad; }
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void draw();
	void init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void loadModel(const std::string& filename);
	void initModel(const IndexedModel& model);
	void setSphereData(glm::vec3 pos, float r);

	Sphere meshSphere;

	glm::vec3 GetSpherePos() { return meshSphere.position; }
	float GetSphere() { return meshSphere.radius; }

private:



	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw
};

