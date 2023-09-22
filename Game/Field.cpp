#include "Field.h"
#include <DxLib.h>
#include "../game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Field::Field(int fieldNumber)
{
	_modelBaseH = MV1LoadModel("data/block.mv1");
	_modelWallH = MV1LoadModel("data/block1.mv1");
	
	this->SetMapData(fieldNumber);

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

void Field::SetMapData(int fieldNumber)
{
	std::string fieldHandle = "data/fieldData/field";
	/*switch (fieldNumber) {
	case 0:	fieldHandle = "data/fieldData/field0.csv"; break;
	case 1:	fieldHandle = "data/fieldData/field1.csv"; break;
	case 2:	fieldHandle = "data/fieldData/field2.csv"; break;
	case 3:	fieldHandle = "data/fieldData/field3.csv"; break;
	default:break;
	}*/

	fieldHandle += std::to_string(fieldNumber);

	fieldHandle += ".csv";

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
		// ‹æØ‚è•¶Žš‚ª‚È‚­‚È‚é‚Ü‚Å•¶Žš‚ð‹æØ‚Á‚Ä‚¢‚­
		while (getline(stream, tmp, ','))
		{
			// ‹æØ‚ç‚ê‚½•¶Žš‚ªtmp‚É“ü‚é
			mapData[i][j] = atoi(tmp.c_str());
			j++;
		}
		j = 0;
		i++;  // ŽŸ‚Ìl‚Ì”z—ñ‚ÉˆÚ‚é
	}

	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < stageSizeY; i++)
		{
			for (int j = 0; j < stageSizeX; j++)
			{
				MV1DeleteModel(_modelH[k][i][j]);
			}
		}
	}

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
