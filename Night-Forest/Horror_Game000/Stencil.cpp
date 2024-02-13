//<======================================================
//ステンシル処理(Stencil.cpp)
//
//Author:kazuki watanabe
//<======================================================
#include "Stencil.h"
#include "manager.h"

//<=======================================
//ステンシルのコンストラクタ
//<=======================================
CStencil::CStencil()
{
	m_bUse = false;
	m_nStencil = INITIAL_INT;
}
//<=======================================
//ステンシルのデストラクタ
//<=======================================
CStencil::~CStencil()
{

}
//<=======================================
//ステンシルの生成処理
//<=======================================
CStencil *CStencil::Create(const bool bUse, const int nStencil)
{
	CStencil *pStencil = new CStencil;

	assert(pStencil != nullptr);

	//値設定
	pStencil->m_bUse = bUse;
	pStencil->m_nStencil = nStencil;

	pStencil->Init();

	return pStencil;
}
//<=======================================
//ステンシルの初期化処理
//<=======================================
void CStencil::Init()
{
	//ステンシルを使うなら
	if (m_bUse)
	{
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
	}
	//使わないなら
	else
	{
		//ステンシルを使用せずZテストを有効にする
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILENABLE, FALSE);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	}
}
//<=======================================
//ステンシルの終了処理
//<=======================================
void CStencil::Uninit(void)
{
	//ステンシルを使用せずZテストを有効にする
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}
//<=======================================
//ステンシルの終了処理
//<=======================================
void CStencil::Setting(const bool bUse, const int nStencil)
{
	m_bUse = bUse;

	//ステンシルを使うなら
	if (m_bUse)
	{
		m_nStencil = nStencil;
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILENABLE, TRUE);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_NEVER);
	}
	//使わないなら
	else
	{
		m_nStencil = 0;
		//ステンシルを使用せずZテストを有効にする
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILENABLE, FALSE);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	}
}
//<=======================================
//ステンシルの描画処理
//<=======================================
void CStencil::DrawStencilTest(void)
{
	//ステンシルを使うなら
	if (m_bUse)
	{
		//深度テスト設定
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

		//ステンシル参照値の設定
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILREF, m_nStencil);

		//ステンシルマスクの設定
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

		//もし既定値より大きかったら
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATER);

		//ステンシルテストに失敗したら置き換えをする
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_REPLACE);		

		//ステンシルテストに成功し、Zテストに失敗していたらインクリメントをする
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT);	

		//両方に成功していたらインクリメントする
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);	

		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));
	}
}
//<*************************************************************************************************************
//D3DSTENCILOPの内容
//1:D3DSTENCILOP_KEEP		=	何もしない
//2:D3DSTENCILOP_ZERO		=	0にする
//3:D3DSTENCILOP_REPLACE	=	基準値で置き換え
//4:D3DSTENCILOP_INCRSAT	= + 1する（最大値ではそのまま）
//5:D3DSTENCILOP_DECRSAT	= - 1する（最小値ではそのまま）
//6:D3DSTENCILOP_INVERT	=	ビット反転
//7:D3DSTENCILOP_INCR		= + 1する（最大値では0に戻す）
//8:D3DSTENCILOP_DECR		= - 1する（最小値では最大値に戻す）
//<*************************************************************************************************************