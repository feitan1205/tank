#pragma once
#include "Scene.h"

class ChangeStageScene :public Scene
{
public:
	ChangeStageScene(SceneManager& manager);

	~ChangeStageScene();

	void Update(const InputState& input);
	void Draw();

private:

	int _gradH;
	int _waitFlame;

};
