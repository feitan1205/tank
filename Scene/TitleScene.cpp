#include "TitleScene.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "GameplayingScene.h"
#include "OptionScene.h"
#include <DxLib.h>

void TitleScene::FadeInUpdate(const InputState& input)
{
				 //�^�������珙�X�ɕ\������ꍇ�ꍇ
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
				//�O���f�[�V�������g���ď��X�ɕ\������ꍇ
				/*fadeTimer_;*/
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &TitleScene::NormalUpdate;
		fadeValue_ = 0;
	}
}

void TitleScene::NormalUpdate(const InputState& input)
{
	//���ւ̃{�^���������ꂽ�玟�̃V�[���֍s��
	if (input.IsTriggered(InputType::next))
	{
		updateFunc_ = &TitleScene::FadeOutUpdate;
	}
	if (input.IsTriggered(InputType::prev))
	{
		manager_.ChangeScene(new OptionScene(manager_));
		return;
	}
}

void TitleScene::FadeOutUpdate(const InputState& input)
{
	fadeValue_ = 255 * (static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval));
	if (++fadeTimer_ == fade_interval)
	{
		manager_.ChangeScene(new GameplayingScene(manager_));
		return;
	}
}

TitleScene::TitleScene(SceneManager& manager) :
	Scene(manager),
	updateFunc_(&TitleScene::FadeInUpdate)
{
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleH_);
}

void TitleScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void TitleScene::Draw()
{
	DrawFormatString(100, 100, 0xffffff, "title");

	//�����珑���摜�ƁA���łɕ`�悳��Ă���X�N���[���Ƃ�
	//�u�����h�̎d�����w�肵�Ă���B
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	//��ʑS�̂�^�����ɓh��Ԃ�
	DrawBox(0, 0, 640, 480, 0x000000, true);
	
	/*SetDrawBlendMode(DX_BLENDMODE_MULA, fadeValue_);
	//��ʑS�̂��e�N�X�`���œh��Ԃ�
	DrawGraph(0, 0, gradH_, true);*/

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}