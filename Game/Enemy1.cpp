#include "EnemyBase.h"
#include "Enemy1.h"
#include "DxLib.h"
#include "Field.h"
#include "AllCollision.h"
#include "../game.h"

Enemy1::Enemy1() :
	_hitCircleScale(15),
	_tempPos(VGet(0, 0, 0)),
	_modelPos(VGet(0, 0, 0)),
	_speed(2)
{
	_pos = VGet(32 * 20, 32 * 9, 0);
	_vec = VGet(0, 0, 0);
	_modelH = MV1LoadModel("data/tank.mv1");
	//_modelPos = VGet(_pos.x - Game::kScreenWidth / 2, -(_pos.y) + Game::kScreenHeight / 2, _pos.z);
	_modelPos = VGet(_pos.x - Game::kScreenWidth / 2, _pos.z, -(_pos.y) + Game::kScreenHeight / 2);

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
	_tempPos = _pos;

	_vec.x = GetRand(3);
	_vec.y = GetRand(3);

	if (VSize(_vec) != 0) {
		_vec = VNorm(_vec);
	}

	_vec = VScale(_vec, _speed);

	//_pos = VAdd(_pos, _vec);

	_pos.x += _vec.x;

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

	_modelPos = VGet(_pos.x - Game::kScreenWidth / 2, _pos.z, -(_pos.y) + Game::kScreenHeight / 2);

	MV1SetPosition(_modelH, _modelPos);

	_vec = VGet(0, 0, 0);

}

void Enemy1::UpdateCancel(bool XorY)
{
	if (XorY) {
		_pos.x = _tempPos.x;
	}
	if (!XorY) {
		_pos.y = _tempPos.y;
	}
}

void Enemy1::Draw()
{

	/*DrawBox(_pos.x - 15, _pos.y - 15, _pos.x + 16, _pos.y + 16, 0x00ff00, true);
	DrawCircle(_pos.x, _pos.y, _hitCircleScale, 0x0000ff, true);*/

	MV1DrawModel(_modelH);
}

void Enemy1::SetFieldData(Field* field)
{
	_field = field;
	_fieldSize = _field->GetFieldSize();
}
