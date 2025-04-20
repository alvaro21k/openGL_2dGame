#pragma once

#include <vector>
#include <fstream>
#include <sstream>

#include "GameObject.h"
#include "../utilities/ResourceManagement.h"


class GameLevel {
public:
	//level state
	std::vector<GameObject> bricks;
	//check if the level is completed
	

	GameLevel(){}
	//load level from file
	void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
	//render level
	void Draw(SpriteRenderer& renderer);
	bool isCompleted();

private:
	//init level from tile data
	void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};