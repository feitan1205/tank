#include "EnemyBase.h"
#include "Enemy1.h"
#include "DxLib.h"
#include "Field.h"
#include "AllCollision.h"
#include "../game.h"

Enemy1::Enemy1() :
	_hitCircleScale(15),
	_temp2DPos(VGet(0, 0, 0)),
	_modelPos(VGet(0, 0, 0)),
	_speed(1),
	_vecUpdateCount(0),
	_isenable(true)
{
	_pos = VGet(32 * 20, 32 * 8, 0);
	_vec = VGet(0, 0, 0);
	_modelH = MV1LoadModel("data/tank.mv1");
	//_modelPos = VGet(_pos.x - Game::kScreenWidth / 2, -(_pos.y) + Game::kScreenHeight / 2, _pos.z);
	_modelPos = VGet(32 * (20 - 14), 0.0f, 32 * (8 - 8));

	MV1SetPosition(_modelH, _modelPos);
	//MV1SetPosition(_modelH,VGet(50, 0, 0));
	MV1SetScale(_modelH, VGet(25.0f, 25.0f, 25.0f));
}


Enemy1::~Enemy1()
{
	MV1DeleteModel(_modelH);
}

void Enemy1::Update()
{
	_temp2DPos = _pos;
	_temp3DPos = _modelPos;

	_vecUpdateCount--;

	if (_vecUpdateCount < 0) {
		_vec.x = GetRand(1000);
		if (GetRand(2)) {
			_vec.x *= -1;
		}
		_vec.y = GetRand(1000);
		if (GetRand(2)) {
			_vec.y *= -1;
		}
		_vecUpdateCount = 200;
	}

	if (VSize(_vec) != 0) {
		_vec = VNorm(_vec);
	}

	_vec = VScale(_vec, _speed);

	//_pos = VAdd(_pos, _vec);

	_pos.x += _vec.x;
	_modelPos.x += _vec.x;

	for (int i = 0; i < _fieldSize.y; i++) {
		for (int j = 0; j < _fieldSize.x; j++) {
			if (_field->GetFieldData(i, j)) {
				if (AllCollision::CollCheck_Box_Circle(
					_field->GetMinHitBox(i, j),
					_field->GetMaxHitBox(i, j),
					this->GetPos(),
					this->GetCircleScale()))
				{
					this->UpdateCancel(true);
				}
			}
		}
	}

	_pos.y += _vec.y;
	_modelPos.z -= _vec.y;

	for (int i = 0; i < _fieldSize.y; i++) {
		for (int j = 0; j < _fieldSize.x; j++) {
			if (_field->GetFieldData(i, j)) {
				if (AllCollision::CollCheck_Box_Circle(
					_field->GetMinHitBox(i, j),
					_field->GetMaxHitBox(i, j),
					this->GetPos(),
					this->GetCircleScale()))
				{
					this->UpdateCancel(false);
				}
			}
		}
	}


	MV1SetPosition(_modelH, _modelPos);

	//_vec = VGet(0, 0, 0);

}

void Enemy1::UpdateCancel(bool XorY)
{
	if (XorY) {
		_pos.x = _temp2DPos.x;
		_modelPos.x = _temp3DPos.x;
	}
	if (!XorY) {
		_pos.y = _temp2DPos.y;
		_modelPos.z = _temp3DPos.z;
	}
}

void Enemy1::Draw()
{

	//DrawBox(_pos.x - 15, _pos.y - 15, _pos.x + 16, _pos.y + 16, 0x00ff00, true);
	//DrawCircle(_pos.x, _pos.y, _hitCircleScale, 0x0000ff, true);
	if (_isenable) {
		MV1DrawModel(_modelH);
	}
}

void Enemy1::SetFieldData(Field* field)
{
	_field = field;
	_fieldSize = _field->GetFieldSize();
}

void Enemy1::EnemyKill()
{
	_isenable = false;
}
