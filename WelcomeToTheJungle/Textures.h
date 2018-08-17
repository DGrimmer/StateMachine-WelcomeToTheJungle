#pragma once
#include <map>
#include <SFML/Graphics/Texture.hpp>


class Textures
{
public:
	static Textures &GetInstance();
	sf::Texture* GetTexture(std::string name);
private:
	Textures();
	~Textures();
	std::map<std::string, sf::Texture*> textures;
};

