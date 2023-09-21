#pragma once
#include "DxLib.h"
#include <vector>
#include <memory>

namespace {
	constexpr int stageSizeX = 28;
	constexpr int stageSizeY = 16;
	constexpr int blockSizeX = 32;
	constexpr int blockSizeY = 32;
	constexpr int fieldLayer = 3;
};

class Field
{
public:
	Field(int fieldNumber);
	~Field();

	void Update();
	void Draw();

	VECTOR GetFieldSize() { return VGet(stageSizeX, stageSizeY,0); }
	int GetFieldData(int y, int x) {return mapData[y][x]; }
	VECTOR GetMinHitBox(int y, int x) { return VGet(static_cast<float>(blockSizeX * x),static_cast<float>(blockSizeY * y),0.0f); }
	VECTOR GetMaxHitBox(int y, int x) { return VGet(static_cast<float>(blockSizeX * x + blockSizeX), static_cast<float>(blockSizeY * y + blockSizeY),0.0f); }

	void SetMapData(int fieldNumber);

private:

	int mapData[stageSizeY][stageSizeX];

	int _modelBaseH;
	int _modelWallH;
	int _modelH[fieldLayer][stageSizeY][stageSizeX];
	int _indexEvaluation[stageSizeY][stageSizeX];
};

