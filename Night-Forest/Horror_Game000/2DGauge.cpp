//<==============================================
//2Dゲージ処理(2DGauge.ch)
//
//Author:kazuki watanabe
//<==============================================
#include "2DGauge.h"
#include "manager.h"
#include "Texture.h"
#include "DebugProc.h"

//<**********************************************************
//名前宣言(メンバ変数を使うことはできない)
//<**********************************************************
namespace
{

	const D3DXVECTOR2 SIZEPOS_X = D3DXVECTOR2(130.0f, 15.0f);	//横方向だった場合の位置
	const D3DXVECTOR2 SIZEPOS_Y = D3DXVECTOR2(150.0f, 50.0f);	//縦方向だった場合の位置
	const D3DXVECTOR2 SIZEMAX_X = D3DXVECTOR2(125.0f, 15.0f);	//横方向の場合のサイズの最大値
	const D3DXVECTOR2 SIZEMAX_Y = D3DXVECTOR2(15.0f, 100.0f);	//縦方向の場合のサイズの最大値
	const float		VALUE_ALPHA = 0.05f;						//透明度変更値		
	const int		INIT_MAX	= 500;							//静的メンバ変数の初期値
	const int MAX_VALUE = 1000;
	const int MIN_VALUE = 0;
}
int C2DGauge::m_nFixedMax = INIT_MAX;		//設定用の最大値

int C2DGauge::m_nMaxLimit = MAX_VALUE;		//最大値
int C2DGauge::m_nMinLimit = MIN_VALUE;		//最小値
float C2DGauge::m_StaAddValue = INITIAL_FLOAT;
//<===============================================================
//
//<===============================================================
C2DGauge::C2DGauge(int nPriority)
{
	//値のクリア
	m_rPos = D3DXVECTOR2(0.0f,0.0f);
	m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	m_rCol = COLOR_VALUE::COLOR_GREEN;
	m_fAddValue =INITIAL_FLOAT;
	m_fOldAdd = INITIAL_FLOAT;
	m_fChange = INITIAL_FLOAT;
	m_fCurrent = INITIAL_FLOAT;
	m_nNum = INITIAL_INT;
	m_nMax = INITIAL_INT;
	m_eVer = VERTEX_MAX;

	m_pVtxBuff = nullptr;
}
//<===============================================================
//
//<===============================================================
C2DGauge::~C2DGauge()
{
	
}
//<===============================================================
//
//<===============================================================
C2DGauge *C2DGauge::Create(const D3DXVECTOR2 pos,const int nMaxNum, const VERTEX eVer, const MODE eMode)
{
	C2DGauge *p2DGauge = new C2DGauge;

	assert(p2DGauge != nullptr);

	//列挙型変数
	p2DGauge->m_eVer = eVer;
	p2DGauge->m_eMode = eMode;

	//値の設定
	p2DGauge->m_rPos = pos;
	p2DGauge->m_nMax = nMaxNum;

	//初期化
	assert(SUCCEEDED(p2DGauge->Init()));

	p2DGauge->SetNum(nMaxNum);

	return p2DGauge;
}
//<===============================================================
//
//<===============================================================
HRESULT C2DGauge::Init(void)
{
	//横型だったら
	if (m_eVer == VERTEX_X)
	{
		//サイズの設定
		m_rSize = D3DXVECTOR2(SIZEMAX_X.x, SIZEMAX_X.y);
	}
	//縦型だったら
	else if (m_eVer == VERTEX_Y)
	{
		//サイズの設定
		m_rSize = D3DXVECTOR2(SIZEMAX_Y.x, SIZEMAX_Y.y);
	}

	//頂点バッファの生成
	if (CManager::GetRenderer()->GetDevice()->CreateVertexBuffer
	(sizeof(VERTEX_2D) * INT_VALUE::MAX_TOP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL) != D3D_OK)
	{
		return E_FAIL;
	}

	SetVtx();

	return S_OK;
}
//<===============================================================
//
//<===============================================================
void C2DGauge::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//オブジェクトの破棄
	Release();
}
//<===============================================================
//
//<===============================================================
void C2DGauge::Update(void)
{
	//常に表示させるモード
	if (m_eMode == MODE::MODE_ALWAYS)
	{
		//今のゲージが最大ゲージの半分になっていたら
		if (m_fCurrent <= m_nMax/2)
		{
			m_rCol = COLOR_VALUE::COLOR_RED;
		}
		//それ以外の場合
		else
		{
			m_rCol = COLOR_VALUE::COLOR_INIT;
		}
	}
	//使っている時だけ表示させるモード
	else if (m_eMode == MODE::MODE_ONLY_USE)
	{
	
	}

	CManager::GetDebugProc()->Print("[m_fOldAdd]：%f\n", m_fOldAdd);
	CManager::GetDebugProc()->Print("[m_fAddValue]：%f\n", m_fAddValue);
	CManager::GetDebugProc()->Print("[m_fCurrent]：%f\n", m_fCurrent);
	CManager::GetDebugProc()->Print("[m_nNum]：%d\n", m_nNum);

	SetVtx();
}
//<===============================================================
//
//<===============================================================
void C2DGauge::Draw(void)
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
	CManager::GetRenderer()->GetDevice()->SetTexture(0, NULL);
		
	//描画する
	CManager::GetRenderer()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	
}
//<===============================================================
//加算処理
//<===============================================================
void C2DGauge::Add(const int nValue)
{
	m_fCurrent = (float)m_nNum;

	m_fChange = ((float)nValue / 5.0f);

	m_nNum += nValue;
}
//<===============================================================
//設定処理
//<===============================================================
void C2DGauge::SetNum(const int nNum)
{
	m_nNum = nNum;

	m_fCurrent = (float)m_nNum;

	//横型だったら
	if (m_eVer == VERTEX_X)
	{
		//最大値の限界値を基準として加減したりさせる
		m_fAddValue = (m_fCurrent * ((m_rSize.x * 2) / (float)m_nMaxLimit)) - m_rSize.x;
	}
	//縦型だったら
	else if (m_eVer == VERTEX_Y)
	{
		//最大値の限界値を基準として加減したりさせる
		m_fAddValue = (m_fCurrent * ((m_rSize.y * 2) / (float)m_nMaxLimit)) - m_rSize.y;
	}
}
//<===============================================================
//
//<===============================================================
void C2DGauge::SetVtx(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファのチェック
	assert(m_pVtxBuff != nullptr);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//横型だったら
	if (m_eVer == VERTEX_X)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(m_rPos.x - m_rSize.x, m_rPos.y - m_rSize.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_rPos.x - m_rSize.x, m_rPos.y + m_rSize.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_rPos.x + m_fAddValue, m_rPos.y - m_rSize.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_rPos.x + m_fAddValue, m_rPos.y + m_rSize.y, 0.0f);
	}
	//縦型だったら
	else if (m_eVer == VERTEX_Y)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(m_rPos.x - m_rSize.x, m_rPos.y - m_fAddValue, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_rPos.x - m_rSize.x, m_rPos.y + m_rSize.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_rPos.x + m_rSize.x, m_rPos.y - m_fAddValue, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_rPos.x + m_rSize.x, m_rPos.y + m_rSize.y, 0.0f);
	}
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = m_rCol;
	pVtx[1].col = m_rCol;
	pVtx[2].col = m_rCol;
	pVtx[3].col = m_rCol;
	
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}