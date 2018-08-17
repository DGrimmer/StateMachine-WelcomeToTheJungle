// StateMachine.cpp : Defines the entry point for the console application.
//

#include "StateMachine.h"
#include "Animal.h"
#include "State.h"


using namespace std;

StateMachine::StateMachine(Animal* animal) 
{
	this->animal = animal;
	
	idle = new State_Idle(this, animal);
	mate = new State_LookingToMate(this, animal);
	goDrink = new State_GoDrink(this, animal);
	goEat = new State_GoEat(this, animal);
	dead = new State_Dead(this, animal);

	SetStartState(idle);
};

StateMachine::~StateMachine() 
{

};

void StateMachine::SetStartState(State* startState) {
	previousState = startState;
	currentState = startState;
	currentState->Enter();
}

void StateMachine::Update()
{
	currentState->Update();
}

void StateMachine::ChangeState_Idle() {
	ChangeState(idle);
}

void StateMachine::ChangeState_LookingToMate() {
	ChangeState(mate);
}

void StateMachine::ChangeState_GoDrink() {
	ChangeState(goDrink);
}

void StateMachine::ChangeState_GoEat() {
	ChangeState(goEat);
}

void StateMachine::ChangeState_Die() {
	ChangeState(dead);
}

void StateMachine::ChangeState(State* newState)
{
	if (currentState == newState)
		return;
	
	if (!currentState->ExitReq() || !newState->EnterReq())
		return;
	

	previousState = currentState;
	currentState->Exit();
	currentState = newState;
	currentState->Enter();
}

void StateMachine::ChangeToPreviousState()
{
	ChangeState(previousState);
}

Variables StateMachine::GetHostsVariables()
{
	return animal->GetVariables();
}

