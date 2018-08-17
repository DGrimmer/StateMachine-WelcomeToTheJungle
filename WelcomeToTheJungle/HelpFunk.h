#pragma once

#include "SFML\Graphics.hpp"
#include <algorithm>
#include <iostream>

const float DELTATIME = 1.0f / 60.0f;

//Game stuff
const int GAME_NROFANIMALS = 200;

//Map stuff
static const unsigned int MAP_SIZE = 50;
const float MAP_TILESIZE = 32;

const float FOOD_VALUE = 35.0f;
const float FOOD_RESPAWNTIME = 15.0f;

//Animal stuff
const float BASE_HUNGERBUFFER = 50;
const float BASE_CONSIDERSELFHUNGRY = 0.75f;
const float BASE_HUNGERSPEED = 1; //how fast hunger goes down
const float BASE_LIFESPAN = 100; //how many seconds until getting too old 
const float BASE_SPEED = 32;
const float BASE_HP = 10.0f;
const float BASE_SIZE = 5;

const float ANIMAL_WANDERINGLEANGTH = 64.0f;

const float ANIMAL_MATURE = 20;
const float ANIMAL_FINDMATEDIST = 20 * MAP_TILESIZE;
const float ANIMAL_FINDNEWMATECOOLDOWN = 15;

const float ANIMAL_TIMEDEAD_DELETE = 10;

//## Movement multipiers ##
const float MOVE_GRASS_MULTIPLIER = 1;
const float MOVE_WATER_MULTIPLIER = 0.5f;
const float MOVE_STEPPE_MULTIPLIER = 0.9f;
const float MOVE_BEACH_MULTIPLIER = 0.8f;

//## Helpful functions ##
static float GetLength(sf::Vector2f v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}
static float GetDist(sf::Vector2f a, sf::Vector2f b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
static void Normalize(sf::Vector2f& v) {
	v /= GetLength(v);
}
static sf::Vector2f RandomPos() {
	int nrOfPixels = MAP_SIZE * MAP_TILESIZE;
	return sf::Vector2f(rand() % nrOfPixels, rand() % nrOfPixels);
}