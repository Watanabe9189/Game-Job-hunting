#include "Option.h"


C2DGauge *COption::m_p2DGauge = nullptr;
CNumber  *COption::m_pNumber = nullptr;

LPDIRECT3DTEXTURE9	COption::m_apTexture[INT_VALUE::MAX_TEX] = {};

//テクスチャへのポインタ
const char*			COption::m_acFilename[] =
{
	"data\\TEXTURE\\HORROR-OPTION001.png",
	"data\\TEXTURE\\HORROR-OPTION002.png",
	"data\\TEXTURE\\HORROR-SELECT002.png",
	"data\\TEXTURE\\number_02.png"

};				//ファイル名

namespace
{
	const float			DISTANCE_Y = 250.0f;								//Y軸の距離
	const float			DISTANCE_GAUGE= 400.0f;								//ゲージ距離
	const float			DISTANCE_NUM = 305.0f;								//番号距離

	const D3DXVECTOR2 OPTION_POS = D3DXVECTOR2(485.0f, 100.0f);				//オプション位置
	const D3DXVECTOR2 OPTION_SIZE = D3DXVECTOR2(300.0f, 200.0f);			//オプションサイズ
	const D3DXVECTOR2 NUM_SIZE = D3DXVECTOR2(100.0f, 100.0f);				//番号のサイズ		

	const int MAX_COLCOUNT = 50;

}
//<===================================
//
//<===================================
COption::COption()
{
	//値のクリア
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}
	m_pNumber = nullptr;
	m_p2DGauge = nullptr;
	m_nSelect = INITIAL_INT;
	m_nOldSelect = INITIAL_INT;
	m_nStamina = INITIAL_INT;
	m_nNumEnemy = INITIAL_INT;
	m_rCol = INIT_COL;
}
//<===================================
//
//<===================================
COption::~COption()
{

}
//<===================================
//
//<===================================
HRESULT COption::Init(void)
{
	//情報を取得してくる
	m_nStamina = C2DGauge::GetFixed();
	m_nNumEnemy = C3DEnemy::GetNumSet();

	CManager::GetSound()->PlaySound(CSound::LABEL_BGM_OPTION);

	//テクスチャの初期化
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		//最初だけ読み込む
		if (m_apTexture[nCnt] == nullptr)
		{
			//テクスチャの読み込み
			CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt]);
		}
	}

	//選択肢の数分繰り返す
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		//生成する
		m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR2(OPTION_POS.x, OPTION_POS.y + DISTANCE_Y * nCnt), OPTION_SIZE);

		//中身チェック
		assert(m_apObject2D[nCnt] != nullptr);

		//テクスチャ割り当て
		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

	//2Dのゲージを作成
	m_p2DGauge = C2DGauge::Create(D3DXVECTOR2(m_apObject2D[SELECT::SELECT_STAMINA]->GetPosition().x + DISTANCE_GAUGE,
		m_apObject2D[SELECT::SELECT_STAMINA]->GetPosition().y), m_nStamina, C2DGauge::VERTEX_X, C2DGauge::MODE_ALWAYS);

	//番号設定
	m_pNumber = CNumber::Create(D3DXVECTOR2(m_apObject2D[SELECT::SELECT_ENEMYNUM]->GetPosition().x + DISTANCE_NUM,
		m_apObject2D[SELECT::SELECT_ENEMYNUM]->GetPosition().y), NUM_SIZE,m_apTexture[3]);

	//中身チェック
	assert(m_p2DGauge != nullptr&&m_pNumber != nullptr);

	//数を設定する
	m_pNumber->SetNum(&m_nNumEnemy);

	return S_OK;
}
//<===================================
//
//<===================================
void COption::Uninit(void)
{
	//選択肢の数分繰り返す
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		//中身があれば
		if (m_apObject2D[nCnt] != nullptr)
		{
			//終了処理
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
	}
	//中身があれば
	if (m_p2DGauge != nullptr)
	{
		//終了処理
		m_p2DGauge->Uninit();
		m_p2DGauge = nullptr;
	}
	//中身があれば
	if (m_pNumber != nullptr)
	{
		//終了処理
		m_pNumber->Uninit();
		m_pNumber = nullptr;
	}
	Release();
}
//<===================================
//
//<===================================
void COption::Update(void)
{
	//選択肢の数分繰り返す
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->SetVtx();
	}

	//フェード状態が何もしていない状態だったら
	if (CManager::GetFade()->GetType() == CFade::TYPE_FADE_NONE)
	{
		Select();

		if (m_nSelect == SELECT::SELECT_STAMINA)
		{
			//左キーが押されていたら
			if (CManager::GetKeyboard()->bGetPress(DIK_LEFTARROW)
				|| CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_LEFT, 0))
			{
				m_nStamina--;

				if (m_nStamina <= C2DGauge::GetLimitMin())
				{
					m_nStamina = C2DGauge::GetLimitMin();
				}

				m_p2DGauge->SetNum(m_nStamina);
			}

			//右キーが押されていたら
			else if (CManager::GetKeyboard()->bGetPress(DIK_RIGHTARROW)
				|| CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_RIGHT, 0))
			{
				m_nStamina++;

				if (m_nStamina >= C2DGauge::GetLimitMax())
				{
					m_nStamina = C2DGauge::GetLimitMax();
				}

				m_p2DGauge->SetNum(m_nStamina);
			}
		}
		//EXITボタンに行っていて決定ボタンが押されていたら
		else if (m_nSelect == SELECT::SELECT_ENEMYNUM)
		{
			//左キーが押されていたら
			if (CManager::GetKeyboard()->bGetTrigger(DIK_LEFTARROW)
				|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_LEFT, 0))
			{
				m_nNumEnemy--;

				if (m_nNumEnemy <= C3DEnemy::GetNumMin())
				{
					m_nNumEnemy = C3DEnemy::GetNumMin();
				}

				m_pNumber->SetNum(&m_nNumEnemy);
			}
			//右キーが押されていたら
			else if (CManager::GetKeyboard()->bGetTrigger(DIK_RIGHTARROW)
				|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_RIGHT, 0))
			{
				m_nNumEnemy++;

				if (m_nNumEnemy >= C3DEnemy::GetNumMax())
				{
					m_nNumEnemy = C3DEnemy::GetNumMax();
				}

				m_pNumber->SetNum(&m_nNumEnemy);
			}
		}
		//EXITボタンに行っていて決定ボタンが押されていたら
		else if (CManager::GetKeyboard()->bGetTrigger(DIK_RETURN) == true
			|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0)&&m_nSelect == SELECT::SELECT_EXIT)
		{
			CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECTED);
			CManager::SetFade(CScene::MODE::MODE_TITLE);
			C2DGauge::SetFixed(m_nStamina);				//スタミナ最大値を設定
			C3DEnemy::SetNumSet(m_nNumEnemy);
		}
	}
}
//<===================================
//
//<===================================
void COption::Draw(void)
{
	//選択肢の数分繰り返す
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_apObject2D[nCnt]->Draw();
	}
}
//<===================================
//
//<===================================
void COption::Select(void)
{
	//前回の選択を保存する
	m_nOldSelect = m_nSelect;

	//色を変える
	m_rCol = Change::ChangeColInter(m_rCol, 1.0f, 0.3f, 0.025f);

	//左キーが押されていたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_UPARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_UP, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + (SELECT_MAX - 1)) % SELECT_MAX;
		m_rCol.a = 1.0f;
	}
	//右キーが押されていたら
	else if (CManager::GetKeyboard()->bGetTrigger(DIK_DOWNARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_DOWN, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + 1) % SELECT_MAX;
		m_rCol.a = 1.0f;
	}

	//カラーを設定する
	m_apObject2D[m_nOldSelect]->SetColor(INIT_COL);

	m_apObject2D[m_nSelect]->SetColor(m_rCol);

}