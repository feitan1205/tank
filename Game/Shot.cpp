#include "Shot.h"

#include "DxLib.h"
#include "../game.h"
#include "Field.h"
#include "AllCollision.h"

Shot::Shot() :
	_shotScale(shotScale),
	_enableFlg(false),
	_brittleFlg(false),
	_field(nullptr),
	_fieldSize(VGet(0,0,0)),
	_3DPos(VGet(0,0,0)),
	_temp3DPos(VGet(0,0,0)),
	_3DVec(VGet(0,0,0))
{
}

Shot::~Shot()
{
}

void Shot::Update()
{
	_temp3DPos = _3DPos;
	_temp2DPos = _2DPos;

	_3DPos.x += _3DVec.x;
	_2DPos.x += _2DVec.x;

	if (HitCheck()) {
		_3DVec.x *= -1;
		_3DPos = _temp3DPos;
		_2DVec.x *= -1;
		_2DPos = _temp2DPos;
		if (_brittleFlg) {
			_enableFlg = false;
		}
		_brittleFlg = true;
	}

	_3DPos.z += _3DVec.z;
	_2DPos.y += _2DVec.y;

	if (HitCheck()) {
		_3DVec.z *= -1;
		_3DPos = _temp3DPos;
		_2DVec.y *= -1;
		_2DPos = _temp2DPos;
		if (_brittleFlg) {
			_enableFlg = false;
		}
		_brittleFlg = true;
	}

}

void Shot::Draw()
{
	DrawCircle(static_cast<int>(_2DPos.x), static_cast<int>(_2DPos.y), _shotScale, 0xffffff, true);
	DrawSphere3D(VGet(_3DPos.x,16, _3DPos.z), 4, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), true);
}

void Shot::Start(VECTOR playerPos, VECTOR targetPos)
{
	_enableFlg = true;
	_3DPos = playerPos;
	_2DPos = VGet(playerPos.x + 32 * 14, 32 * 8 - playerPos.z, 0.0f);
	targetPos.y = 0.0f;
	_3DVec = VSub(targetPos,playerPos);
	_3DVec = VNorm(_3DVec);
	_2DVec = VGet(_3DVec.x, -(_3DVec.z), _3DVec.y);
	_3DPos = VAdd(_3DPos,VScale(_3DVec, 18));
	_2DPos = VAdd(_2DPos, VScale(_2DVec,18));
	_3DVec = VScale(_3DVec,speed);
	_2DVec = VScale(_2DVec, speed);
}

void Shot::ShotKill()
{
	_enableFlg = false;
}

void Shot::SetFieldData(Field* field)
{
	_field = field;
	_fieldSize = _field->GetFieldSize();
}

bool Shot::HitCheck()
{
	for (int i = 0; i < _fieldSize.y; i++) {
		for (int j = 0; j < _fieldSize.x; j++) {
			if (_field->GetFieldData(i, j)) {
				if (AllCollision::CollCheck_Box_Circle(
					_field->GetMinHitBox(i, j),
					_field->GetMaxHitBox(i, j),
					this->GetPos(),
					this->GetCircleScale())) {
					return true;
				}
			}
		}
	}
	return false;
}
