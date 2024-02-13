#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "main.h"
#include "XObject.h"

class CBuilding : public CXObject
{
public:

	enum TYPE
	{
		TYPE_CABIN = 0,
		TYPE_TENT,
		TYPE_MAX
	};

	CBuilding();
	~CBuilding();

	//<==========================
	//オーバーロードメンバ関数
	//<==========================
	HRESULT Init(void);
	void Uninit(void) { CXObject::Uninit(); }
	void Update(void);
	void Draw(void) { CXObject::Draw(); }

	static CBuilding *Create(const D3DXVECTOR3 pos,const TYPE eType);
	static CBuilding *ReadCreate(CBuilding *apBuilding[MAX_OBJECT]);
	static CBuilding *RandCreate(CBuilding *apBuilding[MAX_OBJECT], const int nNum);

	D3DXVECTOR3 GetHideRad(void) { return m_rHideRad; }
	static int GetNum(void) { return m_nNumAll; }

private:

	//<==============
	//位置情報関連
	//<==============
	D3DXVECTOR3 m_pos;									//前回の位置
	D3DXVECTOR3 m_rot;										//向き
	D3DXVECTOR3 m_move;										//移動値

	static int m_nNumAll;	//総数


															//<==============
															//マテリアル関連
															//<==============
	LPD3DXMESH			m_pMesh;							//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER		m_pBuffMat;							//マテリアルへのポインタ
	DWORD				m_dwNumMat;							//マテリアルの数
	D3DXMATERIAL*		m_pMat;								//マテリアルデータへのポインタ

													//<==============
													//テクスチャ関連
													//<==============
	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];			//テクスチャへのポインタ
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//ファイル名

															//<=============
															//頂点情報関連
															//<=============
	D3DXVECTOR3			m_vtxMin;					//頂点の最小値
	D3DXVECTOR3			m_vtxMax;					//頂点の最大値

	D3DXVECTOR3 m_rHideRad;

	D3DXVECTOR3 m_rSize;
	D3DXVECTOR3 m_rSizeX;
	D3DXVECTOR3 m_rSizeZ;

	TYPE m_eType;

};

#endif
