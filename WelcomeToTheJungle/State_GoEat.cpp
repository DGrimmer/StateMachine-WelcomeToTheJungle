#include "State.h"
#include "Animal.h"
#include <iostream>
#include "GameManager.h"

using namespace std;
using namespace sf;

State_GoEat::State_GoEat(StateMachine* machine, Animal* animal) : State(machine, animal)
{

}
State_GoEat::~State_GoEat()
{

}

bool State_GoEat::EnterReq() {
	return true;
}

void State_GoEat::Enter()
{

}

void State_GoEat::Update()
{
	State::Update();


	targetPos = GameManager::GetInstance().GetCloseBush(animal->GetPos());


	if (animal->GoToPoint(targetPos)) {
		animal->AddToHunger(TileMap::GetInstance().GetFoodFromTile(animal->GetPos()));
		targetPos = GameManager::GetInstance().GetCloseBush(animal->GetPos());

	}

	if (animal->GetHungerSatisfaction() >= BASE_CONSIDERSELFHUNGRY)
		machine->ChangeState_Idle();

}

bool State_GoEat::ExitReq() {
	return true;
}

void State_GoEat::Exit()
{
}