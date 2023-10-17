#pragma once

class Player;

class BackScreenDraw
{
public:

	BackScreenDraw();
	~BackScreenDraw();

	void Updata();
	void Draw();
	void GuideDraw();

	void SetMousePos(int posX, int posY);
	void SetMousePos3D(VECTOR mousePos3D);
	void SetPlayerData(Player* player) { _player = player; }

private:

	VECTOR _mousePos3D;
	VECTOR _mousePos;
	VECTOR _reticleStart;
	VECTOR _reticleEnd;
	VECTOR _playerModelPos2D;
	int _reticleH;
	int _dotH;

	Player* _player;

};

