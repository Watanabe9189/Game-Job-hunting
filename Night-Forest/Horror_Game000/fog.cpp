//<========================================================
//
//
//
//<========================================================
#include "fog.h"
#include "manager.h"

namespace Fog
{
	const float MAX_START = 0.0f;
	const float MAX_END = 5000.0f;
	const float MAX_DENSITY = 0.002f;
}

//<========================================================
//
//<========================================================
CFog::CFog(int nPriority)
{
	//�l�̏�����
	m_Col = INIT_COL;
	m_Type = TYPE::TYPE_NONE;
	m_dMode = D3DFOG_NONE;
	m_fStart = INITIAL_FLOAT;
	m_fEnd = INITIAL_FLOAT;
	m_fDensity = INITIAL_FLOAT;
	m_bUse = true;

}
//<========================================================
//
//<========================================================
CFog::~CFog()
{

}
//<========================================================
//
//<========================================================
CFog *CFog::Create(const D3DXCOLOR Col, const D3DFOGMODE Mode, const TYPE Type, const float fDensity)
{
	CFog *pFog = new CFog;

	assert(pFog != nullptr);

	assert(SUCCEEDED(pFog->Init()));

	pFog->m_Col = Col;
	pFog->m_dMode = Mode;
	pFog->m_Type = Type;
	pFog->m_fDensity = fDensity;

	return pFog;
}
//<========================================================
//
//<========================================================
HRESULT CFog::Init(void)
{
	//
	m_fStart = Fog::MAX_START;
	m_fEnd = Fog::MAX_END;

	return S_OK;
}
//<========================================================
//
//<========================================================
void CFog::Update(void)
{
	//�g���ꍇ
	if (m_bUse)
	{
		//���_���ꍇ
		if (m_Type == TYPE::TYPE_VERTEX)
		{
			SetupVertexFog(m_Col, m_Type, FALSE);//���_�t�H�O�̐ݒ�
		}
		//�g��Ȃ��ꍇ
		else if (m_Type == TYPE::TYPE_PIXEL)
		{
			SetupPixelFog(m_Type);//�s�N�Z���t�H�O�̐ݒ�
		}
	}
	//�����g��Ȃ��ꍇ
	else
	{
		//���̃u�����h�𖳌��ɂ���
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);
	}
}
//<===========================================
//���_�t�H�O�̐ݒ�
//<===========================================
void CFog::SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange)
{
	//���̃u�����h��L���ɂ���
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//�F��ݒ�
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGCOLOR, Color);
	
	//���̃p�����[�^�[��ݒ�
	//�������`�����[�h��������
	if (Mode == D3DFOG_LINEAR)
	{
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&m_fStart));
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&m_fEnd));
	}
	//���̂ق�
	else
	{
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGDENSITY, *(DWORD *)(&m_fDensity));

		//�����x��0.0f����1.0f�͈̔͂Őݒ肷��
	}

	//���_�t�H�O�����ŃT�|�[�g����Ă���ꍇ�͂��͈̔͂̃t�H�O��L���ɂ���
	//����UseRange��0�ȊO�̏ꍇ�A
	if (UseRange != FALSE)
	{
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);
	}

}
//<===========================================
//�s�N�Z���t�H�O�̐ݒ�
//<===========================================
void CFog::SetupPixelFog(DWORD Mode)
{
	//���̃u�����h��L���ɂ���
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//�F��ݒ�
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGCOLOR, m_Col);

	//�������`�����[�h��������
	if (Mode == D3DFOG_LINEAR)
	{//���`���̃p�����[�^��ݒ肷��

		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGTABLEMODE, Mode);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&m_fStart));
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&m_fEnd));
	}
	//���̂ق�
	else
	{
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGTABLEMODE, Mode);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGDENSITY, *(DWORD *)(&m_fDensity));
	}

}