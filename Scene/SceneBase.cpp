#include "SceneBase.h"
#include "DxLib.h"
#include "../game.h"
#include "../InputState.h"

namespace
{
	// フェード速度
	constexpr int kFadeSpeed = 8;
}

SceneBase::SceneBase()
{
	// 初期設定はフェードアウト状態
	_fadeColor = GetColor(0, 0, 0);
	_fadeBright = 255;
	_fadeSpeed = -kFadeSpeed;
}

SceneBase::SceneBase(InputState* input)
{
	_input = input;
	
}

void SceneBase::updateFade()
{
	_fadeBright += _fadeSpeed;
	if (_fadeBright >= 255)
	{
		_fadeBright = 255;
		if (_fadeSpeed > 0)
		{
			_fadeSpeed = 0;
		}
	}
	if (_fadeBright <= 0)
	{
		_fadeBright = 0;
		if (_fadeSpeed < 0)
		{
			_fadeSpeed = 0;
		}
	}
}

void SceneBase::drawFade() const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _fadeBright);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, _fadeColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool SceneBase::isFadingIn() const
{
	if (_fadeSpeed < 0)	return true;
	return false;
}

bool SceneBase::isFadingOut() const
{
	if (_fadeSpeed > 0)	return true;
	return false;
}

void SceneBase::startFadeOut()
{
	_fadeSpeed = kFadeSpeed;
}