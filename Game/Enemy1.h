#pragma once
#include "EnemyBase.h"
#include "DxLib.h"

class Field;
class Player;

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

	void SetPos(int y,int x);

	void SetFieldData(Field* field);

	VECTOR GetPos() { return _pos; }
	VECTOR GetModelPos() { return _modelPos; }
	int GetCircleScale() { return _hitCircleScale; }

	void EnemyKill();

	bool IsEnable() { return _enable; }

	void SetPlayerData(Player* player) { _player = player; }

	void Shot();
	bool GetShotFlg() { return _shotFlg; }

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
	Player* _player;
	int _shotCount;
	bool _shotFlg;
	bool _enable;
	int _shotStiffCount;
	int _caterpillarModelH;
	int _cockpitModelH;

};

