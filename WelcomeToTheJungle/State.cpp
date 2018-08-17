#include "State.h"
#include "Animal.h"

using namespace std;

void State::Update() {
	//over time effects	
	CooldownTick();
	animal->GetVariables().age += DELTATIME;
	animal->GetVariables().hunger -= BASE_HUNGERSPEED * DELTATIME;
	//animal->GetVariables().thirst -= 2.5f * DELTATIME;





	//hunger dmg
	if (animal->GetVariables().hunger < 0) {
		animal->GetVariables().hp -= 1.0f * DELTATIME;
	}

	// set color based on age
	sf::Color color = animal->GetVariables().startColor;
	float colorAlteration = 1 - (animal->GetVariables().age / BASE_LIFESPAN);
	color.r *= colorAlteration;
	color.g *= colorAlteration;
	color.b *= colorAlteration;
	animal->GetVariables().shape.setFillColor(color);

	//Death Checking 
	if (animal->GetVariables().age > BASE_LIFESPAN) {
		cout << "Death: Age" << endl;
		machine->ChangeState_Die();
		return;
	}
	if (animal->GetVariables().hp < 0) {
		cout << "Death: Hunger" << endl;
		machine->ChangeState_Die();
		return;
	}
	// needs food?
	if (animal->GetHungerSatisfaction() < BASE_CONSIDERSELFHUNGRY) {
		machine->ChangeState_GoEat();
		return;
	}
}

void State::CooldownTick() {
	if (cooldown_FindMate > 0)
		cooldown_FindMate -= DELTATIME;
}

bool State::isFindMateOnCD() {
	return cooldown_FindMate > 0;
}

void State::ResetTimer_findMate() {
	cooldown_FindMate = ANIMAL_FINDNEWMATECOOLDOWN;
}
