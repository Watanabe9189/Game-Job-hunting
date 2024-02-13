//<==============================================
//3Dオブジェクト専門の処理[Xファイルなし](Object3D.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"

//<******************************************
//3Dオブジェクトのクラス定義
//<******************************************
class CObject3D : public CObject
{
public:

	enum TYPE
	{
		TYPE_PLANE = 0,
		TYPE_PLANE_Y,
		TYPE_MAX


	};

	//<================================
	//コンストラクタ・デストラクタ
	//<================================
	CObject3D(int nPriority = FIX_PRIORITY);
	~CObject3D();

	static CObject3D *Create(const D3DXVECTOR3 rPos = INIT_VECTOR, const D3DXVECTOR3 rSize = INIT_VECTOR, 
		const D3DXVECTOR3 rRot = INIT_VECTOR, const D3DXCOLOR rColor = INIT_COL,const TYPE eType = TYPE::TYPE_PLANE,const LPDIRECT3DTEXTURE9 pTexture = nullptr);



	//<==========================
	//オーバーロードメンバ関数
	//<==========================
	HRESULT Init(void);
	HRESULT InitWith(const D3DXVECTOR3 rPos = INIT_VECTOR, const D3DXVECTOR3 rSize = INIT_VECTOR,
		const D3DXVECTOR3 rRot = INIT_VECTOR, const D3DXCOLOR rColor = INIT_COL, const TYPE eType = TYPE::TYPE_PLANE, const LPDIRECT3DTEXTURE9 pTexture = nullptr);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtx(void);

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture) {m_pTexture = pTexture;}

	//<==========================================
	//Set系のメンバ関数
	//<==========================================
	void SetPosition(const D3DXVECTOR3& pos)		{ m_pos = pos; }			//位置設定
	void SetRotation(const D3DXVECTOR3& rot)		{ m_rot = rot; }			//向き設定
	void SetSize	(const D3DXVECTOR3& Size)		
	{ 
		//サイズの設定
		m_Size = Size; 
	
		//長さと向きの設定
		SetLength(sqrtf(m_Size.x *m_Size.x + m_Size.y * m_Size.y));
		SetAngle(atan2f(m_Size.x, m_Size.y));

	}			//向き設定

	//初期値にさせる
	void SetSizeToZero(void) { m_Size = INIT_VECTOR; }

	void SetColor	(const D3DXCOLOR& rCol)			{ m_rCol = rCol; }			//向き設定

	void SetLength(const float& fLength) { m_fLength = fLength; }	//対角線の長さ設定
	void SetAngle(const float& fAngle) { m_fAngle = fAngle; }		//対角線の向き設定

	void SetDrawfalse(void) { m_bDraw = false; }	//描画のオンオフ
	void SetDrawtrue(void) { m_bDraw = true; }	//描画のオンオフ


	//<==========================================
	//Get系のメンバ関数
	//<==========================================
	CObject2D *GetObject2D(void) { return NULL; }
	CObject3D *GetObject3D(void) { return this; }

	D3DXVECTOR3 GetPosition(void) const { return m_pos; }				//位置取得
	D3DXVECTOR3 GetRotation(void) const { return m_rot; }				//向き取得
	D3DXVECTOR3 GetSize(void) const		{ return m_Size; }				//向き取得
	D3DXCOLOR GetColor(void) const { return m_rCol; }				//位置取得
	float GetAngle(void)const { return m_fAngle; }
	float GetLength(void)const {return m_fLength;}

	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) const { return m_pVtxBuff; }		//頂点バッファの取得

private:

	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファ
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス

	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_rot;					//向き
	D3DXVECTOR3 m_move;					//移動量
	D3DXVECTOR3 m_Size;					//サイズ
	D3DXCOLOR m_rCol;

	TYPE m_eType;

	float m_fAngle;
	float m_fLength;

	bool m_bDraw;
};
#endif