#include "GameClearScene.h"
#include "../InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include <DxLib.h>

void GameClearScene::FadeInUpdate(const InputState& input)
{
	_fadeValue = 255 * static_cast<float>(_fadeTimer) / static_cast<float>(fade_interval);
	if (--_fadeTimer == 0)
	{
		_updateFunc = &GameClearScene::NormalUpdate;
	}
}

void GameClearScene::NormalUpdate(const InputState& input)
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

	if (input.IsTriggered(InputType::next))
	{
		_updateFunc = &GameClearScene::FadeOutUpdate;
		_fadeColor = 0xff0000;
	}
	if (input.IsTriggered(InputType::prev))
	{
		_manager.ChangeScene(new TitleScene(_manager));
		return;
	}
}

void GameClearScene::FadeOutUpdate(const InputState& input)
{
	_fadeValue = 255 * static_cast<float>(_fadeTimer) / static_cast<float>(fade_interval);
	_textFadeValue -= _fadeValue;
	if (++_fadeTimer == fade_interval)
	{
		_manager.ChangeScene(new TitleScene(_manager));
		return;
	}
}

GameClearScene::GameClearScene(SceneManager& manager) :
	Scene(manager),
	_updateFunc(&GameClearScene::FadeInUpdate)
{
	_gameClearH = LoadGraph("data/2DData/gameclear.png");
	_gameClearTextH = LoadGraph("data/2DData/overtext.png");
}


void GameClearScene::Update(const InputState& input)
{
	(this->*_updateFunc)(input);
}

void GameClearScene::Draw()
{
	DrawExtendGraph(0, 0, 1920, 1080, _gameClearH, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _fadeValue);
	DrawBox(0, 0, 1920, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _textFadeValue);
	DrawExtendGraph(0, 0, 1920, 1080, _gameClearTextH, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
