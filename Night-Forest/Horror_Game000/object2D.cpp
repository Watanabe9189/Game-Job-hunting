//<==============================================
//2Dオブジェクト専門の処理(2DObject.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "object2D.h"
#include "manager.h"
#include "renderer.h"
#include "Texture.h"

//<*************************************************************************
// マクロ定義
//<*************************************************************************

//<**********************************************
//静的メンバ変数の宣言
//<**********************************************

//<==================================================================================
//オブジェクト2Dのコンストラクタ
//<==================================================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	//値のクリア
	m_aObj.pos = D3DXVECTOR2(0.0f,0.0f);
	m_aObj.rot = INIT_VECTOR;
	m_aObj.move = D3DXVECTOR2(0.0f, 0.0f);
	m_aObj.Size = D3DXVECTOR2(0.0f, 0.0f);
	m_aObj.Col = COLOR_VALUE::COLOR_INIT;
	m_aObj.fAngle = INITIAL_FLOAT;
	m_aObj.fLength = INITIAL_FLOAT;

	m_pTexture = NULL;							//テクスチャへのポインタ
	m_pVtxBuff = NULL;							//頂点バッファ
}
//<==================================================================================
//オブジェクト2Dのデストラクタ
//<==================================================================================
CObject2D::~CObject2D()
{

}
//<==================================================================================
//オブジェクト2Dの生成処理
//<==================================================================================
CObject2D *CObject2D::Create(const D3DXVECTOR2 rPos, const D3DXVECTOR2 rSize, const D3DXCOLOR rColor,const LPDIRECT3DTEXTURE9 pTexture)
{
	//インスタンス生成
	CObject2D *pObject2D = new CObject2D;

	//中身と初期化チェック
	assert(pObject2D != nullptr && pObject2D->Init() == S_OK);

	pObject2D->SetPosition(rPos);

	pObject2D->SetSize(rSize);

	pObject2D->SetColor(rColor);

	pObject2D->BindTexture(pTexture);

	return pObject2D;

}
//<==================================================================================
//2Dオブジェクトの初期化処理
//<==================================================================================
HRESULT CObject2D::Init(void)
{
	//頂点バッファの生成
	if (CManager::GetRenderer()->GetDevice()->CreateVertexBuffer
		(sizeof(VERTEX_2D) * INT_VALUE::MAX_TOP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)!= D3D_OK)
	{
		return E_FAIL;
	}

	//頂点情報設定
	SetVtx();

	return S_OK;
}
//<==================================================================================
//2Dオブジェクトの終了処理
//<==================================================================================
HRESULT CObject2D::InitWith(const D3DXVECTOR2 rPos, const D3DXVECTOR2 rSize,
	const D3DXCOLOR rColor, const LPDIRECT3DTEXTURE9 pTexture)
{
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

	SetPosition(rPos);

	SetSize(rSize);

	SetColor(rColor);

	BindTexture(pTexture);

	SetVtx();

	return S_OK;

}
//<==================================================================================
//2Dオブジェクトの終了処理
//<==================================================================================
void CObject2D::Uninit(void)
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
//<==================================================================================
//2Dオブジェクトの更新処理
//<==================================================================================
void CObject2D::Update(void)
{

}
//<==================================================================================
//2Dオブジェクトの描画処理
//<==================================================================================
void CObject2D::Draw(void)
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
	CManager::GetRenderer()->GetDevice()->SetTexture(0, m_pTexture);
	//<======================================================
	//描画方法を指定
	//<======================================================
	CManager::GetRenderer()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//<==================================================================================
//2Dオブジェクトの頂点座標設定処理
//<==================================================================================
void CObject2D::SetVtx(void)
{
	// 頂点情報へのポインタ
	VERTEX_2D *pVtx;

	assert(m_pVtxBuff != NULL);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//それぞれの情報の取得
	m_aObj.pos = GetPosition();
	m_aObj.rot = GetRotation();
	m_aObj.fAngle = GetAngle();
	m_aObj.fLength = GetLength();

	//左上
	pVtx[0].pos.x = m_aObj.pos.x + sinf(m_aObj.rot.z - D3DX_PI + m_aObj.fAngle) * m_aObj.fLength;
	pVtx[0].pos.y = m_aObj.pos.y + cosf(m_aObj.rot.z - D3DX_PI + m_aObj.fAngle) * m_aObj.fLength;
	pVtx[0].pos.z = 0.0f;

	//右上
	pVtx[1].pos.x = m_aObj.pos.x + sinf(m_aObj.rot.z + D3DX_PI - m_aObj.fAngle) * m_aObj.fLength;
	pVtx[1].pos.y = m_aObj.pos.y + cosf(m_aObj.rot.z + D3DX_PI - m_aObj.fAngle) * m_aObj.fLength;
	pVtx[1].pos.z = 0.0f;

	//左下
	pVtx[2].pos.x = m_aObj.pos.x + sinf(m_aObj.rot.z - m_aObj.fAngle) * m_aObj.fLength;
	pVtx[2].pos.y = m_aObj.pos.y + cosf(m_aObj.rot.z - m_aObj.fAngle) * m_aObj.fLength;
	pVtx[2].pos.z = 0.0f;

	//右下
	pVtx[3].pos.x = m_aObj.pos.x + sinf(m_aObj.rot.z + m_aObj.fAngle) * m_aObj.fLength;
	pVtx[3].pos.y = m_aObj.pos.y + cosf(m_aObj.rot.z + m_aObj.fAngle) * m_aObj.fLength;
	pVtx[3].pos.z = 0.0f;


	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = m_aObj.Col;
	pVtx[1].col = m_aObj.Col;
	pVtx[2].col = m_aObj.Col;
	pVtx[3].col = m_aObj.Col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}
//<==========================================================================
//サイズ設定
//<==========================================================================
void CObject2D::SetSize(const D3DXVECTOR2& size)
{
	//サイズの設定
	m_aObj.Size = size;	
	SetLength(sqrtf(m_aObj.Size.x * m_aObj.Size.x + m_aObj.Size.y * m_aObj.Size.y));
	SetAngle(atan2f(m_aObj.Size.x, m_aObj.Size.y));	
}