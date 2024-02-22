//<==================================
//����(.cpp)
//
//Author:kazuki watanabe
//<==================================
#include "DestArrow2D.h"
#include "manager.h"
#include "Texture.h"
#include "game.h"

LPDIRECT3DTEXTURE9 CDestArrow2D::m_pTexture = nullptr;
const char*	CDestArrow2D::m_cFilename ="data\\TEXTURE\\DestArrow001.png";

int CDestArrow2D::m_nNumAll = INITIAL_INT;

//<=======================================
//
//<=======================================
CDestArrow2D::CDestArrow2D()
{
	//�l�̏�����
	m_rPos = INIT_VECTOR2;		//�ʒu
	m_rSize = INIT_VECTOR2;		//�T�C�Y
	m_rDis = INIT_VECTOR2;		//����
	m_rRot = INIT_VECTOR;		//����
}
//<=======================================
//
//<=======================================
CDestArrow2D::~CDestArrow2D()
{

}
//<=======================================
//
//<=======================================
CDestArrow2D *CDestArrow2D::Create(const D3DXVECTOR2 rPos)
{
	CDestArrow2D *pDestArrow2D = new CDestArrow2D;

	//���g�Ə������`�F�b�N
	assert(pDestArrow2D != nullptr&&pDestArrow2D->Init() == S_OK);

	//�ʒu�̐ݒ�
	pDestArrow2D->SetPosition(rPos);

	//�e�N�X�`���̊��蓖��
	pDestArrow2D->BindTexture(m_pTexture);

	return pDestArrow2D;
}
//<=======================================
//
//<=======================================
HRESULT CDestArrow2D::Init(void) 
{
	//�e�N�X�`���̓ǂݍ���
	if ((CManager::GetTex()->Regist(m_cFilename, m_pTexture)) <= -1)
	{
		return E_FAIL;
	}

	//�T�C�Y�ݒ�
	m_rSize = D3DXVECTOR2(90.0f, 90.0f);
	SetSize(m_rSize);

	CObject2D::Init();

	return S_OK;
}
//<=======================================
//
//<=======================================
void CDestArrow2D::Update(void) 
{
	CObject2D::SetVtx();

	m_rPos = GetPosition();
	m_rRot = GetRotation();

	//�ړI�n�̕����֌���
	m_rRot.z = Calculate::RotateToDest(m_rRot.z, D3DXVECTOR3(m_rDis.x,m_rDis.y,0.0f), 0.1f);

	RotateDest();

	SetPosition(m_rPos);
	SetRotation(m_rRot);

}
//<=======================================
//
//<=======================================
void CDestArrow2D::RotateDest(void)
{
		//�����̐�����
		for (int nCnt = 0; nCnt < CBuilding::GetNum(); nCnt++)
		{
			//���̌�����������
			if (CScene::GetGame()->GetBuil(nCnt)->GetImportance()
				== CBuilding::IMPORTANCE_HIGH)
			{
				//�ړI�n�܂ł̋���
				m_rDis = D3DXVECTOR2(CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().x - CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetPosition().x,
					CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().z - CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetPosition().z);
			}
		}
}