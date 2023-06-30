#pragma once

#include <deque>

//�v���g�^�C�v�錾
class Scene;
class InputState;

//�V�[���Ď��N���X
class SceneManager	
{
public:

	/// <summary>
	/// �V�[���̐؂�ւ����s��
	/// </summary>
	/// <param name="scene">�؂�ւ��������V�[���̃A�h���X</param>
	void ChangeScene(Scene* scene);

	/// <summary>
	/// �V�[������ɐς�
	/// Update�Ŏ��s�����̂͏�ɂ܂ꂽ�V�[���̂�
	/// </summary>
	/// <param name="scene"></param>
	void PushScene(Scene* scene);

	/// <summary>
	/// ��ԏ�̃V�[�����폜����
	/// �������A���̌��ʃX�^�b�N����ɂȂ邱�Ƃ̂Ȃ��悤��
	/// </summary>
	void PopScene();

	/// <summary>
	/// �������V�[����Update���s��
	/// </summary>
	/// <param name="input">���̓X�e�[�g</param>
	void Update(const InputState& input);
	/// <summary>
	/// �e�V�[���̕`����s��
	/// </summary>
	void Draw();
	
private:
	//�����s���̃V�[����؂�ւ��Ă��������̂�	
	//�Q�Ƃł͂Ȃ��|�C���^�Ƃ��Đ錾
	std::deque<Scene*> _scene;	
};

