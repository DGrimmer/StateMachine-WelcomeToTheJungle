#include "GameManager.h"
#include "HelpFunk.h"
#include <iostream>

using namespace std;
using namespace sf;

GameManager &GameManager::GetInstance() 
{
	static GameManager instance;
	return instance;
}

GameManager::GameManager()
{
	font_plz.loadFromFile("PLZ.ttf");
	text_nrAnimal.setFont(font_plz);
	text_nrAnimal.setCharacterSize(20);
	text_nrAnimal.setPosition(20, 0);

	

	for (int i = 0; i < GAME_NROFANIMALS; i++) {
		animals.push_back(new Animal());
	}
	LoadMap();
}

void GameManager::LoadMap() {
	listBush = TileMap::GetInstance().GetAllBush();
	listFish= TileMap::GetInstance().GetAllFish();
}

GameManager::~GameManager()
{
}

void GameManager::Update(float deltatime) 
{
	DeleteAllDeadAnimals();

	for each (Animal* animal in animals)
		animal->Update(deltatime);


	CreateNewAnimals();
}

Vector2f GameManager::FindMate(Vector2f fromPos) {
	Vector2f bestTarget;
	float bestDist = ANIMAL_FINDMATEDIST;
	bool foundBetter = false;

	for each(Animal* animal in animals) {
		//not it self
		if (fromPos == animal->GetPos())
			continue;
		//not dead animals
		if (animal->GetVariables().isDead)
			continue;
		//not babies
		if (animal->GetVariables().age < ANIMAL_MATURE)
			continue;


		float dist = GetDist(animal->GetPos(), fromPos);
		if (dist < bestDist) {
			foundBetter = true;
			bestDist = dist;
			bestTarget = animal->GetPos();
		}
	}
	
	if (foundBetter) 
		return bestTarget;
	else
		return fromPos;
}

void GameManager::ReadyToMate(Animal* animal) {
	animalsReadyToMate.push_back(animal);
}

void GameManager::CreateNewAnimals() {
		//TODO, inga peddon, eller necrofilister
	
	for each(Animal* animal in animalsReadyToMate) {
		animals.push_back(new Animal(animal->GetPos()));
		cout << "new baby" << endl;
	}

	animalsReadyToMate.clear();
}

void GameManager::DeleteAllDeadAnimals() {
	for (int i = 0; i < animalsReadyToBeDeleted.size(); i++) {
		for (int j = 0; j < animals.size(); j++) {
			if (animalsReadyToBeDeleted[i] == animals[j]) {
				delete(animals[j]);
				animals.erase(animals.begin() + j);
				break;
			}
		}
	}
	animalsReadyToBeDeleted.clear();
}

void GameManager::ReadyToBeDeletedAnimal(Animal* animal) {
	animalsReadyToBeDeleted.push_back(animal);
}

Vector2f GameManager::GetCloseFish(Vector2f fromPos) {
	bool foundTarget = false;
	float bestDist = 100000;
	Vector2f targetPos;

	for each(Vector2f pos in listFish) {
		float dist = GetDist(fromPos, pos);
		if (dist < bestDist) {
			bestDist = dist;
			foundTarget = true;
			targetPos = pos;
		}
	}
	if (foundTarget)
		return targetPos;
	
	return fromPos;
}
Vector2f GameManager::GetCloseBush(Vector2f fromPos) {
	bool foundTarget = false;
	float bestDist = 100000;
	Vector2f targetPos;

	for each(Vector2f pos in listBush) {
		if (TileMap::GetInstance().GetTileObj(pos) == Empty)
			continue;
		
		float dist = GetDist(fromPos, pos);
		if (dist < bestDist) {
			bestDist = dist;
			foundTarget = true;
			targetPos = pos;
		}
	}
	if (foundTarget)
		return targetPos;

	return fromPos;
}
int GameManager::GetNrOfAnimals() {
	return animals.size();
}

void GameManager::Draw(RenderWindow &window)
{
	for each (Animal* animal in animals)
		animal->Draw(window);
	
	text_nrAnimal.setString("Animals: " + to_string(animals.size()));
	window.draw(text_nrAnimal);
}