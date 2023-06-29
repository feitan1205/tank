#include "Player.h"
#include "DxLib.h"
#include "../InputState.h"
#include "Field.h"
#include "AllCollision.h"

Player::Player():
	_hitCircleScale(15),
	_tempPos(VGet(0,0,0)),
	_speed(2)
{
	_pos = VGet(32 * 2, 32 * 9,0);
	_vec = VGet(0, 0,0);
}

Player::~Player()
{
}

void Player::Update(const InputState& input)
{
	_tempPos = _pos;

	if (input.IsPressed(InputType::up)) _vec = VAdd(_vec,VGet(0.0f, -1.0f, 0.0f));
	if (input.IsPressed(InputType::down)) _vec = VAdd(_vec, VGet(0.0f, 1.0f, 0.0f));
	if (input.IsPressed(InputType::right)) _vec = VAdd(_vec, VGet(1.0f, 0.0f, 0.0f));
	if (input.IsPressed(InputType::left)) _vec = VAdd(_vec, VGet(-1.0f, 0.0f, 0.0f));

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

	_vec = VGet(0, 0, 0);

}

void Player::UpdateCancel(bool XorY)
{
	if (XorY) {
		_pos.x = _tempPos.x;
	}
	if (!XorY) {
		_pos.y = _tempPos.y;
	}
}

void Player::Draw()
{

	DrawBox(_pos.x - 15, _pos.y - 15, _pos.x + 16, _pos.y + 16, 0x00ff00, true);
	DrawCircle(_pos.x, _pos.y, _hitCircleScale, 0x0000ff, true);
}

void Player::SetFieldData(Field* field)
{
	_field = field;
	_fieldSize = _field->GetFieldSize();
}
