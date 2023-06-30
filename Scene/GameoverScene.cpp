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
}


void GameoverScene::Update(const InputState& input)
{
	(this->*_updateFunc)(input);
}

void GameoverScene::Draw()
{
	DrawRotaGraph(320, 240, 0.5, 0.0, _gameOverH, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _fadeValue);
	DrawBox(0, 0, 640, 480, _fadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
