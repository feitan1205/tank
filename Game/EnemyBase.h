#pragma once

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

	virtual void SetFieldData(Field* field) = 0;

	virtual const VECTOR GetPos() = 0;
	virtual const int GetCircleScale() = 0;


private:

	//bool enableFlg;


};

