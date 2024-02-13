//<==============================================
//3Dオブジェクト専門の処理[Xファイルなし](Object3D.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "Object3D.h"
#include "manager.h"
#include "input.h"
#include "Texture.h"

//<=================================
//3Dオブジェクトのコンストラクタ
//<=================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_mtxWorld = {};

	m_pos	=	INIT_VECTOR;
	m_rot	=	INIT_VECTOR;
	m_move	=	INIT_VECTOR;
	m_Size	=	INIT_VECTOR;
	m_rCol = INIT_COL;
	m_eType = TYPE::TYPE_MAX;
	m_bDraw = true;
}
//<=================================
//3Dオブジェクトのデストラクタ
//<=================================
CObject3D::~CObject3D()
{

}
//<=================================
//
//<=================================
CObject3D *CObject3D::Create(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rSize,  const D3DXVECTOR3 rRot,const D3DXCOLOR rColor,
	const TYPE eType,const LPDIRECT3DTEXTURE9 pTexture)
{
	CObject3D *pObject3D = new CObject3D;

	assert(pObject3D != nullptr && pObject3D->Init() == S_OK);

	//情報設定
	pObject3D->SetPosition(rPos);
	pObject3D->SetSize(rSize);
	pObject3D->SetRotation(rRot);
	pObject3D->SetColor(rColor);
	pObject3D->BindTexture(pTexture);
	pObject3D->m_eType = eType;

	return pObject3D;
}
//<=================================
//3Dオブジェクトの初期化処理
//<=================================
HRESULT CObject3D::Init(void)
{

	//頂点バッファの生成
	if (FAILED(CManager::GetRenderer()->GetDevice()->
		CreateVertexBuffer(sizeof(VERTEX_3D) *INT_VALUE::MAX_TOP,
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
//<=========================================================================
//
//<=========================================================================
HRESULT CObject3D::InitWith(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rSize,
	const D3DXVECTOR3 rRot, const D3DXCOLOR rColor, const TYPE eType, const LPDIRECT3DTEXTURE9 pTexture)
{
	//頂点バッファの生成
	if (FAILED(CManager::GetRenderer()->GetDevice()->
		CreateVertexBuffer(sizeof(VERTEX_3D) *INT_VALUE::MAX_TOP,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&m_pVtxBuff,
			NULL)))
	{
		return E_FAIL;
	}

	//情報設定
	SetPosition(rPos);
	SetSize(rSize);
	SetRotation(rRot);
	SetColor(rColor);
	BindTexture(pTexture);
	m_eType = eType;

	SetVtx();

	return S_OK;
}
//<=================================
//3Dオブジェクトの終了処理
//<=================================
void CObject3D::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}
//<=================================
//3Dオブジェクトの更新処理
//<=================================
void CObject3D::Update(void)
{

}
//<=================================
//3Dオブジェクトの描画処理
//<=================================
void CObject3D::Draw(void)
{
	if (m_bDraw)
	{
		D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス(この変数はグローバル変数には入れない)

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_mtxWorld);

		//向きを反映させる
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);//この順番は重要である

																		   //ワールドマトリックスを掛ける(乗算)
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

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

		CManager::GetRenderer()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//<=================================
//3Dオブジェクトの頂点設定処理
//<=================================
void CObject3D::SetVtx(void)
{
	VERTEX_3D *pVtx;//頂点情報へのポインタ

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//
	m_pos = GetPosition();
	m_rot = GetRotation();
	m_Size = GetSize();
	m_rCol = GetColor();
	m_fAngle = GetAngle();
	m_fLength = GetLength();

	//平面型だったら
	if (m_eType == TYPE::TYPE_PLANE)
	{
		////頂点座標の設定
		//pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y, m_pos.z + m_Size.z);
		//pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y, m_pos.z + m_Size.z);
		//pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y, m_pos.z - m_Size.z);
		//pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y, m_pos.z - m_Size.z);

		//左上
		pVtx[0].pos.x = 0.0f + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;

		//右上
		pVtx[1].pos.x = 0.0f + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;

		//左下
		pVtx[2].pos.x = 0.0f + sinf(m_rot.z - m_fAngle) * m_fLength;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f + cosf(m_rot.z - m_fAngle) * m_fLength;

		//右下
		pVtx[3].pos.x = 0.0f + sinf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.y = 0.0f;
		pVtx[3].pos.z = 0.0f + cosf(m_rot.z + m_fAngle) * m_fLength;


		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	}
	//縦型だったら
	else if (m_eType == TYPE::TYPE_PLANE_Y)
	{
		//左上
		pVtx[0].pos.x = 0.0f + sinf(m_rot.z + D3DX_PI + m_fAngle) * m_fLength;
		pVtx[0].pos.y = m_pos.y - cosf(m_rot.z + D3DX_PI + m_fAngle) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		//右上
		pVtx[1].pos.x = 0.0f + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
		pVtx[1].pos.y = m_pos.y - cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		//左下
		pVtx[2].pos.x = 0.0f + sinf(m_rot.z - m_fAngle) * m_fLength;
		pVtx[2].pos.y = m_pos.y - cosf(m_rot.z - m_fAngle) * m_fLength;
		pVtx[2].pos.z = 0.0f;

		//右下
		pVtx[3].pos.x = 0.0f + sinf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.y = m_pos.y - cosf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.z = 0.0f;

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

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

	m_pVtxBuff->Unlock();
}

