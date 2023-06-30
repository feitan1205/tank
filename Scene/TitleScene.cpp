#include "TitleScene.h"
#include "../InputState.h"
#include "SceneManager.h"
#include "GameplayingScene.h"
#include "OptionScene.h"
#include <DxLib.h>

void TitleScene::FadeInUpdate(const InputState& input)
{
				 //真っ黒から徐々に表示する場合場合
	_fadeValue = 255 * (static_cast<float>(_fadeTimer) / static_cast<float>(fade_interval));
				//グラデーションを使って徐々に表示する場合
				/*fadeTimer_;*/
	if (--_fadeTimer == 0)
	{
		updateFunc_ = &TitleScene::NormalUpdate;
		_fadeValue = 0;
	}
}

void TitleScene::NormalUpdate(const InputState& input)
{
	//次へのボタンが押されたら次のシーンへ行く
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

	//今から書く画像と、すでに描画されているスクリーンとの
	//ブレンドの仕方を指定している。
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _fadeValue);
	//画面全体を真っ黒に塗りつぶす
	DrawBox(0, 0, 640, 480, 0x000000, true);
	
	/*SetDrawBlendMode(DX_BLENDMODE_MULA, fadeValue_);
	//画面全体をテクスチャで塗りつぶす
	DrawGraph(0, 0, gradH_, true);*/

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}