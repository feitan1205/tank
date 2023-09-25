#include "Field.h"
#include <DxLib.h>
#include "../game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Field::Field(int fieldNumber)
{
	//�t�B�[���h���f���̃��[�h
	_modelBaseH = MV1LoadModel("data/block.mv1");
	_modelWallH = MV1LoadModel("data/block1.mv1");
	
	this->SetMapData(fieldNumber);
}

Field::~Field()
{
	//�S���f���폜
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

	//�t�B�[���h�̃n���h��
	std::string fieldHandle = "data/fieldData/field";
	
	fieldHandle += std::to_string(fieldNumber);

	fieldHandle += ".csv";

	//�n���h����csv�t�@�C�����J��
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
		// ��؂蕶�����Ȃ��Ȃ�܂ŕ�������؂��Ă���
		while (getline(stream, tmp, ','))
		{
			// ��؂�ꂽ������tmp�ɓ���
			mapData[i][j] = atoi(tmp.c_str());
			j++;
		}
		j = 0;
		i++;  // ���̐l�̔z��Ɉڂ�
	}

	//���f������x�S����
	for (int k = 0; k < 2; k++) {
		for (int i = 0; i < stageSizeY; i++)
		{
			for (int j = 0; j < stageSizeX; j++)
			{
				MV1DeleteModel(_modelH[k][i][j]);
			}
		}
	}

	//�V�����}�b�v�f�[�^�Ɋ�Â��ă��f���𐶐�
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
