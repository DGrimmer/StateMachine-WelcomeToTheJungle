
#include "Animal.h"
#include <iostream>
#include "HelpFunk.h"
#include "TileMap.h"
#include <random>


using namespace std;
using namespace sf;


Animal::Animal()
{
	stateMachine = new StateMachine(this);

	variables.hunger = variables.hunger_buffer;
	variables.thirst = variables.thirst_buffer;
	
	variables.canEatMeat = false;
	variables.canEatVeggies = true;
	
	variables.shape.setRadius(variables.size);
	variables.shape.setOrigin(Vector2f(variables.shape.getRadius(), variables.shape.getRadius()));
	variables.shape.setFillColor(variables.startColor);

	pos = RandomPos();
}

Animal::Animal(Vector2f startPos) : Animal(){
	pos = startPos;
}


Animal::~Animal()
{
}

void Animal::Update(float deltatime) 
{
	

	stateMachine->Update();
}

void Animal::AddToThirst(float value) 
{
	
	variables.thirst += value;
	if (variables.thirst > variables.thirst_buffer)
		variables.thirst = variables.thirst_buffer;
}

void Animal::AddToHunger(float value)
{
	variables.hunger += value;
	if (variables.hunger > variables.hunger_buffer)
		variables.hunger = variables.hunger_buffer;
}

float Animal::GetHungerSatisfaction() {
	return variables.hunger / variables.hunger_buffer;
}

bool Animal::GoToPoint(sf::Vector2f targetPos) {
	if (GetDist(pos, targetPos) < 0.3) {	
		return true;
	}

	Vector2f dir = targetPos - pos;
	Normalize(dir);

	SetPos(pos + dir * variables.speed * TileMap::GetInstance().GetMoveMulti(pos) * DELTATIME);
	return false;
}

Vector2f Animal::GetPos() {
	return pos;
}

void Animal::SetPos(Vector2f newPos) {
	pos = newPos;
}

void Animal::Draw(RenderWindow &window) {
	variables.shape.setPosition(pos);
	window.draw(variables.shape);
}

Variables &Animal::GetVariables() {
	return variables;
}

