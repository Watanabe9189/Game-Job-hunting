//<==============================================
//2Dゲージ処理(2DGauge.ch)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _2DGAUGE_H_
#define _2DGAUGE_H_

#include "main.h"
#include "object.h"

//<****************************************
//クラス定義
//<****************************************
class C2DGauge : public CObject
{
public:

	//<===================================
	//
	//<===================================
	enum VERTEX
	{
		VERTEX_X = 0,
		VERTEX_Y,
		VERTEX_MAX
	};

	//<===================================
	//
	//<===================================
	enum TYPE
	{
		TYPE_BACK = 0,
		TYPE_GAUGE,
		TYPE_FRAME,
		TYPE_MAX
	};
	//<===================================
	//
	//<===================================
	enum MODE
	{
		MODE_ALWAYS = 0,
		MODE_ONLY_USE,
		MODE_MAX
	};

	C2DGauge(int nPriority = FIX_PRIORITY);
	~C2DGauge();

	static C2DGauge *Create(const D3DXVECTOR2 pos,const int nMaxNum,const VERTEX eVer,const MODE eMode);

	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override;
	void Draw(void)		override;
	void SetVtx(void)	override;

	CObject2D *GetObject2D(void)override { return NULL; }

	void Add(const int nValue);
	void SetNum(const int nNum);
	static void SetFixed(const int nFixed) 
	{ m_nFixedMax = nFixed; }
	static int GetFixed(void) { return m_nFixedMax; }
	static int GetLimitMax(void) { return m_nMaxLimit; }
	static int GetLimitMin(void) { return m_nMinLimit; }

private:

	D3DXVECTOR2 m_rPos;					//位置
	D3DXVECTOR2 m_rSize;				//サイズ
	D3DXCOLOR m_rCol;					//色
	static int m_nFixedMax;
	static int m_nMaxLimit;
	static int m_nMinLimit;
	static float m_StaAddValue;
	float m_fAddValue;					//加算する値
	float m_fOldAdd;
	float m_fChange;					//変動量
	float m_fCurrent;					//今のゲージ量
	int m_nNum;							//ゲージ量
	int m_nMax;							//最大ゲージ量
	VERTEX m_eVer;						//方向列挙型
	MODE m_eMode;						//モード列挙型

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファ

};

#endif
