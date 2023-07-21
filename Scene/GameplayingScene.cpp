#include "GameplayingScene.h"
#include "../InputState.h"
#include "GameoverScene.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include <DxLib.h>
#include <vector>
#include <memory>
#include "../Game/AllCollision.h"
#include "../Game/Player.h"
#include "../Game/EnemyBase.h"
#include "../Game/Enemy1.h"
#include "../Game/Field.h"
#include "../Game/Shot.h"
#include "../Game/BackScreenDraw.h"
#include "../game.h"

void GameplayingScene::FadeInUpdate(const InputState& input)
{
	_fadeValue = 255 * static_cast<float>(_fadeTimer) / static_cast<float>(fade_interval);
	if (--_fadeTimer == 0)
	{
		updateFunc_ = &GameplayingScene::NormalUpdate;
	}
}

void GameplayingScene::NormalUpdate(const InputState& input)
{
	
	GetMousePoint(&_mousePosX, &_mousePosY);
	float per2DMousePosY;
	per2DMousePosY = (Game::kScreenHeight - static_cast<float>(_mousePosY)) / Game::kScreenHeight;
	float mouse3DZ = (0.275758f - 0.186309f) * per2DMousePosY + 0.186309f;
	_mousePos3D = ConvScreenPosToWorldPos(VGet(static_cast<float>(_mousePosX), static_cast<float>(_mousePosY), mouse3DZ));//static_cast<float>(_mousePosX), static_cast<float>(_mousePosY), 1.0f//0.186309f//0.23101f//0.275758f
	//printfDx("%f\n", _mousePos3D.x);
	//_mousePos3D.y = 18.0f;
	_backScreen->SetMousePos(_mousePosX, _mousePosY);
	_backScreen->SetMousePos3D(_mousePos3D);

	//�V���b�g����
	if (_shots.size() < maxShotNum) {
		if (input.IsTriggered(InputType::next)) {
			_shots.push_back(std::make_shared<Shot>());
			_shots.back()->Start(_player->GetModelPos(), _mousePos3D);//VGet(static_cast<float>(_mousePosX), static_cast<float>(_mousePosY),0)
			_shots.back()->SetFieldData(_field);
		}
	}

	//�v���C���[�A�b�v�f�[�g
	_player->Update(input);
	//�G�l�~�[�A�b�v�f�[�g
	_enemy->Update();
	//�t�B�[���h�A�b�v�f�[�g
	_field->Update();
	//�V���b�g�A�b�v�f�[�g
	for (auto shot : _shots) {
		shot->Update();
	}
	_backScreen->Updata();

	//�V���b�g���m�̓����蔻��
	for (int i = 0; i < _shots.size(); i++) {
		for (int j = 0; j < _shots.size(); j++) {
			if (i == j)continue;
			if (AllCollision::CollCheck_Circle_Circle(
				_shots[i]->GetPos(),
				_shots[i]->GetCircleScale(),
				_shots[j]->GetPos(),
				_shots[j]->GetCircleScale())) {
				_shots[i]->ShotKill();
				_shots[j]->ShotKill();
			}
		}
	}

	//�v���C���[�A�G�l�~�[�ƃV���b�g�̓����蔻��
	for (int i = 0; i < _shots.size(); i++) {

		if (AllCollision::CollCheck_Circle_Circle(
			_shots[i]->GetPos(),
			_shots[i]->GetCircleScale(),
			_player->GetPos(),
			_player->GetCircleScale())) {
			//printfDx("dasdfasadf");
			_shots[i]->ShotKill();
		}

		if (AllCollision::CollCheck_Circle_Circle(
			_shots[i]->GetPos(),
			_shots[i]->GetCircleScale(),
			_enemy->GetPos(),
			_enemy->GetCircleScale())) {
			//printfDx("dasdfasadf");
			_enemy->EnemyKill();
			_shots[i]->ShotKill();
		}

	}

	//�V���b�g�폜
	auto rmIt = std::remove_if        // �����ɍ��v�������̂�����
	(_shots.begin(),			// �Ώۂ�enemies_�̍ŏ�����
		_shots.end(),			// �Ō�܂�
	   // �����Ă��炤������\�������_��
	   // true���Ə�����Bfalse���Ə����Ȃ�
		[](const std::shared_ptr<Shot>& shot)
		{
			return !shot->IsEnabled();
		});
	_shots.erase(rmIt, _shots.end());

	if (input.IsTriggered(InputType::prev))
	{
		_manager.ChangeScene(new TitleScene(_manager));
		return;
	}
	if (input.IsTriggered(InputType::pause))
	{
		_manager.PushScene(new PauseScene(_manager));
	}
}

void GameplayingScene::FadeOutUpdate(const InputState& input)
{
	_fadeValue = 255 * static_cast<float>(_fadeTimer) / static_cast<float>(fade_interval);
	if (++_fadeTimer == fade_interval)
	{
		_manager.ChangeScene(new GameoverScene(_manager));
		return;
	}
}

GameplayingScene::GameplayingScene(SceneManager& manager) :
	Scene(manager),
	updateFunc_(&GameplayingScene::FadeInUpdate)
{

	//////////////// �J�����̐ݒ� //////////////////

	// �J��������ǂꂾ�����ꂽ�Ƃ���( Near )����A �ǂ��܂�( Far )�̂��̂�`�悷�邩��ݒ�
	SetCameraNearFar(5.0f, 2800.0f);

	// �J�����̈ʒu�A�ǂ������Ă��邩��ݒ肷��
	SetCameraPositionAndTarget_UpVecY(VGet(0, 600, -300), VGet(0, 0, 0));

	// �J�����̎���p��ݒ�(���W�A��)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);

	SetUseLighting(true);
	SetLightPosition(VGet(50, 500, -150.0f));
	//SetLightDirection(VGet(0.0f, 0.0f, 0.0f));

	SetupCamera_Ortho(500.0f);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	_per2Dto3D = (1.0f / (2500.0f + 295.0f)) * 295.0f;

	_player = new Player();
	_enemy = new Enemy1();
	_field = new Field();
	_fieldSize = _field->GetFieldSize();
	_player->SetFieldData(_field);
	_enemy->SetFieldData(_field);
	_backScreen = new BackScreenDraw();
	_backScreen->SetPlayerData(_player);
}



void GameplayingScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameplayingScene::Draw()
{
	
	//�t�B�[���h�`��
	_field->Draw();
	//�V���b�g�`��
	for (auto shot : _shots) {
		shot->Draw();
	}
	_backScreen->Draw();
	//�v���C���[�`��
	_player->Draw();
	_enemy->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _fadeValue);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, fadeColor_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}