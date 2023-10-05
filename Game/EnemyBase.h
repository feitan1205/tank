#pragma once
#include "DxLib.h"

class Field;
class Player;

class EnemyBase
{
public:

	EnemyBase();
	virtual ~EnemyBase();

	 virtual void Update() = 0;
	/// <summary>
	/// �ړ����Ȃ�
	/// </summary>
	/// <param name="XorY">true = X�Afalse = Y</param>
	virtual void UpdateCancel(bool XorY) = 0;
	virtual void Draw() = 0;

	virtual void SetPos(int y, int x) = 0;

	virtual void SetFieldData(Field* field) = 0;

	virtual VECTOR GetPos() = 0;
	virtual VECTOR GetModelPos() = 0;
	virtual int GetCircleScale() = 0;

	virtual void EnemyKill() = 0;

	virtual bool IsEnable() = 0;

	virtual void SetPlayerData(Player* player) = 0;

	virtual void Shot() = 0;
	virtual bool GetShotFlg() = 0;

private:

	//bool enableFlg;


};

