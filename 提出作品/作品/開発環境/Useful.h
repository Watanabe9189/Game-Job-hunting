//<================================================
//汎用関数処理(Useful.h)
//
//Author:kazuki watanabe
//<================================================
#ifndef _USEFUL_H_
#define _USEFUL_H_

#include "main.h"

//<************************************************************************************************************
//名前宣言(色変更関連)
//<************************************************************************************************************
namespace InitChangerCol
{
	static const D3DXCOLOR	COLOR_INIT	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
	static const float		MIN_INIT	= 0.3f;
	static const float		CHANGE_INIT = 0.03f;
	static const int		INTER_MAX	= 200;
}
//<============================================================================================================
//コリジョン(当たり判定)関連の名前宣言
//<============================================================================================================
namespace Collision
{
	//<*****************************************************************************************************
	//引数
	//rOwnerPos				= 所持者の位置
	//rOwnerSizeX			= 所持者のサイズX
	//rOwnerSizeZ			= 所持者のサイズZ
	//rOwnerVtxMax			= 所持者の頂点最大値
	//rOwnerVtxMin			= 所持者の頂点最小値
	//rTargetPos			= 対象となるオブジェクトの位置
	//rTargetPosOld			= 対象となるオブジェクトの過去位置
	//rTargetMove			= 対象となるオブジェクトの移動値
	//rTargetVtxMax			= 対象となるオブジェクトの頂点最大値
	//rTargetVtxMin			= 対象となるオブジェクトの頂点最小値
	//bDecay				= 減衰するかどうか
	//<*****************************************************************************************************
	void CollidXZ(const D3DXVECTOR3 rOwnerPos, const D3DXVECTOR3 rOwnerSizeX, const D3DXVECTOR3 rOwnerSizeZ,
		const D3DXVECTOR3 rOwnerVtxMax, const D3DXVECTOR3 rOwnerVtxMin,
		D3DXVECTOR3 *rTargetPos, const D3DXVECTOR3 rTargetPosOld, D3DXVECTOR3 *rTargetMove
		, const D3DXVECTOR3 rTargetVtxMax, const D3DXVECTOR3 rTargetVtxMin, const bool bDecay = true);

	//<*****************************************************************************************************
	//引数
	//rTargetPos			= 対象となるオブジェクトの位置
	//rOwnerSizeX			= 対象となるオブジェクトのサイズX
	//rOwnerSizeZ			= 対象となるオブジェクトのサイズZ
	//rTargetVtxMax			= 対象となるオブジェクトの頂点最大値
	//rTargetVtxMin			= 対象となるオブジェクトの頂点最小値
	//rOwnerPos				= 所持者の位置
	//rOwnerVtxMax			= 所持者の頂点最大値
	//rOwnerVtxMin			= 所持者の頂点最小値
	//<*****************************************************************************************************
	bool OnlyCollid(const D3DXVECTOR3 rTargetPos, const D3DXVECTOR3 rTargetSizeX, const D3DXVECTOR3 rTargetSizeZ,
		const D3DXVECTOR3 rTargetVtxMax, const D3DXVECTOR3 rTargetVtxMin, 
		const D3DXVECTOR3 rOwnerPos,const D3DXVECTOR3 rOwnerVtxMax, const D3DXVECTOR3 rOwnerVtxMin);


	//<*****************************************************************************************************
	//引数
	//rOwnerPos				= 所持者の位置
	//rOwnerSize			= 所持者のサイズ
	//rTargetPos			= 対象となるオブジェクトの位置
	//rTargetVtxMax			= 対象となるオブジェクトの頂点最大値
	//rTargetVtxMin			= 対象となるオブジェクトの頂点最小値
	//<*****************************************************************************************************
	bool CollidAll(const D3DXVECTOR3 rOwnerPos,const D3DXVECTOR3 rOwnerSize, const D3DXVECTOR3 rTargetPos, 
					const D3DXVECTOR3 rTargetVtxMax, const D3DXVECTOR3 rTargetVtxMin);
}
//<============================================================================================================
//補正関連の名前宣言
//<============================================================================================================
namespace Correction
{
	float NormalizeRotation(const float fRotY);
	D3DXVECTOR3 LimitPos(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rLimitPos, const bool bBoolX, const bool bBoolY, const bool bBoolZ);
}
//<============================================================================================================
//変更関連の名前宣言
//<============================================================================================================
namespace Change
{
	bool Changebool(bool bBool, const BOOL nBool);
}
//<============================================================================================================
//計算関連の名前宣言
//<============================================================================================================
namespace Calculate
{
	//<インライン関数>
	//目的地計算関数
	inline D3DXVECTOR3 CalculateDest(const D3DXVECTOR3 rOwnerPos, const D3DXVECTOR3 rTargetPos)
	{
		D3DXVECTOR3 rCalPos = INIT_VECTOR;	//計算用位置

		rCalPos.x = rOwnerPos.x - rTargetPos.x;	//X座標
		rCalPos.y = rOwnerPos.y - rTargetPos.y;	//Y座標
		rCalPos.z = rOwnerPos.z - rTargetPos.z;	//Z座標

		return rCalPos;
	}

	//<********************************************************************************************
	//ランダム関連の関数
	//<********************************************************************************************
	//fMax = 最大値
	//fMin = 最小値
	//<********************************************************************************************
	inline float CalculateRandfloat(const float fMax, const float fMin)
	{
		return fMin + (int)(rand() * (fMax - fMin + 1.0) / (1.0 + RAND_MAX));
	}
	//<********************************************************************************************
	//nMax = 最大値
	//nMin = 最小値
	//<********************************************************************************************
	inline int CalculeteRandInt(const int nMax, const int nMin)
	{
		return nMin + (int)(rand() * (nMax - nMin + 1.0) / (1.0 + RAND_MAX));
	}
	//<********************************************************************************************
	//rMax = 最大値
	//rMin = 最小値
	//bUseY= Y座標を使用するか
	//<********************************************************************************************
	inline D3DXVECTOR3 CalculteRandVec3(const D3DXVECTOR3 rMax, const D3DXVECTOR3 rMin, const bool bUseY)
	{
		D3DXVECTOR3 rVec3 = INIT_VECTOR;

		//Y座標を使うなら
		if (bUseY)
		{
			//それぞれの位置を設定する
			rVec3.x = rMin.x + (int)(rand() * (rMax.x - rMin.x + 1.0) / (1.0 + RAND_MAX));
			rVec3.y = rMin.y + (int)(rand() * (rMax.y - rMin.y + 1.0) / (1.0 + RAND_MAX));
			rVec3.z = rMin.x + (int)(rand() * (rMax.z - rMin.z + 1.0) / (1.0 + RAND_MAX));
		}
		//使わないなら
		else
		{
			//それぞれの位置を設定する
			rVec3.x = rMin.x + (int)(rand() * (rMax.x - rMin.x + 1.0) / (1.0 + RAND_MAX));
			rVec3.z = rMin.x + (int)(rand() * (rMax.z - rMin.z + 1.0) / (1.0 + RAND_MAX));
		}

		return rVec3;
	}

	//その方向へ向く関数
	inline float RotateToDest(const float rOwnerRot, const D3DXVECTOR3 fDestRot, const float fRotateValue)
	{
		float fRot = rOwnerRot;		//向き
		float fRotDest = INITIAL_FLOAT;	//目的向き
		float fRotDiff = INITIAL_FLOAT;	//向き

										//角度設定
		fRotDest = atan2f((fDestRot.x), (fDestRot.z));
		fRotDiff = fRotDest - fRot;

		//プレイヤーのいる位置に向く
		return fRot += fRotDiff * fRotateValue;
	}
}
//<============================================================================================================
//bool型判定関連の名前宣言
//<============================================================================================================
namespace Bool
{
	bool bMove(const D3DXVECTOR3 rMove);
	bool bApproach(const D3DXVECTOR3 rDis,const float fDisValue);
}
//<============================================================================================================
//bool型判定関連の名前宣言
//<============================================================================================================
namespace Color
{

	float AlphaChange(const float fOwnerAlpha, const float fAlphaValue);
	D3DXMATERIAL *AlphaChangeMaterial(D3DXMATERIAL *pMat, const float fAlphaValue, const DWORD dwNumMat);

}
//<============================================================================================================
//色変更関連のクラス宣言
//<============================================================================================================
class ChangeCol
{
public:

	ChangeCol();
	~ChangeCol();

	static ChangeCol* Create(const D3DXCOLOR pColor= InitChangerCol::COLOR_INIT, const float MAX_COLOR = INIT_COL.a,
		const float MIN_COLOR= InitChangerCol::MIN_INIT, const float fValueChange = InitChangerCol::CHANGE_INIT,
		const int nInter = InitChangerCol::INTER_MAX);

	void ChangeColAdd(void);

	inline D3DXCOLOR GetColor(void) { return m_rCol; }
	inline float GetMaxAlpha(void) { return m_fMaxAlpha; }
	inline float GetMinAlpha(void) { return m_fMinAlpha; }

	inline void SetColor(const D3DXCOLOR rCol) 
	{ 
		//その色の値にする
		m_rCol = rCol; 
	
		//最大値に到達していたら
		if (m_rCol.a >= INIT_COL.a) 
		{ 
			m_rCol.a = INIT_COL.a;
			m_bEnd = true; 
		
		}
		//最小値に到達していたら
		else if (m_rCol.a <= m_fMinAlpha)
		{
			m_rCol.a = m_fMinAlpha;
			m_bEnd = false;
		}
	
	}


private:

	D3DXCOLOR m_rCol;			//色
	float m_fMaxAlpha;			//透明度の最大値
	float m_fMinAlpha;			//透明度の最小値
	float m_fChangeValue;		//変更値
	int m_nInter;				//インターバル
	int m_nCounter;				//カウンター
	bool m_bEnd;				//色変えが終了しているかどうか

};

//<********************************************
//メモとして(About:Inline)
//あまり長い関数に使うのは控えたほうがいい
//<********************************************
#endif
