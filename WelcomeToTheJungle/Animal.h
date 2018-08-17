#pragma once
#include "StateMachine.h"
#include "SFML\Graphics.hpp"
#include "HelpFunk.h"

struct Variables{
	float hunger_buffer = BASE_HUNGERBUFFER;
	float hp = BASE_HP;
	float size = BASE_SIZE;
	float speed = BASE_SPEED;
	
	float thirst_buffer;
	float hunger;
	float thirst;
	float age = 0;

	bool canEatMeat;
	bool canEatVeggies;
	bool isDead = false;
	//bool canSwim = false;

	//sf stuff
	sf::CircleShape shape;
	sf::Color startColor = sf::Color::Magenta;

};

class Animal
{
public:
	Animal();
	Animal(sf::Vector2f startPos);
	~Animal();

	void AddToThirst(float value);
	float GetHungerSatisfaction();
	void AddToHunger(float value);
	


	Variables &GetVariables();
	sf::Vector2f GetPos();
	void SetPos(sf::Vector2f pos);

	void Update(float deltatime);
	void Draw(sf::RenderWindow &window);
	bool GoToPoint(sf::Vector2f pos);

	StateMachine* stateMachine;
private:
	Variables variables;
	sf::Vector2f pos;

	//bool hasTarget = false;
	//sf::Vector2f targetPos;
	
};

