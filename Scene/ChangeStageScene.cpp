#include "ChangeStageScene.h"
#include "DxLib.h"
#include "../game.h"
#include "../InputState.h"
#include "SceneManager.h"

ChangeStageScene::ChangeStageScene(SceneManager& manager) :
	Scene(manager),
	_waitFlame(30)
{
	_gradH = LoadGraph("data/2DData/clear.png");
}

ChangeStageScene::~ChangeStageScene()
{
}

void ChangeStageScene::Update(const InputState& input)
{
	if (_waitFlame > 0) {
		_waitFlame--;
	}

	_perAlpha = static_cast<float>(30 - _waitFlame) / static_cast<float>(30);
	_alpha = (float)255 * _perAlpha;

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

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, _gradH, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

