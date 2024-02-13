#include "Pause.h"

namespace
{
	const D3DXVECTOR2 SIZE_PAUSE = D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT);
	const D3DXVECTOR2 POS_SELECT = D3DXVECTOR2(625.0f, 125.0f);
	const D3DXVECTOR2 SIZE_SELECT = D3DXVECTOR2(300.0f, 150.0f);
	const float DISTANCE_Y = 200.0f;
}

LPDIRECT3DTEXTURE9	CPause::m_apTexture[INT_VALUE::MAX_TEX] = {};		//テクスチャへのポインタ
const char*			CPause::m_acFilename[]
{
	NULL,
	NULL,
	"data\\TEXTURE\\Pause\\Pause001.png",
	"data\\TEXTURE\\Pause\\Pause002.png",
	"data\\TEXTURE\\Pause\\Pause003.png",
};				//ファイル名

//<==========================================
//
//<==========================================
CPause::CPause()
{
	//値のクリア
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_apSelct[nCnt] = nullptr;
	}
	m_rSizeSelect = D3DXVECTOR2(0.0f, 0.0f);
	m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	m_rCOl = INIT_COL;

	m_nSelect = SELECT::SELECT_RESUME;
	m_nOldSelect = SELECT::SELECT_RESUME;
}
//<==========================================
//
//<==========================================
CPause::~CPause()
{

}
//<==========================================
//
//<==========================================
void CPause::Init(void)
{
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
	//値のクリア
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR2(0.0f, 0.0f), SIZE_PAUSE, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f), m_apTexture[nCnt]);

		assert(m_apObject2D[nCnt] != nullptr);
	}
	//値のクリア
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		m_apSelct[nCnt] = CObject2D::Create(D3DXVECTOR2(POS_SELECT.x, POS_SELECT.y + DISTANCE_Y * nCnt), SIZE_SELECT, m_rCOl, m_apTexture[nCnt+2]);

		assert(m_apSelct[nCnt] != nullptr);
	}
}
//<==========================================
//
//<==========================================
void CPause::Uninit(void)
{
	
}
//<==========================================
//
//<==========================================
void CPause::Update(void)
{
	//値のクリア
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->SetVtx();

			//ポーズされていたら
			if (CManager::GetPause() == true)
			{
				//サイズを取得してくる
				m_rSize = SIZE_PAUSE;
			}
			//されていなければ
			else
			{
				//サイズで表示させなくする
				m_rSize = D3DXVECTOR2(0.0f, 0.0f);
				m_nSelect = SELECT::SELECT_RESUME;
			}

			m_apObject2D[nCnt]->SetSize(m_rSize);
		}
	}
	//値のクリア
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; nCnt++)
	{
		if (m_apSelct[nCnt] != nullptr)
		{
			m_apSelct[nCnt]->SetVtx();

			//ポーズされていたら
			if (CManager::GetPause() == true)
			{
				//サイズを取得してくる
				m_rSizeSelect = SIZE_SELECT;
			}
			//されていなければ
			else
			{
				//サイズで表示させなくする
				m_rSizeSelect = D3DXVECTOR2(0.0f, 0.0f);
				m_nSelect = SELECT::SELECT_RESUME;
				m_rCOl = INIT_COL;
			}

			m_apSelct[nCnt]->SetColor(m_rCOl);
			m_apSelct[nCnt]->SetSize(m_rSizeSelect);
		}
	}
	Select();
}
//<====================================
//
//<====================================
void CPause::Select(void)
{
	//前回の選択を保存する
	m_nOldSelect = m_nSelect;

	//左キーが押されていたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_UPARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_UP, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + (SELECT_MAX - 1)) % SELECT_MAX;
	}
	//右キーが押されていたら
	else if (CManager::GetKeyboard()->bGetTrigger(DIK_DOWN)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_DOWN, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + 1) % SELECT_MAX;
	}

	//カラーを設定する
	m_apSelct[m_nOldSelect]->SetColor(INIT_COL);

	//カラーを透明にする
	m_apSelct[m_nSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
}