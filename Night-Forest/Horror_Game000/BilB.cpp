//<==============================================
//ビルボード処理(BillB.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "BilB.h"
#include "manager.h"
#include "Texture.h"

//<================================
//ビルボードのコンストラクタ
//<================================
CBillB::CBillB(int nPriority) : CObject(nPriority)
{
	//値のクリア
	m_pos = INIT_VECTOR;
	m_move = INIT_VECTOR;
	m_Size = INIT_VECTOR;
	m_col = COLOR_VALUE::COLOR_INIT;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	m_mtxview = {};

	m_pTexture = NULL;
	m_bDraw = true;
}
//<================================
//ビルボードのデストラクタ
//<================================
CBillB::~CBillB()
{

}
//<================================
//ビルボードの初期化処理
//<================================
CBillB *CBillB::Create(const D3DXVECTOR3 rPos, const D3DXVECTOR2 rSize,const D3DXCOLOR rColor, const LPDIRECT3DTEXTURE9 pTex)
{
	CBillB *pBillB = new CBillB;

	assert(pBillB != nullptr && pBillB->Init() == S_OK);

	pBillB->SetVector3(rPos, INIT_VECTOR, D3DXVECTOR3(rSize.x, rSize.y, 0.0f));
	pBillB->SetColor(rColor);
	pBillB->BindTexture(pTex);

	return pBillB;
}
//<================================
//ビルボードの初期化処理
//<================================
HRESULT CBillB::InitWith(const D3DXVECTOR3 rPos, const D3DXVECTOR2 rSize, const D3DXCOLOR rColor, const LPDIRECT3DTEXTURE9 pTex)
{
	//頂点バッファの生成
	if (FAILED(CManager::GetRenderer()->GetDevice()->CreateVertexBuffer
	(sizeof(VERTEX_3D) * INT_VALUE::MAX_TOP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	SetVector3(rPos, INIT_VECTOR, D3DXVECTOR3(rSize.x, rSize.y, 0.0f));
	SetColor(rColor);
	BindTexture(pTex);

	SetVtx();

	return S_OK;
}
//<================================
//ビルボードの初期化処理
//<================================
HRESULT CBillB::Init(void)
{
	//頂点バッファの生成
	if (FAILED(CManager::GetRenderer()->GetDevice()->CreateVertexBuffer
		(sizeof(VERTEX_3D) * INT_VALUE::MAX_TOP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	SetVtx();

	return S_OK;
}
//<================================
//ビルボードの終了処理
//<================================
void CBillB::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}
//<================================
//ビルボードの更新処理
//<================================
void CBillB::Update(void)
{
	
}
//<================================
//ビルボードの描画処理
//<================================
void CBillB::Draw(void)
{
	if (m_bDraw)
	{
		D3DXMATRIX mtxTrans;	//計算用マトリックス

								//Zテストを無効にする
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	//常に描画する

																							//ビューマトリックスの取得
		CManager::GetRenderer()->GetDevice()->GetTransform(D3DTS_VIEW, &m_mtxview);

		//カメラを正面として向く
		D3DXMatrixInverse(&m_mtxWorld, NULL, &m_mtxview);
		m_mtxWorld._41 = 0.0f;
		m_mtxWorld._42 = 0.0f;
		m_mtxWorld._43 = 0.0f;

		//<=========================================================
		//位置の反映はそのオブジェクトから生成する場合、使用しない
		//そのまま設定する場合は使用してもOK
		//<========================================================
		//位置を反映させる
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		//ワールドマトリックスを掛ける(乗算)
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		CManager::GetRenderer()->GetDevice()->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//頂点バッファをデータストリームに設定
		CManager::GetRenderer()->GetDevice()->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		CManager::GetRenderer()->GetDevice()->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		CManager::GetRenderer()->GetDevice()->SetTexture(0, m_pTexture);

		//テクスチャの描画
		CManager::GetRenderer()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//Zテストを有効にする
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
}
//<================================
//ビルボードの頂点情報設定処理
//<================================
void CBillB::SetVtx(void)
{
	//2D頂点情報のポインタ
	VERTEX_3D *pVtx;

	//頂点バッファのロック
  	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//位置の取得
	m_pos = GetPos();

	//サイズの取得
	m_Size = GetSize();

	//色の取得
	m_col = GetColor();

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f - m_Size.x, 0.0f + m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f + m_Size.x, 0.0f + m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f - m_Size.x, 0.0f - m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f + m_Size.x, 0.0f - m_Size.y, 0.0f);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	//頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();
}
//<================================
//ビルボードのVector3型の設定処理
//<================================
void CBillB::SetVector3(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXVECTOR3& Size)
{
	//もし位置の情報があったら
	if (pos != NULL)
	{
		m_pos = pos;
	}
	//もし移動値の情報があったら
	if (move != NULL)
	{
		m_move = move;
	}
	//もしサイズの情報があったら
	if (Size != NULL)
	{
		m_Size = Size;
	}
}