//<==================================================================================
//チュートリアル画面処理(Tutorial.cpp)
//
//Author:kazuki watanabe
//<==================================================================================
#include "Tutorial.h"
#include "input.h"
#include "Texture.h"
#include "DebugProc.h"

//<*****************************************
//3D関連
//<*****************************************
#include "Light.h"

LPDIRECT3DTEXTURE9	CTutorial::m_apTexture[INT_VALUE::MAX_TEX] = {};	//テクスチャへのポインタ

															//ファイル名
const char*			CTutorial::m_acFilename[TUTORIAL_STEP_MAX] =
{
	"data/TEXTURE/TUTORIAL/C++Tutorial000.png",
	"data/TEXTURE/TUTORIAL/C++Tutorial001.png",
	"data/TEXTURE/TUTORIAL/C++Tutorial002.png",
	"data/TEXTURE/TUTORIAL/C++Tutorial003.png"
};
int CTutorial::m_nTutorialStep = INITIAL_INT;

CLight *CTutorial::m_pLight;					//

LPDIRECT3DVERTEXBUFFER9 CTutorial::m_pVtxBuff = nullptr;

//<===========================================================
//チュートリアルのコンストラクタ
//<===========================================================
CTutorial::CTutorial()
{
	//値のクリア
	m_pos = INIT_VECTOR;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = INIT_COL;
}
//<===========================================================
//チュートリアルのデストラクタ
//<===========================================================
CTutorial::~CTutorial()
{

}
//<===========================================================
//チュートリアルの初期化処理
//<===========================================================
HRESULT CTutorial::Init(void)
{

	for (int nCnt = 0; nCnt < sizeof(m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		if (m_apTexture[nCnt] == nullptr)
		{
			//テクスチャの読み込み
			if ((CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt])) <= -1)
			{
				return E_FAIL;
			}
		}
	}

	//頂点バッファの生成
	if (m_pVtxBuff == nullptr &&
		CManager::GetRenderer()->GetDevice()->CreateVertexBuffer
	(sizeof(VERTEX_2D) * INT_VALUE::MAX_TOP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL) != D3D_OK)
	{
		return E_FAIL;
	}

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//要素の設定
	m_pos = D3DXVECTOR3(660.0f, 620.0f, 0.0f);

	m_Size = D3DXVECTOR2(600.0f, 100.0f);

	m_nTutorialStep = INITIAL_INT;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//背景
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, 0.0f);

	//頂点カラーの設定
	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//rhwの設定
	pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}
//<===========================================================
//チュートリアルの終了処理
//<===========================================================
void CTutorial::Uninit(void)
{
	//頂点バッファを破棄する
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	Release();
}
//<=========================================================
//チュートリアルの更新処理
//<=========================================================
void CTutorial::Update(void)
{
	//SPACEキーが押されたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_RIGHTARROW) == true ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_RIGHT, 0) == true)
	{
		//チュートリアルステップを進める
		m_nTutorialStep += 1;

		//もしチュートリアルステップが最大値を超えていたら
		if (m_nTutorialStep >= TUTORIAL_STEP_MAX)
		{
			//ゲーム画面に遷移
			CManager::SetMode(CScene::MODE::MODE_GAME);
		}
	}

	//SPACEキーが押されたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_LEFTARROW) == true ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_LEFT, 0) == true)
	{
		//チュートリアルステップを進める
		m_nTutorialStep -= 1;

		//もし最小値に到達しようとしたら
		if (m_nTutorialStep <= TUTORIAL_STEP_1)
		{
			m_nTutorialStep = TUTORIAL_STEP_1;
		}
	}
	//SPACEキーが押されたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_LSHIFT) == true ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_START, 0) == true)
	{
		//ゲーム画面に遷移
		CManager::SetMode(CScene::MODE::MODE_GAME);
	}
	CManager::GetDebugProc()->Print("[現在のチュートリアルステップ->%d]\n", m_nTutorialStep);

}
//<==========================================================
//チュートリアルの描画処理
//<==========================================================
void CTutorial::Draw(void)
{
	//<======================================================
	//頂点バッファをデータストリームに登録
	//<======================================================
	CManager::GetRenderer()->GetDevice()->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	CManager::GetRenderer()->GetDevice()->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	CManager::GetRenderer()->GetDevice()->SetTexture(0, m_apTexture[m_nTutorialStep]);

	//ポリゴンの描画
	CManager::GetRenderer()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}