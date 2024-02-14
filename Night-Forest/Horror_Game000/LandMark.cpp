#include "LandMark.h"
#include "game.h"

const char*			CLandMark::m_acFilename[TYPE::TYPE_MAX]
{
	"data\\MODEL\\LandMark\\SignBoard000.x",
	"data\\MODEL\\LandMark\\TrunkTable000.x",
	"data\\MODEL\\LandMark\\Car000.x",
	"data\\MODEL\\LandMark\\House001.x",
};
int CLandMark::m_nNumAll = INITIAL_INT;
//<================================================
//
//<================================================
CLandMark::CLandMark(int nPriority)
{
	m_nNumAll++;

	//値のクリア
	m_pos = INIT_VECTOR;
	m_rot = INIT_VECTOR;
	m_move = INIT_VECTOR;

	m_eType = TYPE::TYPE_MAX;

	m_pBillBIcon = nullptr;
	m_sModel = {};
}
//<================================================
//
//<================================================
CLandMark::~CLandMark()
{
	m_nNumAll--;
}
//<================================================
//
//<================================================
CLandMark *CLandMark::FixedCreate(CLandMark *apLandMark[MAX_OBJECT])
{
	//プレイヤー情報を取得する
	C3DPlayer *pPlayer = CManager::GetScene()->GetGame()->Get3DPlayer();

	//エリアの限界範囲
	const float MAX_AREA = 4000.0f;

	//タイプマックス分繰り返す
	for (int nCnt = 0; nCnt < TYPE::TYPE_MAX; nCnt++)
	{
		apLandMark[nCnt] = new CLandMark;

		assert(apLandMark[nCnt] != nullptr);

		//処理を分ける
		switch (nCnt)
		{
			//一番目
		case TYPE::TYPE_FIRST:

			//プレイヤーの初期位置に設定する
			apLandMark[nCnt]->SetPosition(D3DXVECTOR3(pPlayer->GetPosition().x, pPlayer->GetPosition().y, pPlayer->GetPosition().z + 200.0f));

			break;

			//二番目
		case TYPE::TYPE_SECOND:

			//原点に設定する
			apLandMark[nCnt]->SetPosition(INIT_VECTOR);

			break;

			//三番目
		case TYPE::TYPE_THIRD:


			//原点に設定する
			apLandMark[nCnt]->SetPosition(D3DXVECTOR3(Calculate::CalculateRandfloat(4000, -4000.0f), 0.0f, -2500.0f));

			break;

			//四番目
		case TYPE::TYPE_FOURTH:

			//原点に設定する
			apLandMark[nCnt]->SetPosition(D3DXVECTOR3(-2500.0f, 0.0f, Calculate::CalculateRandfloat(4000, -4000.0f)));

			break;
		}
	
		//表示させる
		apLandMark[nCnt]->m_pBillBIcon = CBilBIcon::Create(D3DXVECTOR3(apLandMark[nCnt]->GetPosition().x,
			apLandMark[nCnt]->GetPosition().y + 125.0f ,
			apLandMark[nCnt]->GetPosition().z),
			nCnt);

		//タイプを設定する
		apLandMark[nCnt]->m_eType = (TYPE)nCnt;

		//初期化処理
		apLandMark[nCnt]->Init();
	}


	return *apLandMark;
}
//<================================================
//
//<================================================
HRESULT CLandMark::Init(void)
{
	m_sModel = BindModel(m_acFilename[m_eType]);
	//もし初期化に失敗したら
	if (FAILED(CXObject::Init()))
	{
		return E_FAIL;
	}

	return S_OK;
}
//<================================================
//
//<================================================
void CLandMark::Update(void)
{
	//位置を取得
	m_pos = GetPosition();

	//移動量の取得
	m_move = GetMove();

	//向きを取得
	m_rot = GetRotation();

	CManager::GetDebugProc()->Print("[位置]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_pos.x, m_pos.y, m_pos.z);

	Collid();

	SetVector3(m_pos, m_rot, m_move);
}
//<================================================
//
//<================================================
void CLandMark::Collid(void)
{
	//当たっていたら
	if (Collision::CollidAll(m_pos, m_sModel.rSize, CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition(),
		CManager::GetScene()->GetGame()->Get3DPlayer()->GetModel().vtxMax, 
		CManager::GetScene()->GetGame()->Get3DPlayer()->GetModel().vtxMin))
	{
		//もし中身があれば
		if (m_pBillBIcon != nullptr)
		{
			//表示させる
			m_pBillBIcon->SetDrawtrue();
		}
	}
	else
	{
		//もし中身があれば
		if (m_pBillBIcon != nullptr)
		{
			//表示させる
			m_pBillBIcon->SetDrawfalse();
		}
	}
}