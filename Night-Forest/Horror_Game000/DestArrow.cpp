#include "DestArrow.h"
#include "game.h"

LPDIRECT3DTEXTURE9	CDestArrow::m_pTexture = NULL;	//�e�N�X�`�����

																	//<==========================================
																	//�t�@�C�����w��
																	//<==========================================
const char		*CDestArrow::m_pFilename = "data/TEXTURE/DestArrow001.png";		//�G�Q

namespace
{
	const float MAX_SERACH_RAD = 1000.0f;		//�{���͈͂̍ő�l
}
//<=============================
//
//<=============================
CDestArrow::CDestArrow(int nPriority)
{
	//�l�̃N���A
	m_rPos = INIT_VECTOR;
	m_rRot = INIT_VECTOR;
	m_rSize = INIT_VECTOR;
	m_rDis = INIT_VECTOR;

	m_rRotDest = INIT_VECTOR;

	m_fRotDest = INITIAL_FLOAT;
	m_fRotDiff = INITIAL_FLOAT;

	m_bFind = false;

	//������
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_SIZE; nCnt++)
	{
		m_apItem[nCnt] = nullptr;
	}

	m_p3DPlayer = nullptr;
	m_nNum = INITIAL_INT;
}
//<=============================
//
//<=============================
CDestArrow::~CDestArrow()
{

}
//<=============================
//
//<=============================
CDestArrow *CDestArrow::Create(void)
{
	CDestArrow *pDestArrow = new CDestArrow;

	assert(pDestArrow != nullptr&&pDestArrow->Init() == S_OK);

	return pDestArrow;
}
//<=============================
//
//<=============================
HRESULT CDestArrow::Init(void)	
{
	//�e�N�X�`���̓ǂݍ���
	if ((CManager::GetTex()->Regist(m_pFilename, m_pTexture)) <= -1)
	{
		return E_FAIL;
	}

	//��������̏�����������
	CObject3D::InitWith(D3DXVECTOR3(CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().x,
		CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().y,
		CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().z)
		, D3DXVECTOR3(25.0f, 40.0f, 25.0f), INIT_VECTOR, INIT_COL, CObject3D::TYPE::TYPE_PLANE, m_pTexture);

	return S_OK;
}
//<=============================
//
//<=============================
void CDestArrow::Uninit(void)	
{
	CObject3D::Uninit();
}
//<=============================
//
//<=============================
void CDestArrow::Update(void)	
{
	CObject3D::SetVtx();

	//���̎擾
	m_rPos = GetPosition();
	m_rSize = GetSize();
	m_rRot = GetRotation();
	
	m_rPos = D3DXVECTOR3(CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().x,
		CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().y+125.0f,
		CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().z);

	RotateToDest();

	//�ړI�n�̕����֌���
	m_rRot.y = Calculate::RotateToDest(m_rRot.y, m_rDis, 0.1f);

	//���̐ݒ�
	SetPosition(m_rPos);
	SetRotation(m_rRot);
	
	SetSize(m_rSize);
	
}
//<========================================
//�ړI�n
//<========================================
void CDestArrow::RotateToDest(void)
{
	if (CItem::bGetFlag())
	{
		//�����̐�����
		for (int nCnt = 0; nCnt < CBuilding::GetNum(); nCnt++)
		{
			//���̌�����������
			if (CScene::GetGame()->GetBuil(nCnt)->GetImportance()
				== CBuilding::IMPORTANCE_HIGH)
			{
				//�ړI�n�܂ł̋���
				m_rDis = D3DXVECTOR3(CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().x - CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetPosition().x,
					CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().y - CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetPosition().y,
					CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().z - CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetPosition().z);
			}
		}
	}
}