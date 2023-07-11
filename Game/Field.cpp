#include "Field.h"
#include <DxLib.h>
#include "../game.h"


Field::Field()
{
	_modelBaseH = MV1LoadModel("data/block.mv1");
	_modelWallH = MV1LoadModel("data/block1.mv1");

	for (int i = 0; i < stageSizeY; i++)
	{
		for (int j = 0; j < stageSizeX; j++) 
		{
			_modelH[0][i][j] = MV1DuplicateModel(_modelBaseH);
			MV1SetPosition(_modelH[0][i][j], VGet(32.0f * j - (Game::kScreenWidth / 2) + 15, 0.0f, 32.0f * (stageSizeY - i) - (Game::kScreenHeight / 2) - 15));
			MV1SetScale(_modelH[0][i][j], VGet(32.0f, 32.0f, 32.0f));
			if (mapData[i][j] == 1) {
				_modelH[1][i][j] = MV1DuplicateModel(_modelWallH);
				MV1SetPosition(_modelH[1][i][j], VGet(32.0f * j - (Game::kScreenWidth / 2) + 15, 32.0f, 32.0f * (stageSizeY - i) - (Game::kScreenHeight / 2) - 15));
				MV1SetScale(_modelH[1][i][j], VGet(32.0f, 32.0f, 32.0f));
			}
		}
	}

}

Field::~Field()
{
	MV1DeleteModel(_modelBaseH);
	MV1DeleteModel(_modelWallH);
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < stageSizeY; i++)
		{
			for (int j = 0; j < stageSizeX; j++)
			{
				MV1DeleteModel(_modelH[k][i][j]);
			}
		}
	}
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
