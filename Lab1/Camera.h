#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	Camera()
	{
	}

	//initialise the camera at a position with a specified projection
	void initCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	//returns our view projection
	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	//returns where the camera is currently positioned
	glm::vec3 GetCameraPos()
	{
		return this->pos;
	}

protected:
private:
	glm::mat4 projection; //the projection of our camera
	glm::vec3 pos; //where our camera is

	//these two vector3 represent our cameras rotation
	glm::vec3 forward;
	glm::vec3 up;
};


