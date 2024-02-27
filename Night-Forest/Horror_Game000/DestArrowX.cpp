#include "DestArrowX.h"
#include "game.h"

namespace
{
	const float MAX_SERACH_RAD = 750.0f;		//捜索範囲の最大値
}
//<=============================
//
//<=============================
CDestArrowX::CDestArrowX(int nPriority)
{
	//値のクリア
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

	//情報の取得
	m_rPos = GetPosition();
	m_rRot = GetRotation();

	m_rRotDest = m_rDis;

	//角度設定
	m_fRotDest = atan2f((m_rRotDest.x), (m_rRotDest.z));
	m_fRotDiff = m_fRotDest - m_rRot.y;

	m_rPos = D3DXVECTOR3(CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().x,
		CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().y + 110.0f,
		CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().z);

	//目的地の方向に向く
	m_rRot.y += m_fRotDiff * 0.1f;

	//情報の設定
	SetPosition(m_rPos);
	SetRotation(m_rRot);
}
//<========================================
//目的地
//<========================================
void CDestArrowX::RotateToDest(void)
{
	//アイテムの数分繰り返す
	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		if (!CManager::GetScene()->GetGame()->GetItem(nCnt)->bGetSealed())
		{
			//当たっていたら
			if (Collision::CollidAll(CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition(),
				D3DXVECTOR3(MAX_SERACH_RAD, MAX_SERACH_RAD, MAX_SERACH_RAD), CManager::GetScene()->GetGame()->GetItem(nCnt)->GetPosition(),
				CManager::GetScene()->GetGame()->GetItem(nCnt)->GetModel().vtxMax, CManager::GetScene()->GetGame()->GetItem(nCnt)->GetModel().vtxMin))
			{
				//見つかっている状態にし、見つかったアイテムの番号を保存する
				m_bFind = true;
				m_nNum = nCnt;
				break;
			}
			//範囲内に入っていなければ
			else
			{
				m_bFind = false;
			}
		}
	}
	//見つかっていて、見ているアイテムがゲットされたら
	if (m_bFind == true && CManager::GetScene()->GetGame()->GetItem(m_nNum)->bGet())
	{
		//見つかっていない状態にする
		m_bFind = false;
	}
	//見つかっていて、見ているアイテムがゲットされたら
	if (m_bFind == true && !CManager::GetScene()->GetGame()->GetItem(m_nNum)->bGet())
	{
		//目的地までの距離
		m_rDis = D3DXVECTOR3(CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().x - CManager::GetScene()->GetGame()->GetItem(m_nNum)->GetPosition().x,
			CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().y - CManager::GetScene()->GetGame()->GetItem(m_nNum)->GetPosition().y,
			CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().z - CManager::GetScene()->GetGame()->GetItem(m_nNum)->GetPosition().z);
	}
}