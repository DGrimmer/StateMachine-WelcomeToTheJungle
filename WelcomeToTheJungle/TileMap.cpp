#include "TileMap.h"
#include <fstream>
#include <direct.h>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;
using namespace sf;

TileMap& TileMap::GetInstance() {
	static TileMap instance;
	return instance;
}

TileMap::TileMap() : textureBank(Textures::GetInstance())
{
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			tileMapGround[i][j] = Grass;
		}
	}
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			tileMapObj[i][j] = Empty;
		}
	}
	LoadFromFile();
}

TileMap::~TileMap()
{
}

void TileMap::Update_Event(sf::RenderWindow& window, sf::Event event) {

	//only map editing things
	if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::O)) {
		canEdit = !canEdit;
		cout << "edit: " << std::to_string(canEdit) << endl;
	}
	if (!canEdit) // skips all if not editing
		return;

	if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left) || isHoldingMousebotton) {
		isHoldingMousebotton = true;

		Vector2i mousePos = Mouse::getPosition(window);
		sf::Vector2f worldpos = window.mapPixelToCoords(mousePos);

		worldpos.x /= GetTileSize();
		worldpos.y /= GetTileSize();

		SetTileTypeToSelected(worldpos);
	}
	if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::LControl) && Keyboard::isKeyPressed(Keyboard::S)) {
		SaveToFile();
	}
	if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Add) || Keyboard::isKeyPressed(Keyboard::Subtract)) {
		if (Keyboard::isKeyPressed(Keyboard::Add))
			onLayer++;
		if (Keyboard::isKeyPressed(Keyboard::Subtract))
			onLayer--;
		if (onLayer > 1)
			onLayer = 1;
		if (onLayer < 0)
			onLayer = 0;
		cout << "On Layer: " << onLayer << endl;
	}
	if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Num1)) {
		cout << "changed to grass" << endl;
		drawTileLayer1 = Grass;
	}
	if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Num2)) {
		cout << "changed to water" << endl;
		drawTileLayer1 = Water;
	}
	if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Num3)) {
		cout << "changed to steppe" << endl;
		drawTileLayer1 = Steppe;
	}
	if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Num4)) {
		cout << "changed to beach" << endl;
		drawTileLayer1 = Beach;
	}
	if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Num5)) {
		cout << "changed to forest" << endl;
		drawTileLayer2 = Forest;
	}
	if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Num6)) {
		cout << "changed to bush" << endl;
		drawTileLayer2 = Bush;
	}
	if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Num7)) {
		cout << "changed to fish" << endl;
		drawTileLayer2 = Fish;
	}
	if (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Num8)) {
		cout << "changed to empty" << endl;
		drawTileLayer2 = Empty;
	}
	if (event.type == Event::MouseButtonReleased) {
		isHoldingMousebotton = false;
	}
}

void TileMap::Update() {
	for (int i = 0; i < activatedTiles.size(); i++) {
		activatedTiles[i].timer -= DELTATIME;
		if (activatedTiles[i].timer < 0) {
			tileMapObj[activatedTiles[i].index.x][activatedTiles[i].index.y] = activatedTiles[i].type;
			
			activatedTiles.erase(activatedTiles.begin() + i);
		}
	}
}

bool TileMap::isEditingOn() {
	return canEdit;
}

void TileMap::SetTileTypeToSelected(sf::Vector2f pos) {
	if (MAP_SIZE < pos.x || MAP_SIZE < pos.y)
		return;

	cout << "changing on layer: " << onLayer << endl;
	if (onLayer == 0)
		tileMapGround[(int)pos.x][(int)pos.y] = drawTileLayer1;
	else if (onLayer == 1)
		tileMapObj[(int)pos.x][(int)pos.y] = drawTileLayer2;
}
Vector2i TileMap::Conv_WorldPosToMapIndex(sf::Vector2f pos) {
	pos.x /= MAP_TILESIZE;
	pos.y /= MAP_TILESIZE;
	return (Vector2i)pos;
}

float TileMap::GetMoveMulti(Vector2f pos) {
	Vector2i mapIndex = Conv_WorldPosToMapIndex(pos);
	TileGround current = tileMapGround[mapIndex.x][mapIndex.y];
	switch (current)
	{
	case Grass:
		return MOVE_GRASS_MULTIPLIER;
		break;
	case Beach:
		return MOVE_BEACH_MULTIPLIER;
		break;
	case Steppe:
		return MOVE_STEPPE_MULTIPLIER;
		break;
	case Water:
		return MOVE_WATER_MULTIPLIER;
		break;
	default:
		cout << "ERROR, in GetMoveMulti" << endl;
		break;
	}
}

TileObj TileMap::GetTileObj(sf::Vector2f pos) {
	Vector2i mapIndex = Conv_WorldPosToMapIndex(pos);
	return tileMapObj[mapIndex.x][mapIndex.y];
}

vector<Vector2f> TileMap::GetAllBush() {
	vector<Vector2f> result;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (tileMapObj[i][j] == Bush)
				result.push_back(Vector2f(i* MAP_TILESIZE + MAP_TILESIZE / 2, j* MAP_TILESIZE + MAP_TILESIZE / 2));
		}
	}
	return result;
}
vector<Vector2f> TileMap::GetAllFish() {
	vector<Vector2f> result;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (tileMapObj[i][j] == Fish)
				result.push_back(Vector2f(i * MAP_TILESIZE + MAP_TILESIZE / 2, j * MAP_TILESIZE + MAP_TILESIZE / 2));
		}
	}
	return result;
}

Vector2f TileMap::GetCloseWater(Vector2f fromPos) {
	cout << "TODO getcloseWater" << endl;
	return Vector2f(-1, -1);
}

float TileMap::GetFoodFromTile(Vector2f currentPos) {
	Vector2i mapindex = Conv_WorldPosToMapIndex(currentPos);

	if (tileMapObj[mapindex.x][mapindex.y] == Empty) {
		return 0;
	}

	activatedTiles.push_back(TimerElement(FOOD_RESPAWNTIME, mapindex, tileMapObj[mapindex.x][mapindex.y]));
	tileMapObj[mapindex.x][mapindex.y] = Empty;

	return FOOD_VALUE;
}

int TileMap::GetTileSize() {
	return MAP_TILESIZE;
}

int TileMap::GetMapSize() {
	return MAP_SIZE;
}


void TileMap::SaveToFile() {
	cout << "Saving.." << endl;
	ofstream fileLayer1(mapName + layer1Name, std::ofstream::trunc);
	if (fileLayer1.is_open()) {
		for (int i = 0; i < GetMapSize(); ++i) {
			for (int j = 0; j < GetMapSize(); ++j) {
				fileLayer1 << tileMapGround[i][j] << " ";
			}
			fileLayer1 << endl;
		}
	}
	fileLayer1.close();

	ofstream fileLayer2(mapName + layer2Name, std::ofstream::trunc);
	if (fileLayer2.is_open()) {
		for (int i = 0; i < GetMapSize(); ++i) {
			for (int j = 0; j < GetMapSize(); ++j) {
				fileLayer2 << tileMapObj[i][j] << " ";
			}
			fileLayer2 << endl;
		}
	}
	fileLayer2.close();

	cout << "..Saved" << endl;
}

void TileMap::LoadFromFile() {

	ifstream fileLayer1(mapName + layer1Name);
	string data;
	if (fileLayer1.is_open()) {
		for (int i = 0; i < GetMapSize(); ++i) {
			for (int j = 0; j < GetMapSize(); ++j) {
				getline(fileLayer1, data, ' ');
				tileMapGround[i][j] = (TileGround)std::stoi(data);
			}
		}
	}
	fileLayer1.close();

	data = "";
	ifstream fileLayer2(mapName + layer2Name);
	if (fileLayer2.is_open()) {
		for (int i = 0; i < GetMapSize(); ++i) {
			for (int j = 0; j < GetMapSize(); ++j) {
				getline(fileLayer2, data, ' ');
				tileMapObj[i][j] = (TileObj)std::stoi(data);
			}
		}
	}
	fileLayer2.close();
}


void TileMap::Draw(RenderWindow& window) {
	Sprite sprite;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {

			sprite.setPosition(Vector2f(i*MAP_TILESIZE, j*MAP_TILESIZE));

			switch (tileMapGround[i][j])
			{
			case Grass:
				sprite.setTexture(*textureBank.GetTexture("Grass"));
				break;
			case Water:
				sprite.setTexture(*textureBank.GetTexture("Water"));
				break;
			case Steppe:
				sprite.setTexture(*textureBank.GetTexture("Steppe"));
				break;
			case Beach:
				sprite.setTexture(*textureBank.GetTexture("Beach"));
				break;
			default:
				cout << "ERROR, dont know what sprite to get.. (ground)" << "" << endl;
				break;
			}
			window.draw(sprite);
		}
	}

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			bool isEmpty = false;
			sprite.setPosition(Vector2f(i*MAP_TILESIZE, j*MAP_TILESIZE));
			switch (tileMapObj[i][j])
			{
			case Empty:
				isEmpty = true;
				break;
			case Forest:
				sprite.setTexture(*textureBank.GetTexture("Forest"));
				break;
			case Bush:
				sprite.setTexture(*textureBank.GetTexture("Bush"));
				break;
			case Fish:
				sprite.setTexture(*textureBank.GetTexture("Fish"));
				break;
			default:
				cout << "ERROR, dont know what sprite to get.. (obj)" << endl;
				break;
			}
			if (!isEmpty)
				window.draw(sprite);
		}
	}

}