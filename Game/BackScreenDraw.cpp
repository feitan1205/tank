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
	DrawLine3D(_player->GetModelPos(), _mousePos3D, 0xff0000);
	DrawRotaGraph(_mousePos.x, _mousePos.y,
		0.7, 0,
		_reticleH,true,true);

	DrawGraph(_player->GetModelPos().x + (Game::kScreenWidth / 2), _player->GetModelPos().z + (Game::kScreenHeight / 2), _dotH, true);

	DrawFormatString(100, 100, 0xffffff, "%f,%f", true);

	/*for (int i = 1; i < 7; i++) {
		DrawRotaGraph(((_mousePos.x - _player->GetModelPos().x) / 7 * i), ((_mousePos.y - _player->GetModelPos().y) / 7 * i),
			0.7, 0,
			_dotH, true, true);
	}*/
}

void BackScreenDraw::SetMousePos(int posX, int posY)
{
	_mousePos = VGet(static_cast<float>(posX), static_cast<float>(posY),0);
}

void BackScreenDraw::SetMousePos3D(VECTOR mousePos3D)
{
	_mousePos3D = mousePos3D;
}
