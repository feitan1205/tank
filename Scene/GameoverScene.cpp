#include "GameoverScene.h"
#include "../InputState.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include <DxLib.h>

void GameoverScene::FadeInUpdate(const InputState& input)
{
	_fadeValue = 255 * static_cast<float>(_fadeTimer) / static_cast<float>(fade_interval);
	if (--_fadeTimer == 0)
	{
		_updateFunc = &GameoverScene::NormalUpdate;
	}
}

void GameoverScene::NormalUpdate(const InputState& input)
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
		_updateFunc = &GameoverScene::FadeOutUpdate;
		_fadeColor = 0xff0000;
	}
	if (input.IsTriggered(InputType::prev))
	{
		_manager.ChangeScene(new TitleScene(_manager));
		return;
	}
}

void GameoverScene::FadeOutUpdate(const InputState& input)
{
	_fadeValue = 255 * static_cast<float>(_fadeTimer) / static_cast<float>(fade_interval);
	if (++_fadeTimer == fade_interval)
	{
		_manager.ChangeScene(new TitleScene(_manager));
		return;
	}
}

GameoverScene::GameoverScene(SceneManager& manager) :
	Scene(manager),
	_updateFunc(&GameoverScene::FadeInUpdate)
{
	_gameOverH = LoadGraph("data/2DData/gameover.png");
	_gameOverTextH = LoadGraph("data/2DData/overtext.png");
}


void GameoverScene::Update(const InputState& input)
{
	(this->*_updateFunc)(input);
}

void GameoverScene::Draw()
{
	DrawExtendGraph(0, 0, 1920, 1080, _gameOverH, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _fadeValue);
	DrawBox(0, 0, 1920, 1080, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _textFadeValue);
	DrawExtendGraph(0, 0, 1920, 1080, _gameOverTextH, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
