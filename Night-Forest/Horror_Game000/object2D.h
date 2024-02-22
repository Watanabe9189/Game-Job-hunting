//<==============================================
//2Dオブジェクト専門の処理(2DObject.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _2DOBJECT_H_//もしこの名前が別の.hにあったら、以下の処理を実行しない
#define _2DOBJECT_H_

#include "main.h"

//<**********************************************
//2Dオブジェクトのクラス定義(継承)
//<**********************************************
class CObject2D : public CObject
{
public:

	//<=======================================
	//2Dオブジェクトの構造体
	//<=======================================
	struct Object2D
	{

		D3DXVECTOR2 pos;	//位置
		D3DXVECTOR3 rot;	//向き
		D3DXVECTOR2 move;	//移動値
		D3DXVECTOR2 Size;	//サイズ
		D3DXCOLOR Col;		//色
		float fAngle;		//角度
		float fLength;		//長さ


	};

	CObject2D(int nPriority = FIX_PRIORITY);
	~CObject2D();

	//オーバーライドされた関数
	HRESULT Init(void);
	HRESULT InitWith(const D3DXVECTOR2 rPos = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2 rSize = D3DXVECTOR2(0.0f, 0.0f),
		const D3DXCOLOR rColor = INIT_COL, const LPDIRECT3DTEXTURE9 pTexture = nullptr);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObject2D *Create(const D3DXVECTOR2 rPos = D3DXVECTOR2(0.0f, 0.0f), const D3DXVECTOR2 rSize = D3DXVECTOR2(0.0f,0.0f),
		const D3DXCOLOR rColor = INIT_COL,const LPDIRECT3DTEXTURE9 pTexture = nullptr);

	virtual void SetVtx(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) { m_pTexture = pTexture; };

	void SetPosition(const D3DXVECTOR2& pos) { m_aObj.pos = pos; }			//位置設定
	void SetRotation(const D3DXVECTOR3& rot) { m_aObj.rot = rot; }			//向き設定
	void SetMove(const D3DXVECTOR2& move)	{ m_aObj.move = move; }			//移動量設定
	void SetSize(const D3DXVECTOR2& size);									//サイズの設定
	void SetLength(const float& fLength)		{ m_aObj.fLength = fLength; }	//対角線の長さ設定
	void SetAngle(const float& fAngle)		{ m_aObj.fAngle = fAngle; }		//対角線の向き設定
	void SetColor(const D3DXCOLOR& rCol)		{ m_aObj.Col = rCol; }			//色の設定
	void SetDrawfalse(void) { m_bDraw = false; }	//描画のオンオフ
	void SetDrawtrue(void) { m_bDraw = true; }	//描画のオンオフ

	bool GetDraw(void) { return m_bDraw; }

	//<=======================================================
	//メンバ関数(Get系)
	//<=======================================================
	D3DXVECTOR2 GetPosition(void) const { return m_aObj.pos; }		//位置取得
	D3DXVECTOR3 GetRotation(void) const { return m_aObj.rot;}		//向き取得
	D3DXVECTOR2 GetMove(void) const		{ return m_aObj.move; }		//移動量取得
	D3DXVECTOR2 GetSize(void) const		{ return m_aObj.Size; }		//サイズの取得
	float GetLength(void) const			{ return m_aObj.fLength; }	//対角線の長さ取得
	float GetAngle(void) const			{ return m_aObj.fAngle; }	//対角線の向き取得
	D3DXCOLOR GetColor(void) const		{ return m_aObj.Col; }		//色の取得
	CObject2D *GetObject2D(void) { return this; }							//自分自身へのポインタ
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) const { return m_pVtxBuff; }	//頂点バッファの取得
	int GetNumTex(void) {return m_nNumTex; }

private:

	Object2D m_aObj;					//2Dオブジェクトの情報	
	int m_nNumTex;
	bool m_bDraw;

	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファ
};



#endif