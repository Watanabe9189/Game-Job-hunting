//<==============================================
//���͏���(Input.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "Input.h"

//<======================================
//�ÓI�����o�ϐ��錾
//<======================================
LPDIRECTINPUT8 CInput::m_pInput = NULL;		//

											//<======================================
											//���͂̃R���X�g���N�^
											//<======================================
CInput::CInput()
{
	//�l�̃N���A
	m_pDevice = NULL;
}
//<======================================
//���͂̃f�X�g���N�^
//<======================================
CInput::~CInput()
{

}
//<======================================
//���͏����̏�����
//<======================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{
		//DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}
//<======================================
//���͏����̏I������
//<======================================
void CInput::Uninit(void)
{
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	//�L�[�{�[�h�ւ̃A�N�Z�X�������
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
//�L�[�{�[�h�̃R���X�g���N�^
//<======================================
CKeyboard::CKeyboard()
{
	//���g���Ȃ���
	for (int nCnt = 0; nCnt < NUM_KEY; nCnt++)
	{
		m_aState[nCnt] = NULL;
	}
}
//<======================================
//�L�[�{�[�h�̃f�X�g���N�^
//<======================================
CKeyboard::~CKeyboard()
{

}
//<======================================
//�L�[�{�[�h�̏���������
//<======================================
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}
//<======================================
//�L�[�{�[�h�̏I������
//<======================================
void CKeyboard::Uninit(void)
{
	CInput::Uninit();
}
//<======================================
//�L�[�{�[�h�̍X�V����
//<======================================
void CKeyboard::Update(void)
{
	const int REPEAT_TIME = 10;

	BYTE aKeyState[NUM_KEY];	//�L�[�{�[�h�̓��͏��
	static int RepeatCount[NUM_KEY] = {};

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{

		for (int nCntKey = 0; nCntKey < NUM_KEY; nCntKey++)
		{
			m_aStateTrigger[nCntKey] = (m_aState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];		//�g���K�[����ۑ�
			m_aStateRelease[nCntKey] = (m_aState[nCntKey] ^ aKeyState[nCntKey]) & m_aState[nCntKey];	//�����[�X����ۑ�
			m_aState[nCntKey] = aKeyState[nCntKey];															//�L�[�{�[�h�̃v���X����ۑ�
			m_aStateRepeat[nCntKey] = m_aStateTrigger[nCntKey];

			//���s�[�g����(�v���X���Ă����)
			if (bGetPress(nCntKey) == true)
			{
				//�J�E���g�����Z���Ă���
				RepeatCount[nCntKey]++;

				//���Ԃ̍ő�𒴂�����
				if (RepeatCount[nCntKey] >= REPEAT_TIME)
				{
					m_aStateRepeat[nCntKey] = m_aState[nCntKey];
				}
				else
				{
					//g_aKeyStateRepeat[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey];	//���s�[�g�Ƀ����[�X�̏��ۑ�
					m_aStateRepeat[nCntKey] = m_aStateRelease[nCntKey];
				}
			}
			//���������Ă�����
			else
			{
				//�J�E���g��0�ɂ���
				RepeatCount[nCntKey] = 0;
			}
			//
			if (bGetRelease(nCntKey) == true)
			{//�����[�X���͂��ꂽ�Ƃ�
				RepeatCount[nCntKey] = 0;
			}
		}

	}
	else
	{
		m_pDevice->Acquire();	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}
//<======================================
//�W���C�p�b�h�̃R���X�g���N�^
//<======================================
CJoyPad::CJoyPad()
{

}
//<======================================
//�W���C�p�b�h�̃f�X�g���N�^
//<======================================
CJoyPad::~CJoyPad()
{

}
//<======================================
//�W���C�p�b�h�̏���������
//<======================================
HRESULT CJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	//XInput��L����
	XInputEnable(true);

	//���X�e�B�b�N�̏���������
	m_bLeftStickSelect = false;
	m_nLeftStickCount = 0;

	//�������N���A
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
//�W���C�p�b�h�̏I������
//<======================================
void CJoyPad::Uninit(void)
{
	CInput::Uninit();

	XInputEnable(false);
}
//<======================================
//�W���C�p�b�h�̍X�V����
//<======================================
void CJoyPad::Update(void)
{
	XINPUT_STATE  aGamepadState[NUM_KEY];

	const int REPEAT_TIME = 10;

	//���̓f�o�C�X����f�[�^���擾
	for (int nCnt = 0; nCnt < NUM_KEY; nCnt++)
	{
		if (XInputGetState(nCnt, &aGamepadState[nCnt]) == ERROR_SUCCESS)
		{
			//�L�[�{�[�h�̃g���K�[����ۑ�
			m_aStateTrigger[nCnt].Gamepad.wButtons =
				(~m_aState[nCnt].Gamepad.wButtons) & aGamepadState[nCnt].Gamepad.wButtons;

			//�����[�X����ۑ�
			m_aStateRelease[nCnt].Gamepad.wButtons =
				(m_aState[nCnt].Gamepad.wButtons ^ aGamepadState[nCnt].Gamepad.wButtons) & m_aState[nCnt].Gamepad.wButtons;


			//�L�[�{�[�h�̃v���X����ۑ�
			m_aState[nCnt] = aGamepadState[nCnt];

			if ((m_nCntPadrepeat % REPEAT_TIME) == 0)
			{
				//���s�[�g����ۑ�
				m_nCntPadrepeat = (m_nCntPadrepeat + 1) % REPEAT_TIME;
				m_aStateRepeat[nCnt].Gamepad.wButtons = aGamepadState[nCnt].Gamepad.wButtons;
			}
			else
			{
				//���s�[�g�Ƀ����[�X�̏��ۑ�
				m_aStateRepeat[nCnt].Gamepad.wButtons =
					(m_aState[nCnt].Gamepad.wButtons ^ m_aState[nCnt].Gamepad.wButtons) & m_aState[nCnt].Gamepad.wButtons;
			}
		}

		if (YGetStickPressL(BUTTON_LY, 0) == 0 && XGetStickPressL(BUTTON_LX, 0) == 0)
		{//�X�e�B�b�N�����Ƃɖ߂��Ă���Ƃ�

		 //�J�E���g��������
			m_nLeftStickCount = 0;

			//�����OFF
			m_bLeftStickSelect = false;
		}

	}
}
//<======================================
//�}�E�X�̃R���X�g���N�^
//<======================================
CMouse::CMouse()
{
	m_bUse = true;
}
//<======================================
//�}�E�X�̃f�X�g���N�^
//<======================================
CMouse::~CMouse()
{

}
//<======================================
//�}�E�X�̏���������
//<======================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�����g��
	if (m_bUse == true)
	{
		CInput::Init(hInstance, hWnd);

		//���̓f�o�C�X�̐ݒ�
		if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
		{
			return E_FAIL;
		}

		//�f�[�^�t�H�[�}�b�g��ݒ�
		if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
		{
			return E_FAIL;
		}

		//�������[�h��ݒ�
		if (FAILED(m_pDevice->SetCooperativeLevel
		(
			hWnd,
			(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)
		)))
		{
			return E_FAIL;
		}

		// �f�o�C�X�̐ݒ�
		DIPROPDWORD diprop;
		diprop.diph.dwSize = sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwObj = 0;
		diprop.diph.dwHow = DIPH_DEVICE;
		diprop.dwData = DIPROPAXISMODE_REL; //���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

											//�v���p�e�B�ݒ�
		if (FAILED(m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
		{
			// �f�o�C�X�̐ݒ�Ɏ��s
			return E_FAIL;
		}

		//�}�E�X�ւ̃A�N�Z�X�����擾
		m_pDevice->Acquire();
	}

	return S_OK;
}
//<======================================
//�}�E�X�̏I������
//<======================================
void CMouse::Uninit(void)
{
	CInput::Uninit();
}
//<======================================
//�}�E�X�̍X�V����
//<======================================
void CMouse::Update(void)
{
	if (m_bUse == true)
	{
		DIMOUSESTATE2 mouse; //�}�E�X�̓��͏��

							 //���̓f�o�C�X����f�[�^���擾
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(mouse), &mouse)))
		{
			//���͏��̕ۑ�
			m_State = mouse;

			//�}�E�X�̈ʒu���擾
			GetCursorPos(&m_pos);

		}
		else
		{
			m_pDevice->Acquire(); //�}�E�X�ւ̃A�N�Z�X��
		}
	}
}
//<======================================
//�}�E�X�̃v���X���擾
//<======================================
bool CMouse::GetMousePress(MOUSE_BUTTON nKey)
{
	//�����g��
	if (m_bUse == true)
	{
		return (m_State.rgbButtons[nKey] & 0x80) ? true : false;
	}

	return false;
}
//<======================================
//�}�E�X�̃}�E�X�̈ړ��ʎ擾
//<======================================
D3DXVECTOR3 CMouse::GetMouseMove(void)
{
	//�����g��
	if (m_bUse == true)
	{
		return D3DXVECTOR3(((float)m_State.lX) * MOUSE_MOVE_SENS, (-(float)m_State.lY) * MOUSE_MOVE_SENS, (-(float)m_State.lZ) * MOUSE_MOVE_SENS);
	}
	return{};
}
//<======================================
//�}�E�X�̃}�E�X�̈ړ��ʎ擾
//<======================================
D3DXVECTOR2 CMouse::GetMouseRotate(void)
{
	//�����g��
	if (m_bUse == true)
	{
		return D3DXVECTOR2(((float)m_State.lX) * MOUSE_ROTATE_SENSE, (-(float)m_State.lY) * MOUSE_ROTATE_SENSE);
	}
	return{};
}
//<==========================================
//�}�E�X�̈ʒu���擾
//<==========================================
D3DXVECTOR3 CMouse::GetMousePos(void)
{
	//�����g��
	if (m_bUse == true)
	{
		return D3DXVECTOR3((float)m_pos.x, (float)m_pos.y, 0.0f);
	}
	return{};
}