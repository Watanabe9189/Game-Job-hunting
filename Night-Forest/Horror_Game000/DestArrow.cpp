#include "DestArrow.h"
#include "game.h"

LPDIRECT3DTEXTURE9	CDestArrow::m_pTexture = NULL;	//�e�N�X�`�����

																	//<==========================================
																	//�t�@�C�����w��
																	//<==========================================
const char		*CDestArrow::m_pFilename = "data/TEXTURE/DestArrow000.png";		//�G�Q

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
		, D3DXVECTOR3(25.0f, 25.0f, 25.0f), INIT_VECTOR, INIT_COL, CObject3D::TYPE::TYPE_PLANE, m_pTexture);

	return S_OK;
}
//<=============================
//
//<=============================
void CDestArrow::Uninit(void)	
{
	if (m_p3DPlayer != nullptr)
	{
		m_p3DPlayer->Uninit();
		m_p3DPlayer = nullptr;
	}
	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		if (m_apItem[nCnt] != nullptr)
		{
			m_apItem[nCnt]->Uninit();
			m_apItem[nCnt] = nullptr;
		}
	}
	CObject3D::Uninit();
}
//<=============================
//
//<=============================
void CDestArrow::Update(void)	
{
	m_p3DPlayer = CManager::GetScene()->GetGame()->Get3DPlayer();

	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		m_apItem[nCnt] = CManager::GetScene()->GetGame()->GetItem(nCnt);
	}

	CObject3D::SetVtx();

	RotateToDest();

	//���̎擾
	m_rPos = GetPosition();
	m_rSize = GetSize();
	m_rRot = GetRotation();
	
	m_rRotDest = m_rDis;

	//�p�x�ݒ�
	m_fRotDest = atan2f((m_rRotDest.x), (m_rRotDest.z));
	m_fRotDiff = m_fRotDest - m_rRot.y;
	
	m_rPos = D3DXVECTOR3(CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().x,
		CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().y+100.0f,
		CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().z);

	//�ړI�n�̕����Ɍ���
	m_rRot.y += m_fRotDiff * 0.1f;

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
	//�A�C�e���̐����J��Ԃ�
	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		//�������Ă��āA���Ă���A�C�e�����Q�b�g����Ă��Ȃ����
		if (m_bFind == false&&!m_apItem[nCnt]->bGet())
		{
			//�������Ă�����
			if (Collision::CollidAll(m_p3DPlayer->GetPosition(),
				D3DXVECTOR3(MAX_SERACH_RAD, MAX_SERACH_RAD, MAX_SERACH_RAD), m_apItem[nCnt]->GetPosition(),
				m_apItem[nCnt]->GetVtxMax(), m_apItem[nCnt]->GetVtxMin()))
			{
				//�������Ă����Ԃɂ��A���������A�C�e���̔ԍ���ۑ�����
				m_bFind = true;
				m_nNum = nCnt;
				break;
			}
		}
	}
	//�������Ă��āA���Ă���A�C�e�����Q�b�g���ꂽ��
	if (m_bFind == true && m_apItem[m_nNum]->bGet())
	{
		//�������Ă��Ȃ���Ԃɂ���
		m_bFind = false;
	}
	//�������Ă��āA���Ă���A�C�e�����Q�b�g���ꂽ��
	if (m_bFind == true && !m_apItem[m_nNum]->bGet())
	{
		//�ړI�n�܂ł̋���
		m_rDis = D3DXVECTOR3(m_p3DPlayer->GetPosition().x - m_apItem[m_nNum]->GetPosition().x,
			m_p3DPlayer->GetPosition().y - m_apItem[m_nNum]->GetPosition().y,
			m_p3DPlayer->GetPosition().z - m_apItem[m_nNum]->GetPosition().z);
	}
}