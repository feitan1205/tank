#pragma once
#include "EnemyBase.h"
#include "DxLib.h"

class Field;

class Enemy1:public EnemyBase
{
public:

	Enemy1();
	virtual ~Enemy1();

	void Update();
	/// <summary>
	/// 移動しない
	/// </summary>
	/// <param name="XorY">true = X、false = Y</param>
	void UpdateCancel(bool XorY);
	void Draw();

	void SetFieldData(Field* field);

	const VECTOR GetPos()const { return _pos; }
	const int GetCircleScale()const { return _hitCircleScale; }

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

