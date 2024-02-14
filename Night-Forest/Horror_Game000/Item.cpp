#include "Item.h"
#include "game.h"
#include "3DParticle.h"
//<*******************************************
//静的メンバ変数の宣言
//<*******************************************
//テクスチャ関連
//<==========================================
//ファイル名指定
//<==========================================
const char		*CItem::m_acFilename[TYPE::TYPE_MAX] =
{
	"data/MODEL/Item000-V2.x",		//アイテム１
	"data/MODEL/Item000-V2.x",		//アイテム２
	"data/MODEL/Item000-V2.x",		//アイテム３
	"data/MODEL/Item000-V2.x",		//アイテム４
	"data/MODEL/Item000-V2.x",		//アイテム５
};
//<==========================================
//Int型
//<==========================================
int CItem::m_nNumAll = NULL;									//数
int CItem::m_NumCollect = NULL;									//数
int CItem::m_MaxNum = NULL;										//最大の数
int CItem::m_nLeft = NULL;

//<==========================================================
//
//<==========================================================
CItem::CItem(int nPriority)
{
	//最大値
	m_nNumAll++;
	m_MaxNum = m_nNumAll;

	//値のクリア
	m_pos = INIT_VECTOR;
	m_rot = INIT_VECTOR;

	m_eType = TYPE::TYPE_MAX;

	m_bGet = false;
	m_bAppro = false;

	m_pPlayer = nullptr;
}
//<==========================================================
//
//<==========================================================
CItem::~CItem()
{
	//静的メンバ変数の初期化
	m_nNumAll--;
	m_MaxNum = INITIAL_INT;
	m_NumCollect = INITIAL_INT;
	m_nLeft = INITIAL_INT;
}
//<==========================================================
//単体での読み込み
//<==========================================================
CItem *CItem::Create(const D3DXVECTOR3 pos, const TYPE eType)
{
	//インスタンス生成
	CItem *pItem = new CItem;

	//中身チェック
	assert(pItem != nullptr);

	//情報設定
	pItem->SetVector3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false), pItem->m_rot, {});
	pItem->m_eType = eType;

	//アイテムタイプに設定
	pItem->SetType3D(TYPE_3D::TYPE_ITEM);

	return pItem;
}
//<==========================================================
//
//<==========================================================
HRESULT CItem::Init(void)
{
	//初期化とマテリアルデータ取得どちらも成功しているかのチェック
	assert(SUCCEEDED(CXObject::Init()));

	m_sModel = BindModel(m_acFilename[m_eType]);

	return S_OK;
}
//<==========================================================
//ランダム生成
//<==========================================================
CItem *CItem::RandCreate(CItem *apItem[MAX_OBJECT], int nNum)
{
	//変数宣言
	D3DXVECTOR3 rRandPos = INIT_VECTOR;
	int nRandType = TYPE::TYPE_MAX;

	//数分生成する
	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		//インスタンスを生成する
		apItem[nCnt] = new CItem;

		//中身チェック
		assert(apItem[nCnt] != nullptr);

		rRandPos = D3DXVECTOR3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false));
		nRandType = rand() % TYPE::TYPE_MAX + TYPE::TYPE_ITEM0;

		//情報設定
		apItem[nCnt]->SetVector3(rRandPos, apItem[nCnt]->m_rot, {});
		apItem[nCnt]->m_eType = (CItem::TYPE)nRandType;

		apItem[nCnt]->Init();

		//アイテムタイプに設定
		apItem[nCnt]->SetType3D(TYPE_3D::TYPE_ITEM);

		//<******************************************
		//壁の破棄
		//<******************************************
		for (int nCntBuild = 0; nCntBuild < CBuilding::GetNum(); nCntBuild++)
		{
			//中身があれば
			if (CManager::GetScene()->GetGame()->GetBuil(nCnt) != nullptr)
			{
				//
				if (Collision::CollidAll(CManager::GetScene()->GetGame()->GetBuil(nCntBuild)->GetPosition(),
					CManager::GetScene()->GetGame()->GetBuil(nCntBuild)->GetModel().rSize,
					apItem[nCnt]->GetPosition(), apItem[nCnt]->GetModel().vtxMax, apItem[nCnt]->GetModel().vtxMin)==true)
				{
					//重ならないように位置を変える
					rRandPos = D3DXVECTOR3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false));
					apItem[nCnt]->SetPosition(rRandPos);
				}
			}
		}
	}

	//残り数を代入する
	m_nLeft = nNum;

	//全部のポインタを返す
	return *apItem;
}
//<==========================================================
//
//<==========================================================
void CItem::Update(void)
{
	//ゲットしていない状態だったら
	if (!m_bGet)
	{
		//情報取得
		m_pos = GetPosition();
		m_rot = GetRotation();

		m_rot.y = Correction::NormalizeRotation(m_rot.y);

	/*	m_pMat = GetMaterial();*/

		//情報を取得してくる
		m_pPlayer = CManager::GetScene()->GetGame()->Get3DPlayer();

		m_rot.y += 0.01f;

	/*	CManager::GetDebugProc()->Print("[アイテム位置]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_pos.x, m_pos.y, m_pos.z);*/
		/*CManager::GetDebugProc()->Print("[アイテム向き]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_rot.x, m_rot.y, m_rot.z);*/
		//CManager::GetDebugProc()->Print("[アイテムタイプ]：%d\n", m_eType);

		Collid();

		//情報設定
		SetVector3(m_pos, m_rot, {});
	}
}
//<==========================================================
//
//<==========================================================
void CItem::Collid(void)
{
	//当たっていれば
	if (Collision::CollidAll(m_pPlayer->GetPosition(), m_pPlayer->GetModel().rSize,
		m_pos, m_sModel.vtxMax, m_sModel.vtxMin))
	{
		m_bAppro = true;

		//Lボタンが押された+ゲット状態がfalseだったら
		if (CManager::GetKeyboard()->bGetTrigger(DIK_L) || CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_A, 0) && !m_bGet)
		{
			//ゲットした判定にする
			/*C3DParticle::Create(m_pos, D3DXCOLOR(1.0f, 0.5f, 0.1f, 1.0f), C3DParticle::TYPE::TYPE_TEST);*/
			m_NumCollect++;
			m_nLeft--;
			CManager::GetSound()->PlaySound(CSound::LABEL::LABEL_SE_ITEMGET);
			m_bGet = true;
		}
	}
	//当たっていなければ
	else
	{
		m_bAppro = false;
	}
}