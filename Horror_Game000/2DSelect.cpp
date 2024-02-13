//<======================================================================
//
//
//
//<======================================================================
#include "2DSelect.h"
#include "manager.h"

//<======================================================================
//
//<======================================================================
C2DSelect::C2DSelect(int nPriority)
{
	//�l�̃N���A
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_TEX; nCnt++)
	{
		m_acFilename[nCnt] = {};
		m_apTexture[nCnt] = {};
	}

	//������
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_SIZE; nCnt++)
	{
		m_apObject2D[nCnt] = {};
	}

	m_nNumSelect = INITIAL_INT;
	m_nSelect = INITIAL_INT;
	m_nOldSelect = INITIAL_INT;

	m_fDistance = 350.0f;

	m_rPos = D3DXVECTOR2(0.0f,0.0f);
	m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	m_rCol = INIT_COL;
}
//<======================================================================
//
//<======================================================================
C2DSelect::~C2DSelect()
{

}
//<======================================================================
//
//<======================================================================
C2DSelect *C2DSelect::Create(const D3DXVECTOR2 rPos,const int nNumSelect)
{
	C2DSelect *p2DSelect = new C2DSelect;

	assert(p2DSelect != nullptr);

	//�l�̑��
	p2DSelect->m_rPos = rPos;
	p2DSelect->m_nNumSelect = nNumSelect;

	p2DSelect->Init();

	return p2DSelect;
}
//<======================================================================
//
//<======================================================================
HRESULT C2DSelect::Init(void)
{
	//�Z���N�g�̐����J��Ԃ�
	for (int nCnt = 0; nCnt < m_nNumSelect; nCnt++)
	{
		//��������
		m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR2(m_rPos.x +m_fDistance *nCnt,m_rPos.y), D3DXVECTOR2(150.0f, 150.0f), m_rCol);

		assert(m_apObject2D[nCnt] != nullptr);
	}

	return S_OK;
}
//<======================================================================
//
//<======================================================================
void C2DSelect::Uninit(void)
{
	//�Z���N�g�̐����J��Ԃ�
	for (int nCnt = 0; nCnt < m_nNumSelect; nCnt++)
	{
		//
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
	}
	Release();
}
//<======================================================================
//
//<======================================================================
void C2DSelect::Update(void)
{
	//�Z���N�g�X�V
	SelectUpdate();

	//�Z���N�g�̐����J��Ԃ�
	for (int nCnt = 0; nCnt < m_nNumSelect; nCnt++)
	{
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->SetVtx();

			//���̎擾
			m_rPos = m_apObject2D[nCnt]->GetPosition();
			m_rSize = m_apObject2D[nCnt]->GetSize();

			//�ݒ�
			m_apObject2D[nCnt]->SetPosition(m_rPos);
			m_apObject2D[nCnt]->SetSize(m_rSize);

		}

	}
}
//<======================================================================
//
//<======================================================================
void C2DSelect::Draw(void) 
{
	
}
//<======================================================================
//
//<======================================================================
void C2DSelect::SelectUpdate(void)
{
	//�O��̑I����ۑ�����
	m_nOldSelect = m_nSelect;

	//�F��ς���
	m_rCol = Change::ChangeColInter(m_rCol, 1.0f, 0.3f, 0.025f);

	//���L�[��������Ă�����
	if (CManager::GetKeyboard()->bGetTrigger(DIK_LEFTARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_LEFT, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + (m_nNumSelect - 1)) % m_nNumSelect;
		m_rCol.a = 1.0f;
	}
	//�E�L�[��������Ă�����
	else if (CManager::GetKeyboard()->bGetTrigger(DIK_RIGHTARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_RIGHT, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + 1) % m_nNumSelect;
		m_rCol.a = 1.0f;
	}

	//�J���[��ݒ肷��
	m_apObject2D[m_nOldSelect]->SetColor(INIT_COL);
	m_apObject2D[m_nSelect]->SetColor(m_rCol);
}
//<=============================================
//
//<=============================================
void C2DSelect::SetTexName(const char *pFileName, int nCnt)
{
	//�t�@�C�����̑��
	m_acFilename[nCnt] = pFileName;

	//�e�N�X�`���̓ǂݍ���
	CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt]);

	//���g�������
	if (m_apObject2D[nCnt] != nullptr)
	{
		//�e�N�X�`���̊��蓖��
		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

}