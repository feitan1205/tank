#include "SceneManager.h"
#include "Scene.h"

void SceneManager::ChangeScene(Scene* scene)
{
	//�V�[���X�^�b�N����ł͂Ȃ�������...
	if (!_scene.empty())
	{
		delete _scene.front();	//top�͂Ă��؂�̗v�f��Ԃ��Ă�
		_scene.pop_front();			//1���� -> �ӂ���0�ɂȂ�
	}
	_scene.push_front(scene);			//1������
}

void SceneManager::PushScene(Scene* scene)
{
	_scene.push_front(scene);			//1������
}

void SceneManager::PopScene()
{
	//�|�b�v�̌��ʁA�V�[����0�ɂȂ�Ȃ��悤�ɂ���
	if (_scene.size() > 1)
	{
		delete _scene.front();
		_scene.pop_front();
	}
}

void SceneManager::Update(const InputState& input)
{
	_scene.front()->Update(input);
}

void SceneManager::Draw()
{
	for (int i = _scene.size() - 1; i >= 0; --i)
	{
		_scene[i]->Draw();
	}
}
