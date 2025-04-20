#include "Game.h"

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(500.0f);

GameObject* Player;
SpriteRenderer* Renderer;

Game::Game(unsigned int width, unsigned int height)
    : state(GAME_ACTIVE), keys(), width(width), height(height)
{

}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    ResourceManager::loadShader("./src/shaders/sprite.vs", "./src/shaders/sprite.fs", nullptr, "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
    ResourceManager::getShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::getShader("sprite").SetMatrix4("projection", projection);

    Renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));

    //load textures
    ResourceManager::loadTexture("./textures/background.jpg", false, "background");
    ResourceManager::loadTexture("./textures/awesomeface.png", true, "face");
    ResourceManager::loadTexture("./textures/block.png", false, "block");
    ResourceManager::loadTexture("./textures/block_solid.png", false, "block_solid");
    ResourceManager::loadTexture("./textures/paddle.png", true, "paddle");
    //load levels
    GameLevel one; one.Load("./levels/one.lvl", this->width, this->height / 2);
    GameLevel two; two.Load("./levels/two.lvl", this->width, this->height / 2);
    GameLevel three; three.Load("./levels/three.lvl", this->width, this->height / 2);
    GameLevel four; four.Load("./levels/four.lvl", this->width, this->height / 2);

    this->levels.push_back(one);
    this->levels.push_back(two);
    this->levels.push_back(three);
    this->levels.push_back(four);
    this->level = 0;

    glm::vec2 playerPos = glm::vec2(this->width / 2.0f - PLAYER_SIZE.x / 2.0f, this->height - PLAYER_SIZE.y);

    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::getTexture("paddle"));
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
    if (this->state == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        //move player board
        if (this->keys[GLFW_KEY_A] || this->keys[GLFW_KEY_LEFT])
        {
            if (Player->position.x >= 0)
                Player->position.x -= velocity;
        }

        if (this->keys[GLFW_KEY_D] || this->keys[GLFW_KEY_RIGHT])
        {
            if (Player->position.x <= this->width - Player->size.x)
                Player->position.x += velocity;
        }
    }
}

void Game::Render()
{
    if (this->state == GAME_ACTIVE)
    {
        //draw background
        Renderer->DrawSprite(ResourceManager::getTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);
        //draw level
        this->levels[this->level].Draw(*Renderer);
        Player->Draw(*Renderer);
    }
}