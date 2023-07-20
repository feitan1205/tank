#pragma once
#include "DxLib.h"

namespace {
	constexpr float speed = 5.0;
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
	const VECTOR GetPos()const { return _2DPos; }
	const int GetCircleScale() const { return _shotScale; }
	bool IsEnabled() { return _enableFlg; }

	bool HitCheck();
private:

	VECTOR _3DPos;
	VECTOR _2DPos;
	VECTOR _3DVec;
	VECTOR _2DVec;

	VECTOR _temp3DPos;
	VECTOR _temp2DPos;

	Field* _field;
	VECTOR _fieldSize;

	int _shotScale;
	bool _brittleFlg;

	bool _enableFlg;
};

