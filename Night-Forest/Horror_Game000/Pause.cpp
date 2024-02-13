#include "Pause.h"

namespace
{
	const D3DXVECTOR2 SIZE_PAUSE = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	const D3DXVECTOR2 POS_SELECT = D3DXVECTOR2(625.0f, 125.0f);
	const D3DXVECTOR2 SIZE_SELECT = D3DXVECTOR2(300.0f, 150.0f);
	const float DISTANCE_Y = 200.0f;
}

LPDIRECT3DTEXTURE9	CPause::m_apTexture[INT_VALUE::MAX_TEX] = {};		//�e�N�X�`���ւ̃|�C���^
const char*			CPause::m_acFilename[]
{
	NULL,
	NULL,
	"data\\TEXTURE\\Pause\\Pause001.png",
	"data\\TEXTURE\\Pause\\Pause002.png",
	"data\\TEXTURE\\Pause\\Pause003.png",
};				//�t�@�C����

//<==========================================
//
//<==========================================
CPause::CPause()
{
	//�l�̃N���A
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_apSelct[nCnt] = nullptr;
	}
	m_rSizeSelect = D3DXVECTOR2(0.0f, 0.0f);
	m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	m_rCOl = INIT_COL;

	m_nSelect = SELECT::SELECT_RESUME;
	m_nOldSelect = SELECT::SELECT_RESUME;
}
//<==========================================
//
//<==========================================
CPause::~CPause()
{

}
//<==========================================
//
//<==========================================
void CPause::Init(void)
{
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
	//�l�̃N���A
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR2(0.0f, 0.0f), SIZE_PAUSE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f), m_apTexture[nCnt]);

		assert(m_apObject2D[nCnt] != nullptr);
	}
	//�l�̃N���A
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_apSelct[nCnt] = CObject2D::Create(D3DXVECTOR2(POS_SELECT.x, POS_SELECT.y + DISTANCE_Y * nCnt), SIZE_SELECT, m_rCOl, m_apTexture[nCnt+2]);

		assert(m_apSelct[nCnt] != nullptr);
	}
}
//<==========================================
//
//<==========================================
void CPause::Uninit(void)
{
	
}
//<==========================================
//
//<==========================================
void CPause::Update(void)
{
	//�l�̃N���A
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->SetVtx();

			//�|�[�Y����Ă�����
			if (CManager::GetPause() == true)
			{
				//�T�C�Y���擾���Ă���
				m_rSize = SIZE_PAUSE;
			}
			//����Ă��Ȃ����
			else
			{
				//�T�C�Y�ŕ\�������Ȃ�����
				m_rSize = D3DXVECTOR2(0.0f, 0.0f);
				m_nSelect = SELECT::SELECT_RESUME;
			}

			m_apObject2D[nCnt]->SetSize(m_rSize);
		}
	}
	//�l�̃N���A
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		if (m_apSelct[nCnt] != nullptr)
		{
			m_apSelct[nCnt]->SetVtx();

			//�|�[�Y����Ă�����
			if (CManager::GetPause() == true)
			{
				//�T�C�Y���擾���Ă���
				m_rSizeSelect = SIZE_SELECT;
			}
			//����Ă��Ȃ����
			else
			{
				//�T�C�Y�ŕ\�������Ȃ�����
				m_rSizeSelect = D3DXVECTOR2(0.0f, 0.0f);
				m_nSelect = SELECT::SELECT_RESUME;
				m_rCOl = INIT_COL;
			}

			m_apSelct[nCnt]->SetColor(m_rCOl);
			m_apSelct[nCnt]->SetSize(m_rSizeSelect);
		}
	}
	Select();
}
//<====================================
//
//<====================================
void CPause::Select(void)
{
	//�O��̑I����ۑ�����
	m_nOldSelect = m_nSelect;

	//���L�[��������Ă�����
	if (CManager::GetKeyboard()->bGetTrigger(DIK_UPARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_UP, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}
	//�E�L�[��������Ă�����
	else if (CManager::GetKeyboard()->bGetTrigger(DIK_DOWN)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_DOWN, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + 1) % SELECT_MAX;
	}

	//�J���[��ݒ肷��
	m_apSelct[m_nOldSelect]->SetColor(INIT_COL);

	//�J���[�𓧖��ɂ���
	m_apSelct[m_nSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
}