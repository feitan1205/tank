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
	_pos(VGet(0,0,0)),
	_tempPos(VGet(0,0,0)),
	_vec(VGet(0,0,0))
{
}

Shot::~Shot()
{
}

void Shot::Update()
{
	_tempPos = _pos;

	_pos.x += _vec.x;

	if (HitCheck()) {
		_vec.x *= -1;
		_pos = _tempPos;
		if (_brittleFlg) {
			_enableFlg = false;
		}
		_brittleFlg = true;
	}

	_pos.y += _vec.y;

	if (HitCheck()) {
		_vec.y *= -1;
		_pos = _tempPos;
		if (_brittleFlg) {
			_enableFlg = false;
		}
		_brittleFlg = true;
	}

}

void Shot::Draw()
{
	DrawCircle(static_cast<int>(_pos.x), static_cast<int>(_pos.y), _shotScale, 0xffffff, true);
	//DrawSphere3D(VGet(_pos.x - (Game::kScreenWidth / 2),16, -(_pos.y - (Game::kScreenHeight / 2))), 4, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), true);
}

void Shot::Start(VECTOR playerPos, VECTOR targetPos)
{
	_enableFlg = true;
	_pos = playerPos;
	_vec = VSub(targetPos,playerPos);
	_vec = VNorm(_vec);
	_pos = VAdd(_pos,VScale(_vec, 18));
	_vec = VScale(_vec,speed);
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
