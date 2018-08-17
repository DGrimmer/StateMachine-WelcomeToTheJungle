#pragma once
#include <vector>
#include "Animal.h"
#include "SFML\Graphics.hpp"
#include "TileMap.h"

class GameManager
{
public:
	static GameManager& GetInstance();

	void Update(float delatatime);
	void Draw(sf::RenderWindow &window);
	void LoadMap();

	sf::Vector2f GetCloseFish(sf::Vector2f fromPos);
	sf::Vector2f GetCloseBush(sf::Vector2f fromPos);
	sf::Vector2f FindMate(sf::Vector2f fromPos);
	
	void ReadyToBeDeletedAnimal(Animal* animal);
	void ReadyToMate(Animal* animal);
	int GetNrOfAnimals();

private:
	GameManager();
	~GameManager();

	void DeleteAllDeadAnimals();
	void CreateNewAnimals();
	std::vector<Animal*> animals;
	std::vector<Animal*> animalsReadyToMate;
	std::vector<Animal*> animalsReadyToBeDeleted;


	std::vector<sf::Vector2f> listFish;
	std::vector<sf::Vector2f> listBush;
	
	sf::Font font_plz;
	sf::Text text_nrAnimal;
};

