#include "InputState.h"
#include <DxLib.h>

InputState::InputState()
{
	inputMapTable_[InputType::next] = { {InputCategory::keybd, KEY_INPUT_RETURN},
										{InputCategory::pad, PAD_INPUT_R },			//�X�^�[�g�{�^��
										{InputCategory::mouse, MOUSE_INPUT_LEFT }};

	inputMapTable_[InputType::prev] = { {InputCategory::keybd, KEY_INPUT_SPACE},
										{InputCategory::pad, PAD_INPUT_B } };

	inputMapTable_[InputType::pause] = { {InputCategory::keybd, KEY_INPUT_P},
										{InputCategory::pad, PAD_INPUT_L }};		//�Z���N�g�{�^��


	inputMapTable_[InputType::keyconf] = { {InputCategory::keybd, KEY_INPUT_K},
										{InputCategory::pad, PAD_INPUT_Y } };		//���V�����_�[

	inputMapTable_[InputType::change] = { {InputCategory::keybd, KEY_INPUT_C},
										{InputCategory::pad, PAD_INPUT_Z } };		//�E�V�����_�[

	inputMapTable_[InputType::up] = { {InputCategory::keybd, KEY_INPUT_W},
										{InputCategory::pad, PAD_INPUT_UP } };		//��

	inputMapTable_[InputType::down] = { {InputCategory::keybd, KEY_INPUT_S},
										{InputCategory::pad, PAD_INPUT_DOWN } };	//��

	inputMapTable_[InputType::right] = { {InputCategory::keybd, KEY_INPUT_D},
										{InputCategory::pad, PAD_INPUT_RIGHT } };	//��

	inputMapTable_[InputType::left] = { {InputCategory::keybd, KEY_INPUT_A},
										{InputCategory::pad, PAD_INPUT_LEFT } };	//��

	//�ꎞ�}�b�v�e�[�u���ɃR�s�[
	tempMapTable_ = inputMapTable_;

	//���̓^�C�v�̖��O�̃e�[�u�������
	inputNameTable_[InputType::next] = L"next";
	inputNameTable_[InputType::prev] = L"prev";
	inputNameTable_[InputType::pause] = L"pause";
	inputNameTable_[InputType::keyconf] = L"keyconf";
	inputNameTable_[InputType::change] = L"change";


	currentInput_.resize(static_cast<int>(InputType::max));
	lastInput_.resize(static_cast<int>(InputType::max));
}

void InputState::Update()
{
	lastInput_ = currentInput_;	//���O�̓��͏����L�����Ă���

	char keystate[256];
	GetHitKeyStateAll(keystate); //�S�L�[���擾

	int padState = GetJoypadInputState(DX_INPUT_PAD1);	//�p�b�h1�R���̏����擾����
	int mouseState = GetMouseInput();

	//�}�b�v�̑S�������[�v����
	for (const auto& keymap : inputMapTable_)
	{
		//���͏��z������[�v����
		for (const auto& input : keymap.second)
		{
			//����input�̒��g�́Akeybd,KEY_INPUT_RETURN�Ȃǂ̃Z�b�g(InputInfo)�������Ă���
			//keymap.second�́A���̓��͏��Z�b�gInputInfo�������Ă���
			//keymap.first�́A�Ή�����Q�[�����͖���"InputType::next"�Ȃǂ������Ă���
			if (input.cat == InputCategory::keybd)
			{
				currentInput_[static_cast<int>(keymap.first)] = keystate[input.id];
			}
			else if (input.cat == InputCategory::pad)
			{
				currentInput_[static_cast<int>(keymap.first)] = padState & input.id;
			}
			else if (input.cat == InputCategory::mouse)
			{
				currentInput_[static_cast<int>(keymap.first)] = mouseState & input.id;
			}
			//3�̓��͂̂����ǂꂩ��true������������u���͂���Ă�v
			//�Ƃ݂Ȃ��āAbreak����B
			if (currentInput_[static_cast<int>(keymap.first)])
			{
				break;
			}
		}
	}
}

void InputState::RewriteInputInfo(InputType type, InputCategory cat, int id)
{
	//���͎��(���蓖�Đ�)���Ȃ���΁A�����Ȃ̂Ŗ������܂�
	if (tempMapTable_.count(type) == 0)
	{
		return;
	}
	bool isRewrite = false;
	for (auto& inputInfo : tempMapTable_[type])
	{
		//�J�e�S�����q�b�g������
		if (inputInfo.cat == cat)
		{
			//ID���㏑������
			inputInfo.id = id;
			isRewrite = true;
			break;
		}
	}
	//�����J�e�S�������݂��Ȃ�������A�����Œǉ����Ă���
	if (!isRewrite)
	{
		tempMapTable_[type].push_back({ cat, id });
	}
}

void InputState::CommitChangedInputInfo()
{
	inputMapTable_ = tempMapTable_;
}

void InputState::RollbackChangedInputInfo()
{
	tempMapTable_ = inputMapTable_;
}

bool InputState::IsPressed(InputType type) const
{
	return currentInput_[static_cast<int>(type)];
}

bool InputState::IsTriggered(InputType type) const
{
	return IsPressed(type) && !lastInput_[static_cast<int>(type)];
}
