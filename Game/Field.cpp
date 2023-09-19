#include "Field.h"
#include <DxLib.h>
#include "../game.h"
#include "Player.h"

Field::Field(Player* player)
{
	_modelBaseH = MV1LoadModel("data/block.mv1");
	_modelWallH = MV1LoadModel("data/block1.mv1");

	_player = player;

	for (int i = 0; i < stageSizeY; i++)
	{
		for (int j = 0; j < stageSizeX; j++) 
		{
			_modelH[0][i][j] = MV1DuplicateModel(_modelBaseH);
			MV1SetPosition(_modelH[0][i][j], VGet(32.0f * j + 15 - 32 * 14, 0.0f, 32.0f * (stageSizeY - i) - 15 - 32 * 8));
			MV1SetScale(_modelH[0][i][j], VGet(32.0f, 32.0f, 32.0f));
			if (mapData[i][j] == 1) {
				_modelH[1][i][j] = MV1DuplicateModel(_modelWallH);
				MV1SetPosition(_modelH[1][i][j], VGet(32.0f * j + 15 - 32 * 14, 32.0f, 32.0f * (stageSizeY - i) - 15 - 32 * 8));
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

	_playerIndex.x = _player->GetPos().x / 32;
	_playerIndex.y = _player->GetPos().y / 32;

	for (int i = 0; i < stageSizeY; i++) {
		for (int j = 0; j < stageSizeX; j++) {
			if (_playerIndex.x + j < 28 && _playerIndex.x - j > 0) {
			}
		}
	}

}

void Field::Draw()
{
	

	for (int i = 0; i < stageSizeY; i++) {
		for (int j = 0; j < stageSizeX; j++) {
			MV1DrawModel(_modelH[0][i][j]);
			MV1DrawModel(_modelH[1][i][j]);
			if (mapData[i][j] == 1) {
				
				DrawBox(blockSizeX * j, blockSizeY * i, blockSizeX * j + blockSizeX - 1, blockSizeY * i + blockSizeY - 1,0xff0000,true);

			}
		}
	}

	/*for (int i = 0; i < stageSizeY; i++) {
		DrawLine(0, 32 * i, 32 * 28, 32 * i, 0xffffff);
	}
	for (int i = 0; i < stageSizeX; i++) {
		DrawLine(32 * i, 0, 32 * i, 32 * 16, 0xffffff);
	}*/

}
