//<==============================================
//���͏���(Input.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _INPUT_H_	//��d�C���N���[�h�h�~
#define _INPUT_H_

#include "main.h"



//<************************************************
//�}�N����`
//<************************************************
namespace
{
	const int NUM_KEY = 256;					//�L�[�̍ő吔
	const float MOUSE_MOVE_SENS = 0.5f;			//�}�E�X�ړ����x�̕␳
	const float MOUSE_ROTATE_SENSE = 0.005f;	//�}�E�X��]���x
}

//<============================================
//�p�b�h�̃{�^���̗񋓌^
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
//���͏����̃N���X��`(�e�N���X)
//<************************************************
class CInput
{
public:

	//<================================
	//�R���X�g���N�^�E�f�X�g���N�^
	//<================================
	CInput();
	virtual ~CInput();

	//<================================
	//�������z�֐�
	//<================================
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected:

	//<================================
	//�����o�ϐ�(���͊֘A)
	//<================================
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;

};

//<************************************************
//�L�[�{�[�h�̃N���X��`(�q�N���X)
//<************************************************
class CKeyboard : public CInput
{
public:

	//<================================
	//�R���X�g���N�^�E�f�X�g���N�^
	//<================================
	CKeyboard();
	~CKeyboard();

	//<================================
	//�����o�֐�
	//<================================
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	//<================================
	//Get�n�̃L�[�{�[�h����
	//<================================
	bool bGetPress(int nKey) { return (m_aState[nKey] & 0x80) ? true : false; }
	bool bGetTrigger(int nKey) { return (m_aStateTrigger[nKey] & 0x80) ? true : false; }
	bool bGetRelease(int nKey) { return (m_aStateRelease[nKey] & 0x80) ? true : false; }
	bool bGetRepeat(int nKey) { return (m_aStateRepeat[nKey] & 0x80) ? true : false; }

private:

	//<================================
	//�L�[�{�[�h�̓��͏��
	//<================================
	BYTE m_aState[NUM_KEY];				//�L�[�{�[�h�̃v���X���
	BYTE m_aStateTrigger[NUM_KEY];		//�L�[�{�[�h�̃g���K�[���
	BYTE m_aStateRelease[NUM_KEY];		//�L�[�{�[�h�̃����[�X���
	BYTE m_aStateRepeat[NUM_KEY];		//�L�[�{�[�h�̃��s�[�g���

};
#if 1
//<************************************************
//�W���C�p�b�h�̃N���X��`
//<************************************************
class CJoyPad : public CInput
{
public:

	//<============================================
	//�R���X�g���N�^�E�f�X�g���N�^
	//<============================================
	CJoyPad();
	~CJoyPad();

	//<============================================
	//���M�����[����
	//<============================================
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	//<============================================
	//Get�n�̃p�b�h����
	//<============================================
	bool bGetPress(BUTTON nKey, int nCnt) { return (m_aState[nCnt].Gamepad.wButtons & (0x01 << nKey)) ? true : false; }
	bool GetTrigger(BUTTON nKey, int nCnt) { return (m_aStateTrigger[nCnt].Gamepad.wButtons & (0x01 << nKey)) ? true : false; }
	bool GetRepeat(BUTTON nKey, int nCnt) { return (m_aStateRepeat[nCnt].Gamepad.wButtons & (0x01 << nKey)) ? true : false; }
	bool GetRelease(BUTTON nKey, int nCnt) { return (m_aStateRelease[nCnt].Gamepad.wButtons & (0x01 << nKey)) ? true : false; }
	bool GetPressLTrigger(BUTTON nKey, int nCnt) { return (m_aState[nCnt].Gamepad.bLeftTrigger & (0x01 << nKey)) ? true : false; }
	bool GetPressRTrigger(BUTTON nKey, int nCnt) { return (m_aState[nCnt].Gamepad.bRightTrigger & (0x01 << nKey)) ? true : false; }

	//<============================================
	//�p�b�h�̃X�e�B�b�N�֘A(Get�n)
	//<============================================
	SHORT XGetStickPressL(BUTTON nKey, int nCnt) { return m_aState[nCnt].Gamepad.sThumbLX; }
	SHORT YGetStickPressL(BUTTON nKey, int nCnt) { return m_aState[nCnt].Gamepad.sThumbLY; }
	SHORT XGetStickPressR(BUTTON nKey, int nCnt) { return m_aState[nCnt].Gamepad.sThumbRX; }
	SHORT YGetStickPressR(BUTTON nKey, int nCnt) { return m_aState[nCnt].Gamepad.sThumbRY; }
	//<============================================
	//�p�b�h�̃{�^���֘A
	//<============================================
	void SetEnableStickSelect(bool bStick) { m_bLeftStickSelect = bStick; }
	bool GetStickSelect(void) { return m_bLeftStickSelect; }

private:

	XINPUT_STATE m_aState[NUM_KEY];
	XINPUT_STATE m_aStateTrigger[NUM_KEY];		//�p�b�h�̃g���K�[���
	XINPUT_STATE m_aStateRelease[NUM_KEY];		//�p�b�h�̃����[�X���
	XINPUT_STATE m_aStateRepeat[NUM_KEY];		//�p�b�h�̃��s�[�g���
	bool m_bLeftStickSelect;					//���g���K�[�̑I�𔻒�
	int m_nLeftStickCount;						//���g���K�[�̑I���J�E���g
	int m_nCntPadrepeat;
};

//<************************************************
//�}�E�X�̃N���X��`(�q�N���X)
//<************************************************
class CMouse : public CInput
{
public:

	//<============================================
	//�}�E�X�{�^���̗񋓌^
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
	//�R���X�g���N�^�E�f�X�g���N�^
	//<============================================
	CMouse();
	~CMouse();

	//<============================================
	//���M�����[����
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

	DIMOUSESTATE2 m_State; //�S���͏��̕ۊ�
	DIMOUSESTATE2 m_StateTrigger; //�g���K�[���
	DIMOUSESTATE2 m_StateRerease; //�����[�X���
	DIMOUSESTATE2 m_StateRepeat; //���s�[�g���
	BYTE m_aOldState[8]; //�O��̓��͏���ۑ�

	bool m_bUse;

};
#endif
#endif
