//<==============================================
//2D文字処理(2DChar.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _2DCHAR_H_
#define _2DCHAR_H_

#include "object2D.h"

//<**********************************************
//
//<**********************************************
class C2DChar : public CObject2D
{
public:

	//<*****************************************
	//文字タイプ
	//<*****************************************
	enum CHAR_TYPE
	{
		CHAR_TYPE_TITLE = 0,			//目的
		CHAR_TYPE_HIDEINFO,				//
		CHAR_TYPE_PICKUP_INFO,
		CHAR_TYPE_COMEOUT_INFO,
		CHAR_TYPE_MAX
	};
	//<*****************************************
	//どこから移動してくるかの列挙型
	//<*****************************************
	enum MOVE_FROM
	{
		MOVE_FROM_NONE = 0,
		MOVE_FROM_UP,
		MOVE_FROM_DOWN,
		MOVE_FROM_RIGHT,
		MOVE_FROM_LEFT,
		MOVE_FROM_MAX

	};

	C2DChar(int nPriority = FIX_PRIORITY);
	~C2DChar();

	static C2DChar *Create(const D3DXVECTOR2 pos = D3DXVECTOR2(0.0f,0.0f),
		const D3DXVECTOR2 Size = D3DXVECTOR2(0.0f, 0.0f), const int CType = CHAR_TYPE::CHAR_TYPE_MAX, 
		const MOVE_FROM eMoveFrom = MOVE_FROM_NONE,const bool bDisp = true);

	HRESULT Init(void);
	void Uninit(void) {CObject2D::Uninit();}
	void Update(void);
	void Draw(void) 
	{
		if (m_bDisp != false)
		{
			CObject2D::Draw();
		}
	}
	void SetVtx(void);
	static int GetNum(void) { return m_nNumAll; }

	void SetDispfalse (void) { m_bDisp = false; }
	void SetDisptrue(void) { m_bDisp = true; }

private:

#define MAX_DEST	(2)

	void MoveSide(void);
	void MoveVer(void);

	static LPDIRECT3DTEXTURE9 m_apTexture[INT_VALUE::MAX_TEX];

	static const char*			m_acFilename[CHAR_TYPE::CHAR_TYPE_MAX];				//ファイル名

	static int m_nNumAll;

	D3DXVECTOR2 m_pos;
	D3DXVECTOR2 m_posDest[MAX_DEST];
	D3DXVECTOR2 m_Size;

	int m_eCType;
	int m_nLiveTime;
	bool m_bDisp;
	bool m_bArrived;

	MOVE_FROM m_eFromMove;

};

#endif