#pragma once
#include "SFML\Graphics.hpp"
#include "HelpFunk.h"

using namespace std;

class StateMachine;
class Animal;
class GameManager;

class State
{
public:
	virtual bool EnterReq() = 0;
	virtual void Enter() = 0;

	virtual void Update();

	virtual bool ExitReq() = 0;
	virtual void Exit() = 0;
	void ResetTimer_findMate();
protected:
	State(StateMachine* machine, Animal* animal) {
		this->machine = machine;
		this->animal = animal;
	}
	StateMachine* machine;
	Animal* animal;
	sf::Vector2f targetPos;

	bool isFindMateOnCD();
private:
	//cooldown
	void CooldownTick();
	float cooldown_FindMate;

};

class State_Idle : public State 
{
public:
	State_Idle(StateMachine* machine, Animal* animal);
	~State_Idle();

	virtual bool EnterReq();
	virtual void Enter();

	virtual void Update();


	virtual bool ExitReq();
	virtual void Exit();

private:
	bool isWandering = false;

};

class State_LookingToMate : public State
{
public:
	State_LookingToMate(StateMachine* machine, Animal* animal);
	~State_LookingToMate();

	virtual bool EnterReq();
	virtual void Enter();

	virtual void Update();

	virtual bool ExitReq();
	virtual void Exit();

private:
	bool isGoingToMate = false;
	bool isWandering = false;
};

class State_GoDrink : public State
{
public:
	State_GoDrink(StateMachine* machine, Animal* animal);
	~State_GoDrink();

	virtual bool EnterReq();
	virtual void Enter();

	virtual void Update();


	virtual bool ExitReq();
	virtual void Exit();
};

class State_GoEat : public State
{
public:
	State_GoEat(StateMachine* machine, Animal* animal);
	~State_GoEat();

	virtual bool EnterReq();
	virtual void Enter();

	virtual void Update();

	virtual bool ExitReq();
	virtual void Exit();
};

class State_Dead : public State 
{
public:
	State_Dead(StateMachine* machine, Animal* animal);
	~State_Dead();

	virtual bool EnterReq();
	virtual void Enter();

	virtual void Update();

	virtual bool ExitReq();
	virtual void Exit();

	
private:
	float deathTimer = ANIMAL_TIMEDEAD_DELETE;
};