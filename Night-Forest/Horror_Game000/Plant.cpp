//<======================================================================================
//植物関連の処理(Plant.cpp)
//
//Author:kazuki watanabe
//<======================================================================================
#include "Plant.h"

LPDIRECT3DTEXTURE9	CPlant::m_apTexture[TYPE::TYPE_MAX] = {};		//テクスチャへのポインタ
const char*			CPlant::m_acFilename[TYPE::TYPE_MAX] =
{
	"data\\TEXTURE\\Grass.png",				//草
	"data\\TEXTURE\\Tree000.png",			//木
};

int CPlant::m_nNumAll = INITIAL_INT;

//<********************************************
//名前宣言
//<********************************************
namespace
{
	const D3DXVECTOR3 GRASS_SIZE = D3DXVECTOR3(75.0f, 75.0f,0.0f);		//草サイズ
	const D3DXVECTOR3 TREE_SIZE = D3DXVECTOR3(75.0f, 125.0f, 0.0f);		//木サイズ
	const float GRASS_POSY = 25.0f;										//補正用の草位置Y
	const float TREE_POSY = TREE_SIZE.y/2.0f;							//補正用の木位置Y
}
//<============================================
//コンストラクタ
//<============================================
CPlant::CPlant(int nPriority)
{
	//値のクリア
	m_nNumAll++;

	m_rPos = INIT_VECTOR;
	m_rRot = INIT_VECTOR;
	m_rSize = INIT_VECTOR;
	m_rCol = INIT_COL;

	m_fMove = INITIAL_FLOAT;

	//初期化
	memset(&m_apGrass[0], 0, sizeof(m_apGrass));
}
//<============================================
//デストラクタ
//<============================================
CPlant::~CPlant()
{
	m_nNumAll--;
}
//<============================================
//ランダム生成
//<============================================
CPlant *CPlant::RandCreate(CPlant *apPlant[MAX_OBJECT], const int nNum)
{
	//ここでしか使わない変数の宣言
	D3DXVECTOR3 rRandPos = INIT_VECTOR;
	int nRandType = INITIAL_INT;

	//数分回す
	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		apPlant[nCnt] = new CPlant;

		assert(apPlant[nCnt] != nullptr);

		nRandType = rand() % TYPE::TYPE_MAX + TYPE::TYPE_GRASS;

		if (nRandType == TYPE::TYPE_TREE)
		{
			rRandPos = D3DXVECTOR3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, TREE_POSY, 4000.0f), D3DXVECTOR3(-4000.0f, TREE_POSY, -4000.0f), true));
		}
		else
		{
			rRandPos = D3DXVECTOR3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, GRASS_POSY, 4000.0f), D3DXVECTOR3(-4000.0f, GRASS_POSY, -4000.0f), true));
		}

		apPlant[nCnt]->m_rPos = rRandPos;
		apPlant[nCnt]->m_eType = (TYPE)nRandType;

		apPlant[nCnt]->Init();
	}

	return *apPlant;
}
//<============================================
//初期化処理
//<============================================
HRESULT CPlant::Init(void)
{
	//テクスチャの初期化
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		//最初だけ読み込む
		if (m_apTexture[nCnt] == nullptr)
		{
			//テクスチャの読み込み
			if ((CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt])) <= -1)
			{
				return E_FAIL;
			}
		}
	}
	//草だったら
	if (m_eType == TYPE::TYPE_GRASS)
	{
		m_rSize = GRASS_SIZE;

		//草の最大数分繰り返し
		for (int nCnt = 0; nCnt < MAX_GRASS; nCnt++)
		{
			switch (nCnt)
			{
			case 0:

				m_apGrass[nCnt] = CObject3D::Create(m_rPos, m_rSize, D3DXVECTOR3(0.0f, 0.45f, 0.0f), m_rCol,
					CObject3D::TYPE::TYPE_PLANE_Y, m_apTexture[m_eType]);

				break;

			case 1:

				m_apGrass[nCnt] = CObject3D::Create(m_rPos, m_rSize, D3DXVECTOR3(0.0f, -0.45f, 0.0f), m_rCol,
					CObject3D::TYPE::TYPE_PLANE_Y, m_apTexture[m_eType]);

				break;
			}
		}
	}
	//木だったら
	else if (m_eType == TYPE::TYPE_TREE)
	{
		m_rSize = TREE_SIZE;

		m_apGrass[0] = CObject3D::Create(m_rPos, m_rSize, INIT_VECTOR, m_rCol,
			CObject3D::TYPE::TYPE_PLANE_Y, m_apTexture[m_eType]);
	}

	return S_OK;
}
//<============================================
//終了処理
//<============================================
void CPlant::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_GRASS; nCnt++)
	{
		if (m_apGrass[nCnt] != nullptr)
		{
			m_apGrass[nCnt]->Uninit();
			m_apGrass[nCnt] = nullptr;
		}
	}
}
//<============================================
//更新処理
//<============================================
void CPlant::Update(void)	
{
	//数ぶん回す
	for (int nCnt = 0; nCnt < MAX_GRASS; nCnt++)
	{
		//中身チェック
		if (m_apGrass[nCnt] != nullptr)
		{
			m_apGrass[nCnt]->SetVtx();

			//情報の取得
			m_rPos = m_apGrass[nCnt]->GetPosition();
			m_rSize = m_apGrass[nCnt]->GetSize();

			//情報の設定
			m_apGrass[nCnt]->SetPosition(m_rPos);
			m_apGrass[nCnt]->SetSize(m_rSize);
		}
	}

	/*CManager::GetDebugProc()->Print("[植物位置]：{X軸:%f},{Y軸:%f},{Z軸:%f}\n", m_rPos.x, m_rPos.y, m_rPos.z);*/
	//CManager::GetDebugProc()->Print("[植物タイプ]：%d\n", m_eType);
}