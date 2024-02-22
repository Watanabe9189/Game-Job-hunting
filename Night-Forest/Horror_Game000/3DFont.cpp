#include "3DFont.h"
#include "manager.h"

//<==================================
//
//<==================================
C3DFont::C3DFont()
{
	//値のクリア
	m_cName = nullptr;
	m_fMaxdevi = INITIAL_FLOAT;
	m_fZextrusion = INITIAL_FLOAT;
	m_pos = INIT_VECTOR;
	m_rot = INIT_VECTOR;
	m_move = INIT_VECTOR;
	m_Glyph = {};

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	m_pMesh = nullptr;
}
//<==================================
//
//<==================================
C3DFont::~C3DFont()
{

}
//<==================================
//
//<==================================
HRESULT C3DFont::Init()
{
	CManager::GetRenderer()->GetBackBuffer()->GetDC(&m_Hdc);

	//テキストを生成する
	if (D3DXCreateText(CManager::GetRenderer()->GetDevice(),
		m_Hdc,
		m_cName,
		m_fMaxdevi,
		m_fZextrusion,
		&m_pMesh,
		NULL,
		NULL) != D3D_OK)
	{
		return E_FAIL;
	}

	return S_OK;
}
//<==================================
//
//<==================================
void C3DFont::Uninit()
{
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	Release();
}
//<==================================
//
//<==================================
void C3DFont::Draw()
{
	//この関数でしか使わない変数宣言
	D3DXMATRIX			mtxRot = {}, mtxTrans = {};		//計算用マトリックス宣言
	D3DMATERIAL9		matDef = {};					//現在のマテリアル保存用変数

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映する
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映する
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	CManager::GetRenderer()->GetDevice()->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを取得
	CManager::GetRenderer()->GetDevice()->GetMaterial(&matDef);

	//モデルの描画
	m_pMesh->DrawSubset(0);

	//保存していたマテリアルを戻す
	CManager::GetRenderer()->GetDevice()->SetMaterial(&matDef);
}
//<==================================
//
//<==================================
C3DFont *C3DFont::Create(const char *pName, const D3DXVECTOR3 rPos,
	const float fZextrusion, const float fMaxdevi, const GLYPHMETRICSFLOAT eGlyph)
{
	C3DFont *p3DFont = new C3DFont;

	p3DFont->m_cName = pName;
	p3DFont->m_pos = rPos;
	p3DFont->m_fZextrusion = fZextrusion;
	p3DFont->m_fMaxdevi = fMaxdevi;

	p3DFont->Init();

	return p3DFont;
}