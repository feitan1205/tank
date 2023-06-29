#pragma once
#include "DxLib.h"

class InputState;

class Player
{
public:

	Player();
	~Player();

	void Update(const InputState& input);
	void UpdateCancel();
	void Draw();

	const VECTOR GetPos()const { return _pos; }
	const int GetCircleScale()const { return _hitCircleScale; }

private:

	VECTOR _pos;
	VECTOR _tempPos;
	VECTOR _vec;
	int _hitCircleScale;

};

