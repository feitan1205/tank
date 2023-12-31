#pragma once

//プロトタイプ宣言
class SceneManager;	//シーンマネージャー
class InputState;	//入力ステート
//この時点ではSceneManagerとInputStateは
//ポインタもしくは参照としてしか扱えない。

/// <summary>
/// シーン基底クラス
/// </summary>
class Scene
{
protected:
	SceneManager& _manager; //シーンマネーシャーへの参照
public:
	Scene(SceneManager& manager) :
		_manager(manager)
	{
	}
	virtual ~Scene(){};
	//シーンを更新する
	virtual void Update(const InputState& input) = 0;
	//シーンを描画する
	virtual void Draw() = 0;						 
};

