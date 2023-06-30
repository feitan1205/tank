#pragma once

class InputState;
// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase();
	SceneBase(InputState* input);
	virtual ~SceneBase() {}


	virtual void init() {}
	virtual void end()	{}

	virtual SceneBase* update() { return this; }
	virtual void draw() {}

	// フェード関連
	void updateFade();
	void drawFade() const;

	bool isFadingIn() const;	// フェードイン中
	bool isFadingOut() const;	// フェードアウト中
	bool isFading() const { return isFadingIn() || isFadingOut(); }	// フェードインorアウト中

	void startFadeOut();	// フェードアウト開始

	/// <summary>
	/// フェードの明るさを取得
	/// </summary>
	/// <returns>0(フェードしていない)～255(真っ黒)</returns>
	int getFadeBright() const { return _fadeBright; }

protected:

	InputState* _input;

private:
	// フェード関連処理
	int _fadeColor;
	int _fadeBright;
	int _fadeSpeed;
};