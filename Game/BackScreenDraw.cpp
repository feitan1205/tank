#include "DxLib.h"

#include "BackScreenDraw.h"
#include "Player.h"



BackScreenDraw::BackScreenDraw()
{
	_reticleStart.x = -10;
	_reticleStart.y = -10;
	_reticleEnd.x = 10;
	_reticleEnd.y = 10;
}

BackScreenDraw::~BackScreenDraw()
{
}

void BackScreenDraw::Updata()
{



}

void BackScreenDraw::Draw()
{
	/*DrawLine(_player->GetPos().x, _player->GetPos().y, _mousePos.x, _mousePos.y, 0xffffff);

	DrawCircle(_mousePos.x, _mousePos.y, 4, 0xffffff, false);
	DrawCircle(_mousePos.x, _mousePos.y, 3, 0x00ff00, false);

	DrawLine(_mousePos.x + _reticleStart.x, _mousePos.y + _reticleStart.y, _mousePos.x + _reticleStart.x + 5, _mousePos.y + _reticleStart.y + 5, 0x00ff00, true);
	DrawLine(_mousePos.x + _reticleEnd.x, _mousePos.y + _reticleStart.y, _mousePos.x + _reticleEnd.x - 5, _mousePos.y + _reticleStart.y + 5, 0x00ff00, true);
	DrawLine(_mousePos.x + _reticleStart.x, _mousePos.y + _reticleEnd.y, _mousePos.x + _reticleStart.x + 5, _mousePos.y + _reticleEnd.y - 5, 0x00ff00, true);
	DrawLine(_mousePos.x + _reticleEnd.x, _mousePos.y + _reticleEnd.y, _mousePos.x + _reticleEnd.x - 5, _mousePos.y + _reticleEnd.y - 5, 0x00ff00, true);*/
	DrawLine3D(_player->GetModelPos(), _mousePos3D, 0xff0000);
}

void BackScreenDraw::SetMousePos(int posX, int posY)
{
	_mousePos = VGet(static_cast<float>(posX), static_cast<float>(posY),0);
}

void BackScreenDraw::SetMousePos3D(VECTOR mousePos3D)
{
	_mousePos3D = mousePos3D;
}
