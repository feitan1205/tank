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

	void EnemyKill();

private:

	int _modelH;

	VECTOR _pos;
	VECTOR _temp2DPos;
	VECTOR _temp3DPos;
	VECTOR _modelPos;
	VECTOR _vec;
	Field* _field;
	VECTOR _fieldSize;
	float _speed;
	int _hitCircleScale;
	int _vecUpdateCount;

	bool _isenable;

};

