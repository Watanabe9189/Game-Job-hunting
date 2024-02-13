//<======================================================
//�X�e���V������(Stencil.cpp)
//
//Author:kazuki watanabe
//<======================================================
#include "Stencil.h"
#include "manager.h"

//<=======================================
//�X�e���V���̃R���X�g���N�^
//<=======================================
CStencil::CStencil()
{
	m_bUse = false;
	m_nStencil = INITIAL_INT;
}
//<=======================================
//�X�e���V���̃f�X�g���N�^
//<=======================================
CStencil::~CStencil()
{

}
//<=======================================
//�X�e���V���̐�������
//<=======================================
CStencil *CStencil::Create(const bool bUse, const int nStencil)
{
	CStencil *pStencil = new CStencil;

	assert(pStencil != nullptr);

	//�l�ݒ�
	pStencil->m_bUse = bUse;
	pStencil->m_nStencil = nStencil;

	pStencil->Init();

	return pStencil;
}
//<=======================================
//�X�e���V���̏���������
//<=======================================
void CStencil::Init()
{
	//�X�e���V�����g���Ȃ�
	if (m_bUse)
	{
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
	}
	//�g��Ȃ��Ȃ�
	else
	{
		//�X�e���V�����g�p����Z�e�X�g��L���ɂ���
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILENABLE, FALSE);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	}
}
//<=======================================
//�X�e���V���̏I������
//<=======================================
void CStencil::Uninit(void)
{
	//�X�e���V�����g�p����Z�e�X�g��L���ɂ���
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}
//<=======================================
//�X�e���V���̏I������
//<=======================================
void CStencil::Setting(const bool bUse, const int nStencil)
{
	m_bUse = bUse;

	//�X�e���V�����g���Ȃ�
	if (m_bUse)
	{
		m_nStencil = nStencil;
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
	}
	//�g��Ȃ��Ȃ�
	else
	{
		m_nStencil = 0;
		//�X�e���V�����g�p����Z�e�X�g��L���ɂ���
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILENABLE, FALSE);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	}
}
//<=======================================
//�X�e���V���̕`�揈��
//<=======================================
void CStencil::DrawStencilTest(void)
{
	//�X�e���V�����g���Ȃ�
	if (m_bUse)
	{
		//�[�x�e�X�g�ݒ�
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

		//�X�e���V���Q�ƒl�̐ݒ�
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILREF, m_nStencil);

		//�X�e���V���}�X�N�̐ݒ�
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

		//��������l���傫��������
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATER);

		//�X�e���V���e�X�g�Ɏ��s������u������������
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_REPLACE);		

		//�X�e���V���e�X�g�ɐ������AZ�e�X�g�Ɏ��s���Ă�����C���N�������g������
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT);	

		//�����ɐ������Ă�����C���N�������g����
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);	

		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));
	}
}
//<*************************************************************************************************************
//D3DSTENCILOP�̓��e
//1:D3DSTENCILOP_KEEP		=	�������Ȃ�
//2:D3DSTENCILOP_ZERO		=	0�ɂ���
//3:D3DSTENCILOP_REPLACE	=	��l�Œu������
//4:D3DSTENCILOP_INCRSAT	= + 1����i�ő�l�ł͂��̂܂܁j
//5:D3DSTENCILOP_DECRSAT	= - 1����i�ŏ��l�ł͂��̂܂܁j
//6:D3DSTENCILOP_INVERT	=	�r�b�g���]
//7:D3DSTENCILOP_INCR		= + 1����i�ő�l�ł�0�ɖ߂��j
//8:D3DSTENCILOP_DECR		= - 1����i�ŏ��l�ł͍ő�l�ɖ߂��j
//<*************************************************************************************************************