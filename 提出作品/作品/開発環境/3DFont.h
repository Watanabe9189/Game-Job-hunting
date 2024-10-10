#ifndef _3DFONT_H_
#define _3DFONT_H_

#include "main.h"

class C3DFont : public CObject
{
public:

	C3DFont();
	~C3DFont();

	HRESULT Init();
	void Uninit();
	void Draw();

	//<============================================
	//今回使用しないオーバーロードメンバ関数
	//<============================================
	void Update(void) { return; }
	void SetVtx(void) { return; }

	static C3DFont *Create(const char *pName, const D3DXVECTOR3 rPos , 
		const float fZextrusion, const float fMaxdevi, const GLYPHMETRICSFLOAT eGlyph);

private:

	const char*			m_cName;
	float m_fZextrusion;			//負のZ軸への押出量
	float m_fMaxdevi;				//最大僅差


	LPD3DXMESH			m_pMesh;
	D3DXMATRIX			m_mtxWorld;					//ワールドマトリックス

													//ベクトル関連
	D3DXVECTOR3			m_pos;						//位置
	D3DXVECTOR3			m_rot;						//向き
	D3DXVECTOR3			m_move;						//移動量

	LPGLYPHMETRICSFLOAT m_Glyph;
	HDC m_Hdc;
};

#endif
