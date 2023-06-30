#include "TitleScene.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "GameplayingScene.h"
#include "OptionScene.h"
#include <DxLib.h>

void TitleScene::FadeInUpdate(const InputState& input)
{
				 //�^�������珙�X�ɕ\������ꍇ�ꍇ
	_fadeValue = 255 * (static_cast<float>(_fadeTimer) / static_cast<float>(fade_interval));
				//�O���f�[�V�������g���ď��X�ɕ\������ꍇ
				/*fadeTimer_;*/
	if (--_fadeTimer == 0)
	{
		updateFunc_ = &TitleScene::NormalUpdate;
		_fadeValue = 0;
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
		_manager.ChangeScene(new OptionScene(_manager));
		return;
	}
}

void TitleScene::FadeOutUpdate(const InputState& input)
{
	_fadeValue = 255 * (static_cast<float>(_fadeTimer) / static_cast<float>(fade_interval));
	if (++_fadeTimer == fade_interval)
	{
		_manager.ChangeScene(new GameplayingScene(_manager));
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
	DeleteGraph(_titleH);
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _fadeValue);
	//��ʑS�̂�^�����ɓh��Ԃ�
	DrawBox(0, 0, 640, 480, 0x000000, true);
	
	/*SetDrawBlendMode(DX_BLENDMODE_MULA, fadeValue_);
	//��ʑS�̂��e�N�X�`���œh��Ԃ�
	DrawGraph(0, 0, gradH_, true);*/

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}