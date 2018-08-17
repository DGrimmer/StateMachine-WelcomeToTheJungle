
#include "State.h"
#include "Animal.h"
#include "GameManager.h"
#include <iostream>
#include <random>
#include "TileMap.h"

using namespace sf;

State_LookingToMate::State_LookingToMate(StateMachine* machine, Animal* animal) : State(machine, animal)
{
}
State_LookingToMate::~State_LookingToMate()
{
}

bool State_LookingToMate::EnterReq() {
	return !isFindMateOnCD() && animal->GetVariables().age > ANIMAL_MATURE;
}
void State_LookingToMate::Enter() {
	isWandering = false;
	isGoingToMate = false;
}

void State_LookingToMate::Update() {
	State::Update();

	//find mate
	Vector2f matePos = GameManager::GetInstance().FindMate(animal->GetPos());
	//check if valid target
	if (animal->GetPos() != matePos) 
		targetPos = matePos;
	else {
		//no target, better luck next time
		State::ResetTimer_findMate();
		machine->ChangeState_Idle();
	}

	if (animal->GoToPoint(targetPos)) {

		ResetTimer_findMate();
		GameManager::GetInstance().ReadyToMate(animal);
		machine->ChangeState_Idle();
	}
}

bool State_LookingToMate::ExitReq() {
	return true;
}

void State_LookingToMate::Exit() {

}