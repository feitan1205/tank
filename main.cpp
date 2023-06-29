#include "DxLib.h"
#include "game.h"
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"
#include "InputState.h"



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	InputState input;

	SceneManager sceneManager;
	sceneManager.ChangeScene(new TitleScene(sceneManager));

	while (ProcessMessage() != -1)
	{
		LONGLONG  time = GetNowHiPerformanceCount();

		ClearDrawScreen();

		input.Update();

		sceneManager.Update(input);
		sceneManager.Draw();

		ScreenFlip();

		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
		// fpsを60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}