#pragma once
#include "Scene.h"
#include "DxLib.h"
#include <memory>
#include <vector>

namespace {
	constexpr int maxShotNum = 6;
}

class Player;
class EnemyBase;
class Enemy1;	
class Field;
class BackScreenDraw;
class Shot;

/// <summary>
/// ゲーム中シーン
/// </summary>
class GameplayingScene : public Scene
{
private:

	//ゲームプレイデータ
	Player* _player;
	std::vector<std::shared_ptr<EnemyBase>> _enemies;
	std::vector<std::shared_ptr<Shot>> _playerShot;
	std::vector<std::shared_ptr<Shot>> _enemyShot;
	int _maxFieldNum;
	int _fieldNumber;
	Field* _field;
	VECTOR _fieldSize;
	int _mousePosX;
	int _mousePosY;
	BackScreenDraw* _backScreen;
	float _per2Dto3D;
	VECTOR _mousePos3D;
	bool _changeSceneFlag;
	bool _guideDrawFlg;
	
	int _UIH;

	unsigned int  fadeColor_ = 0x000000; //フェードの色(デフォ黒)

	static constexpr int fade_interval = 60;
	int _fadeTimer = fade_interval;
	int _fadeValue = 255;

	void FadeInUpdate(const InputState& input);
	void NormalUpdate(const InputState& input);
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void (GameplayingScene::*) (const InputState& input);
	UpdateFunc_t updateFunc_ = nullptr;

	void ReSetField();

public:
	GameplayingScene(SceneManager& manager);

	
	~GameplayingScene(){}

	void Update(const InputState& input);
	void Draw();
};

