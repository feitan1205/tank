#pragma once
#include "DxLib.h"
#include <memory>
#include <vector>

namespace {
	constexpr int shotMaxNum = 6;
}

class InputState;
class Field;
class Shot;

class Player
{
public:

	Player();
	~Player();

	void Update(const InputState& input,const VECTOR mousePos3D);
	/// <summary>
	/// à⁄ìÆÇµÇ»Ç¢
	/// </summary>
	/// <param name="XorY">true = XÅAfalse = Y</param>
	void UpdateCancel(bool XorY);
	void Draw();

	void SetFieldData(Field* field);

	const VECTOR GetPos()const { return _pos; }
	const VECTOR GetModelPos()const { return _modelPos; }
	const int GetCircleScale()const { return _hitCircleScale; }

private:

	int _modelH;

	VECTOR _pos;
	VECTOR _temp2DPos;
	VECTOR _temp3DPos;
	VECTOR _modelPos;
	VECTOR _vec;
	Field* _field;
	VECTOR _fieldSize;
	std::vector<std::shared_ptr<Shot>> _shots;
	float _speed;
	int _hitCircleScale;
	int _shotStiffCount;

};

