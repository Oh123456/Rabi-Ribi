#pragma once
#include "Object.h"
class Stage : public Object
{
	SUPER(Object);
public:
	Stage() : mainTile(nullptr), middleTile(nullptr), backTile(nullptr) {};
	~Stage() {};
	class TileMap* GetMainTile() { return mainTile; }
protected:
	class TileMap* mainTile;
	class TileMap* middleTile;
	class TileMap* backTile;
};

