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
	/// à⁄ìÆÇµÇ»Ç¢
	/// </summary>
	/// <param name="XorY">true = XÅAfalse = Y</param>
	void UpdateCancel(bool XorY);
	void Draw();

	void SetFieldData(Field* field);

	VECTOR GetPos() { return _pos; }
	int GetCircleScale() { return _hitCircleScale; }

	void EnemyKill();

	bool IsEnable() { return _enable; }

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
	VECTOR _targetIndex;

	bool _enable;

};

