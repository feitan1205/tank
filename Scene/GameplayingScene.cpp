#include "GameplayingScene.h"
#include "../InputState.h"
#include "GameoverScene.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include <DxLib.h>
#include <vector>
#include <memory>
#include "../Game/AllCollision.h"
#include "../Game/Player.h"
#include "../Game/EnemyBase.h"
#include "../Game/Enemy1.h"
#include "../Game/Field.h"
#include "../Game/Shot.h"
#include "../Game/BackScreenDraw.h"
#include "../game.h"

void GameplayingScene::FadeInUpdate(const InputState& input)
{
	_fadeValue = 255 * static_cast<float>(_fadeTimer) / static_cast<float>(fade_interval);
	if (--_fadeTimer == 0)
	{
		updateFunc_ = &GameplayingScene::NormalUpdate;
	}
}
void GameplayingScene::NormalUpdate(const InputState& input)
{
	
	GetMousePoint(&_mousePosX, &_mousePosY);
	float per2DMousePosY;
	per2DMousePosY = (Game::kScreenHeight - static_cast<float>(_mousePosY)) / Game::kScreenHeight;
	float mouse3DZ = (0.275758f - 0.186309f) * per2DMousePosY + 0.186309f;
	_mousePos3D = ConvScreenPosToWorldPos(VGet(static_cast<float>(_mousePosX), static_cast<float>(_mousePosY), mouse3DZ));//static_cast<float>(_mousePosX), static_cast<float>(_mousePosY), 1.0f//0.186309f//0.23101f//0.275758f
	printfDx("%f\n", _mousePos3D.x);
	//_mousePos3D.y = 18.0f;
	_backScreen->SetMousePos(_mousePosX, _mousePosY);
	_backScreen->SetMousePos3D(_mousePos3D);

	//ショット発射
	if (_shots.size() < maxShotNum) {
		if (input.IsTriggered(InputType::next)) {
			_shots.push_back(std::make_shared<Shot>());
			_shots.back()->Start(_player->GetModelPos(), _mousePos3D);//VGet(static_cast<float>(_mousePosX), static_cast<float>(_mousePosY),0)
			_shots.back()->SetFieldData(_field);
		}
	}

	//プレイヤーアップデート
	_player->Update(input);
	//エネミーアップデート
	_enemy->Update();
	//フィールドアップデート
	_field->Update();
	//ショットアップデート
	for (auto shot : _shots) {
		shot->Update();
	}
	_backScreen->Updata();

	//ショット同士の当たり判定
	for (int i = 0; i < _shots.size(); i++) {
		for (int j = 0; j < _shots.size(); j++) {
			if (i == j)continue;
			if (AllCollision::CollCheck_Circle_Circle(
				_shots[i]->GetPos(),
				_shots[i]->GetCircleScale(),
				_shots[j]->GetPos(),
				_shots[j]->GetCircleScale())) {
				_shots[i]->ShotKill();
				_shots[j]->ShotKill();
			}
		}
	}

	//プレイヤーとショットの当たり判定
	for (int i = 0; i < _shots.size(); i++) {

		if (AllCollision::CollCheck_Circle_Circle(
			_shots[i]->GetPos(),
			_shots[i]->GetCircleScale(),
			_player->GetPos(),
			_player->GetCircleScale())) {
			printfDx("dasdfasadf");
			_shots[i]->ShotKill();
		}

	}

	//ショット削除
	auto rmIt = std::remove_if        // 条件に合致したものを消す
	(_shots.begin(),			// 対象はenemies_の最初から
		_shots.end(),			// 最後まで
	   // 消えてもらう条件を表すラムダ式
	   // trueだと消える。falseだと消えない
		[](const std::shared_ptr<Shot>& shot)
		{
			return !shot->IsEnabled();
		});
	_shots.erase(rmIt, _shots.end());

	if (input.IsTriggered(InputType::prev))
	{
		_manager.ChangeScene(new TitleScene(_manager));
		return;
	}
	if (input.IsTriggered(InputType::pause))
	{
		_manager.PushScene(new PauseScene(_manager));
	}
}

void GameplayingScene::FadeOutUpdate(const InputState& input)
{
	_fadeValue = 255 * static_cast<float>(_fadeTimer) / static_cast<float>(fade_interval);
	if (++_fadeTimer == fade_interval)
	{
		_manager.ChangeScene(new GameoverScene(_manager));
		return;
	}
}

GameplayingScene::GameplayingScene(SceneManager& manager) :
	Scene(manager),
	updateFunc_(&GameplayingScene::FadeInUpdate)
{

	//////////////// カメラの設定 //////////////////

	// カメラからどれだけ離れたところ( Near )から、 どこまで( Far )のものを描画するかを設定
	SetCameraNearFar(5.0f, 2800.0f);

	// カメラの位置、どこを見ているかを設定する
	SetCameraPositionAndTarget_UpVecY(VGet(0, 600, -300), VGet(0, 0, 0));

	// カメラの視野角を設定(ラジアン)
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);

	SetUseLighting(true);
	SetLightPosition(VGet(50, 500, -150.0f));
	//SetLightDirection(VGet(0.0f, 0.0f, 0.0f));

	SetupCamera_Ortho(500.0f);

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	_per2Dto3D = (1.0f / (2500.0f + 295.0f)) * 295.0f;

	_player = new Player();
	_enemy = new Enemy1();
	_field = new Field();
	_fieldSize = _field->GetFieldSize();
	_player->SetFieldData(_field);
	_enemy->SetFieldData(_field);
	_backScreen = new BackScreenDraw();
	_backScreen->SetPlayerData(_player);
}



void GameplayingScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameplayingScene::Draw()
{
	
	//フィールド描画
	_field->Draw();
	//ショット描画
	for (auto shot : _shots) {
		shot->Draw();
	}
	_backScreen->Draw();
	//プレイヤー描画
	_player->Draw();
	_enemy->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _fadeValue);
	DrawBox(0, 0, 640, 480, fadeColor_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}