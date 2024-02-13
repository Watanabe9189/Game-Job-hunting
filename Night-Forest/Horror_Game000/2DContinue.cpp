//<==================================================
//2D�ł̃R���e�B�j���[�\���ɓ�����������(2DContinue.cpp)
//
//Author:kazuki watanabe
//<==================================================
#include "2DContinue.h"
#include "manager.h"

//<*************************************************************************
//
//<*************************************************************************
LPDIRECT3DTEXTURE9	C2DContinue::m_apTexture[TYPE::TYPE_MAX] = {};
const char*			C2DContinue::m_acFilename[TYPE::TYPE_MAX] =
{
	NULL,
	"data\\TEXTURE\\GameOver001.png",
	"data\\TEXTURE\\GameOver-Yes.png",
	"data\\TEXTURE\\GameOver-No.png",
};
//<*************************************************************************
//���O�錾
//<*************************************************************************
namespace
{
	const float			DISTANCE_VALUE	= 250.0f;								//�����̒l
	const D3DXCOLOR		FRAME_COL		= D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.6f);	//�t���[���̐F
	const D3DXVECTOR2	FRAME_POS		= D3DXVECTOR2(625.0f, 375.0f);			//�t���[���̈ʒu
	const D3DXVECTOR2	FRAME_SIZE		= D3DXVECTOR2(300.0f, 300.0f);			//�t���[���̃T�C�Y
	const D3DXVECTOR2	CONTINUE_POS	= D3DXVECTOR2(625.0f, 175.0f);			//�R���e�B�j���[�����̈ʒu
	const D3DXVECTOR2	CONTINUE_SIZE	= D3DXVECTOR2(300.0f, 200.0f);			//�R���e�B�j���[�����̃T�C�Y
	const D3DXVECTOR2	YESNO_POS		= D3DXVECTOR2(500.0f, 500.0f);			//YESNO�����̈ʒu
	const D3DXVECTOR2	YESNO_SIZE		= D3DXVECTOR2(150.0f, 150.0f);			//YESNO�����̃T�C�Y
}
//<======================================================================
//
//<======================================================================
C2DContinue::C2DContinue(int nPriority)
{
	//������
	for (int nCnt = 0; nCnt < TYPE::TYPE_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = {};
	}

	//������
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_apSelect[nCnt] = {};
	}
	m_nNumSelect = INITIAL_INT;
	m_nSelect = INITIAL_INT;
	m_nOldSelect = INITIAL_INT;

	m_rPos = D3DXVECTOR2(0.0f, 0.0f);
	m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	m_rCol = INIT_COL;
	m_bUpdate = false;
}
//<======================================================================
//
//<======================================================================
C2DContinue::~C2DContinue()
{

}
//<======================================================================
//
//<======================================================================
C2DContinue *C2DContinue::Create(void)
{
	C2DContinue *p2DSelect = new C2DContinue;

	assert(p2DSelect != nullptr);

	p2DSelect->Init();

	return p2DSelect;
}
//<======================================================================
//
//<======================================================================
HRESULT C2DContinue::Init(void)
{
	//�e�N�X�`���̏�����
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		//�ŏ������ǂݍ���
		if (m_apTexture[nCnt] == nullptr)
		{
			//�e�N�X�`���̓ǂݍ���
			if (CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt]) <= -1)
			{
				return E_FAIL;
			}
		}
	}

	m_rPos = FRAME_POS;

	//�Z���N�g�̐����J��Ԃ�
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		//
		if (nCnt == TYPE::TYPE_FRAME)
		{
			m_rCol = FRAME_COL;
			m_rSize = FRAME_SIZE;
		}
		else if (nCnt != TYPE::TYPE_FRAME)
		{
			m_rPos = CONTINUE_POS;
			m_rCol = INIT_COL;
			m_rSize = CONTINUE_SIZE;
		}

		//��������
		m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR2(m_rPos.x, m_rPos.y), m_rSize, m_rCol,m_apTexture[nCnt]);

		assert(m_apObject2D[nCnt] != nullptr);
	}
	//�Z���N�g�̐����J��Ԃ�
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_rSize = YESNO_SIZE;
		m_rPos = YESNO_POS;

		//��������
		m_apSelect[nCnt] = CObject2D::Create(D3DXVECTOR2(m_rPos.x + DISTANCE_VALUE *nCnt, m_rPos.y), m_rSize, m_rCol, m_apTexture[nCnt+2]);

		assert(m_apSelect[nCnt] != nullptr);
	}
	return S_OK;
}
//<======================================================================
//
//<======================================================================
void C2DContinue::Uninit(void)
{
	//�Z���N�g�̐����J��Ԃ�
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		//
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
		//
		if (m_apSelect[nCnt] != nullptr)
		{
			m_apSelect[nCnt]->Uninit();
			m_apSelect[nCnt] = nullptr;
		}
	}
	Release();
}
//<======================================================================
//
//<======================================================================
void C2DContinue::Update(void)
{
	if (m_bUpdate)
	{
		//�Z���N�g�X�V
		SelectUpdate();

		//�Z���N�g�̐����J��Ԃ�
		for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
		{
			if (m_apSelect[nCnt] != nullptr)
			{
				m_apSelect[nCnt]->SetVtx();

				//���̎擾
				m_rPos = m_apSelect[nCnt]->GetPosition();
				m_rSize = m_apSelect[nCnt]->GetSize();

				//�ݒ�
				m_apSelect[nCnt]->SetPosition(m_rPos);
				m_apSelect[nCnt]->SetSize(m_rSize);

			}
		}

		//�Z���N�g�̐����J��Ԃ�
		for (int nCnt = 0; nCnt < TYPE::TYPE_MAX; nCnt++)
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
}
//<======================================================================
//
//<======================================================================
void C2DContinue::Draw(void)
{

}
//<======================================================================
//
//<======================================================================
void C2DContinue::SelectUpdate(void)
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
		m_nSelect = (m_nSelect + (SELECT::SELECT_MAX - 1)) % SELECT::SELECT_MAX;
		m_rCol.a = 1.0f;
	}
	//�E�L�[��������Ă�����
	else if (CManager::GetKeyboard()->bGetTrigger(DIK_RIGHTARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_RIGHT, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + 1) % SELECT::SELECT_MAX;
		m_rCol.a = 1.0f;
	}

	//�J���[��ݒ肷��
	m_apSelect[m_nOldSelect]->SetColor(INIT_COL);
	m_apSelect[m_nSelect]->SetColor(m_rCol);
}