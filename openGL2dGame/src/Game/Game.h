#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>

#include "../utilities/ResourceManagement.h"
#include "../utilities/SpriteRenderer.h"
#include "../utilities/textures.h"
#include "./GameLevel.h"
#include "./GameObjects/BallObject.h"

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game {
public:
    std::vector<GameLevel> levels;
    unsigned int level;
	//game state
	GameState state;
	bool keys[1024];
	unsigned int width, height;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();  
    void DoCollision();
};