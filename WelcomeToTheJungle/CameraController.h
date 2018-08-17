#pragma once

#include "SFML\Graphics.hpp"
#include <iostream>
#include "TileMap.h"
#include "GameManager.h"

using namespace std;
using namespace sf;

class CameraController
{

public:
	CameraController(RenderWindow& window) : myWindow(window) {
		myView = myWindow.getView();
		
		font.loadFromFile("PLZ.ttf");
		text.setFont(font);
		text.setCharacterSize(20);
		text.setPosition(20, 0);
		text.setPosition(Vector2f(myView.getCenter().x - myWindow.getSize().x * GetZoomScale() / 2, myView.getCenter().y - myWindow.getSize().y * GetZoomScale() / 2));

	}
	~CameraController() {};
	void UpdateEvent(RenderWindow& window, Event event) {
		newChange = false;

		if (event.type == Event::MouseWheelMoved) {
			myView.zoom(1.0f - event.mouseWheel.delta / 10.0f);
			newChange = true;
		}
		if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::W)) {
			myView.move(RotMove(Vector2f(0, -speed * GetZoomScale()), myView.getRotation()));
			newChange = true;
		}
		if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::S)) {
			myView.move(RotMove(Vector2f(0, speed * GetZoomScale()), myView.getRotation()));
			newChange = true;
		}
		if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::D)) {
			myView.move(RotMove(Vector2f(speed * GetZoomScale(), 0), myView.getRotation()));
			newChange = true;
		}
		if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::A)) {
			myView.move(RotMove(Vector2f(-speed * GetZoomScale(), 0), myView.getRotation()));
			newChange = true;
		}
		if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Q)) {
			myView.rotate(rotSpeed);
			newChange = true;
		}

		if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::E)) {
			myView.rotate(-rotSpeed);
			newChange = true;
		}

		
		if (newChange) {
			text.setPosition(Vector2f(myView.getCenter().x - myWindow.getSize().x * GetZoomScale() /2, myView.getCenter().y - myWindow.getSize().y * GetZoomScale() / 2));
			text.setScale(GetZoomScale(),GetZoomScale());
			myWindow.setView(myView);
		}

	}

	void Update() {
		text.setString("Animal: " + to_string(GameManager::GetInstance().GetNrOfAnimals()));
	}

	float GetZoomScale() {
		float zoomScale = myView.getSize().x/ myWindow.getSize().x ;
		return zoomScale;
	}

	void Draw(RenderWindow& window) {
		window.draw(text);
	}
private:
	Vector2f RotMove(Vector2f move, float angle) {

		//convert to radians
		angle = angle * (3.1415f / 180.0f);

		return Vector2f(move.x * cosf(angle) - move.y * sinf(angle),
			move.x * sinf(angle) + move.y * cosf(angle));
	}
	sf::Text text;
	sf::Font font;
	float rotSpeed = 5.0f;
	float speed = 15.0f;
	bool newChange = false;
	View myView;
	RenderWindow &myWindow;

};

