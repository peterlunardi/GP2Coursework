#pragma once

#include <glm\glm.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <glm/gtc/type_ptr.hpp>

class Audio
{
	//these two structs store the data of the sound file to be read
	struct data {
		int sourceID, bufferID;
		char* buffer;
		std::string name;
		data(unsigned int sI, unsigned int bI, char* b, const char* n)
		{
			this->sourceID = sI;
			this->bufferID = bI;
			this->buffer = b;
			this->name = n;
		}

	};

	struct Vector3
	{
		float x, y, z;
	};
	std::vector<data> datas;
	ALCcontext* context; //holds the openAL context
	ALCdevice *device; //references our sound card
	bool isBigEndian(); //how does our computer store sound data?
	int convertToInt(char* buffer, int length); //converts char arrays to int arrays
	char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size); //used to load wav files

public:
	Audio();
	~Audio();
	unsigned int loadSound(const char* filename); //loads the sounds file at the specified pathway
	void deleteSound(unsigned int id);
	void playSound(unsigned int id); //plays the sound referenced by the unsigned int parameter
	void playSound(unsigned int id, glm::vec3& pos); //plays a sound at a specific vector 3 position
	void stopSound(unsigned int id); //stops a sound from playing
	void setlistener(glm::vec3& pos, glm::vec3& camLookAt); //sets up the listener based on the cameras position and projection

private:
	
};

