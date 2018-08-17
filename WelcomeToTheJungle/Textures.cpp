#include "Textures.h"


using namespace std;
using namespace sf;

Textures &Textures::GetInstance()
{
	static Textures instance;
	return instance;
}

sf::Texture* Textures::GetTexture(std::string name)
{
	return textures.at(name);
}

Textures::Textures()
{
	Texture* grass = new sf::Texture();
	grass->loadFromFile("Tiles/Grass.png");

	Texture* water = new sf::Texture();
	water->loadFromFile("Tiles/Water.png");

	Texture* steppe = new sf::Texture();
	steppe->loadFromFile("Tiles/Steppe.png");

	Texture* beach = new sf::Texture();
	beach->loadFromFile("Tiles/Beach.png");

	Texture* forest = new sf::Texture();
	forest->loadFromFile("Tiles/Forest.png");

	Texture* bush = new Texture();
	bush->loadFromFile("Tiles/Bush.png");

	Texture* fish = new Texture();
	fish->loadFromFile("Tiles/Fish.png");

	textures.insert(pair<string, Texture*>("Grass", grass));
	textures.insert(pair<string, Texture*>("Water", water));
	textures.insert(pair<string, Texture*>("Steppe", steppe));
	textures.insert(pair<string, Texture*>("Beach", beach));
	textures.insert(pair<string, Texture*>("Forest", forest));
	textures.insert(pair<string, Texture*>("Bush", bush));
	textures.insert(pair<string, Texture*>("Fish", fish));

}

Textures::~Textures()
{

}