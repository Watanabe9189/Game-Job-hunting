//<==============================================
//入力処理(Input.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _INPUT_H_	//二重インクルード防止
#define _INPUT_H_

#include "main.h"



//<************************************************
//マクロ定義
//<************************************************
namespace
{
	const int NUM_KEY = 256;					//キーの最大数
	const float MOUSE_MOVE_SENS = 0.5f;			//マウス移動感度の補正
	const float MOUSE_ROTATE_SENSE = 0.005f;	//マウス回転感度
}

//<============================================
//パッドのボタンの列挙型
//<============================================
enum BUTTON
{
	BUTTON_UP = 0,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_START,
	BUTTON_BACK,
	BUTTON_LSTICKPUSH,
	BUTTON_RSTICKPUSH,
	BUTTON_LB,
	BUTTON_RB,
	BUTTON_LT,
	BUTTON_RT,
	BUTTON_A,
	BUTTON_B,
	BUTTON_X,
	BUTTON_Y,
	BUTTON_LX,
	BUTTON_LY,
	BUTTON_18,
	BUTTON_19,
	BUTTON_MAX

};

//<************************************************
//入力処理のクラス定義(親クラス)
//<************************************************
class CInput
{
public:

	//<================================
	//コンストラクタ・デストラクタ
	//<================================
	CInput();
	virtual ~CInput();

	//<================================
	//純粋仮想関数
	//<================================
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:

	//<================================
	//メンバ変数(入力関連)
	//<================================
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;

};

//<************************************************
//キーボードのクラス定義(子クラス)
//<************************************************
class CKeyboard : public CInput
{
public:

	//<================================
	//コンストラクタ・デストラクタ
	//<================================
	CKeyboard();
	~CKeyboard();

	//<================================
	//メンバ関数
	//<================================
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	//<================================
	//Get系のキーボード入力
	//<================================
	bool bGetPress(int nKey) { return (m_aState[nKey] & 0x80) ? true : false; }
	bool bGetTrigger(int nKey) { return (m_aStateTrigger[nKey] & 0x80) ? true : false; }
	bool bGetRelease(int nKey) { return (m_aStateRelease[nKey] & 0x80) ? true : false; }
	bool bGetRepeat(int nKey) { return (m_aStateRepeat[nKey] & 0x80) ? true : false; }

private:

	//<================================
	//キーボードの入力情報
	//<================================
	BYTE m_aState[NUM_KEY];				//キーボードのプレス情報
	BYTE m_aStateTrigger[NUM_KEY];		//キーボードのトリガー情報
	BYTE m_aStateRelease[NUM_KEY];		//キーボードのリリース情報
	BYTE m_aStateRepeat[NUM_KEY];		//キーボードのリピート情報

};
#if 1
//<************************************************
//ジョイパッドのクラス定義
//<************************************************
class CJoyPad : public CInput
{
public:

	//<============================================
	//コンストラクタ・デストラクタ
	//<============================================
	CJoyPad();
	~CJoyPad();

	//<============================================
	//レギュラー処理
	//<============================================
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	//<============================================
	//Get系のパッド入力
	//<============================================
	bool bGetPress(BUTTON nKey, int nCnt) { return (m_aState[nCnt].Gamepad.wButtons & (0x01 << nKey)) ? true : false; }
	bool GetTrigger(BUTTON nKey, int nCnt) { return (m_aStateTrigger[nCnt].Gamepad.wButtons & (0x01 << nKey)) ? true : false; }
	bool GetRepeat(BUTTON nKey, int nCnt) { return (m_aStateRepeat[nCnt].Gamepad.wButtons & (0x01 << nKey)) ? true : false; }
	bool GetRelease(BUTTON nKey, int nCnt) { return (m_aStateRelease[nCnt].Gamepad.wButtons & (0x01 << nKey)) ? true : false; }
	bool GetPressLTrigger(BUTTON nKey, int nCnt) { return (m_aState[nCnt].Gamepad.bLeftTrigger & (0x01 << nKey)) ? true : false; }
	bool GetPressRTrigger(BUTTON nKey, int nCnt) { return (m_aState[nCnt].Gamepad.bRightTrigger & (0x01 << nKey)) ? true : false; }

	//<============================================
	//パッドのスティック関連(Get系)
	//<============================================
	SHORT XGetStickPressL(BUTTON nKey, int nCnt) { return m_aState[nCnt].Gamepad.sThumbLX; }
	SHORT YGetStickPressL(BUTTON nKey, int nCnt) { return m_aState[nCnt].Gamepad.sThumbLY; }
	SHORT XGetStickPressR(BUTTON nKey, int nCnt) { return m_aState[nCnt].Gamepad.sThumbRX; }
	SHORT YGetStickPressR(BUTTON nKey, int nCnt) { return m_aState[nCnt].Gamepad.sThumbRY; }
	//<============================================
	//パッドのボタン関連
	//<============================================
	void SetEnableStickSelect(bool bStick) { m_bLeftStickSelect = bStick; }
	bool GetStickSelect(void) { return m_bLeftStickSelect; }

private:

	XINPUT_STATE m_aState[NUM_KEY];
	XINPUT_STATE m_aStateTrigger[NUM_KEY];		//パッドのトリガー情報
	XINPUT_STATE m_aStateRelease[NUM_KEY];		//パッドのリリース情報
	XINPUT_STATE m_aStateRepeat[NUM_KEY];		//パッドのリピート情報
	bool m_bLeftStickSelect;					//左トリガーの選択判定
	int m_nLeftStickCount;						//左トリガーの選択カウント
	int m_nCntPadrepeat;
};

//<************************************************
//マウスのクラス定義(子クラス)
//<************************************************
class CMouse : public CInput
{
public:

	//<============================================
	//マウスボタンの列挙型
	//<============================================
	enum MOUSE_BUTTON
	{
		MOUSE_BUTTON_LEFT = 0,
		MOUSE_BUTTON_RIGHT,
		MOUSE_BUTTON_WHEEL,
		MOUSE_BUTTON_SIDE_1,
		MOUSE_BUTTON_SIDE_2
	};

	//<============================================
	//コンストラクタ・デストラクタ
	//<============================================
	CMouse();
	~CMouse();

	//<============================================
	//レギュラー処理
	//<============================================
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	bool GetMousePress(MOUSE_BUTTON nKey);

	D3DXVECTOR3 GetMouseMove(void);
	D3DXVECTOR2 GetMouseRotate(void);
	D3DXVECTOR3 GetMousePos(void);

	void SetUse(void){m_bUse == true ? m_bUse = false : m_bUse = true;}

private:

	POINT m_pos;

	DIMOUSESTATE2 m_State; //全入力情報の保管
	DIMOUSESTATE2 m_StateTrigger; //トリガー情報
	DIMOUSESTATE2 m_StateRerease; //リリース情報
	DIMOUSESTATE2 m_StateRepeat; //リピート情報
	BYTE m_aOldState[8]; //前回の入力情報を保存

	bool m_bUse;

};
#endif
#endif
