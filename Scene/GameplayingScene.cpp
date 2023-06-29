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
#include "../Game/Field.h"
#include "../Game/Shot.h"
#include "../Game/BackScreenDraw.h"

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
	
	GetMousePoint(&_mousePosX, &_mousePosY);
	_backScreen->SetMousePos(_mousePosX, _mousePosY);

	//ショット発射
	if (shots.size() < maxShotNum) {
		if (input.IsTriggered(InputType::next)) {
			shots.push_back(std::make_shared<Shot>());
			shots.back()->Start(_player->GetPos(), VGet(static_cast<float>(_mousePosX), static_cast<float>(_mousePosY),0));
			shots.back()->SetFieldData(_field);
		}
	}

	//プレイヤーアップデート
	_player->Update(input);
	//フィールドアップデート
	_field->Update();
	//ショットアップデート
	for (auto shot : shots) {
		shot->Update();
	}
	_backScreen->Updata();

	//ショット同士の当たり判定
	for (int i = 0; i < shots.size(); i++) {
		for (int j = 0; j < shots.size(); j++) {
			if (i == j)continue;
			if (AllCollision::CollCheck_Circle_Circle(
				shots[i]->GetPos(),
				shots[i]->GetCircleScale(),
				shots[j]->GetPos(),
				shots[j]->GetCircleScale())) {
				shots[i]->ShotKill();
				shots[j]->ShotKill();
			}
		}
	}

	for (int i = 0; i < shots.size(); i++) {

		if (AllCollision::CollCheck_Circle_Circle(
			shots[i]->GetPos(),
			shots[i]->GetCircleScale(),
			_player->GetPos(),
			_player->GetCircleScale())) {
			printfDx("dasdfasadf");
		}

	}

	//ショット削除
	auto rmIt = std::remove_if        // 条件に合致したものを消す
	(shots.begin(),			// 対象はenemies_の最初から
		shots.end(),			// 最後まで
	   // 消えてもらう条件を表すラムダ式
	   // trueだと消える。falseだと消えない
		[](const std::shared_ptr<Shot>& shot)
		{
			return !shot->IsEnabled();
		});
	shots.erase(rmIt, shots.end());

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
	_player = new Player();
	_field = new Field();
	_fieldSize = _field->GetFieldSize();
	_player->SetFieldData(_field);
	_backScreen = new BackScreenDraw();
	_backScreen->SetPlayerData(_player);
}



void GameplayingScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameplayingScene::Draw()
{
	
	//プレイヤー描画
	_player->Draw();
	//フィールド描画
	_field->Draw();
	//ショット描画
	for (auto shot : shots) {
		shot->Draw();
	}
	_backScreen->Draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, 640, 480, fadeColor_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}