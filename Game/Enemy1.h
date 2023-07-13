#pragma once
#include "EnemyBase.h"
#include "DxLib.h"

class Field;

class Enemy1:public EnemyBase
{
public:

	Enemy1();
	~Enemy1();

	void Update();
	/// <summary>
	/// �ړ����Ȃ�
	/// </summary>
	/// <param name="XorY">true = X�Afalse = Y</param>
	void UpdateCancel(bool XorY);
	void Draw();

	void SetFieldData(Field* field);

	VECTOR GetPos() { return _pos; }
	int GetCircleScale() { return _hitCircleScale; }

private:

	int _modelH;

	VECTOR _pos;
	VECTOR _tempPos;
	VECTOR _modelPos;
	VECTOR _vec;
	Field* _field;
	VECTOR _fieldSize;
	float _speed;
	int _hitCircleScale;

};

