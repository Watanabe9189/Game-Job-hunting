//<===================================
//�ԍ��֘A�̏���(Number.cpp)
//
//Author:kazuki watanabe
//<===================================
#include "Number.h"
#include "object2D.h"
#include "manager.h"
#include "Texture.h"

//<=====================================
//�ԍ��̃R���X�g���N�^
//<=====================================
CNumber::CNumber(int nPriority)
{
	//�l�̃N���A
	m_nNum = INITIAL_INT;
	m_pObject2D = nullptr;
}
//<=====================================
//�ԍ��̃f�X�g���N�^
//<=====================================
CNumber::~CNumber()
{

}
//<=====================================
//�ԍ��̐�������
//<=====================================
CNumber *CNumber::Create(const D3DXVECTOR2 rPos, const D3DXVECTOR2 rSize, const LPDIRECT3DTEXTURE9 pTexture)
{
	CNumber *pNumber = new CNumber;

	assert(pNumber != nullptr);

	//����������
	pNumber->Init(rPos, rSize, pTexture);

	return pNumber;
}
//<=====================================
//�ԍ��̏���������
//<=====================================
HRESULT CNumber::Init(const D3DXVECTOR2 rPos, const D3DXVECTOR2 rSize, const LPDIRECT3DTEXTURE9 pTexture)
{
	m_pObject2D = CObject2D::Create(rPos, rSize);

	assert(m_pObject2D != nullptr);

	m_pObject2D->BindTexture(pTexture);

	return S_OK;
}
//<=====================================
//�ԍ��̏I������
//<=====================================
void CNumber::Uninit(void)
{
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Uninit();
		m_pObject2D = nullptr;
	}
}
//<=====================================
//�ԍ��̍X�V����
//<=====================================
void CNumber::Update(void)
{
	//�����擾
	m_nNum = GetNum();

	//���_���W�ݒ�
	SetVtx();

	//����ݒ�
	SetNum(&m_nNum);
}
//<=====================================
//�ԍ��̒��_���ݒ�
//<=====================================
void CNumber::SetVtx(void)
{
	//���g�������
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->SetVtx();

		VERTEX_2D *pVtx;

		m_pObject2D->GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < m_nNum; nCnt++)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(m_nNum*0.1f + 0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(m_nNum*0.1f + 0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(m_nNum*0.1f + 0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(m_nNum*0.1f + 0.1f, 1.0f);

		}

		m_pObject2D->GetVtxBuff()->Unlock();
	}
}