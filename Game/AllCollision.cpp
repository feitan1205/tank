#include "AllCollision.h"
#include <cmath>
#include "DxLib.h"

namespace AllCollision{

	/// <summary>
	/// �{�b�N�X�ƃT�[�N���̓����蔻��
	/// </summary>
	/// <param name="minHitBox">�{�b�N�X�̍ŏ����W</param>
	/// <param name="maxHitBox">�{�b�N�X�̍ő���W</param>
	/// <param name="pos">�T�[�N���̒��S���W</param>
	/// <param name="circleScale">�T�[�N���̔��a</param>
	/// <returns>�������Ă��邩</returns>
    bool CollCheck_Box_Circle(VECTOR minHitBox, VECTOR maxHitBox, VECTOR pos, int circleScale)
    {
		     
		if (minHitBox.y > pos.y + circleScale)	return false;
		if (minHitBox.x > pos.x + circleScale)	return false;
		if (maxHitBox.y < pos.y - circleScale)	return false;
		if (maxHitBox.x < pos.x - circleScale)	return false;
		return true;
    }

	bool CollCheck_Circle_Circle(VECTOR pos1, int circleScale1, VECTOR pos2, int circleScale2)
	{
		int hitDistance = circleScale1 + circleScale2;

		int distance;

		distance = std::abs(sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2)));

		if (hitDistance > distance) {
			return true;
		}

		return false;

	}

}

