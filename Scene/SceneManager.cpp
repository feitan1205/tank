#include "SceneManager.h"
#include "Scene.h"

void SceneManager::ChangeScene(Scene* scene)
{
	//�V�[���X�^�b�N����ł͂Ȃ�������...
	if (!scene_.empty())
	{
		delete scene_.front();	//top�͂Ă��؂�̗v�f��Ԃ��Ă�
		scene_.pop_front();			//1���� -> �ӂ���0�ɂȂ�
	}
	scene_.push_front(scene);			//1������
}

void SceneManager::PushScene(Scene* scene)
{
	scene_.push_front(scene);			//1������
}

void SceneManager::PopScene()
{
	//�|�b�v�̌��ʁA�V�[����0�ɂȂ�Ȃ��悤�ɂ���
	if (scene_.size() > 1)
	{
		delete scene_.front();
		scene_.pop_front();
	}
}

void SceneManager::Update(const InputState& input)
{
	scene_.front()->Update(input);
}

void SceneManager::Draw()
{
	for (int i = scene_.size() - 1; i >= 0; --i)
	{
		scene_[i]->Draw();
	}
}
