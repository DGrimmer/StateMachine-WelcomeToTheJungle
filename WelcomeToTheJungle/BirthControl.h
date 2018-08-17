#pragma once

#include "GameManager.h"

class State_LookingForMate;

class BirthControl
{
public:
	BirthControl();
	~BirthControl();

	void ReadyToMate(State_LookingForMate* state);
private:
	void CheckForValidMating();

	std::vector<State_LookingForMate*> wantToMate;

	GameManager& GM;
};

