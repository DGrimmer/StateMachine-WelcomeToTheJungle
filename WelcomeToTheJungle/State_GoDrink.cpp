
#include "State.h"
#include "Animal.h"
#include <iostream>


State_GoDrink::State_GoDrink(StateMachine* machine, Animal* animal) : 
	State(machine, animal)
{
}

State_GoDrink::~State_GoDrink()
{
}

bool State_GoDrink::EnterReq() {
	return true;
}

void State_GoDrink::Enter() {
	cout << "Warning, drinking state not complete!!" << endl;
	cout << "MM lets go for a drink" << endl;
}

void State_GoDrink::Update() {
	State::Update();
}

bool State_GoDrink::ExitReq() {
	return true;
}

void State_GoDrink::Exit() {
	cout << "No time for drinking" << endl;
}

