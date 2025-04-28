#include "Game.h"

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(500.0f);
// Initial velocity of the ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);

const float BALL_RADIUS(12.5f);

BallObject* Ball;
GameObject* Player;
SpriteRenderer* Renderer;

bool CheckCollision(GameObject& one, GameObject& two);
//bool CheckCollision(BallObject& ball, GameObject& two);

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
    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);

    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::getTexture("paddle"));
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::getTexture("face"));
}

void Game::Update(float dt)
{
    Ball->Move(dt, this->width);
    this->DoCollision();
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
            {
                Player->position.x -= velocity;
                if (Ball->stuck)
                {
                    Ball->position.x -= velocity;
                }
            }              
        }

        if (this->keys[GLFW_KEY_D] || this->keys[GLFW_KEY_RIGHT])
        {
            if (Player->position.x <= this->width - Player->size.x)
            {
                Player->position.x += velocity;
                if (Ball->stuck)
                {
                    Ball->position.x += velocity;
                }
            }      
        }

        if (this->keys[GLFW_KEY_SPACE])
        {
            Ball->stuck = false;
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
        Ball->Draw(*Renderer);
    }
}

void Game::DoCollision()
{
    for (GameObject& box : this->levels[this->level].bricks)
    {
        if (!box.isDestroyed)
        {
            if (CheckCollision(*Ball, box))
            {
                if (!box.isSolid)
                {
                    box.isDestroyed = true;
                }
            }
        }
    }
}

bool CheckCollision(GameObject& one, GameObject& two)
{
    bool collisionX = one.position.x + one.size.x >= two.position.x &&
        two.position.x + two.size.x >= one.position.x;

    bool collisionY = one.position.y + one.size.y >= two.position.y &&
        two.position.y + two.size.y >= one.position.y;

    return collisionX && collisionY;
}

bool CheckCollision(BallObject& ball, GameObject& two)
{
    glm::vec2 center(ball.position + ball.radius);

    glm::vec2 half_extents(two.size.x / 2.0f, two.size.y / 2.0f);
    glm::vec2 aabb_center(two.position.x + half_extents.x, two.position.y + half_extents.y);
    glm::vec2 difference = center - aabb_center;

    glm::vec2 clamped = glm::clamp(difference, -half_extents, half_extents);
    glm::vec2 closest = aabb_center + clamped;

    difference = closest - center;
    return glm::length(difference) < ball.radius;
}