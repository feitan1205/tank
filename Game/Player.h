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
	/// 移動しない
	/// </summary>
	/// <param name="XorY">true = X、false = Y</param>
	void UpdateCancel(bool XorY);
	void Draw();

	//setter
	void SetFieldData(Field* field);

	//getter
	const VECTOR GetPos()const { return _pos; }
	const VECTOR GetModelPos()const { return _modelPos; }
	const int GetCircleScale()const { return _hitCircleScale; }
	bool GetEnable() { return _enable; }

	//setter
	void SetPos(int y, int x) {
		_pos.y = y * 32 + 16;
		_pos.x = x * 32 + 16;
		_modelPos = VGet(32 * (-14 + x) + 16, 0, 32 * (7 - y) + 16);
	}

	/// <summary>
	/// ショットした時のプレイヤー挙動
	/// </summary>
	void Shot() 
	{
		this->UpdateCancel(true);
		this->UpdateCancel(false);
		_shotStiffCount = 5; 
	};

	/// <summary>
	/// プレイヤーが死ぬ
	/// </summary>
	void Kill() {
		_lifePoint--;
		if (_lifePoint == 0) 
		{
			_enable = false;
		}
	}


private:

	int _caterpillarModelH;
	int _cockpitModelH;

	VECTOR _pos;			//2D座標
	VECTOR _modelPos;		//3D座標
	VECTOR _temp2DPos;		//一時的な2D座標
	VECTOR _temp3DPos;		//一時的な3D座標
	VECTOR _indexPos;		//フィールド座標
	VECTOR _vec;			//移動ベクトル
	Field* _field;			//フィールドデータ
	VECTOR _fieldSize;		//フィールドのサイズ
	float _speed;			//移動量
	int _hitCircleScale;	//当たり判定
	int _shotStiffCount;	//ショット後の硬直時間
	int _lifePoint;			//持ち自機数
	bool _enable;			//存在フラグ
	float t = 0.0f;

};

