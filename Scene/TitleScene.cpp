#include "TitleScene.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "GameplayingScene.h"
#include "OptionScene.h"
#include "../game.h"
#include <DxLib.h>

void TitleScene::FadeInUpdate(const InputState& input)
{
				 //�^�������珙�X�ɕ\������ꍇ�ꍇ
	_fadeValue = static_cast<int>(255 * (static_cast<float>(_fadeTimer) /
		static_cast<float>(fade_interval)));
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
	if (!_fadeUpFlag) {
		_textFadeValue = static_cast<int>(255 * (static_cast<float>(_textFadeTimer) /
			static_cast<float>(_textFadeInterval)));
		if (--_textFadeTimer == 0)
		{
			_textFadeValue = 0;
			_fadeUpFlag = true;
		}
	}
	if (_fadeUpFlag) {
		_textFadeValue = static_cast<int>(255 * (static_cast<float>(_textFadeTimer) / static_cast<float>(_textFadeInterval)));
		if (++_textFadeTimer == _textFadeInterval)
		{
			_textFadeValue = 255;
			_fadeUpFlag = false;
		}
	}

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
	_textFadeValue = 255 - _fadeValue;
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
	_titleH = LoadGraph("data/2DData/title.png");
	_gradH = LoadGraph("data/2DData/starttext.png");
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
	DrawExtendGraph(0, 0,Game::kScreenWidth,Game::kScreenHeight, _titleH, true);

	//�����珑���摜�ƁA���łɕ`�悳��Ă���X�N���[���Ƃ�
	//�u�����h�̎d�����w�肵�Ă���B
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _fadeValue);
	//��ʑS�̂�^�����ɓh��Ԃ�
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _textFadeValue);

	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, _gradH, true);
	//DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}