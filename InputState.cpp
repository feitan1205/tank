#include "InputState.h"
#include <DxLib.h>

InputState::InputState()
{
	_inputMapTable[InputType::next] = { {InputCategory::keybd, KEY_INPUT_RETURN},
										{InputCategory::pad, PAD_INPUT_R },			//スタートボタン
										{InputCategory::mouse, MOUSE_INPUT_LEFT }};

	_inputMapTable[InputType::prev] = { {InputCategory::keybd, KEY_INPUT_SPACE},
										{InputCategory::pad, PAD_INPUT_B } };

	_inputMapTable[InputType::pause] = { {InputCategory::keybd, KEY_INPUT_P},
										{InputCategory::pad, PAD_INPUT_L }};		//セレクトボタン


	_inputMapTable[InputType::keyconf] = { {InputCategory::keybd, KEY_INPUT_K},
										{InputCategory::pad, PAD_INPUT_Y } };		//左ショルダー

	_inputMapTable[InputType::change] = { {InputCategory::keybd, KEY_INPUT_C},
										{InputCategory::pad, PAD_INPUT_Z } };		//右ショルダー

	_inputMapTable[InputType::up] = { {InputCategory::keybd, KEY_INPUT_W},
										{InputCategory::pad, PAD_INPUT_UP } };		//↑

	_inputMapTable[InputType::down] = { {InputCategory::keybd, KEY_INPUT_S},
										{InputCategory::pad, PAD_INPUT_DOWN } };	//↓

	_inputMapTable[InputType::right] = { {InputCategory::keybd, KEY_INPUT_D},
										{InputCategory::pad, PAD_INPUT_RIGHT } };	//→

	_inputMapTable[InputType::left] = { {InputCategory::keybd, KEY_INPUT_A},
										{InputCategory::pad, PAD_INPUT_LEFT } };	//←

	_inputMapTable[InputType::guide] = { {InputCategory::mouse, MOUSE_INPUT_RIGHT} };

	//一時マップテーブルにコピー
	_tempMapTable = _inputMapTable;

	//入力タイプの名前のテーブルを作る
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
	_lastInput = _currentInput;	//直前の入力情報を記憶しておく

	char keystate[256];
	GetHitKeyStateAll(keystate); //全キー情報取得

	int padState = GetJoypadInputState(DX_INPUT_PAD1);	//パッド1コンの情報を取得する
	int mouseState = GetMouseInput();

	//マップの全情報をループする
	for (const auto& keymap : _inputMapTable)
	{
		//入力情報配列をループする
		for (const auto& input : keymap.second)
		{
			//このinputの中身は、keybd,KEY_INPUT_RETURNなどのセット(InputInfo)が入っている
			//keymap.secondは、この入力情報セットInputInfoが入っている
			//keymap.firstは、対応するゲーム入力名の"InputType::next"などが入っている
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
			//3つの入力のうちどれかがtrueだったらもう「入力されてる」
			//とみなして、breakする。
			if (_currentInput[static_cast<int>(keymap.first)])
			{
				break;
			}
		}
	}
}

void InputState::RewriteInputInfo(InputType type, InputCategory cat, int id)
{
	//入力種別(割り当て先)がなければ、無効なので無視します
	if (_tempMapTable.count(type) == 0)
	{
		return;
	}
	bool isRewrite = false;
	for (auto& inputInfo : _tempMapTable[type])
	{
		//カテゴリがヒットしたら
		if (inputInfo.cat == cat)
		{
			//IDを上書きする
			inputInfo.id = id;
			isRewrite = true;
			break;
		}
	}
	//もしカテゴリが存在しなかったら、ここで追加しておく
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
