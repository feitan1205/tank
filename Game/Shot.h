#pragma once
#include "DxLib.h"

namespace {
	constexpr float speed = 3.0;
	constexpr int shotScale = 3;
}

class Field;

class Shot
{
public:

	Shot();
	~Shot();

	void Update();
	void Draw();

	void Start(VECTOR playerPos, VECTOR targetPos);

	void ShotKill();

	void SetFieldData(Field* field);
	const VECTOR GetPos()const { return _pos; }
	const int GetCircleScale() const { return _shotScale; }
	bool IsEnabled() { return _enableFlg; }

	bool HitCheck();
private:

	VECTOR _pos;
	VECTOR _vec;
	VECTOR _tempPos;

	Field* _field;
	VECTOR _fieldSize;

	int _shotScale;
	bool _brittleFlg;

	bool _enableFlg;
};

