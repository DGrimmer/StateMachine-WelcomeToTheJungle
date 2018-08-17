#include "State.h"
#include "Animal.h"

using namespace std;
using namespace sf;


State_Idle::State_Idle(StateMachine* machine, Animal* animal) :
	State(machine, animal)
{

}
State_Idle::~State_Idle() {

}

bool State_Idle::EnterReq() {
	return true;
}
void State_Idle::Enter() {
	isWandering = false;
}

void State_Idle::Update() {
	State::Update();

	//try to change state to "Looking for mate"
	machine->ChangeState_LookingToMate();




	//wander around..
	if (!isWandering) {
		Vector2f dir = Vector2f(sin(rand()), sin(rand()));
		dir = animal->GetPos() + dir *  ANIMAL_WANDERINGLEANGTH;
		dir.x = abs(dir.x);
		dir.y = abs(dir.y);
		if (dir.x > MAP_SIZE*MAP_TILESIZE)
			dir.x = MAP_SIZE*MAP_TILESIZE;
		if (dir.y > MAP_SIZE*MAP_TILESIZE)
			dir.y = MAP_SIZE*MAP_TILESIZE;

		isWandering = true;
		targetPos = dir;
	}
	if (animal->GoToPoint(targetPos)) {
		isWandering = false;
	}
	
}


bool State_Idle::ExitReq() {
	return true;
}
void State_Idle::Exit() {

}