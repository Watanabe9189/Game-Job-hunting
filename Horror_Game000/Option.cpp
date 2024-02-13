#include "Option.h"


C2DGauge *COption::m_p2DGauge = nullptr;
CNumber  *COption::m_pNumber = nullptr;

LPDIRECT3DTEXTURE9	COption::m_apTexture[INT_VALUE::MAX_TEX] = {};

//�e�N�X�`���ւ̃|�C���^
const char*			COption::m_acFilename[] =
{
	"data\\TEXTURE\\HORROR-OPTION001.png",
	"data\\TEXTURE\\HORROR-OPTION002.png",
	"data\\TEXTURE\\HORROR-SELECT002.png",
	"data\\TEXTURE\\number_02.png"

};				//�t�@�C����

namespace
{
	const float			DISTANCE_Y = 250.0f;								//Y���̋���
	const float			DISTANCE_GAUGE= 400.0f;								//�Q�[�W����
	const float			DISTANCE_NUM = 305.0f;								//�ԍ�����

	const D3DXVECTOR2 OPTION_POS = D3DXVECTOR2(485.0f, 100.0f);				//�I�v�V�����ʒu
	const D3DXVECTOR2 OPTION_SIZE = D3DXVECTOR2(300.0f, 200.0f);			//�I�v�V�����T�C�Y
	const D3DXVECTOR2 NUM_SIZE = D3DXVECTOR2(100.0f, 100.0f);				//�ԍ��̃T�C�Y		

	const int MAX_COLCOUNT = 50;

}
//<===================================
//
//<===================================
COption::COption()
{
	//�l�̃N���A
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}
	m_pNumber = nullptr;
	m_p2DGauge = nullptr;
	m_nSelect = INITIAL_INT;
	m_nOldSelect = INITIAL_INT;
	m_nStamina = INITIAL_INT;
	m_nNumEnemy = INITIAL_INT;
	m_rCol = INIT_COL;
}
//<===================================
//
//<===================================
COption::~COption()
{

}
//<===================================
//
//<===================================
HRESULT COption::Init(void)
{
	//�����擾���Ă���
	m_nStamina = C2DGauge::GetFixed();
	m_nNumEnemy = C3DEnemy::GetNumSet();

	CManager::GetSound()->PlaySound(CSound::LABEL_BGM_OPTION);

	//�e�N�X�`���̏�����
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		//�ŏ������ǂݍ���
		if (m_apTexture[nCnt] == nullptr)
		{
			//�e�N�X�`���̓ǂݍ���
			CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt]);
		}
	}

	//�I�����̐����J��Ԃ�
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		//��������
		m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR2(OPTION_POS.x, OPTION_POS.y + DISTANCE_Y * nCnt), OPTION_SIZE);

		//���g�`�F�b�N
		assert(m_apObject2D[nCnt] != nullptr);

		//�e�N�X�`�����蓖��
		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

	//2D�̃Q�[�W���쐬
	m_p2DGauge = C2DGauge::Create(D3DXVECTOR2(m_apObject2D[SELECT::SELECT_STAMINA]->GetPosition().x + DISTANCE_GAUGE,
		m_apObject2D[SELECT::SELECT_STAMINA]->GetPosition().y), m_nStamina, C2DGauge::VERTEX_X, C2DGauge::MODE_ALWAYS);

	//�ԍ��ݒ�
	m_pNumber = CNumber::Create(D3DXVECTOR2(m_apObject2D[SELECT::SELECT_ENEMYNUM]->GetPosition().x + DISTANCE_NUM,
		m_apObject2D[SELECT::SELECT_ENEMYNUM]->GetPosition().y), NUM_SIZE,m_apTexture[3]);

	//���g�`�F�b�N
	assert(m_p2DGauge != nullptr&&m_pNumber != nullptr);

	//����ݒ肷��
	m_pNumber->SetNum(&m_nNumEnemy);

	return S_OK;
}
//<===================================
//
//<===================================
void COption::Uninit(void)
{
	//�I�����̐����J��Ԃ�
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		//���g�������
		if (m_apObject2D[nCnt] != nullptr)
		{
			//�I������
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
	}
	//���g�������
	if (m_p2DGauge != nullptr)
	{
		//�I������
		m_p2DGauge->Uninit();
		m_p2DGauge = nullptr;
	}
	//���g�������
	if (m_pNumber != nullptr)
	{
		//�I������
		m_pNumber->Uninit();
		m_pNumber = nullptr;
	}
	Release();
}
//<===================================
//
//<===================================
void COption::Update(void)
{
	//�I�����̐����J��Ԃ�
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->SetVtx();
	}

	//�t�F�[�h��Ԃ��������Ă��Ȃ���Ԃ�������
	if (CManager::GetFade()->GetType() == CFade::TYPE_FADE_NONE)
	{
		Select();

		if (m_nSelect == SELECT::SELECT_STAMINA)
		{
			//���L�[��������Ă�����
			if (CManager::GetKeyboard()->bGetPress(DIK_LEFTARROW)
				|| CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_LEFT, 0))
			{
				m_nStamina--;

				if (m_nStamina <= C2DGauge::GetLimitMin())
				{
					m_nStamina = C2DGauge::GetLimitMin();
				}

				m_p2DGauge->SetNum(m_nStamina);
			}

			//�E�L�[��������Ă�����
			else if (CManager::GetKeyboard()->bGetPress(DIK_RIGHTARROW)
				|| CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_RIGHT, 0))
			{
				m_nStamina++;

				if (m_nStamina >= C2DGauge::GetLimitMax())
				{
					m_nStamina = C2DGauge::GetLimitMax();
				}

				m_p2DGauge->SetNum(m_nStamina);
			}
		}
		//EXIT�{�^���ɍs���Ă��Č���{�^����������Ă�����
		else if (m_nSelect == SELECT::SELECT_ENEMYNUM)
		{
			//���L�[��������Ă�����
			if (CManager::GetKeyboard()->bGetTrigger(DIK_LEFTARROW)
				|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_LEFT, 0))
			{
				m_nNumEnemy--;

				if (m_nNumEnemy <= C3DEnemy::GetNumMin())
				{
					m_nNumEnemy = C3DEnemy::GetNumMin();
				}

				m_pNumber->SetNum(&m_nNumEnemy);
			}
			//�E�L�[��������Ă�����
			else if (CManager::GetKeyboard()->bGetTrigger(DIK_RIGHTARROW)
				|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_RIGHT, 0))
			{
				m_nNumEnemy++;

				if (m_nNumEnemy >= C3DEnemy::GetNumMax())
				{
					m_nNumEnemy = C3DEnemy::GetNumMax();
				}

				m_pNumber->SetNum(&m_nNumEnemy);
			}
		}
		//EXIT�{�^���ɍs���Ă��Č���{�^����������Ă�����
		else if (CManager::GetKeyboard()->bGetTrigger(DIK_RETURN) == true
			|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0)&&m_nSelect == SELECT::SELECT_EXIT)
		{
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
			CManager::SetFade(CScene::MODE::MODE_TITLE);
			C2DGauge::SetFixed(m_nStamina);				//�X�^�~�i�ő�l��ݒ�
			C3DEnemy::SetNumSet(m_nNumEnemy);
		}
	}
}
//<===================================
//
//<===================================
void COption::Draw(void)
{
	//�I�����̐����J��Ԃ�
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Draw();
	}
}
//<===================================
//
//<===================================
void COption::Select(void)
{
	//�O��̑I����ۑ�����
	m_nOldSelect = m_nSelect;

	//�F��ς���
	m_rCol = Change::ChangeColInter(m_rCol, 1.0f, 0.3f, 0.025f);

	//���L�[��������Ă�����
	if (CManager::GetKeyboard()->bGetTrigger(DIK_UPARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_UP, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + (SELECT_MAX - 1)) % SELECT_MAX;
		m_rCol.a = 1.0f;
	}
	//�E�L�[��������Ă�����
	else if (CManager::GetKeyboard()->bGetTrigger(DIK_DOWNARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_DOWN, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + 1) % SELECT_MAX;
		m_rCol.a = 1.0f;
	}

	//�J���[��ݒ肷��
	m_apObject2D[m_nOldSelect]->SetColor(INIT_COL);

	m_apObject2D[m_nSelect]->SetColor(m_rCol);

}