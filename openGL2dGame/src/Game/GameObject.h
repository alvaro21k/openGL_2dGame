#pragma once

#include <GLM/glm.hpp>
#include <glad/glad.h>

#include "../utilities/textures.h"
#include "../utilities/SpriteRenderer.h"

class GameObject
{
public:
	glm::vec2 position, size, velocity;
	glm::vec3 color;
	float rotation;
	bool isSolid;
	bool isDestroyed;
	Texture2D sprite;

	GameObject() {};
	GameObject(glm::vec2 pos, glm::vec2 size, glm::vec2 vel = glm::vec2(0.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f), Texture2D sprite);

	virtual void Draw(SpriteRenderer& renderer);
};