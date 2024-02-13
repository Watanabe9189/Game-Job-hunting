#include "Useful.h"

//<================================================
//
//<================================================
float Correction::NormalizeRotation(const float fRotY)
{
	//計算用変数
	float fRot = fRotY;

	//<*******************
	//Y軸の補正
	//<*******************
	if (fRot > D3DX_PI)
	{
		fRot = -D3DX_PI;
	}
	//半円を下回っていたら
	else if (fRot < -D3DX_PI)
	{
		fRot = D3DX_PI;
	}
	return fRot;
}
//<================================================
//位置の限界値
//<================================================
D3DXVECTOR3 Correction::LimitPos(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rLimitPos, const bool bBoolX, const bool bBoolY, const bool bBoolZ)
{
	//計算用位置
	D3DXVECTOR3 rCalculatePos = rPos;

	//X軸を判定する場合
	if (bBoolX)
	{
		//X軸の位置が限界範囲を超えそうになったら
		if (rCalculatePos.x >= rLimitPos.x)
		{
			//その位置にする
			rCalculatePos.x = rLimitPos.x;
		}
		//X軸の位置がマイナス限界範囲を超えそうになったら
		else if (rCalculatePos.x <= -rLimitPos.x)
		{
			//その位置にする
			rCalculatePos.x = -rLimitPos.x;
		}
	}
	//Y軸を判定する場合
	if (bBoolY)
	{
		//X軸の位置が限界範囲を超えそうになったら
		if (rCalculatePos.y >= rLimitPos.y)
		{
			//その位置にする
			rCalculatePos.y = rLimitPos.y;
		}
		//X軸の位置がマイナス限界範囲を超えそうになったら
		else if (rCalculatePos.y <= -rLimitPos.y)
		{
			//その位置にする
			rCalculatePos.y = -rLimitPos.y;
		}
	}
	//Z軸を判定する場合
	if (bBoolZ)
	{
		//Z軸の位置が限界範囲を超えそうになったら
		if (rCalculatePos.z >= rLimitPos.z)
		{
			//その位置にする
			rCalculatePos.z = rLimitPos.z;
		}
		//Z軸の位置がマイナス限界範囲を超えそうになったら
		else if (rCalculatePos.z <= -rLimitPos.z)
		{
			//その位置にする
			rCalculatePos.z = -rLimitPos.z;
		}

	}

	//値を返す
	return rCalculatePos;
}
//<================================================
//
//<================================================
D3DXCOLOR Change::ChangeColInter(const D3DXCOLOR pColor, const float MAX_COLOR, const float MIN_COLOR, const float fValueChange)
{
	//値を返す用の色変数
	D3DXCOLOR rCol = pColor;

	//最大色まで言っていたら
	if (rCol.a >= MAX_COLOR&&m_bEnd)
	{
		m_nCounter = 0;
		m_bEnd = false;
	}

	//もし色チェンジが終わっていなければ
	if (!m_bEnd)
	{
		//最小値の色まで行っていたら
		if (rCol.a <= MIN_COLOR)
		{
			//最小値の色にする
			rCol.a = MIN_COLOR;

			//カウンターが最大値まで行っていたら
			if (m_nCounter >= 100)
			{
				m_nCounter = 0;
				m_bEnd = true;
			}
			//行っていなかったら
			else
			{
				//加算する
				m_nCounter++;
			}
		}
		//まだ最小値まで行っていなければ
		else
		{
			//減算する
			rCol.a -= fValueChange;
		}
	}
	//終わっていれば
	else
	{
		//最大色まで行っていたら
		if (rCol.a >= MAX_COLOR)
		{
			//その値にする
			rCol.a = MAX_COLOR;

			//最大カウンターまで行っていたら
			if (m_nCounter >= 100)
			{
				m_nCounter = 0;
				m_bEnd = false;
			}
			//行っていなかったら
			else
			{
				//加算する
				m_nCounter++;
			}

		}
		//その色まで行っていなかったら
		else
		{
			//色を加算する
			rCol.a += fValueChange;
		}
	}
	return rCol;
}
//<==========================================
//bool型の変更処理
//<==========================================
bool Change::Changebool(bool bBool, const BOOL nBool)
{
	bool bUse = bBool;

	//使う状態なら
	if (nBool == TRUE)
	{
		bUse = true;
	}
	else if (nBool == FALSE)
	{
		bUse = false;
	}

	return bUse;
}
//<==========================================
//bool型の変更処理
//<==========================================
D3DXVECTOR3 Calculate::CalculateDest(const D3DXVECTOR3 rOwnerPos, const D3DXVECTOR3 rTargetPos)
{
	D3DXVECTOR3 rCalPos = INIT_VECTOR;	//計算用位置

	rCalPos.x = rOwnerPos.x - rTargetPos.x;	//X座標
	rCalPos.y = rOwnerPos.y - rTargetPos.y;	//Y座標
	rCalPos.z = rOwnerPos.z - rTargetPos.z;	//Z座標

	return rCalPos;
}
//<==========================================
//bool型の変更処理
//<==========================================
float Calculate::CalculateRandfloat(const float fMax, const float fMin)
{
	//計算用の変数
	float fRand = INITIAL_FLOAT;

	fRand = fMin + (int)(rand() * (fMax - fMin + 1.0) / (1.0 + RAND_MAX));
	
	return fRand;
}
//<==========================================
//bool型の変更処理
//<==========================================
int Calculate::CalculeteRandInt(const int nMax, const int nMin)
{
	//計算用の変数
	int nRand = INITIAL_INT;

	nRand = nMin + (int)(rand() * (nMax - nMin + 1.0) / (1.0 + RAND_MAX));

	return nRand;
}
//<==========================================
//bool型の変更処理
//<==========================================
D3DXVECTOR3 Calculate::CalculteRandVec3(const D3DXVECTOR3 rMax, const D3DXVECTOR3 rMin, const bool bUseY)
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
//<==========================================
//bool型の変更処理
//<==========================================
bool Bool::bMove(const D3DXVECTOR3 rMove)
{
	bool bMove = false;	//判定用

	//どの軸でも動いていれば
	if (rMove.x != 0.0f ||rMove.x != -0.0f
		&&rMove.y != 0.0f ||rMove.y != -0.0f
		&& rMove.z != 0.0f ||rMove.z != -0.0f)
	{
		bMove = true;
	}

	return bMove;
}
//<==========================================
//bool型の変更処理
//<==========================================
void Collision::CollidXZ(const D3DXVECTOR3 rOwnerPos, const D3DXVECTOR3 rOwnerSizeX, const D3DXVECTOR3 rOwnerSizeZ,
	const D3DXVECTOR3 rOwnerVtxMax, const D3DXVECTOR3 rOwnerVtxMin,
	D3DXVECTOR3 *rTargetPos,const D3DXVECTOR3 rTargetPosOld,D3DXVECTOR3 *rTargetMove
	, const D3DXVECTOR3 rTargetVtxMax, const D3DXVECTOR3 rTargetVtxMin, const bool bDecay)
{
	//<**********************************************
	//左右判定
	//<**********************************************
	if (rOwnerPos.z + rOwnerSizeX.z > rTargetPos->z + rTargetVtxMin.z&&
		rOwnerPos.z - rOwnerSizeX.z < rTargetPos->z + rTargetVtxMax.z)
	{
		//左側に当たっていたら
		if (rOwnerPos.x + rOwnerVtxMax.x >= rTargetPosOld.x + rTargetVtxMin.x
			&& rOwnerPos.x - rOwnerSizeX.x< rTargetPos->x - rTargetVtxMax.x)
		{
			//オブジェクトの右側に位置を補正
			rTargetPos->x = rOwnerPos.x - rOwnerSizeX.x + rTargetVtxMax.x;
			if (bDecay) { rTargetMove->x = 0.0f; }
		}
		//右側に当たっていたら
		else if (rOwnerPos.x + rOwnerVtxMax.x <= rTargetPosOld.x + rTargetVtxMin.x
			&& rOwnerPos.x + rOwnerSizeX.x > rTargetPos->x + rTargetVtxMax.x)
		{
			//オブジェクトの左側に位置を補正
			rTargetPos->x = rOwnerPos.x + rOwnerSizeX.x - rTargetVtxMax.x;
			if (bDecay) { rTargetMove->x = 0.0f; }
		}
	}
	//<**********************************************
	//左右判定
	//<**********************************************
	if (rOwnerPos.x + rOwnerSizeZ.x >= rTargetPos->x + rTargetVtxMin.x&&
		rOwnerPos.x - rOwnerSizeZ.x <= rTargetPos->x + rTargetVtxMax.x)
	{
		//左側に当たっていたら
		if (rOwnerPos.z + rOwnerVtxMax.z >= rTargetPosOld.z + rTargetVtxMin.z
			&& rOwnerPos.z - rOwnerSizeZ.z< rTargetPos->z - rTargetVtxMax.z)
		{
			//オブジェクトの右側に位置を補正
			rTargetPos->z = rOwnerPos.z - rOwnerSizeZ.z + rTargetVtxMax.z;
			if (bDecay) { rTargetMove->z = 0.0f; }
		}
		//右側に当たっていたら
		else if (rOwnerPos.z + rOwnerVtxMax.z <= rTargetPosOld.z + rTargetVtxMin.z
			&& rOwnerPos.z + rOwnerSizeZ.z > rTargetPos->z + rTargetVtxMax.z)
		{
			//オブジェクトの左側に位置を補正
			rTargetPos->z = rOwnerPos.z + rOwnerSizeZ.z - rTargetVtxMax.z;
			if (bDecay) { rTargetMove->z = 0.0f; }
		}
	}
}
//<==========================================
//bool型の変更処理
//<==========================================
bool Collision::OnlyCollid(const D3DXVECTOR3 rTargetPos, const D3DXVECTOR3 rTargetSizeX, const D3DXVECTOR3 rTargetSizeZ,
	const D3DXVECTOR3 rTargetVtxMax, const D3DXVECTOR3 rTargetVtxMin,
	const D3DXVECTOR3 rOwnerPos, const D3DXVECTOR3 rOwnerVtxMax, const D3DXVECTOR3 rOwnerVtxMin)
{
	bool bHit = false;

	//<**********************************************
	//左右判定
	//<**********************************************
	if (rTargetPos.z + rTargetSizeZ.x >= rOwnerPos.z + rOwnerVtxMin.z&&
		rTargetPos.z - rTargetSizeZ.x <= rOwnerPos.z + rOwnerVtxMax.z)
	{
		//左側に当たっていたら
		if (rTargetPos.x + rTargetVtxMax.x >= rOwnerPos.x + rOwnerVtxMin.x
			&& rTargetPos.x - rTargetSizeX.x < rOwnerPos.x - rOwnerVtxMax.x)
		{
			bHit = true;
		}
		//右側に当たっていたら
		else if (rTargetPos.x + rTargetVtxMax.x <= rOwnerPos.x + rOwnerVtxMin.x
			&& rTargetPos.x + rTargetSizeX.x > rOwnerPos.x + rOwnerVtxMax.x)
		{
			bHit = true;
		}
	}
	//<**********************************************
	//左右判定
	//<**********************************************
	if (rTargetPos.x + rTargetSizeX.z >= rOwnerPos.x + rOwnerVtxMin.x&&
		rTargetPos.x - rTargetSizeX.z <= rOwnerPos.x + rOwnerVtxMax.x)
	{
		//左側に当たっていたら
		if (rTargetPos.z + rTargetVtxMax.z >= rOwnerPos.z + rOwnerVtxMin.z
			&& rTargetPos.z - rTargetSizeZ.z < rOwnerPos.z - rOwnerVtxMax.z)
		{
			bHit = true;
		}
		//右側に当たっていたら
		else if (rTargetPos.z + rTargetVtxMax.z <= rOwnerPos.z + rOwnerVtxMin.z
			&& rTargetPos.z + rTargetSizeZ.z > rOwnerPos.z + rOwnerVtxMax.z)
		{
			bHit = true;
		}
	}
	return bHit;
}
//<================================================
//すべての座標を判定するためのコリジョン
//<================================================
bool Collision::CollidAll(const D3DXVECTOR3 rOwnerPos, const D3DXVECTOR3 rOwnerSize, const D3DXVECTOR3 rTargetPos, const D3DXVECTOR3 rTargetVtxMax, const D3DXVECTOR3 rTargetVtxMin)
{
	//判定用
	bool bCollid = false;

	//どの軸にも当たっていたら
	if (rOwnerPos.z + rOwnerSize.z > rTargetPos.z + rTargetVtxMin.z&&
		rOwnerPos.z + -rOwnerSize.z < rTargetPos.z + rTargetVtxMax.z&&
		rOwnerPos.x + rOwnerSize.x > rTargetPos.x + rTargetVtxMin.x&&
		rOwnerPos.x + -rOwnerSize.x < rTargetPos.x + rTargetVtxMax.x&&
		rOwnerPos.y + rOwnerSize.y > rTargetPos.y + rTargetVtxMin.y&&
		rOwnerPos.y + -rOwnerSize.y < rTargetPos.y + rTargetVtxMax.y)
	{
		//当たっている判定にする
		bCollid = true;
	}
	//当たっていなければ
	else
	{
		//当たっていない判定にする
		bCollid = false;
	}

	//判定を返す
	return bCollid;
}