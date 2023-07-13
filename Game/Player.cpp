#include "Player.h"
#include "DxLib.h"
#include "../InputState.h"
#include "Field.h"
#include "AllCollision.h"
#include "../game.h"

Player::Player():
	_hitCircleScale(31),
	_tempPos(VGet(0,0,0)),
	_modelPos(VGet(0,0,0)),
	_speed(4)
{
	_pos = VGet(64 * 2, 64 * 9,0);
	_vec = VGet(0, 0, 0);
	_modelH = MV1LoadModel("data/tank.mv1");
	//_modelPos = VGet(_pos.x - Game::kScreenWidth / 2, -(_pos.y) + Game::kScreenHeight / 2, _pos.z);
	//_modelPos = VGet(_pos.x - 32 * 28 / 2 ,_pos.z, -(_pos.y) + 32 * 16 / 2);
	_modelPos = VGet(-32 * 10,0,0);


	MV1SetPosition(_modelH, _modelPos);
	//MV1SetPosition(_modelH,VGet(50, 0, 0));
	MV1SetScale(_modelH, VGet(25.0f, 25.0f, 25.0f));
}


Player::~Player()
{
	MV1DeleteModel(_modelH);
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

	_modelPos = VGet(_modelPos.x, _modelPos.y, _modelPos.z);

	MV1SetPosition(_modelH, _modelPos);

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

	DrawBox(_pos.x - 31, _pos.y - 31, _pos.x + 32, _pos.y + 32, 0x00ff00, true);
	DrawCircle(_pos.x, _pos.y, _hitCircleScale, 0x0000ff, true);

	MV1DrawModel(_modelH);
}

void Player::SetFieldData(Field* field)
{
	_field = field;
	_fieldSize = _field->GetFieldSize();
}
