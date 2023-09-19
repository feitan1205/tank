#include "GameplayingScene.h"
#include "../InputState.h"
#include "GameClearScene.h"
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

/// <summary>
/// �Q�[���v���C��ʂւ̃t�F�[�h�C��
/// </summary>
/// <param name="input"></param>
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
	
	//�}�E�X����
	{
		GetMousePoint(&_mousePosX, &_mousePosY);
		float per2DMousePosY;
		per2DMousePosY = (Game::kScreenHeight - static_cast<float>(_mousePosY)) / Game::kScreenHeight;//�}�E�X�|�C���^���W�ƃE�B���h�E���W�Ŋ������o��
		float mouse3DZ = (0.275758f - 0.186309f) * per2DMousePosY + 0.186309f;//3DZ���W�̊�������ʂ̊����ŌŒ�
		_mousePos3D = ConvScreenPosToWorldPos(VGet(static_cast<float>(_mousePosX), static_cast<float>(_mousePosY), mouse3DZ));//static_cast<float>(_mousePosX), static_cast<float>(_mousePosY), 1.0f//0.186309f//0.23101f//0.275758f
		//printfDx("%f\n", _mousePos3D.x);
		//_mousePos3D.y = 18.0f;
		_backScreen->SetMousePos(_mousePosX, _mousePosY);
		_backScreen->SetMousePos3D(_mousePos3D);
	}

	//�V���b�g����
	{
		if (_shots.size() < maxShotNum) {
			if (input.IsTriggered(InputType::next)) {
				_shots.push_back(std::make_shared<Shot>());
				_shots.back()->Start(_player->GetModelPos(), _mousePos3D);//VGet(static_cast<float>(_mousePosX), static_cast<float>(_mousePosY),0)
				_shots.back()->SetFieldData(_field);
				_player->Shot();
			}
		}
	}

	//�A�b�v�f�[�g
	{
		//�v���C���[�A�b�v�f�[�g
		_player->Update(input, _mousePos3D);
		//�G�l�~�[�A�b�v�f�[�g
		for (auto enem : _enemies)
		{
			enem->Update();
		}
		//�t�B�[���h�A�b�v�f�[�g
		_field->Update();
		//�V���b�g�A�b�v�f�[�g
		for (auto shot : _shots) {
			shot->Update();
		}
		//�o�b�N�X�N���[���A�b�v�f�[�g
		_backScreen->Updata();
	}

	//�V���b�g���m�̓����蔻��
	{
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
	}

	//�v���C���[�A�G�l�~�[�ƃV���b�g�̓����蔻��
	{
		for (int i = 0; i < _shots.size(); i++) {

			if (AllCollision::CollCheck_Circle_Circle(
				_shots[i]->GetPos(),
				_shots[i]->GetCircleScale(),
				_player->GetPos(),
				_player->GetCircleScale())) {
				//printfDx("dasdfasadf");
				_shots[i]->ShotKill();
				_player->Kill();
			}

			for (auto enem : _enemies)
			{
				if (AllCollision::CollCheck_Circle_Circle(
					_shots[i]->GetPos(),
					_shots[i]->GetCircleScale(),
					enem->GetPos(),
					enem->GetCircleScale())) {
					printfDx("dasdfasadf");
					enem->EnemyKill();
					_shots[i]->ShotKill();
				}
			}
		}
	}
	
	//�V���b�g�폜
	{
		auto shotRmIt = std::remove_if        // �����ɍ��v�������̂�����
		(_shots.begin(),			// �Ώۂ�enemies_�̍ŏ�����
			_shots.end(),			// �Ō�܂�
		   // �����Ă��炤������\�������_��
		   // true���Ə�����Bfalse���Ə����Ȃ�
			[](const std::shared_ptr<Shot>& shot)
			{
				return !shot->IsEnabled();
			});
		_shots.erase(shotRmIt, _shots.end());
	}

	//�G�l�~�[�폜
	{
		auto enemRmIt = std::remove_if        // �����ɍ��v�������̂�����
		(_enemies.begin(),			// �Ώۂ�enemies_�̍ŏ�����
			_enemies.end(),			// �Ō�܂�
		   // �����Ă��炤������\�������_��
		   // true���Ə�����Bfalse���Ə����Ȃ�
			[](const std::shared_ptr<EnemyBase>& enem)
			{
				return !enem->IsEnable();
			});
		_enemies.erase(enemRmIt, _enemies.end());
	}

	//���̃V�[���ւ̑J��
	{
		if (!_player->GetEnable())
		{
			updateFunc_ = &GameplayingScene::FadeOutUpdate;
		}
		if (_enemies.size() == 0)
		{
			updateFunc_ = &GameplayingScene::FadeOutUpdate;
		}
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
}

/// <summary>
/// �Q�[���v���C��ʂ̃t�F�[�h�A�E�g
/// </summary>
/// <param name="input"></param>
void GameplayingScene::FadeOutUpdate(const InputState& input)
{
	_fadeValue = 255 * static_cast<float>(_fadeTimer) / static_cast<float>(fade_interval);
	if (++_fadeTimer == fade_interval)
	{
		if(!_player->GetEnable())
		{
			_manager.ChangeScene(new GameoverScene(_manager));
			return;
		}

		if (_enemies.size() == 0)
		{
			_manager.ChangeScene(new GameClearScene(_manager));
			return;
		}
	}

}

/// <summary>
/// �Q�[���v���C�̃R���X�g���N�^
/// </summary>
/// <param name="manager"></param>
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

	SetupCamera_Ortho(500.0f);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	_per2Dto3D = (1.0f / (2500.0f + 295.0f)) * 295.0f;

	_player = new Player();
	_enemies.push_back(std::make_shared<Enemy1>());
	_field = new Field(_player);
	_fieldSize = _field->GetFieldSize();
	_player->SetFieldData(_field);
	for (auto enem : _enemies)
	{
		enem->SetFieldData(_field);
	}
	_backScreen = new BackScreenDraw();
	_backScreen->SetPlayerData(_player);

	_UIH = LoadGraph("data/2DData/UI.png");
}

/// <summary>
/// �A�b�v�f�[�g
/// </summary>
/// <param name="input"></param>
void GameplayingScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

/// <summary>
/// �`��
/// </summary>
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
	//�G�l�~�[�`��
	for (auto enem : _enemies) 
	{
		enem->Draw();
	}

	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, _UIH, true);

	//�t�F�[�h�p
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _fadeValue);
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, fadeColor_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}