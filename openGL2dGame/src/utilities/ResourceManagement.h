#pragma once

#include <map>
#include <string>

#include <glad/glad.h>

#include "textures.h"
#include "shader.h"

class ResourceManager {
public:
	//resource storage
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures;
	//loads and generates a shader program from file.
	static Shader loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	//retrieves a stored shader
	static Shader getShader(std::string name);
	//loads and generates a texture from file
	static Texture2D loadTexture(const char* file, bool alpha, std::string name);
	//retrieves a stored texture
	static Texture2D getTexture(std::string name);
	//properly de-allocate all loaded resources
	static void clear();

private:
	ResourceManager(){}
	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);
	static Texture2D loadTextureFromFile(const char* file, bool alpha);


};