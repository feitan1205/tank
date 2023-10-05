#include "Player.h"
#include "DxLib.h"
#include "../InputState.h"
#include "Field.h"
#include "AllCollision.h"
#include "../game.h"
#include "Shot.h"
#include "Enemy1.h"

Player::Player():
	_hitCircleScale(13),
	_temp2DPos(VGet(0,0,0)),
	_temp3DPos(VGet(0, 0, 0)),
	_modelPos(VGet(0,0,0)),
	_speed(2),
	_lifePoint(1),
	_enable(true)
{
	_vec = VGet(0, 0, 0);
	_caterpillarModelH = MV1LoadModel("data/chata.mv1");
	_cockpitModelH = MV1LoadModel("data/cockpit.mv1");

	MV1SetPosition(_caterpillarModelH, _modelPos);
	MV1SetScale(_caterpillarModelH, VGet(20.0f, 23.0f, 23.0f));
	MV1SetPosition(_cockpitModelH, _modelPos);
	MV1SetScale(_cockpitModelH, VGet(20.0f, 23.0f, 23.0f));
}


Player::~Player()
{
	MV1DeleteModel(_caterpillarModelH);
	MV1DeleteModel(_cockpitModelH);
}

void Player::Update(const InputState& input,const VECTOR mousePos3D)
{	
	if (_shotStiffCount != 0) {
		_shotStiffCount--;
		return;
	}

	_temp2DPos = _pos;
	_temp3DPos = _modelPos;

	float k = 0;

	if (input.IsPressed(InputType::up)) _vec = VAdd(_vec, VGet(0.0f, -1.0f, 0.0f));
	if (input.IsPressed(InputType::down)) _vec = VAdd(_vec, VGet(0.0f, 1.0f, 0.0f));
	if (input.IsPressed(InputType::right)) _vec = VAdd(_vec, VGet(1.0f, 0.0f, 0.0f));
	if (input.IsPressed(InputType::left)) _vec = VAdd(_vec, VGet(-1.0f, 0.0f, 0.0f));

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

	_modelPos = VGet(_modelPos.x, _modelPos.y, _modelPos.z);

	MV1SetPosition(_caterpillarModelH, _modelPos);
	MV1SetPosition(_cockpitModelH, _modelPos);

	_indexPos.x = static_cast<int>(_pos.x) / 32;
	_indexPos.y = static_cast<int>(_pos.y) / 32;
	_vec = VGet(0, 0, 0);

	t += 0.1f;

	MV1SetRotationXYZ(_cockpitModelH, VGet(0, t, 0));
	MV1SetRotationXYZ(_caterpillarModelH, VGet(0, -(t), 0));


}

void Player::UpdateCancel(bool XorY)
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

void Player::Draw()
{

	//DrawFormatString(0, 0, 0xffffff, "%f;%f", _indexPos.x, _indexPos.y);
	//DrawBox(_pos.x - 15, _pos.y - 15, _pos.x + 16, _pos.y + 16, 0x00ff00, true);
	//DrawCircle(_pos.x, _pos.y, _hitCircleScale, 0x0000ff, true);

	MV1DrawModel(_caterpillarModelH);
	MV1DrawModel(_cockpitModelH);
}

void Player::SetFieldData(Field* field)
{
	_field = field;
	_fieldSize = _field->GetFieldSize();
}

