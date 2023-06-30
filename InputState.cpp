#include "InputState.h"
#include <DxLib.h>

InputState::InputState()
{
	_inputMapTable[InputType::next] = { {InputCategory::keybd, KEY_INPUT_RETURN},
										{InputCategory::pad, PAD_INPUT_R },			//�X�^�[�g�{�^��
										{InputCategory::mouse, MOUSE_INPUT_LEFT }};

	_inputMapTable[InputType::prev] = { {InputCategory::keybd, KEY_INPUT_SPACE},
										{InputCategory::pad, PAD_INPUT_B } };

	_inputMapTable[InputType::pause] = { {InputCategory::keybd, KEY_INPUT_P},
										{InputCategory::pad, PAD_INPUT_L }};		//�Z���N�g�{�^��


	_inputMapTable[InputType::keyconf] = { {InputCategory::keybd, KEY_INPUT_K},
										{InputCategory::pad, PAD_INPUT_Y } };		//���V�����_�[

	_inputMapTable[InputType::change] = { {InputCategory::keybd, KEY_INPUT_C},
										{InputCategory::pad, PAD_INPUT_Z } };		//�E�V�����_�[

	_inputMapTable[InputType::up] = { {InputCategory::keybd, KEY_INPUT_W},
										{InputCategory::pad, PAD_INPUT_UP } };		//��

	_inputMapTable[InputType::down] = { {InputCategory::keybd, KEY_INPUT_S},
										{InputCategory::pad, PAD_INPUT_DOWN } };	//��

	_inputMapTable[InputType::right] = { {InputCategory::keybd, KEY_INPUT_D},
										{InputCategory::pad, PAD_INPUT_RIGHT } };	//��

	_inputMapTable[InputType::left] = { {InputCategory::keybd, KEY_INPUT_A},
										{InputCategory::pad, PAD_INPUT_LEFT } };	//��

	_inputMapTable[InputType::guide] = { {InputCategory::mouse, MOUSE_INPUT_RIGHT} };

	//�ꎞ�}�b�v�e�[�u���ɃR�s�[
	_tempMapTable = _inputMapTable;

	//���̓^�C�v�̖��O�̃e�[�u�������
	_inputNameTable[InputType::next] = L"next";
	_inputNameTable[InputType::prev] = L"prev";
	_inputNameTable[InputType::pause] = L"pause";
	_inputNameTable[InputType::keyconf] = L"keyconf";
	_inputNameTable[InputType::change] = L"change";


	_currentInput.resize(static_cast<int>(InputType::max));
	_lastInput.resize(static_cast<int>(InputType::max));
}

void InputState::Update()
{
	_lastInput = _currentInput;	//���O�̓��͏����L�����Ă���

	char keystate[256];
	GetHitKeyStateAll(keystate); //�S�L�[���擾

	int padState = GetJoypadInputState(DX_INPUT_PAD1);	//�p�b�h1�R���̏����擾����
	int mouseState = GetMouseInput();

	//�}�b�v�̑S�������[�v����
	for (const auto& keymap : _inputMapTable)
	{
		//���͏��z������[�v����
		for (const auto& input : keymap.second)
		{
			//����input�̒��g�́Akeybd,KEY_INPUT_RETURN�Ȃǂ̃Z�b�g(InputInfo)�������Ă���
			//keymap.second�́A���̓��͏��Z�b�gInputInfo�������Ă���
			//keymap.first�́A�Ή�����Q�[�����͖���"InputType::next"�Ȃǂ������Ă���
			if (input.cat == InputCategory::keybd)
			{
				_currentInput[static_cast<int>(keymap.first)] = keystate[input.id];
			}
			else if (input.cat == InputCategory::pad)
			{
				_currentInput[static_cast<int>(keymap.first)] = padState & input.id;
			}
			else if (input.cat == InputCategory::mouse)
			{
				_currentInput[static_cast<int>(keymap.first)] = mouseState & input.id;
			}
			//3�̓��͂̂����ǂꂩ��true������������u���͂���Ă�v
			//�Ƃ݂Ȃ��āAbreak����B
			if (_currentInput[static_cast<int>(keymap.first)])
			{
				break;
			}
		}
	}
}

void InputState::RewriteInputInfo(InputType type, InputCategory cat, int id)
{
	//���͎��(���蓖�Đ�)���Ȃ���΁A�����Ȃ̂Ŗ������܂�
	if (_tempMapTable.count(type) == 0)
	{
		return;
	}
	bool isRewrite = false;
	for (auto& inputInfo : _tempMapTable[type])
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
		_tempMapTable[type].push_back({ cat, id });
	}
}

void InputState::CommitChangedInputInfo()
{
	_inputMapTable = _tempMapTable;
}

void InputState::RollbackChangedInputInfo()
{
	_tempMapTable = _inputMapTable;
}

bool InputState::IsPressed(InputType type) const
{
	return _currentInput[static_cast<int>(type)];
}

bool InputState::IsTriggered(InputType type) const
{
	return IsPressed(type) && !_lastInput[static_cast<int>(type)];
}
