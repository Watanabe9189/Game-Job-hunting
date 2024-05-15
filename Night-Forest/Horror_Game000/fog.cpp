//<==================================
//霧処理(fog.cpp)
//
//Author:kazuki watanabe
//<==================================
#include "fog.h"
#include "manager.h"

//<********************************************************
//名前宣言
//<********************************************************
namespace Fog
{
	const float MAX_START = 0.0f;		//開始地の最大値
	const float MAX_END = 5000.0f;		//終了値の最大値
	const float MAX_DENSITY = 0.002f;	//霧深度の最大値
}

//<========================================================
//コンストラクタ
//<========================================================
CFog::CFog(int nPriority)
{
	//値の初期化
	m_Col = INIT_COL;
	m_Type = TYPE::TYPE_NONE;
	m_dMode = D3DFOG_NONE;
	m_fStart = INITIAL_FLOAT;
	m_fEnd = INITIAL_FLOAT;
	m_fDensity = INITIAL_FLOAT;
	m_bUse = true;

}
//<========================================================
//デストラクタ
//<========================================================
CFog::~CFog()
{

}
//<========================================================
//生成処理
//<========================================================
CFog *CFog::Create(const D3DXCOLOR Col, const D3DFOGMODE Mode,
	const TYPE Type, const float fDensity)
{
	CFog *pFog = new CFog;

	assert(pFog );

	assert(SUCCEEDED(pFog->Init()));

	pFog->m_Col = Col;
	pFog->m_dMode = Mode;
	pFog->m_Type = Type;
	pFog->m_fDensity = fDensity;

	return pFog;
}
//<========================================================
//初期化処理
//<========================================================
HRESULT CFog::Init(void)
{
	//設定
	m_fStart = Fog::MAX_START;
	m_fEnd = Fog::MAX_END;

	return S_OK;
}
//<========================================================
//更新処理
//<========================================================
void CFog::Update(void)
{
	//使う場合
	if (m_bUse)
	{
		//頂点霧場合
		if (m_Type == TYPE::TYPE_VERTEX)
		{
			SetupVertexFog(m_Col, m_Type, FALSE);//頂点フォグの設定
		}
		//使わない場合
		else if (m_Type == TYPE::TYPE_PIXEL)
		{
			SetupPixelFog(m_Type);//ピクセルフォグの設定
		}
	}
	//霧を使わない場合
	else
	{
		//霧のブレンドを無効にする
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);
	}
}
//<===========================================
//頂点フォグの設定
//<===========================================
void CFog::SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange)
{
	//霧のブレンドを有効にする
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//色を設定
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGCOLOR, Color);
	
	//霧のパラメーターを設定
	//もし線形霧モードだったら
	if (Mode == D3DFOG_LINEAR)
	{
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&m_fStart));
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&m_fEnd));
	}
	//そのほか
	else
	{
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGVERTEXMODE, Mode);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGDENSITY, *(DWORD *)(&m_fDensity));

		//霧密度は0.0fから1.0fの範囲で設定する
	}

	//頂点フォグだけでサポートされている場合はその範囲のフォグを有効にする
	//このUseRangeが0以外の場合、
	if (UseRange != FALSE)
	{
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);
	}
}
//<===========================================
//ピクセルフォグの設定
//<===========================================
void CFog::SetupPixelFog(DWORD Mode)
{
	//霧のブレンドを有効にする
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//色を設定
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGCOLOR, m_Col);

	//もし線形霧モードだったら
	if (Mode == D3DFOG_LINEAR)
	{//線形霧のパラメータを設定する

		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGTABLEMODE, Mode);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGSTART, *(DWORD *)(&m_fStart));
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGEND, *(DWORD *)(&m_fEnd));
	}
	//そのほか
	else
	{
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGTABLEMODE, Mode);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGDENSITY, *(DWORD *)(&m_fDensity));
	}

}