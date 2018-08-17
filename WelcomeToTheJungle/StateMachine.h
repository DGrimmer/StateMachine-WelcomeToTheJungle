#pragma once
#include "State.h"

struct Variables;
class Animal;


class StateMachine {
public:
	StateMachine(Animal* animal);
	~StateMachine();

	void Update();

	void ChangeState_Idle();
	void ChangeState_LookingToMate();
	void ChangeState_GoDrink();
	void ChangeState_GoEat();
	void ChangeState_Die();

	void ChangeToPreviousState();
	

	Variables GetHostsVariables();

private:
	void SetStartState(State* state);

	void ChangeState(State* newState);
	State* currentState;
	State* previousState;

	Animal* animal;

	State_Idle* idle;
	State_LookingToMate* mate;
	State_GoDrink* goDrink;
	State_GoEat* goEat;
	State_Dead* dead;
};
