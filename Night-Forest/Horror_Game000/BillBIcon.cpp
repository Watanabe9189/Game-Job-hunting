//<==============================================
//ビルボードアイコン処理(BillB.h)
//
//Author:kazuki watanabe
//<==============================================
#include "BillBIcon.h"
#include "Texture.h"
#include "manager.h"

LPDIRECT3DTEXTURE9 CBilBIcon::m_apTexture[BICON_MAX] = {};

//ファイル名指定
const char			*CBilBIcon::m_acFilename[BICON_MAX] =
{
	"data/TEXTURE/Explain001.png",		//説明
	"data/TEXTURE/Memo/Memo000.png",	//メモ１
	"data/TEXTURE/Memo/Memo001.png",	//メモ２
	"data/TEXTURE/Memo/Memo002.png"		//メモ３
};
int CBilBIcon::m_nNumAll = INITIAL_INT;
//<======================================================================
//コンストラクタ
//<======================================================================
CBilBIcon::CBilBIcon(int nPriority)
{
	m_nNumAll++;
	//値のクリア
	m_pos = INIT_VECTOR;
	m_Size = INIT_VECTOR;

	m_nIcon = BICON_MAX;
}
//<======================================================================
//デストラクタ
//<======================================================================
CBilBIcon::~CBilBIcon()
{
	m_nNumAll--;
}
//<======================================================================
//生成処理
//<======================================================================
CBilBIcon *CBilBIcon::Create(const D3DXVECTOR3 pos,const int nIcon)
{
	//インスタンス生成用のオブジェクト
	CBilBIcon *pBilBIcon = new CBilBIcon;

	//しっかりメモリ確保されたかのチェック
	assert(pBilBIcon != nullptr);

	//Vector3の要素の設定
	pBilBIcon->SetVector3(pos, {}, pBilBIcon->m_Size);

	//表示させる文字の設定
	pBilBIcon->m_nIcon = nIcon;

	//初期化がしっかりされたかチェック
	assert(SUCCEEDED(pBilBIcon->Init()));

	return pBilBIcon;
}
//<======================================================================
//初期化処理
//<======================================================================
HRESULT CBilBIcon::Init(void)
{		
	//初期化しておく
	m_Size = D3DXVECTOR3(25.0f, 25.0f, 25.0f);

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

	assert(SUCCEEDED(CBillB::InitWith(GetPos(), D3DXVECTOR2(m_Size.x, m_Size.y),INIT_COL, m_apTexture[m_nIcon])));

	return S_OK;
}
//<======================================================================
//更新処理
//<======================================================================
void CBilBIcon::Update(void)
{
	CBillB::SetVtx();

	m_pos = GetPos();

	SetVector3(m_pos, {}, m_Size);
}