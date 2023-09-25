#include "ChangeStageScene.h"
#include "DxLib.h"
#include "../game.h"
#include "../InputState.h"
#include "SceneManager.h"

ChangeStageScene::ChangeStageScene(SceneManager& manager) :
	Scene(manager),
	_waitFlame(60)
{
	_gradH = LoadGraph("data/2DData/clear.png");
}

ChangeStageScene::~ChangeStageScene()
{
}

void ChangeStageScene::Update(const InputState& input)
{
	_waitFlame--;

	if (_waitFlame > 0) {
		return;
	}

	if (input.IsTriggered(InputType::next))
	{
		_manager.PopScene();
		return;
	}
}

void ChangeStageScene::Draw()
{

	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, _gradH, true);

}

