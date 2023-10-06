#include "Field.h"
#include <DxLib.h>
#include "../game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Field::Field(int fieldNumber)
{
	//フィールドモデルのロード
	_modelBaseH = MV1LoadModel("data/model/block.mv1");
	_modelWallH = MV1LoadModel("data/model/block1.mv1");
	
	this->SetMapData(fieldNumber);
}

Field::~Field()
{
	//全モデル削除
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
			/*if (mapData[i][j] == 1) {				
				DrawBox(blockSizeX * j, blockSizeY * i, blockSizeX * j + blockSizeX - 1, blockSizeY * i + blockSizeY - 1,0xff0000,true);
			}*/
		}
	}
}

void Field::SetMapData(int fieldNumber)
{

	//フィールドのハンドル
	std::string fieldHandle = "data/fieldData/field";
	
	fieldHandle += std::to_string(fieldNumber);

	fieldHandle += ".csv";

	//ハンドルのcsvファイルを開く
	std::ifstream ifs(fieldHandle);

	if (!ifs)
	{
		printfDx("error");
	}

	std::string line;
	int i = 0;
	int j = 0;

	while (std::getline(ifs, line)) {
		std::string tmp = "";
		std::istringstream stream(line);
		// 区切り文字がなくなるまで文字を区切っていく
		while (getline(stream, tmp, ','))
		{
			// 区切られた文字がtmpに入る
			mapData[i][j] = atoi(tmp.c_str());
			j++;
		}
		j = 0;
		i++;  // 次の人の配列に移る
	}

	//モデルを一度全消去
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < stageSizeY; i++)
		{
			for (int j = 0; j < stageSizeX; j++)
			{
				MV1DeleteModel(_modelH[k][i][j]);
			}
		}
	}

	//新しいマップデータに基づいてモデルを生成
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
