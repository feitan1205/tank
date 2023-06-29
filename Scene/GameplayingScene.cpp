#include "GameplayingScene.h"
#include "../InputState.h"
#include "GameoverScene.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include <DxLib.h>

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
	vy += 0.1f;
	py += vy;
	if (py >= 400)
	{
		vy = -9.0;
	}

	if (input.IsTriggered(InputType::next))
	{
		updateFunc_ = &GameplayingScene::FadeOutUpdate;
		fadeColor_ = 0xff0000;
	}
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
	px = 320;
	py = 400;
	vx = 0;
	vy = 0;
}


void GameplayingScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameplayingScene::Draw()
{
	DrawRotaGraph(320, 240, 0.5, 0.0, playingH_, true);

	DrawCircle(px, py, 20, 0xaaffaa, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, 640, 480, fadeColor_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}