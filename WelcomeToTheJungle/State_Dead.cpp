#include "State.h"
#include "Animal.h"
#include "GameManager.h"

using namespace std;
using namespace sf;

State_Dead::State_Dead(StateMachine* machine, Animal* animal) : 
	State(machine, animal)
{

}

State_Dead::~State_Dead() {

}

bool State_Dead::EnterReq() {
	return true;
}

void State_Dead::Enter() {
	cout << "Ups i Died" << endl;
	animal->GetVariables().shape.setFillColor(Color(0, 0, 0));
	animal->GetVariables().isDead = true;
}

void State_Dead::Update() {
	deathTimer -= DELTATIME;
	if (deathTimer <= 0)
		GameManager::GetInstance().ReadyToBeDeletedAnimal(animal);
}

bool State_Dead::ExitReq() {
	return false;
}

void State_Dead::Exit() {

}