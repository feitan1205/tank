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
			_modelH[0][i][j] = MV1DuplicateModel(modelH);
			MV1SetPosition(_modelH[0][i][j], VGet(32.0f * j - (Game::kScreenWidth / 2) + 15, 0.0f, 32.0f * (stageSizeY - i) - (Game::kScreenHeight / 2) - 15));
			MV1SetScale(_modelH[0][i][j], VGet(32.0f, 32.0f, 32.0f));
			if (mapData[i][j] == 1) {
				_modelH[1][i][j] = MV1DuplicateModel(modelH);
				MV1SetPosition(_modelH[1][i][j], VGet(32.0f * j - (Game::kScreenWidth / 2) + 15, 32.0f, 32.0f * (stageSizeY - i) - (Game::kScreenHeight / 2) - 15));
				MV1SetScale(_modelH[1][i][j], VGet(32.0f, 32.0f, 32.0f));
			}
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
			MV1DrawModel(_modelH[0][i][j]);
			MV1DrawModel(_modelH[1][i][j]);
			if (mapData[i][j] == 1) {
				
				//DrawBox(blockSizeX * j, blockSizeY * i, blockSizeX * j + blockSizeX - 1, blockSizeY * i + blockSizeY - 1,0xff0000,true);

			}
		}
	}
}
