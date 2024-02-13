//<==============================================
//�}�l�[�W������(manager.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "manager.h"

#include "Title.h"
#include "Tutorial.h"
#include "game.h"
#include "Result.h"
#include "Option.h"

#include "fade.h"

//<**********************************************
//2D�֘A�̃C���N���[�h
//<**********************************************
#include "object2D.h"

//<*********************************
//3D�֘A�̃C���N���[�h
//<*********************************
#include "Object3D.h"
#include "Light.h"
#include "Camera.h"
#include "BilB.h"
#include "XObject.h"
#include "Pause.h"

//<*********************************************
// �ÓI�����o�ϐ��錾
//<*********************************************
CRenderer *CManager::m_pRenderer = nullptr;
//���͊֘A
CKeyboard *CManager::m_pKeyboard = nullptr;
CJoyPad *CManager::m_pJoyPad = nullptr;
CMouse *CManager::m_pMouse = nullptr;
//2D�֘A
CBG *CManager::m_pBg = nullptr;
//���̑��֘A
CTexture *CManager::m_pTexture = nullptr;
CDebug *CManager::m_pDebug = nullptr;
CSound *CManager::m_pSound = nullptr;

CFade *CManager::m_pFade = nullptr;
CPause *CManager::m_pPause = nullptr;

//��ʑJ�ڊ֘A
#ifdef _DEBUG
CScene::MODE CScene::m_Mode = CScene::MODE::MODE_TITLE;
#else 
CScene::MODE CScene::m_Mode = CScene::MODE::MODE_TITLE;
#endif

//<*****************************************************************************
//�V�[���֘A
//<*****************************************************************************
CTitle *CScene::m_pTitle = nullptr;
CTutorial *CScene::m_pTutorial = nullptr;
CGame *CScene::m_pGame = nullptr;
CResult *CScene::m_pResult = nullptr;
COption *CScene::m_pOption = nullptr;
int CScene::m_nCount = INITIAL_INT;
CScene::TYPE_RESULT CScene::m_eTypeRes = CScene::TYPE_RESULT::TYPE_RESULT_FAILED;

//bool�^�̐ÓI�����o�ϐ��錾
bool CManager::m_bPause = false;

HINSTANCE CManager::m_hInstance = nullptr;

//�V�[���֘A
CScene *CManager::m_pScene = nullptr;									
CScene::MODE CManager::m_NowMode = CScene::MODE::MODE_MAX;						//���݂̃��[�h

//<==================================================================================
//�}�l�[�W���̃R���X�g���N�^
//<==================================================================================
CManager::CManager()
{
	
}

//<==================================================================================
//�}�l�[�W���̃f�X�g���N�^
//<==================================================================================
CManager::~CManager()
{

}
//<==================================================================================
//�}�l�[�W���̏���������
//<==================================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	m_hInstance = hInstance;

	//�������m��
	m_pRenderer = new CRenderer;

	//�ǂ�����B������Ă�����
	assert(m_pRenderer != nullptr && SUCCEEDED(m_pRenderer->Init(hWnd, TRUE)));

	//�������m��
	m_pDebug = new CDebug;

	//�ǂ�����B������Ă�����
	assert(m_pDebug != nullptr && SUCCEEDED(m_pDebug->Init()));

	//�������m��
	m_pSound = new CSound;

	//�ǂ�����B������Ă�����
	assert(m_pSound != nullptr && SUCCEEDED(m_pSound->Init(hWnd)));

	//���͏����֘A�̏�����
	InitInput(hInstance, hWnd);

	//�������m��
	m_pTexture = new CTexture;

	//�ǂ�����B������Ă�����
	assert(m_pTexture != nullptr && SUCCEEDED(m_pTexture->Load()));

#if 1

	//
	m_pScene = CScene::Create(GetMode());

	//��������
	m_pFade = CFade::Create();

	m_pPause = new CPause;

	m_pPause->Init();

	//�J�[�\����\�������Ȃ�����
	ShowCursor(FALSE);

#endif

	return S_OK;
}
//<==================================================================================
//�}�l�[�W���̏I������
//<==================================================================================
void CManager::Uninit(void)
{
	//�S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	m_pSound->StopSound();

	//�������m�ۂ�����Ă�����
	if (m_pRenderer != nullptr)
	{
		//�������̉�����s��
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	//�����������m�ۂ�����Ă�����
	if (m_pTexture != nullptr)
	{
		m_pTexture->UnloadAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	//�����������m�ۂ�����Ă�����
	if (m_pDebug != nullptr)
	{
		m_pDebug->Uninit();
		delete m_pDebug;
		m_pDebug = nullptr;
	}
	//�����������m�ۂ�����Ă�����
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}
	if (m_pPause != nullptr)
	{
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = nullptr;
	}
	
	//���͋@��̏I������
	UninitInput();

}
//<==================================================================================
//�}�l�[�W���̍X�V����
//<==================================================================================
void CManager::Update(void)
{
	UpdateInput();

	m_pDebug->Update();

	////P�L�[�������ꂽ��
	//if (m_pKeyboard->bGetTrigger(DIK_0) == true)
	//{
	//	SetD_SPEED();
	//}
	////P�L�[�������ꂽ��
	//if (m_pKeyboard->bGetTrigger(DIK_9) == true)
	//{
	//	SetS_SPEED();
	//}

	//�����|�[�Y����Ă��Ȃ����
	if (!m_bPause&&m_pScene != nullptr)
	{
		if (m_pFade != nullptr&&m_pFade->GetType() != CFade::TYPE_FADE_NONE)
		{
			m_pFade->Update();
		}

		//�����_���[�̍X�V����
		m_pRenderer->Update();
	}
	//�Q�[����ʂ̏ꍇ�݂̂ł����������Ȃ��悤�ɂ���
	if (m_pScene->GetMode() == CScene::MODE::MODE_GAME)
	{
		//P�L�[�������ꂽ��
		if (m_pKeyboard->bGetTrigger(DIK_P) == true)
		{
			//�O�����Z�q�Ń|�[�Y��Ԃ�؂�ւ���
			m_bPause == false ? m_bPause = true : m_bPause = false;
		}
		/*m_pPause->Update();*/
	}
	if (m_pKeyboard->bGetTrigger(DIK_Y) == true)
	{
		m_pRenderer->ScreenShot("data\\TEST.png");
	}
}
//<==================================================================================
//�}�l�[�W���̕`�揈��
//<==================================================================================
void CManager::Draw(void)
{
	
	if (m_pScene != nullptr)
	{
		//�����_���[�̕`�揈��
		m_pRenderer->Draw();
	}

}
//<================================================
//�t�F�[�h�ݒ�
//<================================================
void CManager::SetFade(const CScene::MODE modeNext)
{
	//�������g�������
	if (m_pFade != nullptr)
	{
		//�t�F�[�h���Ă��Ȃ���Ԃ̎��̂ݒʂ�悤�ɂ���
		if (m_pFade->GetType() == CFade::TYPE_FADE_NONE)
		{
			//���g��j������
			m_pFade->Uninit();
			delete m_pFade;
			m_pFade = nullptr;

			//��������
			m_pFade = CFade::Create();

			//���g�����邱�Ƃ��m�F
			assert(m_pFade != nullptr);

			//�t�F�[�h���J�n����
			m_pFade->SetFade(modeNext);
		}
	}
}
//<==================================================================================
//���͏����֘A�̏�����
//<==================================================================================
HRESULT CManager::InitInput(HINSTANCE hInstance, HWND hWnd)
{
	//�������g�������Ȃ����
	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CKeyboard;

		//�������m�ۂ������������̊m�F������
		assert(m_pKeyboard != nullptr);

		//�����������Ɏ��s������
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}
	//�������g�������Ȃ����
	if (m_pJoyPad == nullptr)
	{
		m_pJoyPad = new CJoyPad;

		//�������m�ۂ������������̊m�F������
		assert(m_pJoyPad != nullptr);

		//�����������Ɏ��s������
		if (FAILED(m_pJoyPad->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	//�������g�������Ȃ����
	if (m_pMouse == nullptr)
	{
		m_pMouse = new CMouse;

		//�������m�ۂ������������̊m�F������
		assert(m_pMouse != nullptr);

		//�����������Ɏ��s������
		if (FAILED(m_pMouse->Init(hInstance, hWnd)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}
//<==================================================================================
//���͏����֘A�̏I��
//<==================================================================================
void CManager::UninitInput(void)
{
	//�������m�ۂ�����Ă�����
	if (m_pKeyboard != nullptr)
	{
		//�������̉�����s��
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	//�������m�ۂ�����Ă�����
	if (m_pJoyPad != nullptr)
	{
		//�������̉�����s��
		m_pJoyPad->Uninit();
		delete m_pJoyPad;
		m_pJoyPad = nullptr;
	}

	//�������m�ۂ�����Ă�����
	if (m_pMouse != nullptr)
	{
		//�������̉�����s��
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}
}
//<==================================================================================
//���͏����֘A�̍X�V
//<==================================================================================
void CManager::UpdateInput(void)
{
	m_pKeyboard->Update();

	m_pJoyPad->Update();

	m_pMouse->Update();
}
//<==================================================================================
//���[�h�̐ݒ�
//<==================================================================================
void CManager::SetMode(CScene::MODE Mode)
{
	m_pSound->StopSound();

	//���݂̃V�[���̔j��������
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();
		m_pScene = nullptr;
	}

	//�j�����ꂽ���̃`�F�b�N������
	assert(m_pScene == nullptr);

	//���݂̃V�[���̔j��������������
	if (m_pScene == nullptr)
	{
		//�������s��
		m_pScene = CScene::Create(Mode);
	}
			
	//�j�����ꂽ���̃`�F�b�N������
	assert(m_pScene != nullptr);
}
//<==================================================================================
//
//<==================================================================================
CScene::CScene()
{
	//�l�̃N���A
	m_pTitle = nullptr;
	m_pTutorial = nullptr;
	m_pGame = nullptr;
	m_pResult = nullptr;
	m_pOption = nullptr;
}
//<==================================================================================
//
//<==================================================================================
CScene::~CScene()
{
	
}
//<==================================================================================
//
//<==================================================================================
CScene *CScene::Create(MODE Mode)
{
	//�C���X�^���X�����p�̃I�u�W�F�N�g(�܂��������g�̃|�C���^��Ԃ�)
	CScene *pScene = new CScene;

	//�������m�ۂɓ���O�Ƀ��[�h��ݒ肵�Ă���
	pScene->SetMode(Mode);

	//���[�h�ɂ���ď����𕪂���
	switch (Mode)
	{
		//�^�C�g���������ꍇ
	case MODE::MODE_TITLE:

		//���g����������
		if (m_pTitle != nullptr)
		{
			//2�T�ڈȍ~�ɓ������ۂ̖����ϐ��ւ̃A�N�Z�X��h��
			delete m_pTitle;
			m_pTitle = nullptr;
		}

		//nullptr��������
		if (m_pTitle == nullptr)
		{
			//����p�̃������m�ۂ�����
			m_pTitle = new CTitle;

			//�`�F�b�N
			assert(m_pTitle != nullptr);

			//����������
			m_pTitle->Init();
		}

		//���̐����p�̃I�u�W�F�N�g�ɑ������
		pScene = m_pTitle;

		break;

		//�I�v�V�����������ꍇ
	case MODE::MODE_OPTION:

		//���g����������
		if (m_pOption != nullptr)
		{
			//2�T�ڈȍ~�ɓ������ۂ̖����ϐ��ւ̃A�N�Z�X��h��
			delete m_pOption;
			m_pOption = nullptr;
		}

		//nullptr��������
		if (m_pOption == nullptr)
		{
			//����p�̃������m�ۂ�����
			m_pOption = new COption;

			//�`�F�b�N
			assert(m_pOption != nullptr);

			//����������
			m_pOption->Init();
		}

		//���̐����p�̃I�u�W�F�N�g�ɑ������
		pScene = m_pOption;

		break;

		//�`���[�g���A���������ꍇ
	case MODE::MODE_TUTORIAL:

		//���g����������
		if (m_pTutorial != nullptr)
		{
			//2�T�ڈȍ~�ɓ������ۂ̖����ϐ��ւ̃A�N�Z�X��h��
			delete m_pTutorial;
			m_pTutorial = nullptr;
		}

		//nullptr��������
		if (m_pTutorial == nullptr)
		{
			//����p�̃������m�ۂ�����
			m_pTutorial = new CTutorial;
		}

		//���g����������
		if (m_pTutorial != nullptr)
		{
			//���̐����p�̃I�u�W�F�N�g�ɑ������
			pScene = m_pTutorial;

			//����������
			pScene->Init();

			return pScene;
		}

		break;

		//�Q�[���������ꍇ
	case MODE::MODE_GAME:

		//���g����������
		if (m_pGame != nullptr)
		{
			//2�T�ڈȍ~�ɓ������ۂ̖����ϐ��ւ̃A�N�Z�X��h��
			delete m_pGame;
			m_pGame = nullptr;
		}

		//nullptr��������
		if (m_pGame == nullptr)
		{
			//����p�̃������m�ۂ�����
			m_pGame = new CGame;

			//�`�F�b�N
			assert(m_pGame != nullptr);

			//������
			m_pGame->Init();
		}

		//���̐����p�̃I�u�W�F�N�g�ɑ������
		pScene = m_pGame;

		break;

		//���U���g�������ꍇ
	case MODE::MODE_RESULT:

		m_nCount++;

		//���g����������
		if (m_pResult != nullptr)
		{
			//2�T�ڈȍ~�ɓ������ۂ̖����ϐ��ւ̃A�N�Z�X��h��
			delete m_pResult;
			m_pResult = nullptr;
		}

		//nullptr��������
		if (m_pResult == nullptr)
		{
			//����p�̃������m�ۂ�����
			m_pResult = new CResult;

			//�`�F�b�N
			assert(m_pResult != nullptr);

			//����������
			m_pResult->Init();
		}

		//���̐����p�̃I�u�W�F�N�g�ɑ������
		pScene = m_pResult;

		break;
	}
			
	return pScene;
}
//<==================================================================================
//
//<==================================================================================
HRESULT CScene::Init(void)
{
	return S_OK;
}
//<==================================================================================
//
//<==================================================================================
void CScene::Uninit(void)
{
	
}
//<==================================================================================
//
//<==================================================================================
void CScene::Update(void)
{

}
//<==================================================================================
//
//<==================================================================================
void CScene::Draw(void)
{
	
}