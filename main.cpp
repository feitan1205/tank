#include "DxLib.h"
#include "game.h"
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"
#include "InputState.h"



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
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

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}