#include "Player.h"
#include "DxLib.h"
#include "../InputState.h"
#include "Field.h"
#include "AllCollision.h"
#include "../game.h"
#include "Shot.h"

Player::Player():
	_hitCircleScale(13),
	_temp2DPos(VGet(0,0,0)),
	_temp3DPos(VGet(0, 0, 0)),
	_modelPos(VGet(0,0,0)),
	_speed(1)
{
	_pos = VGet(32 * 2, 32 * 8,0);
	_vec = VGet(0, 0, 0);
	_modelH = MV1LoadModel("data/tank.mv1");
	//_modelPos = VGet(_pos.x - Game::kScreenWidth / 2, -(_pos.y) + Game::kScreenHeight / 2, _pos.z);
	//_modelPos = VGet(_pos.x - 32 * 28 / 2 ,_pos.z, -(_pos.y) + 32 * 16 / 2);
	_modelPos = VGet(-32 * 12, 0, 0);


	MV1SetPosition(_modelH, _modelPos);
	//MV1SetPosition(_modelH,VGet(50, 0, 0));
	MV1SetScale(_modelH, VGet(20.0f, 23.0f, 23.0f));
}


Player::~Player()
{
	MV1DeleteModel(_modelH);
}

void Player::Update(const InputState& input,const VECTOR mousePos3D)
{

	//ショット発射
	if (_shots.size() < shotMaxNum) {
		if (input.IsTriggered(InputType::next)) {
			_shots.push_back(std::make_shared<Shot>());
			_shots.back()->Start(this->GetModelPos(), mousePos3D);//VGet(static_cast<float>(_mousePosX), static_cast<float>(_mousePosY),0)
			_shots.back()->SetFieldData(_field);
			this->UpdateCancel(true);
			this->UpdateCancel(false);
			_shotStiffCount = 5;
		}
	}

	for (int i = 0; i < _shots.size(); i++) {
		_shots[i]->Update();
	}

	if (_shotStiffCount != 0) {
		_shotStiffCount--;
		return;
	}



	//ショット削除
	auto rmIt = std::remove_if        // 条件に合致したものを消す
	(_shots.begin(),			// 対象はenemies_の最初から
		_shots.end(),			// 最後まで
	   // 消えてもらう条件を表すラムダ式
	   // trueだと消える。falseだと消えない
		[](const std::shared_ptr<Shot>& shot)
		{
			return !shot->IsEnabled();
		});
	_shots.erase(rmIt, _shots.end());

	_temp2DPos = _pos;
	_temp3DPos = _modelPos;

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

	//DrawBox(_pos.x - 15, _pos.y - 15, _pos.x + 16, _pos.y + 16, 0x00ff00, true);
	//DrawCircle(_pos.x, _pos.y, _hitCircleScale, 0x0000ff, true);

	for (int i = 0; i < _shots.size(); i++) {
		_shots[i]->Draw();
	}

	MV1DrawModel(_modelH);
}

void Player::SetFieldData(Field* field)
{
	_field = field;
	_fieldSize = _field->GetFieldSize();
}
