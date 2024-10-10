//<==============================================
//ビルボード処理(BillB.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _BILLB_H_		//このマクロ定義がされていなかったら
#define _BILLB_H_		//二重インクルード防止のマクロを定義する

#include "main.h"

//<********************************************
//ビルボードのクラス定義
//<********************************************
class CBillB : public CObject
{
public:

	CBillB(int nPriority = FIX_PRIORITY);
	~CBillB();

	HRESULT Init(void);
	HRESULT InitWith(const D3DXVECTOR3 rPos = INIT_VECTOR, const D3DXVECTOR2 rSize = D3DXVECTOR2(0.0f, 0.0f),
		const D3DXCOLOR rColor = INIT_COL, const LPDIRECT3DTEXTURE9 pTex = nullptr);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtx(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; }

	static CBillB *Create(const D3DXVECTOR3 rPos = INIT_VECTOR, const D3DXVECTOR2 rSize = D3DXVECTOR2(0.0f, 0.0f),
		const D3DXCOLOR rColor = INIT_COL, const LPDIRECT3DTEXTURE9 pTex = nullptr);

	//<==========================================
	//使わないオ－バーロードメンバ関数
	//<==========================================
	CObject2D *GetObject2D(void) { return NULL; }

	void SetVector3(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXVECTOR3& Size);

	void SetColor(const D3DXCOLOR& col)		{ m_col = col; }

	void SetDrawfalse(void) { m_bDraw = false; }	//描画のオンオフ
	void SetDrawtrue(void) { m_bDraw = true; }	//描画のオンオフ

	D3DXVECTOR3 GetPos(void) const			{ return m_pos; }			//位置取得
	D3DXVECTOR3 GetSize(void) const			{ return m_Size; }			//向き取得
	D3DXVECTOR3 GetMove(void) const			{ return m_move; }			//移動量取得
	D3DXCOLOR GetColor(void)const			{ return m_col; }			//色取得
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) const { return m_pVtxBuff; }	//頂点バッファの取得

private:

	LPDIRECT3DTEXTURE9	m_pTexture;	//テクスチャ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;	//頂点バッファ


	D3DXVECTOR3					m_pos;		//位置
	D3DXVECTOR3					m_move;		//移動量
	D3DXVECTOR3					m_Size;		//サイズ
	D3DXCOLOR					m_col;		//色
	D3DXMATRIX					m_mtxWorld;	//ワールドマトリックス
	D3DXMATRIX					m_mtxview;	//マトリックスビュー
		
	bool m_bDraw;

};

#endif
