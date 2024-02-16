#ifndef _USEFUL_H_
#define _USEFUL_H_

#include "main.h"
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
	static int m_nCounter = 0;
	static bool m_bEnd = false;

	D3DXCOLOR ChangeColInter(const D3DXCOLOR pColor, const float MAX_COLOR, const float MIN_COLOR, const float fValueChange);//変える色・最大色値・最小色値・変更値
	bool Changebool(bool bBool, const BOOL nBool);
}
//<============================================================================================================
//計算関連の名前宣言
//<============================================================================================================
namespace Calculate
{
	D3DXVECTOR3 CalculateDest(const D3DXVECTOR3 rOwnerPos,const D3DXVECTOR3 rTargetPos);
	//<********************************************************************************************
	//ランダム関連の関数
	//<********************************************************************************************
	//fMax = 最大値
	//fMin = 最小値
	//<********************************************************************************************
	float CalculateRandfloat(const float fMax, const float fMin);
	//<********************************************************************************************
	//nMax = 最大値
	//nMin = 最小値
	//<********************************************************************************************
	int CalculeteRandInt(const int nMax, const int nMin);
	//<********************************************************************************************
	//rMax = 最大値
	//rMin = 最小値
	//bUseY= Y座標を使用するか
	//<********************************************************************************************
	D3DXVECTOR3 CalculteRandVec3(const D3DXVECTOR3 rMax, const D3DXVECTOR3 rMin, const bool bUseY);

	float RotateToDest(const float rOwnerRot,const D3DXVECTOR3 fDestRot, const float fRotateValue);
}
//<============================================================================================================
//bool型判定関連の名前宣言
//<============================================================================================================
namespace Bool
{
	bool bMove(const D3DXVECTOR3 rMove);
}
namespace Color
{

	float AlphaChange(const float fOwnerAlpha, const float fAlphaValue);
	D3DXMATERIAL *AlphaChangeMaterial(D3DXMATERIAL *pMat, const float fAlphaValue, const DWORD dwNumMat);

}
#endif
