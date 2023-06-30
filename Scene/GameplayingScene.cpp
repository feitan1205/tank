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
#include "../Game/Field.h"
#include "../Game/Shot.h"
#include "../Game/BackScreenDraw.h"

void GameplayingScene::FadeInUpdate(const InputState& input)
{
	fadeValue_ = 255 * static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval);
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &GameplayingScene::NormalUpdate;
	}
}
void GameplayingScene::NormalUpdate(const InputState& input)
{
	
	GetMousePoint(&_mousePosX, &_mousePosY);
	_backScreen->SetMousePos(_mousePosX, _mousePosY);

	//�V���b�g����
	if (shots.size() < maxShotNum) {
		if (input.IsTriggered(InputType::next)) {
			shots.push_back(std::make_shared<Shot>());
			shots.back()->Start(_player->GetPos(), VGet(static_cast<float>(_mousePosX), static_cast<float>(_mousePosY),0));
			shots.back()->SetFieldData(_field);
		}
	}

	//�v���C���[�A�b�v�f�[�g
	_player->Update(input);
	//�t�B�[���h�A�b�v�f�[�g
	_field->Update();
	//�V���b�g�A�b�v�f�[�g
	for (auto shot : shots) {
		shot->Update();
	}
	_backScreen->Updata();

	//�V���b�g���m�̓����蔻��
	for (int i = 0; i < shots.size(); i++) {
		for (int j = 0; j < shots.size(); j++) {
			if (i == j)continue;
			if (AllCollision::CollCheck_Circle_Circle(
				shots[i]->GetPos(),
				shots[i]->GetCircleScale(),
				shots[j]->GetPos(),
				shots[j]->GetCircleScale())) {
				shots[i]->ShotKill();
				shots[j]->ShotKill();
			}
		}
	}

	for (int i = 0; i < shots.size(); i++) {

		if (AllCollision::CollCheck_Circle_Circle(
			shots[i]->GetPos(),
			shots[i]->GetCircleScale(),
			_player->GetPos(),
			_player->GetCircleScale())) {
			printfDx("dasdfasadf");
		}

	}

	//�V���b�g�폜
	auto rmIt = std::remove_if        // �����ɍ��v�������̂�����
	(shots.begin(),			// �Ώۂ�enemies_�̍ŏ�����
		shots.end(),			// �Ō�܂�
	   // �����Ă��炤������\�������_��
	   // true���Ə�����Bfalse���Ə����Ȃ�
		[](const std::shared_ptr<Shot>& shot)
		{
			return !shot->IsEnabled();
		});
	shots.erase(rmIt, shots.end());

	if (input.IsTriggered(InputType::prev))
	{
		manager_.ChangeScene(new TitleScene(manager_));
		return;
	}
	if (input.IsTriggered(InputType::pause))
	{
		manager_.PushScene(new PauseScene(manager_));
	}
}

void GameplayingScene::FadeOutUpdate(const InputState& input)
{
	fadeValue_ = 255 * static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval);
	if (++fadeTimer_ == fade_interval)
	{
		manager_.ChangeScene(new GameoverScene(manager_));
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
	SetCameraPositionAndTarget_UpVecY(VGet(0, 445, -5), VGet(0, 0, 0));

	// �J�����̎���p��ݒ�(���W�A��)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);

	SetUseLighting(true);
	SetLightPosition(VGet(0, 500, -150.0f));

	_player = new Player();
	_field = new Field();
	_fieldSize = _field->GetFieldSize();
	_player->SetFieldData(_field);
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
	for (auto shot : shots) {
		shot->Draw();
	}
	_backScreen->Draw();
	//�v���C���[�`��
	_player->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, 640, 480, fadeColor_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}