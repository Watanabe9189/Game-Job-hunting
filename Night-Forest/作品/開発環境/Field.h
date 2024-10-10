//<=====================================================
//地面処理(Field.h)
//
//Author:kazuki watanabe
//<=====================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"

//<*****************************************************
//地面のクラス定義
//<*****************************************************
class CField : public CObject
{
public:

	CField();
	~CField();

	static CField *Create(const D3DXVECTOR3 pos);
	static CField *ReadCreate(CField *apField[MAX_OBJECT]);

	//<==========================
	//オーバーロードメンバ関数
	//<==========================
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetVtx(void);
	void SetIndex(void);

	static int GetNum(void) { return m_nNumAll; }
	static void SetNum(void) { m_nNumAll = 0; }

	//<==========================================
	//Get系のメンバ関数
	//<==========================================
	CObject2D *GetObject2D(void) { return NULL; }
	bool CollisionField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, TYPE_3D Type3D);

private:

	D3DXVECTOR3 m_pos;			//位置
	D3DXVECTOR3 m_rot;			//向き
	D3DXVECTOR3 m_Size;			//サイズ
	D3DXMATRIX m_mtxWorld;		//ワールドマトリックス
	int m_Depth;				//縦
	int m_width;				//横
	int m_nNumIndex;			//インデックス数
	int m_NumVtx;				//頂点数
	static int m_nNumAll;

	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//インデックスバッファへのポインタ

};

#endif
