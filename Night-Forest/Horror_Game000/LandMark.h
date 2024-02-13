#ifndef _LANDMARK_H_
#define _LANDMARK_H_

#include "XObject.h"
#include "BillBIcon.h"

//<************************************************
//
//<************************************************
class CLandMark :public CXObject
{
public:

	//<****************************************
	//種類別の列挙型
	//<****************************************
	enum TYPE
	{
		TYPE_FIRST = 0,
		TYPE_SECOND,
		TYPE_THIRD,
		TYPE_FOURTH,
		TYPE_MAX
	};

	CLandMark(int nPriority = FIX_PRIORITY);
	~CLandMark();

	//<==========================
	//オーバーロードメンバ関数
	//<==========================
	HRESULT Init(void);
	void Uninit(void) 
	{ 
		CXObject::Uninit();
	
		//もし中身があれば
		if (m_pBillBIcon != nullptr)
		{
			//表示させる
			m_pBillBIcon->Uninit();
			m_pBillBIcon = nullptr;
		}

	}
	void Update(void);
	void Draw(void) { CXObject::Draw(); }

	static CLandMark *FixedCreate(CLandMark *apLandMark[MAX_OBJECT]);
	static int GetNum(void) { return m_nNumAll; }

private:

	void Collid(void);

	//<==============
	//位置情報関連
	//<==============
	D3DXVECTOR3 m_pos;										//位置
	D3DXVECTOR3 m_posOld;									//前回の位置
	D3DXVECTOR3 m_rot;										//向き
	D3DXVECTOR3 m_move;										//移動値


															//<==============
															//マテリアル関連
															//<==============
	LPD3DXMESH	m_pMesh;							//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER	m_pBuffMat;							//マテリアルへのポインタ
	DWORD		m_dwNumMat;							//マテリアルの数
	D3DXMATERIAL	*m_pMat;							//マテリアルデータへのポインタ

	//<==============
	//テクスチャ関連
	//<==============
	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//テクスチャへのポインタ
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//ファイル名
	static int m_nNumAll;	//総数
	//<=============
	//頂点情報関連
	//<=============
	D3DXVECTOR3			m_vtxMin;					//頂点の最小値
	D3DXVECTOR3			m_vtxMax;					//頂点の最大値

	TYPE m_eType;

	D3DXVECTOR3 m_rSize;
	D3DXVECTOR3 m_rSizeX;
	D3DXVECTOR3 m_rSizeZ;

	CBilBIcon *m_pBillBIcon;

};
#endif
