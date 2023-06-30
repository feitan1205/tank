#pragma once

//�v���g�^�C�v�錾
class SceneManager;	//�V�[���}�l�[�W���[
class InputState;	//���̓X�e�[�g
//���̎��_�ł�SceneManager��InputState��
//�|�C���^�������͎Q�ƂƂ��Ă��������Ȃ��B

/// <summary>
/// �V�[�����N���X
/// </summary>
class Scene
{
protected:
	SceneManager& _manager; //�V�[���}�l�[�V���[�ւ̎Q��
public:
	Scene(SceneManager& manager) :
		_manager(manager)
	{
	}
	virtual ~Scene(){};
	//�V�[�����X�V����
	virtual void Update(const InputState& input) = 0;
	//�V�[����`�悷��
	virtual void Draw() = 0;						 
};

