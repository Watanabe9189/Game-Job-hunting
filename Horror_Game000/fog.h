#ifndef _FOG_H_
#define _FOG_H_

#include "main.h"
#include "object.h"
#include "manager.h"

class CFog : public CObject
{
public:

	enum TYPE
	{
		TYPE_VERTEX = 0,		//頂点フォグ
		TYPE_PIXEL,			//ピクセルフォグ
		TYPE_NONE,			//なし
		TYPE_MAX

	};

	//コンストラクタ・デストラクタ
	CFog(int nPriority = FIX_PRIORITY);
	~CFog();

	//生成関数
	static CFog *Create(const D3DXCOLOR Col,const D3DFOGMODE Mode,const TYPE Type,const float fDensity);

	//オーバーライドされた関数
	HRESULT Init(void);
	void Uninit(void) 
	{ 
		//霧のブレンドを無効にする
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

		Release(); 
	};
	void Update(void);
	void Draw(void) {};

	//<===========================================
	//不要関数
	//<===========================================
	void SetVtx(void) { return; }
	CObject2D *GetObject2D(void) { return NULL; }

	void SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange);
	void SetupPixelFog(DWORD Mode);

private:

	D3DXCOLOR m_Col;
	TYPE m_Type;
	D3DFOGMODE m_dMode;

	float m_fStart;
	float m_fEnd;
	float m_fDensity;

};

#endif