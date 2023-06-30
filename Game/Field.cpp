#include "Field.h"
#include <DxLib.h>
#include "../game.h"


Field::Field()
{
	int modelH = MV1LoadModel("data/block.mv1");
	
	for (int i = 0; i < stageSizeY; i++)
	{
		for (int j = 0; j < stageSizeX; j++) 
		{
			_modelH[i][j] = MV1DuplicateModel(modelH);
			MV1SetPosition(_modelH[i][j], VGet(32.0f * j - (Game::kScreenWidth / 2), 0.0f, 32.0f * i - (Game::kScreenHeight / 2)));
			MV1SetScale(_modelH[i][j], VGet(30.0f, 30.0f, 30.0f));
		}
	}
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
				MV1DrawModel(_modelH[i][j]);
				DrawBox(blockSizeX * j, blockSizeY * i, blockSizeX * j + blockSizeX - 1, blockSizeY * i + blockSizeY - 1,0xff0000,true);

			}
		}
	}
}
