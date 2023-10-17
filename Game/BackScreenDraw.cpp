#include "DxLib.h"

#include "../game.h"
#include "BackScreenDraw.h"
#include "Player.h"

BackScreenDraw::BackScreenDraw()
{
	_reticleStart.x = -10;
	_reticleStart.y = -10;
	_reticleEnd.x = 10;
	_reticleEnd.y = 10;
	_reticleH = LoadGraph("data/2DData/reticle.png");
	_dotH = LoadGraph("data/2DData/dot.png");
}

BackScreenDraw::~BackScreenDraw()
{
}

void BackScreenDraw::Updata()
{

}

void BackScreenDraw::Draw()
{
	DrawRotaGraph(_mousePos.x, _mousePos.y,
		0.7, 0,
		_reticleH,true,true);
}

void BackScreenDraw::GuideDraw() {
	_playerModelPos2D = ConvWorldPosToScreenPos(_player->GetModelPos());

	for (int i = 1; i < 7; i++) {
		DrawRotaGraph(((_mousePos.x - _playerModelPos2D.x) / 7 * i) + _playerModelPos2D.x, ((_mousePos.y - _playerModelPos2D.y) / 7 * i) + _playerModelPos2D.y,
			0.7, 0,
			_dotH, true, true);
	}
}

void BackScreenDraw::SetMousePos(int posX, int posY)
{
	_mousePos = VGet(static_cast<float>(posX), static_cast<float>(posY),0);
}

void BackScreenDraw::SetMousePos3D(VECTOR mousePos3D)
{
	_mousePos3D = mousePos3D;
}
