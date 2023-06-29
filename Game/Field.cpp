#include "Field.h"
#include <DxLib.h>



Field::Field()
{
}

Field::~Field()
{
}

void Field::Update()
{
}

void Field::Draw()
{
	for (int i = 0; i < stageSizeY; i++) {
		for (int j = 0; j < stageSizeX; j++) {
			if (mapData[i][j] == 1) {
				DrawBox(blockSizeX * j, blockSizeY * i, blockSizeX * j + blockSizeX - 1, blockSizeY * i + blockSizeY - 1,0xff0000,true);
			}
		}
	}
}
