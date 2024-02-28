//<===========================================
//�Q�[����ʂ̏���(game.cpp)
//
//Author:kazuki watanabe
//<===========================================
#include "game.h"
#include "manager.h"
//<*****************************************
//���̑��֘A
//<*****************************************
#include "Texture.h"
#include "DebugProc.h"
#include "input.h"
#include "fade.h"
#include "2DParticle.h"
#include "3DParticle.h"
#include "Sound.h"
#include "BillBIcon.h"
#include "Pause.h"
//<================================================
//�ÓI�����o�ϐ��錾
//<================================================
//<*****************************************
//3D�֘A
//<*****************************************
CLight *CGame::m_pLight = nullptr;					//
C3DPlayer *CGame::m_p3DPlayer = nullptr;
CField *CGame::m_apField[INT_VALUE::MAX_SIZE] = {};
CFog *CGame::m_pFog = nullptr;
CBuilding *CGame::m_apBuilding[INT_VALUE::MAX_SIZE] = {};
C2DGauge *CGame::m_p2DGauge = nullptr;
C3DEnemy *CGame::m_ap3DEnemy[INT_VALUE::MAX_SIZE];
CItem *CGame::m_apItem[INT_VALUE::MAX_SIZE] = {};
C2DInfo *CGame::m_pInfo = nullptr;
Ccover *CGame::m_pCover = nullptr;
C2DChar *CGame::m_ap2DChar[CGame::CHAR2D::CHAR2D_MAX] = {};
CPlant *CGame::m_apPlant[INT_VALUE::MAX_SIZE] = {};
CLandMark *CGame::m_apLandMark[INT_VALUE::MAX_SIZE] = {};
CDestArrowX *CGame::m_pDestArrowX = nullptr;
CDestArrow *CGame::m_pDestArrow = nullptr;
Ccamera *CGame::m_pCamera = nullptr;

namespace
{
	const int NUM_BUILDING = 20;
	const int NUM_ITEM = 5;
	const int NUM_PLANT = 35;
	const D3DXVECTOR3 PLAYER_POS = D3DXVECTOR3(-4000.0f, 0.0f, 3640.0f);
	const D3DXVECTOR2 GAUGE_POS = D3DXVECTOR2(720.0f,660.0f);
}
//<====================================
//�Q�[����ʂ̃R���X�g���N�^
//<====================================
CGame::CGame()
{
	//�l�̃N���A
	m_nWaitTime = INITIAL_INT;
	m_bMoved = false;
}
//<====================================
//�Q�[����ʂ̃f�X�g���N�^
//<====================================
CGame::~CGame()
{

}
//<====================================
//�Q�[����ʂ̏���������
//<====================================
HRESULT CGame::Init(void)
{
	m_sState = STATE_NONE;
	m_nWaitTime = INITIAL_INT;
	m_bMoved = false;
	CManager::GetRenderer()->SetBoolPix(FALSE);
	CManager::GetSound()->PlaySound(CSound::LABEL_BGM_GAME);
	//<******************************************
	//���C�g�̐���
	//<******************************************
	m_pCamera = Ccamera::Create();

	//���C�g����
	m_pLight = CLight::Create(CLight::MODE::MODE_DIRECTIONAL);

	//�t�H�O����
	m_pFog = CFog::Create(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), D3DFOGMODE::D3DFOG_LINEAR, CFog::TYPE::TYPE_PIXEL,0.002f);

	//�n�ʐ���
	CField::ReadCreate(m_apField);

	//�v���C���[����
	m_p3DPlayer = C3DPlayer::Create(PLAYER_POS);

	//��������
	CBuilding::RandCreate(m_apBuilding, NUM_BUILDING);

	//�A�C�e������
	CItem::RandCreate(m_apItem, NUM_ITEM);

	CPlant::RandCreate(m_apPlant, NUM_PLANT);

	CLandMark::FixedCreate(m_apLandMark);

	m_pDestArrowX = CDestArrowX::Create();

	//�Q�[�W����
	m_p2DGauge = C2DGauge::Create(GAUGE_POS, m_p3DPlayer->GetStamina(), C2DGauge::VERTEX_X, C2DGauge::MODE_ONLY_USE);

	//��񐶐�
	m_pInfo = C2DInfo::Create(C2DInfo::Class::CLASS_NUMBER);

	m_ap2DChar[CHAR2D_HIDE] = C2DChar::Create(D3DXVECTOR2(1150.0f, 675.0f),
		D3DXVECTOR2(125.0f, 125.0f), C2DChar::CHAR_TYPE::CHAR_TYPE_HIDEINFO, C2DChar::MOVE_FROM_NONE, false);

	m_ap2DChar[CHAR2D_PICKUP] = C2DChar::Create(D3DXVECTOR2(1150.0f, 
		m_ap2DChar[CHAR2D_HIDE]->GetPosition().y), D3DXVECTOR2(125.0f, 125.0f),
		C2DChar::CHAR_TYPE::CHAR_TYPE_PICKUP_INFO, C2DChar::MOVE_FROM_NONE, false);

	m_ap2DChar[CHAR2D_COMEOUT] = C2DChar::Create(D3DXVECTOR2(1150.0f, 675.0f),
		D3DXVECTOR2(125.0f, 125.0f), C2DChar::CHAR_TYPE::CHAR_TYPE_COMEOUT_INFO, C2DChar::MOVE_FROM_NONE, false);

	m_ap2DChar[CHAR2D_SEALED] = C2DChar::Create(D3DXVECTOR2(575.0f, 500.0f),
		D3DXVECTOR2(140.0f, 120.0f), C2DChar::CHAR_TYPE::CHAR_TYPE_SEALED_INFO, C2DChar::MOVE_FROM_NONE, false);

	m_pDestArrow = CDestArrow::Create();

	return S_OK;
}
//<====================================
//�Q�[����ʂ̏I������
//<====================================
void CGame::Uninit(void)
{
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
	//�v���C���[�̔j��
	//<******************************************
	if (m_p3DPlayer != nullptr)
	{
		m_p3DPlayer->Uninit();
		m_p3DPlayer = nullptr;
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
	//�Q�[�W�̔j��
	//<******************************************
	if (m_p2DGauge != nullptr)
	{
		m_p2DGauge->Uninit();
		m_p2DGauge = nullptr;
	}
	//<******************************************
	//�C���t�H�̔j��
	//<******************************************
	if (m_pInfo != nullptr)
	{
		m_pInfo->Uninit();
		m_pInfo = nullptr;
	}
	//<******************************************
	//�J�o�[�̔j��
	//<******************************************
	if (m_pCover != nullptr)
	{
		m_pCover->Uninit();
		m_pCover = nullptr;
	}
	//<******************************************
	//�J�o�[�̔j��
	//<******************************************
	if (m_pDestArrowX != nullptr)
	{
		m_pDestArrowX->Uninit();
		m_pDestArrowX = nullptr;
	}
	//<******************************************
	//�J�o�[�̔j��
	//<******************************************
	if (m_pDestArrow != nullptr)
	{
		m_pDestArrow->Uninit();
		m_pDestArrow = nullptr;
	}
	//<******************************************
	//�ǂ̔j��
	//<******************************************
	for (int nCnt = 0; nCnt < CField::GetNum(); nCnt++)
	{
		//�����������m�ۂ�����Ă�����
		if (m_apField[nCnt] != nullptr)
		{
			//�������̉�����s�킸�A�I������������
			m_apField[nCnt]->Uninit();
			m_apField[nCnt] = nullptr;
		}
	}
	//<******************************************
	//�ǂ̔j��
	//<******************************************
	for (int nCnt = 0; nCnt < C3DEnemy::GetNum(); nCnt++)
	{
		//�����������m�ۂ�����Ă�����
		if (m_ap3DEnemy[nCnt] != nullptr)
		{
			//�������̉�����s�킸�A�I������������
			m_ap3DEnemy[nCnt]->Uninit();
			m_ap3DEnemy[nCnt] = nullptr;
		}
	}
	//<******************************************
	//�ǂ̔j��
	//<******************************************
	for (int nCnt = 0; nCnt < CBuilding::GetNum(); nCnt++)
	{
		//�����������m�ۂ�����Ă�����
		if (m_apBuilding[nCnt] != nullptr)
		{
			//�������̉�����s�킸�A�I������������
			m_apBuilding[nCnt]->Uninit();
			m_apBuilding[nCnt] = nullptr;
		}
	}
	//<******************************************
	//�ǂ̔j��
	//<******************************************
	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		//�����������m�ۂ�����Ă�����
		if (m_apItem[nCnt] != nullptr)
		{
			//�������̉�����s�킸�A�I������������
			m_apItem[nCnt]->Uninit();
			m_apItem[nCnt] = nullptr;
		}
	}
	//<******************************************
	//�ǂ̔j��
	//<******************************************
	for (int nCnt = 0; nCnt < C2DChar::GetNum(); nCnt++)
	{
		//�����������m�ۂ�����Ă�����
		if (m_ap2DChar[nCnt] != nullptr)
		{
			//�������̉�����s�킸�A�I������������
			m_ap2DChar[nCnt]->Uninit();
			m_ap2DChar[nCnt] = nullptr;
		}
	}
	//<******************************************
	//�ǂ̔j��
	//<******************************************
	for (int nCnt = 0; nCnt < CPlant::GetNum(); nCnt++)
	{
		//�����������m�ۂ�����Ă�����
		if (m_apPlant[nCnt] != nullptr)
		{
			//�������̉�����s�킸�A�I������������
			m_apPlant[nCnt]->Uninit();
			m_apPlant[nCnt] = nullptr;
		}
	}
	//<******************************************
	//�ǂ̔j��
	//<******************************************
	for (int nCnt = 0; nCnt < CLandMark::GetNum(); nCnt++)
	{
		//�����������m�ۂ�����Ă�����
		if (m_apLandMark[nCnt] != nullptr)
		{
			//�������̉�����s�킸�A�I������������
			m_apLandMark[nCnt]->Uninit();
			m_apLandMark[nCnt] = nullptr;
		}
	}
	Release();
}
//<====================================
//�Q�[����ʂ̍X�V����
//<====================================
void CGame::Update(void)
{
#define MAX_WAIT	(100)	//�ҋ@���Ԃ̍ő�l

	m_pLight->Update();
	m_pCamera->Update();

	//�����Ă����
	if (Bool::bMove(m_p3DPlayer->GetMove())
		&& !m_bMoved)
	{
		//�G����
		C3DEnemy::RandCreate(m_ap3DEnemy);

		//�t���O�𗧂āA���ڂ̐������Ȃ��悤�ɂ���
		m_bMoved = true;
	}
	//���S��Ԃ�������
	if (m_p3DPlayer->GetState() == C3DPlayer::STATE::STATE_DEATH)
	{
		//���g�Ȃ���������
		if (m_pCover == nullptr)
		{
			m_pCover = Ccover::Create(Ccover::TYPE::TYPE_BLOOD_COV);
		}

		CScene::SetResult(TYPE_RESULT_FAILED);

		//�I����Ă����Ԃɂ���
		m_sState = STATE_END;

		//�ҋ@���Ԃ̍ő�l�𒴂��Ă�����
		if (m_nWaitTime >= MAX_WAIT)
		{
			//���U���g��ʂ����s���[�h�ɂ���
			CManager::SetFade(CScene::MODE::MODE_RESULT);
			m_nWaitTime = 0;
		}
		//���Ȃ����
		else
		{
			//���Z���Ă���
			m_nWaitTime++;
		}

	}
	//�A�C�e�����E���I���Ă�����
	if (CItem::GetNumCollect() == CItem::GetMax())
	{
		//�I����Ԃ���Ȃ��ꍇ
		if (m_sState != STATE_END)
		{
			//���̑��̉��y���~�߁A���ʉ����Đ�����
			CManager::GetSound()->StopSound();
			CManager::GetSound()->PlaySound(CSound::LABEL::LABEL_SE_ESCAPED);
		}
		CScene::SetResult(TYPE_RESULT::TYPE_RESULT_SUCCEEDED);

		//���g�Ȃ���������
		if (m_pCover == nullptr)
		{
			m_pCover = Ccover::Create(Ccover::TYPE::TYPE_SAFE_COV);
		}

		//�I����Ă����Ԃɂ���
		m_sState = STATE_END;

		//�ҋ@���Ԃ̍ő�l�𒴂��Ă�����
		if (m_nWaitTime >= MAX_WAIT)
		{
			//���U���g��ʂ𐬌����[�h�ɂ���
			CManager::SetFade(CScene::MODE::MODE_RESULT);
			m_nWaitTime = 0;
		}
		//���Ȃ����
		else
		{
			//���Z���Ă���
			m_nWaitTime++;
		}
	}
	ItemUpdate();
#ifdef _DEBUG

	//<========================================================
	//����^�C�v�ύX����
	//<========================================================
	//SPACE�L�[�������ꂽ��
	if (CManager::GetKeyboard()->bGetTrigger(DIK_1) == true ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_BACK, 0) == true)
	{
		CItem::SetNumCollect(CItem::GetMax());
	}
	//<========================================================
	//����^�C�v�ύX����
	//<========================================================
	//SPACE�L�[�������ꂽ��
	if (CManager::GetKeyboard()->bGetTrigger(DIK_2) == true ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_BACK, 0) == true)
	{
		m_pFog->ChangeUse();
	}
#endif
}
//<====================================
//�Q�[����ʂ̕`�揈��
//<====================================
void CGame::Draw(void)
{
	//<***************************************************
	//CObject��ʂ��Ă���I�u�W�F�N�g�͎����ŏ������s����ׁA
	//�����ɏ����������K�v�͂Ȃ�
	//<***************************************************
	m_pCamera->SetCamera();
}
//<====================================
//�A�C�e���֘A�̍X�V����
//<====================================
void CGame::ItemUpdate(void)
{
	//�A�C�e���̐�����
	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		//�A�C�e�����擾���Ă��Ȃ����
		if (!m_apItem[nCnt]->bGet())
		{
			//�߂Â��Ă�����
			if (m_apItem[nCnt]->GetAppro())
			{
				//�߂Â��Ă�����
				if (m_apItem[nCnt]->bGetSealed())
				{
					//�\���������A�������甲����
					m_ap2DChar[CHAR2D_SEALED]->SetDrawtrue();
					break;
				}
				else
				{
					//�\���������A�������甲����
					m_ap2DChar[CHAR2D_PICKUP]->SetDrawtrue();
					break;
				}
			}
			//����Ă�����
			else if (!m_apItem[nCnt]->GetAppro())
			{
				//�\���������Ȃ�
				m_ap2DChar[CHAR2D_PICKUP]->SetDrawfalse();
				//�\���������Ȃ�
				m_ap2DChar[CHAR2D_SEALED]->SetDrawfalse();
			}
		}
		//�߂Â��Ă�����
		if (!m_apItem[nCnt]->bGetSealed())
		{
			//�\���������Ȃ�
			m_ap2DChar[CHAR2D_SEALED]->SetDrawfalse();
		}
	}

	if (m_ap2DChar[CHAR2D_HIDE]->GetbDraw() || m_ap2DChar[CHAR2D_COMEOUT]->GetbDraw())
	{
		m_ap2DChar[CHAR2D::CHAR2D_PICKUP]->SetPosition(D3DXVECTOR2(1080.0f,
			m_ap2DChar[CHAR2D_HIDE]->GetPosition().y - 140.0f));
	}
	if (!m_ap2DChar[CHAR2D_HIDE]->GetbDraw() && !m_ap2DChar[CHAR2D_COMEOUT]->GetbDraw())
	{
		m_ap2DChar[CHAR2D::CHAR2D_PICKUP]->SetPosition(D3DXVECTOR2(1080.0f,
			m_ap2DChar[CHAR2D_HIDE]->GetPosition().y));
	}
	//
	if (m_p3DPlayer->GetUnsealed())
	{
		if (m_ap2DChar[CHAR2D_FOUND] == nullptr)
		{
			m_ap2DChar[CHAR2D_FOUND] = C2DChar::Create(D3DXVECTOR2(600.0f, 425.0f),
				D3DXVECTOR2(200.0f, 200.0f), C2DChar::CHAR_TYPE::CHAR_TYPE_FOUND_INFO, C2DChar::MOVE_FROM_LEFT, true);
		}
	}
}