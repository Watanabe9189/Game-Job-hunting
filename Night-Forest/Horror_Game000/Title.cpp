//<===========================================
//�^�C�g����ʂ̏���(Title.cpp)
//
//Author:kazuki watanabe
//<===========================================
#include "Title.h"
#include "input.h"
#include "object2D.h"
#include "manager.h"
#include "Texture.h"
#include "DebugProc.h"
#include "fade.h"

//<******************************************************************************
//�ÓI�����o�ϐ�
//<******************************************************************************
C2DChar *CTitle::m_ap2DChar[INT_VALUE::MAX_SIZE] = {};								//2D����

LPDIRECT3DTEXTURE9	CTitle::m_apTexture[INT_VALUE::MAX_TEX] = {};	//�e�N�X�`���|�C���^
const char*			CTitle::m_acFilename[SELECT_MAX] =				//�t�@�C���̖��O
{
		"data\\TEXTURE\\HORROR-SELECT000.png",
		"data\\TEXTURE\\HORROR-SELECT001.png",
		"data\\TEXTURE\\HORROR-SELECT002.png",
};
//<******************************************************************************
//���O�錾
//<******************************************************************************
namespace
{
	const float			DISTANCE_VALUE	= 350.0f;								//����
	const D3DXVECTOR2	SELECT_POS		= D3DXVECTOR2(250.0f, 500.0f);			//�ʒu
	const D3DXVECTOR2	SELECT_SIZE		= D3DXVECTOR2(150.0f, 150.0f);			//�T�C�Y
	const D3DXCOLOR		SELECT_COL		= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);	//�I������Ă��鎞�̐F
	const int MAX_COLCOUNT = 50;
}

CLight *CTitle::m_pLight = nullptr;
CField *CTitle::m_pField = nullptr;

Ccamera *CTitle::m_pCamera = nullptr;
CFog *CTitle::m_pFog = nullptr;

C3DEnemy *CTitle::m_ap3DEnemy[INT_VALUE::MAX_SIZE] = {};

C2DSelect *CTitle::m_pSelect = nullptr;

//<====================================
//�^�C�g���̃R���X�g���N�^
//<====================================
CTitle::CTitle()
{

}
//<====================================
//�^�C�g���̃f�X�g���N�^
//<====================================
CTitle::~CTitle()
{

}
//<====================================
//�^�C�g���̏���������
//<====================================
HRESULT CTitle::Init(void)
{
	CManager::GetSound()->PlaySound(CSound::LABEL_BGM_TITLE);
	//<******************************************
	//���C�g�̐���
	//<******************************************
	m_pCamera = Ccamera::Create();
	//���C�g����
	m_pLight = CLight::Create(CLight::MODE::MODE_DIRECTIONAL);

	//�n�ʐ���
	CField::ReadCreate(&m_pField);

	//�t�H�O����
	m_pFog = CFog::Create(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), D3DFOGMODE::D3DFOG_LINEAR, CFog::TYPE::TYPE_PIXEL,0.001f);

	C3DEnemy::ReadCreate(m_ap3DEnemy);

	//2D�����𐶐�
	m_ap2DChar[0] = C2DChar::Create(D3DXVECTOR2(625.0f, 150.0f), D3DXVECTOR2(350.0f, 100.0f), C2DChar::CHAR_TYPE_TITLE);

	m_pSelect = C2DSelect::Create(SELECT_POS, SELECT_MAX);

	//�e�N�X�`���̏�����
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		//�e�N�X�`���l�[����ݒ肷��
		m_pSelect->SetTexName(m_acFilename[nCnt], nCnt);
	}

	return S_OK;
}
//<====================================
//�^�C�g���̏I������
//<====================================
void CTitle::Uninit(void)
{
	//�t�H���g�̐����J��Ԃ�
	for (int nCnt = 0; nCnt < C2DChar::GetNum(); nCnt++)
	{
		if (m_ap2DChar[nCnt] != nullptr)
		{
			m_ap2DChar[nCnt]->Uninit();
			m_ap2DChar[nCnt] = nullptr;
		}
	}
	//�����������m�ۂ�����Ă�����
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	//<******************************************
	//���C�g�̔j��
	//<******************************************
	//�����������m�ۂ�����Ă�����
	if (m_pLight != nullptr)
	{
		//�������̉�����s��
		delete m_pLight;
		m_pLight = nullptr;
	}
	//<******************************************
	//�t�H�O�̔j��
	//<******************************************
	if (m_pFog != nullptr)
	{
		m_pFog->Uninit();
		m_pFog = nullptr;
	}
	//<******************************************
	//���C�g�̔j��
	//<******************************************
	//�����������m�ۂ�����Ă�����
	if (m_pField != nullptr)
	{
		//�������̉�����s��
		m_pField->Uninit();
		m_pField = nullptr;
	}
	//<******************************************
	//���C�g�̔j��
	//<******************************************
	//�����������m�ۂ�����Ă�����
	if (m_pSelect != nullptr)
	{
		//�������̉�����s��
		m_pSelect->Uninit();
		m_pSelect = nullptr;
	}

	//�t�H���g�̐����J��Ԃ�
	for (int nCnt = 0; nCnt < C3DEnemy::GetNum(); nCnt++)
	{
		if (m_ap3DEnemy[nCnt] != nullptr)
		{
			m_ap3DEnemy[nCnt]->Uninit();
			m_ap3DEnemy[nCnt] = nullptr;
		}
	}

	Release();
}
//<====================================
//�^�C�g���̍X�V����
//<====================================
void CTitle::Update(void)
{
	m_pCamera->Update();

	//�t�F�[�h��Ԃ��������Ă��Ȃ���Ԃ�������
	if (CManager::GetFade()->GetType() == CFade::TYPE_FADE_NONE)
	{
		//<========================================================
		//����^�C�v�ύX����
		//<========================================================
		//SPACE�L�[�������ꂽ��
		if (CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0) && m_pSelect->GetSelect() == SELECT::SELECT_START)
		{
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
			CManager::SetFade(CScene::MODE::MODE_GAME);
		}
		else if (CManager::GetKeyboard()->bGetTrigger(DIK_RETURN) == true && m_pSelect->GetSelect() == SELECT::SELECT_START)
		{
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
			CManager::SetFade(CScene::MODE::MODE_GAME);
		}
		//<========================================================
		//����^�C�v�ύX����
		//<========================================================
		//SPACE�L�[�������ꂽ��
		if (CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0) && m_pSelect->GetSelect() == SELECT::SELECT_OPTION)
		{
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
			CManager::SetFade(CScene::MODE::MODE_OPTION);
		}
		else if (CManager::GetKeyboard()->bGetTrigger(DIK_RETURN) == true && m_pSelect->GetSelect() == SELECT::SELECT_OPTION)
		{
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
			CManager::SetFade(CScene::MODE::MODE_OPTION);
		}
		//<========================================================
		//����^�C�v�ύX����
		//<========================================================
		//SPACE�L�[�������ꂽ��
		if (CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0) && m_pSelect->GetSelect() == SELECT::SELECT_EXIT)
		{
			PostQuitMessage(0);
		}
		else if (CManager::GetKeyboard()->bGetTrigger(DIK_RETURN) == true && m_pSelect->GetSelect() == SELECT::SELECT_EXIT)
		{
			PostQuitMessage(0);
		}
	}
}
//<====================================
//�^�C�g���̕`�揈��
//<====================================
void CTitle::Draw(void)
{
	m_pCamera->SetCamera();
}