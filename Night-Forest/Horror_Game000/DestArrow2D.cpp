//<==================================
//処理(.cpp)
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
	//値の初期化
	m_rPos = INIT_VECTOR2;		//位置
	m_rSize = INIT_VECTOR2;		//サイズ
	m_rDis = INIT_VECTOR2;		//距離
	m_rRot = INIT_VECTOR;		//方向
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

	//中身と初期化チェック
	assert(pDestArrow2D != nullptr&&pDestArrow2D->Init() == S_OK);

	//位置の設定
	pDestArrow2D->SetPosition(rPos);

	//テクスチャの割り当て
	pDestArrow2D->BindTexture(m_pTexture);

	return pDestArrow2D;
}
//<=======================================
//
//<=======================================
HRESULT CDestArrow2D::Init(void) 
{
	//テクスチャの読み込み
	if ((CManager::GetTex()->Regist(m_cFilename, m_pTexture)) <= -1)
	{
		return E_FAIL;
	}

	//サイズ設定
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

	//目的地の方向へ向く
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
		//建物の数分回す
		for (int nCnt = 0; nCnt < CBuilding::GetNum(); nCnt++)
		{
			//その建物だったら
			if (CScene::GetGame()->GetBuil(nCnt)->GetImportance()
				== CBuilding::IMPORTANCE_HIGH)
			{
				//目的地までの距離
				m_rDis = D3DXVECTOR2(CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().x - CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetPosition().x,
					CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition().z - CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetPosition().z);
			}
		}
}