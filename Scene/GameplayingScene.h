#pragma once
#include "Scene.h"
#include "DxLib.h"
#include <memory>
#include <vector>

namespace {
	constexpr int maxShotNum = 6;
}

class Player;
class Field;
class BackScreenDraw;
class Shot;

/// <summary>
/// ゲーム中シーン
/// </summary>
class GameplayingScene : public Scene
{
private:

	Player* _player;
	Field* _field;
	VECTOR _fieldSize;
	int _mousePosX;
	int _mousePosY;
	BackScreenDraw* _backScreen;

	std::vector<std::shared_ptr<Shot>> shots;

	unsigned int  fadeColor_ = 0x000000; //フェードの色(デフォ黒)

	static constexpr int fade_interval = 60;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	void FadeInUpdate(const InputState& input);
	void NormalUpdate(const InputState& input);
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void (GameplayingScene::*) (const InputState& input);
	UpdateFunc_t updateFunc_ = nullptr;

public:
	GameplayingScene(SceneManager& manager);

	
	~GameplayingScene(){}

	void Update(const InputState& input);
	void Draw();
};

