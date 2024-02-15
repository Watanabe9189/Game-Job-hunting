#include "DestArrowX.h"
#include "game.h"

namespace
{
	const float MAX_SERACH_RAD = 1000.0f;		//�{���͈͂̍ő�l
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
}
//<=============================
//
//<=============================
void CDestArrowX::Update(void)
{
	m_p3DPlayer = CManager::GetScene()->GetGame()->Get3DPlayer();

	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		m_apItem[nCnt] = CManager::GetScene()->GetGame()->GetItem(nCnt);
	}

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
		//�������Ă��āA���Ă���A�C�e�����Q�b�g����Ă��Ȃ����
		if (m_bFind == false && !m_apItem[nCnt]->bGet())
		{
			//�������Ă�����
			if (Collision::CollidAll(m_p3DPlayer->GetPosition(),
				D3DXVECTOR3(MAX_SERACH_RAD, MAX_SERACH_RAD, MAX_SERACH_RAD), m_apItem[nCnt]->GetPosition(),
				m_apItem[nCnt]->GetModel().vtxMax, m_apItem[nCnt]->GetModel().vtxMin))
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