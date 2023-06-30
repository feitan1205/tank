#pragma once
#include "Scene.h"

class InputState;

/// <summary>
/// �^�C�g���V�[��
/// </summary>
class TitleScene : public Scene
{
private:
	static constexpr int fade_interval = 60;
	int _titleH = -1;	//�^�C�g���摜
	int _gradH = -1;
	int _fadeTimer = fade_interval;	//�t�F�[�h�^�C�}�[
	int _fadeValue = 255;	//����`�Ƃ̃u�����h�

	//�t�F�[�h�C���̎���Update�֐�
	void FadeInUpdate(const InputState& input);
	//�ʏ��Ԃ�Update�֐�
	void NormalUpdate(const InputState& input);
	//�t�F�[�h�A�E�g�̎���Update�֐�
	void FadeOutUpdate(const InputState& input);

	//Update�p�����o�֐��|�C���^
	void (TitleScene::* updateFunc_)(const InputState& input);

public:
	TitleScene(SceneManager& manager);
	~TitleScene();

	void Update(const InputState& input);
	void Draw();
};