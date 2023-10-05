
#pragma once
#include "Scene.h"

/// <summary>
/// ゲームオーバーシーン
/// </summary>
class GameClearScene : public Scene
{
private:


	int _gameClearH = -1;
	int _gameClearTextH = -1;

	static constexpr int fade_interval = 60;

	int _fadeTimer = fade_interval;
	int _fadeValue = 255;

	unsigned int _fadeColor = 0xff0000;

	void FadeInUpdate(const InputState& input);
	void NormalUpdate(const InputState& input);
	void FadeOutUpdate(const InputState& input);

	using UpdateFucn_t = void (GameClearScene::*)(const InputState&);
	UpdateFucn_t _updateFunc;

public:
	GameClearScene(SceneManager& manager);
	~GameClearScene() {}

	void Update(const InputState& input);
	void Draw();
};