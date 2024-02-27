#include "DestArrowX.h"
#include "game.h"

namespace
{
	const float MAX_SERACH_RAD = 750.0f;		//�{���͈͂̍ő�l
}
//<=============================
//
//<=============================
CDestArrowX::CDestArrowX(int nPriority)
{
	//�l�̃N���A
	m_rPos = INIT_VECTOR;
	m_rRot = INIT_VECTOR;
	m_rDis = INIT_VECTOR;

	m_rRotDest = INIT_VECTOR;

	m_fRotDest = INITIAL_FLOAT;
	m_fRotDiff = INITIAL_FLOAT;

	m_bFind = false;

	m_nNum = INITIAL_INT;
}
//<=============================
//
//<=============================
CDestArrowX::~CDestArrowX()
{

}
//<=============================
//
//<=============================
CDestArrowX *CDestArrowX::Create(void)
{
	CDestArrowX *pDestArrow = new CDestArrowX;

	assert(pDestArrow != nullptr&&pDestArrow->Init() == S_OK);

	return pDestArrow;
}
//<=============================
//
//<=============================
HRESULT CDestArrowX::Init(void)
{
	CXObject::Init();

	m_sModel = BindModel("data\\MODEL\\DestArrow000.x");

	return S_OK;
}
//<=============================
//
//<=============================
void CDestArrowX::Uninit(void)
{
	CXObject::Uninit();
}
//<=============================
//
//<=============================
void CDestArrowX::Update(void)
{
	RotateToDest();

	//���̎擾
	m_rPos = GetPosition();
	m_rRot = GetRotation();

	m_rRotDest = m_rDis;

	//�p�x�ݒ�
	m_fRotDest = atan2f((m_rRotDest.x), (m_rRotDest.z));
	m_fRotDiff = m_fRotDest - m_rRot.y;

	m_rPos = D3DXVECTOR3(CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().x,
		CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().y + 110.0f,
		CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().z);

	//�ړI�n�̕����Ɍ���
	m_rRot.y += m_fRotDiff * 0.1f;

	//���̐ݒ�
	SetPosition(m_rPos);
	SetRotation(m_rRot);
}
//<========================================
//�ړI�n
//<========================================
void CDestArrowX::RotateToDest(void)
{
	//�A�C�e���̐����J��Ԃ�
	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		if (!CManager::GetScene()->GetGame()->GetItem(nCnt)->bGetSealed())
		{
			//�������Ă�����
			if (Collision::CollidAll(CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition(),
				D3DXVECTOR3(MAX_SERACH_RAD, MAX_SERACH_RAD, MAX_SERACH_RAD), CManager::GetScene()->GetGame()->GetItem(nCnt)->GetPosition(),
				CManager::GetScene()->GetGame()->GetItem(nCnt)->GetModel().vtxMax, CManager::GetScene()->GetGame()->GetItem(nCnt)->GetModel().vtxMin))
			{
				//�������Ă����Ԃɂ��A���������A�C�e���̔ԍ���ۑ�����
				m_bFind = true;
				m_nNum = nCnt;
				break;
			}
			//�͈͓��ɓ����Ă��Ȃ����
			else
			{
				m_bFind = false;
			}
		}
	}
	//�������Ă��āA���Ă���A�C�e�����Q�b�g���ꂽ��
	if (m_bFind == true && CManager::GetScene()->GetGame()->GetItem(m_nNum)->bGet())
	{
		//�������Ă��Ȃ���Ԃɂ���
		m_bFind = false;
	}
	//�������Ă��āA���Ă���A�C�e�����Q�b�g���ꂽ��
	if (m_bFind == true && !CManager::GetScene()->GetGame()->GetItem(m_nNum)->bGet())
	{
		//�ړI�n�܂ł̋���
		m_rDis = D3DXVECTOR3(CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().x - CManager::GetScene()->GetGame()->GetItem(m_nNum)->GetPosition().x,
			CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().y - CManager::GetScene()->GetGame()->GetItem(m_nNum)->GetPosition().y,
			CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().z - CManager::GetScene()->GetGame()->GetItem(m_nNum)->GetPosition().z);
	}
}