#pragma once
#include "Scene.h"

class InputState;

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public Scene
{
private:
	static constexpr int fade_interval = 60;
	int _titleH = -1;	//タイトル画像
	int _gradH = -1;
	int _fadeTimer = fade_interval;	//フェードタイマー
	int _fadeValue = 255;	//黒矩形とのブレンド具合

	//フェードインの時のUpdate関数
	void FadeInUpdate(const InputState& input);
	//通常状態のUpdate関数
	void NormalUpdate(const InputState& input);
	//フェードアウトの時のUpdate関数
	void FadeOutUpdate(const InputState& input);

	//Update用メンバ関数ポインタ
	void (TitleScene::* updateFunc_)(const InputState& input);

public:
	TitleScene(SceneManager& manager);
	~TitleScene();

	void Update(const InputState& input);
	void Draw();
};