#pragma once
#include "DxLib.h"
#include <memory>
#include <vector>

namespace {
	constexpr int shotMaxNum = 6;
}

class InputState;
class Field;
class Enemy1;
class Shot;

class Player
{
public:

	Player();
	~Player();

	void Update(const InputState& input,const VECTOR mousePos3D);
	/// <summary>
	/// �ړ����Ȃ�
	/// </summary>
	/// <param name="XorY">true = X�Afalse = Y</param>
	void UpdateCancel(bool XorY);
	void Draw();

	//setter
	void SetFieldData(Field* field);

	//getter
	const VECTOR GetPos()const { return _pos; }
	const VECTOR GetModelPos()const { return _modelPos; }
	const int GetCircleScale()const { return _hitCircleScale; }
	bool GetEnable() { return _enable; }

	/// <summary>
	/// �V���b�g�������̃v���C���[����
	/// </summary>
	void Shot() 
	{
		this->UpdateCancel(true);
		this->UpdateCancel(false);
		_shotStiffCount = 5; 
	};

	/// <summary>
	/// �v���C���[������
	/// </summary>
	void Kill() {
		_lifePoint--;
		if (_lifePoint == 0) 
		{
			_enable = false;
		}
	}


private:

	int _modelH;

	VECTOR _pos;			//2D���W
	VECTOR _modelPos;		//3D���W
	VECTOR _temp2DPos;		//�ꎞ�I��2D���W
	VECTOR _temp3DPos;		//�ꎞ�I��3D���W
	VECTOR _vec;			//�ړ��x�N�g��
	Field* _field;			//�t�B�[���h�f�[�^
	VECTOR _fieldSize;		//�t�B�[���h�̃T�C�Y
	float _speed;			//�ړ���
	int _hitCircleScale;	//�����蔻��
	int _shotStiffCount;	//�V���b�g��̍d������
	int _lifePoint;			//�������@��
	bool _enable;			//���݃t���O

};

