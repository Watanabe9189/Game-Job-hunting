//<==============================================
//�t�F�[�h����(fade.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "fade.h"

//<****************************************************
//���O�錾
//<****************************************************
namespace Fade
{
	const float VALUE_ALPHA = 0.07f;									//�����l�ύX�l
	const int MAX_WAIT = 100;											//�ҋ@���Ԃ̍ő�l
	const D3DXCOLOR INIT_FADECOL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);	//�t�F�[�h�̐F�����l
}

//<====================================================
//�R���X�g���N�^
//<====================================================
CFade::CFade()
{
	//�l�̃N���A
	m_pObject2D = nullptr;
	m_nWaitTime = Fade::MAX_WAIT;
	m_Col = Fade::INIT_FADECOL;
	m_ModeNext = CScene::MODE::MODE_TITLE;
	m_eType = TYPE_FADE_NONE;
	m_rPos = D3DXVECTOR2(0.0f, 0.0f);
}
//<====================================================
//
//<====================================================
CFade::~CFade()
{

}
//<====================================================
//��������
//<====================================================
CFade *CFade::Create(void)
{
	//�����p�̃I�u�W�F�N�g
	CFade *pFade = new CFade;

	//�����`�F�b�N
	assert(pFade != nullptr);

	//�������`�F�b�N
	assert(SUCCEEDED(pFade->Init()));

	return pFade;
}
//<====================================================
//����������
//<====================================================
HRESULT CFade::Init(void)
{
	//���g���Ȃ����
	if (m_pObject2D == nullptr)
	{
		//��������
		m_pObject2D = new CObject2D;
	}

	m_pObject2D->Init();

	return S_OK;
}
//<====================================================
//�X�V����
//<====================================================
void CFade::Update(void)
{
	SetVtx();

	if (m_eType != TYPE_FADE_NONE)
	{
		if (m_eType == TYPE_FADE_OUT)
		{
			SetFadeOut();
		}

		if (m_eType == TYPE_FADE_IN)
		{
			if (m_nWaitTime > 0)
			{
				m_nWaitTime--;
			}

			SetFadeIn();
		}
	}
}
//<====================================================
//���_���ݒ菈��
//<====================================================
void CFade::SetVtx(void)
{
	m_pObject2D->SetVtx();

	VERTEX_2D *pVtx;

	m_pObject2D->GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//�F�̐ݒ�
	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pObject2D->GetVtxBuff()->Unlock();
}
//<====================================================
//�t�F�[�h�A�E�g����
//<====================================================
void CFade::SetFadeOut(void)
{
	//�F�����Z���Ă���
	m_Col.a += Fade::VALUE_ALPHA;

	//�����x��
	if (m_Col.a >= 1.0f)
	{
		m_Col.a = 1.0f;

		m_eType = TYPE_FADE_IN;
	}

}
//<====================================================
//�t�F�[�h�C������
//<====================================================
void CFade::SetFadeIn(void)
{
	//�ҋ@���Ԃ��Ȃ��Ȃ��Ă�����
	if (m_nWaitTime <= 0)
	{
		//�����x����������
		if (m_Col.a == 1.0f)
		{
			//���[�h��ݒ肷��
			CManager::SetMode(m_ModeNext);
		}

		//�F�����炵�Ă���
		m_Col.a -= Fade::VALUE_ALPHA;

		//�����ł͂Ȃ����
		if (m_Col.a <= 0.0f)
		{
			//���̒l�ɂ���
			m_Col.a = 0.0f;

			m_eType = TYPE_FADE_NONE;

			m_pObject2D->SetDrawfalse();
		}
	}
}
//<====================================================
//�t�F�[�h�̐ݒ�
//<====================================================
void CFade::SetFade(CScene::MODE modeNext)
{
	//�t�F�[�h�����Ȃ���Ԃ�������
	if (m_eType == TYPE_FADE_NONE)
	{
		//��ʑS�̂𕢂�
		m_pObject2D->SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));

		m_nWaitTime = Fade::MAX_WAIT;	//�ҋ@���Ԃ��ő�l�ɂ���
		m_ModeNext = modeNext;			//���̃��[�h��ݒ肷��
		m_eType = TYPE_FADE_OUT;		//�t�F�[�h�A�E�g��Ԃɂ���

		m_pObject2D->SetDrawtrue();
	}
}