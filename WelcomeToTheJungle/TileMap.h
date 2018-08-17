#pragma once

#include <vector>
#include "HelpFunk.h"
#include "Textures.h"
#include <map>
#include <tuple>

enum TileGround
{
	Grass,
	Water,
	Steppe,
	Beach
};
enum TileObj {
	Empty,
	Forest,
	Bush,
	Fish
};


class TileMap
{
private:

public:
	static TileMap& GetInstance();
	void SetTileTypeToSelected(sf::Vector2f pos);

	float GetMoveMulti(sf::Vector2f pos);
	TileObj GetTileObj(sf::Vector2f targetPos);
	std::vector<sf::Vector2f> GetAllBush();
	std::vector<sf::Vector2f> GetAllFish();
	sf::Vector2f GetCloseWater(sf::Vector2f fromPos);

	float GetFoodFromTile(sf::Vector2f currentPos);

	int GetTileSize();
	int GetMapSize();

	void SaveToFile();
	void LoadFromFile();
	bool isEditingOn();

	void Update_Event(sf::RenderWindow& window, sf::Event event);
	void Update();
	void Draw(sf::RenderWindow& wndow);

	sf::Vector2i Conv_WorldPosToMapIndex(sf::Vector2f pos);
private:
	TileMap();
	~TileMap();

	Textures& textureBank;

	//edit tools
	bool canEdit = false;
	int onLayer = 0;
	TileGround drawTileLayer1 = Water;
	TileObj drawTileLayer2 = Forest;
	bool isHoldingMousebotton = false;

	//file save and load
	std::string mapName = "TileMap/";
	std::string layer1Name = "Layer1.map";
	std::string layer2Name = "Layer2.map";


	

	struct TimerElement {
		TimerElement(float timer, sf::Vector2i index, TileObj type) :
			timer(timer), index(index), type(type) {};

		float timer;
		sf::Vector2i index;
		TileObj type;
	};
	std::vector<TimerElement> activatedTiles;

	TileGround tileMapGround[MAP_SIZE][MAP_SIZE];
	TileObj tileMapObj[MAP_SIZE][MAP_SIZE];
};

