#include "ChangeStageScene.h"
#include "DxLib.h"
#include "../InputState.h"
#include "SceneManager.h"

ChangeStageScene::ChangeStageScene(SceneManager& manager) :
	Scene(manager)
{
}

ChangeStageScene::~ChangeStageScene()
{
}

void ChangeStageScene::Update(const InputState& input)
{
	if (input.IsTriggered(InputType::pause))
	{
		_manager.PopScene();
		return;
	}
}

void ChangeStageScene::Draw()
{
	constexpr int pw_width = 400;	//�|�[�Y�g�̕�
	constexpr int pw_height = 300;	//�|�[�Y�g�̍���
	constexpr int pw_start_x = (640 - pw_width) / 2;	//�|�[�Y�g�̍�
	constexpr int pw_start_y = (480 - pw_height) / 2;	//�|�[�Y�g��

	SetDrawBlendMode(DX_BLENDMODE_MULA, 196);

	//�|�[�Y�E�B���h�E�Z���t�@��(����)
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//�ʏ�`��ɖ߂�

	//�|�[�Y�����b�Z�[�W
	DrawString(pw_start_x + 10, pw_start_y + 10, "Pausing...", 0xffff88);

	//�|�[�Y�E�B���h�E�g��
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0xffffff, false);
}

