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
}


void GameClearScene::Update(const InputState& input)
{
	(this->*_updateFunc)(input);
}

void GameClearScene::Draw()
{
	DrawRotaGraph(320, 240, 0.5, 0.0, _gameOverH, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _fadeValue);
	DrawBox(0, 0, 640, 480, _fadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
