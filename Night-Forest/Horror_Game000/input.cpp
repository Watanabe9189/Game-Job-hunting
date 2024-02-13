//<==============================================
//入力処理(Input.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "Input.h"

//<======================================
//静的メンバ変数宣言
//<======================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;		//

											//<======================================
											//入力のコンストラクタ
											//<======================================
CInput::CInput()
{
	//値のクリア
	m_pDevice = NULL;
}
//<======================================
//入力のデストラクタ
//<======================================
CInput::~CInput()
{

}
//<======================================
//入力処理の初期化
//<======================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}
//<======================================
//入力処理の終了処理
//<======================================
void CInput::Uninit(void)
{
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	//キーボードへのアクセス権を放棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

}
//<======================================
//キーボードのコンストラクタ
//<======================================
CKeyboard::CKeyboard()
{
	//中身をなくす
	for (int nCnt = 0; nCnt < NUM_KEY; nCnt++)
	{
		m_aState[nCnt] = NULL;
	}
}
//<======================================
//キーボードのデストラクタ
//<======================================
CKeyboard::~CKeyboard()
{

}
//<======================================
//キーボードの初期化処理
//<======================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	m_pDevice->Acquire();

	return S_OK;
}
//<======================================
//キーボードの終了処理
//<======================================
void CKeyboard::Uninit(void)
{
	CInput::Uninit();
}
//<======================================
//キーボードの更新処理
//<======================================
void CKeyboard::Update(void)
{
	const int REPEAT_TIME = 10;

	BYTE aKeyState[NUM_KEY];	//キーボードの入力情報
	static int RepeatCount[NUM_KEY] = {};

	//入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{

		for (int nCntKey = 0; nCntKey < NUM_KEY; nCntKey++)
		{
			m_aStateTrigger[nCntKey] = (m_aState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];		//トリガー情報を保存
			m_aStateRelease[nCntKey] = (m_aState[nCntKey] ^ aKeyState[nCntKey]) & m_aState[nCntKey];	//リリース情報を保存
			m_aState[nCntKey] = aKeyState[nCntKey];															//キーボードのプレス情報を保存
			m_aStateRepeat[nCntKey] = m_aStateTrigger[nCntKey];

			//リピート処理(プレスしている間)
			if (bGetPress(nCntKey) == true)
			{
				//カウントを加算していく
				RepeatCount[nCntKey]++;

				//時間の最大を超えたら
				if (RepeatCount[nCntKey] >= REPEAT_TIME)
				{
					m_aStateRepeat[nCntKey] = m_aState[nCntKey];
				}
				else
				{
					//g_aKeyStateRepeat[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey];	//リピートにリリースの情報保存
					m_aStateRepeat[nCntKey] = m_aStateRelease[nCntKey];
				}
			}
			//もし離していたら
			else
			{
				//カウントを0にする
				RepeatCount[nCntKey] = 0;
			}
			//
			if (bGetRelease(nCntKey) == true)
			{//リリース入力されたとき
				RepeatCount[nCntKey] = 0;
			}
		}

	}
	else
	{
		m_pDevice->Acquire();	//キーボードへのアクセス権を獲得
	}
}
//<======================================
//ジョイパッドのコンストラクタ
//<======================================
CJoyPad::CJoyPad()
{

}
//<======================================
//ジョイパッドのデストラクタ
//<======================================
CJoyPad::~CJoyPad()
{

}
//<======================================
//ジョイパッドの初期化処理
//<======================================
HRESULT CJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//XInputを有効化
	XInputEnable(true);

	//左スティックの情報を初期化
	m_bLeftStickSelect = false;
	m_nLeftStickCount = 0;

	//メモリクリア
	for (int nCnt = 0; nCnt < NUM_KEY; nCnt++)
	{
		memset(&m_aState[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_aStateTrigger[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_aStateRepeat[nCnt], 0, sizeof(XINPUT_STATE));
		memset(&m_aStateRelease[nCnt], 0, sizeof(XINPUT_STATE));
	}

	return S_OK;
}
//<======================================
//ジョイパッドの終了処理
//<======================================
void CJoyPad::Uninit(void)
{
	CInput::Uninit();

	XInputEnable(false);
}
//<======================================
//ジョイパッドの更新処理
//<======================================
void CJoyPad::Update(void)
{
	XINPUT_STATE  aGamepadState[NUM_KEY];

	const int REPEAT_TIME = 10;

	//入力デバイスからデータを取得
	for (int nCnt = 0; nCnt < NUM_KEY; nCnt++)
	{
		if (XInputGetState(nCnt, &aGamepadState[nCnt]) == ERROR_SUCCESS)
		{
			//キーボードのトリガー情報を保存
			m_aStateTrigger[nCnt].Gamepad.wButtons =
				(~m_aState[nCnt].Gamepad.wButtons) & aGamepadState[nCnt].Gamepad.wButtons;

			//リリース情報を保存
			m_aStateRelease[nCnt].Gamepad.wButtons =
				(m_aState[nCnt].Gamepad.wButtons ^ aGamepadState[nCnt].Gamepad.wButtons) & m_aState[nCnt].Gamepad.wButtons;


			//キーボードのプレス情報を保存
			m_aState[nCnt] = aGamepadState[nCnt];

			if ((m_nCntPadrepeat % REPEAT_TIME) == 0)
			{
				//リピート情報を保存
				m_nCntPadrepeat = (m_nCntPadrepeat + 1) % REPEAT_TIME;
				m_aStateRepeat[nCnt].Gamepad.wButtons = aGamepadState[nCnt].Gamepad.wButtons;
			}
			else
			{
				//リピートにリリースの情報保存
				m_aStateRepeat[nCnt].Gamepad.wButtons =
					(m_aState[nCnt].Gamepad.wButtons ^ m_aState[nCnt].Gamepad.wButtons) & m_aState[nCnt].Gamepad.wButtons;
			}
		}

		if (YGetStickPressL(BUTTON_LY, 0) == 0 && XGetStickPressL(BUTTON_LX, 0) == 0)
		{//スティックがもとに戻っているとき

		 //カウントを初期化
			m_nLeftStickCount = 0;

			//判定をOFF
			m_bLeftStickSelect = false;
		}

	}
}
//<======================================
//マウスのコンストラクタ
//<======================================
CMouse::CMouse()
{
	m_bUse = true;
}
//<======================================
//マウスのデストラクタ
//<======================================
CMouse::~CMouse()
{

}
//<======================================
//マウスの初期化処理
//<======================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//もし使う
	if (m_bUse == true)
	{
		CInput::Init(hInstance, hWnd);

		//入力デバイスの設定
		if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}

		//データフォーマットを設定
		if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
		{
			return E_FAIL;
		}

		//協調モードを設定
		if (FAILED(m_pDevice->SetCooperativeLevel
		(
			hWnd,
			(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)
		)))
		{
			return E_FAIL;
		}

		// デバイスの設定
		DIPROPDWORD diprop;
		diprop.diph.dwSize = sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwObj = 0;
		diprop.diph.dwHow = DIPH_DEVICE;
		diprop.dwData = DIPROPAXISMODE_REL; //相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

											//プロパティ設定
		if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
		{
			// デバイスの設定に失敗
			return E_FAIL;
		}

		//マウスへのアクセス権を取得
		m_pDevice->Acquire();
	}

	return S_OK;
}
//<======================================
//マウスの終了処理
//<======================================
void CMouse::Uninit(void)
{
	CInput::Uninit();
}
//<======================================
//マウスの更新処理
//<======================================
void CMouse::Update(void)
{
	if (m_bUse == true)
	{
		DIMOUSESTATE2 mouse; //マウスの入力情報

							 //入力デバイスからデータを取得
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(mouse), &mouse)))
		{
			//入力情報の保存
			m_State = mouse;

			//マウスの位置を取得
			GetCursorPos(&m_pos);

		}
		else
		{
			m_pDevice->Acquire(); //マウスへのアクセス権
		}
	}
}
//<======================================
//マウスのプレス情報取得
//<======================================
bool CMouse::GetMousePress(MOUSE_BUTTON nKey)
{
	//もし使う
	if (m_bUse == true)
	{
		return (m_State.rgbButtons[nKey] & 0x80) ? true : false;
	}

	return false;
}
//<======================================
//マウスのマウスの移動量取得
//<======================================
D3DXVECTOR3 CMouse::GetMouseMove(void)
{
	//もし使う
	if (m_bUse == true)
	{
		return D3DXVECTOR3(((float)m_State.lX) * MOUSE_MOVE_SENS, (-(float)m_State.lY) * MOUSE_MOVE_SENS, (-(float)m_State.lZ) * MOUSE_MOVE_SENS);
	}
	return{};
}
//<======================================
//マウスのマウスの移動量取得
//<======================================
D3DXVECTOR2 CMouse::GetMouseRotate(void)
{
	//もし使う
	if (m_bUse == true)
	{
		return D3DXVECTOR2(((float)m_State.lX) * MOUSE_ROTATE_SENSE, (-(float)m_State.lY) * MOUSE_ROTATE_SENSE);
	}
	return{};
}
//<==========================================
//マウスの位置を取得
//<==========================================
D3DXVECTOR3 CMouse::GetMousePos(void)
{
	//もし使う
	if (m_bUse == true)
	{
		return D3DXVECTOR3((float)m_pos.x, (float)m_pos.y, 0.0f);
	}
	return{};
}