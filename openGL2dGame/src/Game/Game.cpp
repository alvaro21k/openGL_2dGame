#include "Game.h"

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

    ResourceManager::loadTexture("./textures/awesomeface.png", true, "face");
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{
    Renderer->DrawSprite(ResourceManager::getTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}