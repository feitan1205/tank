#pragma once

class Player;

class BackScreenDraw
{
public:

	BackScreenDraw();
	~BackScreenDraw();

	void Updata();
	void Draw();

	void SetMousePos(int posX, int posY);
	void SetPlayerData(Player* player) { _player = player; }

private:

	VECTOR _mousePos;
	VECTOR _reticleStart;
	VECTOR _reticleEnd;

	Player* _player;

};

