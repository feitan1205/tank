#pragma once
#include "DxLib.h"

enum class CollNumber {
	bottom,
	top,
	right,
	left,
	none
};

namespace AllCollision
{

	bool CollCheck_Box_Circle(VECTOR minHitBox, VECTOR maxHitBox, VECTOR pos, int circleScale);
	bool CollCheck_Circle_Circle(VECTOR pos1, int circleScale1, VECTOR pos2, int circleScale2);

};

