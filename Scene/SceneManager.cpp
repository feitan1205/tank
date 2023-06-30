#include "SceneManager.h"
#include "Scene.h"

void SceneManager::ChangeScene(Scene* scene)
{
	//シーンスタックが空ではなかったら...
	if (!_scene.empty())
	{
		delete _scene.front();	//topはてっぺんの要素を返してる
		_scene.pop_front();			//1個減る -> ふつうは0になる
	}
	_scene.push_front(scene);			//1個増える
}

void SceneManager::PushScene(Scene* scene)
{
	_scene.push_front(scene);			//1個増える
}

void SceneManager::PopScene()
{
	//ポップの結果、シーンが0にならないようにする
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
