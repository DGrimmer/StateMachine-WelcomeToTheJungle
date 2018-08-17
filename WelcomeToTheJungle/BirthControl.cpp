#include "BirthControl.h"
#include "State.h"

using namespace std;

BirthControl::BirthControl() : GM(GameManager::GetInstance())
{

}


BirthControl::~BirthControl()
{
}

void BirthControl::ReadyToMate(State_LookingForMate* state) {
	wantToMate.push_back(state);
}

void BirthControl::CheckForValidMating() {

	
}