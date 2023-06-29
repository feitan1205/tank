#pragma once
#include "DxLib.h"

class InputState;
class Field;

class Player
{
public:

	Player();
	~Player();

	void Update(const InputState& input);
	/// <summary>
	/// �ړ����Ȃ�
	/// </summary>
	/// <param name="XorY">true = X�Afalse = Y</param>
	void UpdateCancel(bool XorY);
	void Draw();

	void SetFieldData(Field* field);

	const VECTOR GetPos()const { return _pos; }
	const int GetCircleScale()const { return _hitCircleScale; }

private:

	VECTOR _pos;
	VECTOR _tempPos;
	VECTOR _vec;
	Field* _field;
	VECTOR _fieldSize;
	float _speed;
	int _hitCircleScale;

};

