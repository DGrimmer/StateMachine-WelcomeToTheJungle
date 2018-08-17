
#include <iostream>

#include "SFML\Graphics.hpp"
#include "CameraController.h"
#include "GameManager.h"
#include "TileMap.h"
#include <direct.h>
#include "HelpFunk.h"
#include <time.h>
#include <random>

using namespace std;


int main() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	window.setFramerateLimit(60.0f);
	//float DELTATIME = 1.0f / 60.0f;
	
	srand(time(NULL));
	_mkdir("TileMap");
	TileMap& tileMap = TileMap::GetInstance();
	GameManager &GM = GameManager::GetInstance();
	CameraController CController(window);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			CController.UpdateEvent(window, event);
			tileMap.Update_Event(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
			
		}

		CController.Update();
		tileMap.Update();
		GM.Update(DELTATIME);


		window.clear();
		tileMap.Draw(window);
		GM.Draw(window);
		CController.Draw(window);
		window.display();
	}

	return 0;
}