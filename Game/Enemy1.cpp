#include "EnemyBase.h"
#include "Enemy1.h"
#include "DxLib.h"
#include "Field.h"
#include "Player.h"
#include "Shot.h"
#include "AllCollision.h"
#include "../game.h"

Enemy1::Enemy1() :
	_hitCircleScale(17),
	_temp2DPos(VGet(0, 0, 0)),
	_modelPos(VGet(0, 0, 0)),
	_speed(1),
	_vecUpdateCount(0),
	_enable(true)
{
	_pos = VGet(32 * 20, 32 * 8, 0);
	_vec = VGet(0, 0, 0);
//	_modelH = MV1LoadModel("data/tank.mv1");
	_caterpillarModelH = MV1LoadModel("data/model/e1Chata.mv1");;
	_cockpitModelH = MV1LoadModel("data/model/e1Cockpit.mv1");;

//	MV1SetPosition(_modelH, _modelPos);
//	MV1SetScale(_modelH, VGet(20.0f, 23.0f, 23.0f));
	MV1SetScale(_caterpillarModelH, VGet(20.0f, 23.0f, 23.0f));
	MV1SetScale(_cockpitModelH, VGet(20.0f, 23.0f, 23.0f));

	_shotCount = GetRand(200);
}


Enemy1::~Enemy1()
{
//	MV1DeleteModel(_modelH);
	MV1DeleteModel(_caterpillarModelH);
	MV1DeleteModel(_cockpitModelH);
}

void Enemy1::Update()
{
	_shotStiffCount--;

	if (_shotStiffCount > 0) {
		return;
	}

	_shotCount--;
	if (_shotCount < 0) {
		_shotFlg = true;
	}

	_temp2DPos = _pos;
	_temp3DPos = _modelPos;

	_vecUpdateCount--;

	if (_vecUpdateCount < 0) {
		_targetIndex.x = GetRand(26) + 1;
		_targetIndex.y = GetRand(14) + 1;
		_vec.x = (_targetIndex.x * 32 - 16) - _pos.x;
		_vec.y = (_targetIndex.y * 32 - 16) - _pos.y;
		_vecUpdateCount = 200;
	}


	if (VSize(_vec) != 0) {
		_vec = VNorm(_vec);
	}

	_vec = VScale(_vec, _speed);

	_pos.x += _vec.x;
	_modelPos.x += _vec.x;

	for (int i = 0; i < _fieldSize.y; i++) {
		for (int j = 0; j < _fieldSize.x; j++) {
			if (_field->GetFieldData(i, j) == 1) {
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
			if (_field->GetFieldData(i, j) == 1) {
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

//	MV1SetPosition(_modelH, _modelPos);
	MV1SetPosition(_caterpillarModelH, _modelPos);
	MV1SetPosition(_cockpitModelH, _modelPos);

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

	if (_enable) {
//		MV1DrawModel(_modelH);
		MV1DrawModel(_caterpillarModelH);
		MV1DrawModel(_cockpitModelH);
	}
	
}

void Enemy1::SetPos(int y, int x)
{
	_pos.y = y * 32 + 16;
	_pos.x = x * 32 + 16;
	_modelPos = VGet(32 * (-14 + x) + 16, 0, 32 * (7 - y) + 16);
	MV1SetPosition(_caterpillarModelH, _modelPos);
	MV1SetPosition(_cockpitModelH, _modelPos);
}

void Enemy1::SetFieldData(Field* field)
{
	_field = field;
	_fieldSize = _field->GetFieldSize();
}

void Enemy1::EnemyKill()
{
	_enable = false;
}

void Enemy1::Shot()
{
	_shotFlg = false;
	_shotCount = GetRand(300);
	_shotStiffCount = 5;
}
