#pragma once

class EnemyBase
{
public:

	EnemyBase();
	virtual ~EnemyBase();

	 virtual void Update() = 0;
	/// <summary>
	/// 移動しない
	/// </summary>
	/// <param name="XorY">true = X、false = Y</param>
	virtual void UpdateCancel(bool XorY) = 0;
	virtual void Draw() = 0;

	virtual void SetFieldData(Field* field) = 0;

	virtual const VECTOR GetPos() = 0;
	virtual const int GetCircleScale() = 0;


private:

	//bool enableFlg;


};

