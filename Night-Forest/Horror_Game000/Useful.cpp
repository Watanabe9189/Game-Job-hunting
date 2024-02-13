#include "Useful.h"

//<================================================
//
//<================================================
float Correction::NormalizeRotation(const float fRotY)
{
	//�v�Z�p�ϐ�
	float fRot = fRotY;

	//<*******************
	//Y���̕␳
	//<*******************
	if (fRot > D3DX_PI)
	{
		fRot = -D3DX_PI;
	}
	//���~��������Ă�����
	else if (fRot < -D3DX_PI)
	{
		fRot = D3DX_PI;
	}
	return fRot;
}
//<================================================
//�ʒu�̌��E�l
//<================================================
D3DXVECTOR3 Correction::LimitPos(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rLimitPos, const bool bBoolX, const bool bBoolY, const bool bBoolZ)
{
	//�v�Z�p�ʒu
	D3DXVECTOR3 rCalculatePos = rPos;

	//X���𔻒肷��ꍇ
	if (bBoolX)
	{
		//X���̈ʒu�����E�͈͂𒴂������ɂȂ�����
		if (rCalculatePos.x >= rLimitPos.x)
		{
			//���̈ʒu�ɂ���
			rCalculatePos.x = rLimitPos.x;
		}
		//X���̈ʒu���}�C�i�X���E�͈͂𒴂������ɂȂ�����
		else if (rCalculatePos.x <= -rLimitPos.x)
		{
			//���̈ʒu�ɂ���
			rCalculatePos.x = -rLimitPos.x;
		}
	}
	//Y���𔻒肷��ꍇ
	if (bBoolY)
	{
		//X���̈ʒu�����E�͈͂𒴂������ɂȂ�����
		if (rCalculatePos.y >= rLimitPos.y)
		{
			//���̈ʒu�ɂ���
			rCalculatePos.y = rLimitPos.y;
		}
		//X���̈ʒu���}�C�i�X���E�͈͂𒴂������ɂȂ�����
		else if (rCalculatePos.y <= -rLimitPos.y)
		{
			//���̈ʒu�ɂ���
			rCalculatePos.y = -rLimitPos.y;
		}
	}
	//Z���𔻒肷��ꍇ
	if (bBoolZ)
	{
		//Z���̈ʒu�����E�͈͂𒴂������ɂȂ�����
		if (rCalculatePos.z >= rLimitPos.z)
		{
			//���̈ʒu�ɂ���
			rCalculatePos.z = rLimitPos.z;
		}
		//Z���̈ʒu���}�C�i�X���E�͈͂𒴂������ɂȂ�����
		else if (rCalculatePos.z <= -rLimitPos.z)
		{
			//���̈ʒu�ɂ���
			rCalculatePos.z = -rLimitPos.z;
		}

	}

	//�l��Ԃ�
	return rCalculatePos;
}
//<================================================
//
//<================================================
D3DXCOLOR Change::ChangeColInter(const D3DXCOLOR pColor, const float MAX_COLOR, const float MIN_COLOR, const float fValueChange)
{
	//�l��Ԃ��p�̐F�ϐ�
	D3DXCOLOR rCol = pColor;

	//�ő�F�܂Ō����Ă�����
	if (rCol.a >= MAX_COLOR&&m_bEnd)
	{
		m_nCounter = 0;
		m_bEnd = false;
	}

	//�����F�`�F���W���I����Ă��Ȃ����
	if (!m_bEnd)
	{
		//�ŏ��l�̐F�܂ōs���Ă�����
		if (rCol.a <= MIN_COLOR)
		{
			//�ŏ��l�̐F�ɂ���
			rCol.a = MIN_COLOR;

			//�J�E���^�[���ő�l�܂ōs���Ă�����
			if (m_nCounter >= 100)
			{
				m_nCounter = 0;
				m_bEnd = true;
			}
			//�s���Ă��Ȃ�������
			else
			{
				//���Z����
				m_nCounter++;
			}
		}
		//�܂��ŏ��l�܂ōs���Ă��Ȃ����
		else
		{
			//���Z����
			rCol.a -= fValueChange;
		}
	}
	//�I����Ă����
	else
	{
		//�ő�F�܂ōs���Ă�����
		if (rCol.a >= MAX_COLOR)
		{
			//���̒l�ɂ���
			rCol.a = MAX_COLOR;

			//�ő�J�E���^�[�܂ōs���Ă�����
			if (m_nCounter >= 100)
			{
				m_nCounter = 0;
				m_bEnd = false;
			}
			//�s���Ă��Ȃ�������
			else
			{
				//���Z����
				m_nCounter++;
			}

		}
		//���̐F�܂ōs���Ă��Ȃ�������
		else
		{
			//�F�����Z����
			rCol.a += fValueChange;
		}
	}
	return rCol;
}
//<==========================================
//bool�^�̕ύX����
//<==========================================
bool Change::Changebool(bool bBool, const BOOL nBool)
{
	bool bUse = bBool;

	//�g����ԂȂ�
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
//bool�^�̕ύX����
//<==========================================
D3DXVECTOR3 Calculate::CalculateDest(const D3DXVECTOR3 rOwnerPos, const D3DXVECTOR3 rTargetPos)
{
	D3DXVECTOR3 rCalPos = INIT_VECTOR;	//�v�Z�p�ʒu

	rCalPos.x = rOwnerPos.x - rTargetPos.x;	//X���W
	rCalPos.y = rOwnerPos.y - rTargetPos.y;	//Y���W
	rCalPos.z = rOwnerPos.z - rTargetPos.z;	//Z���W

	return rCalPos;
}
//<==========================================
//bool�^�̕ύX����
//<==========================================
float Calculate::CalculateRandfloat(const float fMax, const float fMin)
{
	//�v�Z�p�̕ϐ�
	float fRand = INITIAL_FLOAT;

	fRand = fMin + (int)(rand() * (fMax - fMin + 1.0) / (1.0 + RAND_MAX));
	
	return fRand;
}
//<==========================================
//bool�^�̕ύX����
//<==========================================
int Calculate::CalculeteRandInt(const int nMax, const int nMin)
{
	//�v�Z�p�̕ϐ�
	int nRand = INITIAL_INT;

	nRand = nMin + (int)(rand() * (nMax - nMin + 1.0) / (1.0 + RAND_MAX));

	return nRand;
}
//<==========================================
//bool�^�̕ύX����
//<==========================================
D3DXVECTOR3 Calculate::CalculteRandVec3(const D3DXVECTOR3 rMax, const D3DXVECTOR3 rMin, const bool bUseY)
{
	D3DXVECTOR3 rVec3 = INIT_VECTOR;

	//Y���W���g���Ȃ�
	if (bUseY)
	{
		//���ꂼ��̈ʒu��ݒ肷��
		rVec3.x = rMin.x + (int)(rand() * (rMax.x - rMin.x + 1.0) / (1.0 + RAND_MAX));
		rVec3.y = rMin.y + (int)(rand() * (rMax.y - rMin.y + 1.0) / (1.0 + RAND_MAX));
		rVec3.z = rMin.x + (int)(rand() * (rMax.z - rMin.z + 1.0) / (1.0 + RAND_MAX));
	}
	//�g��Ȃ��Ȃ�
	else
	{
		//���ꂼ��̈ʒu��ݒ肷��
		rVec3.x = rMin.x + (int)(rand() * (rMax.x - rMin.x + 1.0) / (1.0 + RAND_MAX));
		rVec3.z = rMin.x + (int)(rand() * (rMax.z - rMin.z + 1.0) / (1.0 + RAND_MAX));
	}

	return rVec3;
}
//<==========================================
//bool�^�̕ύX����
//<==========================================
bool Bool::bMove(const D3DXVECTOR3 rMove)
{
	bool bMove = false;	//����p

	//�ǂ̎��ł������Ă����
	if (rMove.x != 0.0f ||rMove.x != -0.0f
		&&rMove.y != 0.0f ||rMove.y != -0.0f
		&& rMove.z != 0.0f ||rMove.z != -0.0f)
	{
		bMove = true;
	}

	return bMove;
}
//<==========================================
//bool�^�̕ύX����
//<==========================================
void Collision::CollidXZ(const D3DXVECTOR3 rOwnerPos, const D3DXVECTOR3 rOwnerSizeX, const D3DXVECTOR3 rOwnerSizeZ,
	const D3DXVECTOR3 rOwnerVtxMax, const D3DXVECTOR3 rOwnerVtxMin,
	D3DXVECTOR3 *rTargetPos,const D3DXVECTOR3 rTargetPosOld,D3DXVECTOR3 *rTargetMove
	, const D3DXVECTOR3 rTargetVtxMax, const D3DXVECTOR3 rTargetVtxMin, const bool bDecay)
{
	//<**********************************************
	//���E����
	//<**********************************************
	if (rOwnerPos.z + rOwnerSizeX.z > rTargetPos->z + rTargetVtxMin.z&&
		rOwnerPos.z - rOwnerSizeX.z < rTargetPos->z + rTargetVtxMax.z)
	{
		//�����ɓ������Ă�����
		if (rOwnerPos.x + rOwnerVtxMax.x >= rTargetPosOld.x + rTargetVtxMin.x
			&& rOwnerPos.x - rOwnerSizeX.x< rTargetPos->x - rTargetVtxMax.x)
		{
			//�I�u�W�F�N�g�̉E���Ɉʒu��␳
			rTargetPos->x = rOwnerPos.x - rOwnerSizeX.x + rTargetVtxMax.x;
			if (bDecay) { rTargetMove->x = 0.0f; }
		}
		//�E���ɓ������Ă�����
		else if (rOwnerPos.x + rOwnerVtxMax.x <= rTargetPosOld.x + rTargetVtxMin.x
			&& rOwnerPos.x + rOwnerSizeX.x > rTargetPos->x + rTargetVtxMax.x)
		{
			//�I�u�W�F�N�g�̍����Ɉʒu��␳
			rTargetPos->x = rOwnerPos.x + rOwnerSizeX.x - rTargetVtxMax.x;
			if (bDecay) { rTargetMove->x = 0.0f; }
		}
	}
	//<**********************************************
	//���E����
	//<**********************************************
	if (rOwnerPos.x + rOwnerSizeZ.x >= rTargetPos->x + rTargetVtxMin.x&&
		rOwnerPos.x - rOwnerSizeZ.x <= rTargetPos->x + rTargetVtxMax.x)
	{
		//�����ɓ������Ă�����
		if (rOwnerPos.z + rOwnerVtxMax.z >= rTargetPosOld.z + rTargetVtxMin.z
			&& rOwnerPos.z - rOwnerSizeZ.z< rTargetPos->z - rTargetVtxMax.z)
		{
			//�I�u�W�F�N�g�̉E���Ɉʒu��␳
			rTargetPos->z = rOwnerPos.z - rOwnerSizeZ.z + rTargetVtxMax.z;
			if (bDecay) { rTargetMove->z = 0.0f; }
		}
		//�E���ɓ������Ă�����
		else if (rOwnerPos.z + rOwnerVtxMax.z <= rTargetPosOld.z + rTargetVtxMin.z
			&& rOwnerPos.z + rOwnerSizeZ.z > rTargetPos->z + rTargetVtxMax.z)
		{
			//�I�u�W�F�N�g�̍����Ɉʒu��␳
			rTargetPos->z = rOwnerPos.z + rOwnerSizeZ.z - rTargetVtxMax.z;
			if (bDecay) { rTargetMove->z = 0.0f; }
		}
	}
}
//<==========================================
//bool�^�̕ύX����
//<==========================================
bool Collision::OnlyCollid(const D3DXVECTOR3 rTargetPos, const D3DXVECTOR3 rTargetSizeX, const D3DXVECTOR3 rTargetSizeZ,
	const D3DXVECTOR3 rTargetVtxMax, const D3DXVECTOR3 rTargetVtxMin,
	const D3DXVECTOR3 rOwnerPos, const D3DXVECTOR3 rOwnerVtxMax, const D3DXVECTOR3 rOwnerVtxMin)
{
	bool bHit = false;

	//<**********************************************
	//���E����
	//<**********************************************
	if (rTargetPos.z + rTargetSizeZ.x >= rOwnerPos.z + rOwnerVtxMin.z&&
		rTargetPos.z - rTargetSizeZ.x <= rOwnerPos.z + rOwnerVtxMax.z)
	{
		//�����ɓ������Ă�����
		if (rTargetPos.x + rTargetVtxMax.x >= rOwnerPos.x + rOwnerVtxMin.x
			&& rTargetPos.x - rTargetSizeX.x < rOwnerPos.x - rOwnerVtxMax.x)
		{
			bHit = true;
		}
		//�E���ɓ������Ă�����
		else if (rTargetPos.x + rTargetVtxMax.x <= rOwnerPos.x + rOwnerVtxMin.x
			&& rTargetPos.x + rTargetSizeX.x > rOwnerPos.x + rOwnerVtxMax.x)
		{
			bHit = true;
		}
	}
	//<**********************************************
	//���E����
	//<**********************************************
	if (rTargetPos.x + rTargetSizeX.z >= rOwnerPos.x + rOwnerVtxMin.x&&
		rTargetPos.x - rTargetSizeX.z <= rOwnerPos.x + rOwnerVtxMax.x)
	{
		//�����ɓ������Ă�����
		if (rTargetPos.z + rTargetVtxMax.z >= rOwnerPos.z + rOwnerVtxMin.z
			&& rTargetPos.z - rTargetSizeZ.z < rOwnerPos.z - rOwnerVtxMax.z)
		{
			bHit = true;
		}
		//�E���ɓ������Ă�����
		else if (rTargetPos.z + rTargetVtxMax.z <= rOwnerPos.z + rOwnerVtxMin.z
			&& rTargetPos.z + rTargetSizeZ.z > rOwnerPos.z + rOwnerVtxMax.z)
		{
			bHit = true;
		}
	}
	return bHit;
}
//<================================================
//���ׂĂ̍��W�𔻒肷�邽�߂̃R���W����
//<================================================
bool Collision::CollidAll(const D3DXVECTOR3 rOwnerPos, const D3DXVECTOR3 rOwnerSize, const D3DXVECTOR3 rTargetPos, const D3DXVECTOR3 rTargetVtxMax, const D3DXVECTOR3 rTargetVtxMin)
{
	//����p
	bool bCollid = false;

	//�ǂ̎��ɂ��������Ă�����
	if (rOwnerPos.z + rOwnerSize.z > rTargetPos.z + rTargetVtxMin.z&&
		rOwnerPos.z + -rOwnerSize.z < rTargetPos.z + rTargetVtxMax.z&&
		rOwnerPos.x + rOwnerSize.x > rTargetPos.x + rTargetVtxMin.x&&
		rOwnerPos.x + -rOwnerSize.x < rTargetPos.x + rTargetVtxMax.x&&
		rOwnerPos.y + rOwnerSize.y > rTargetPos.y + rTargetVtxMin.y&&
		rOwnerPos.y + -rOwnerSize.y < rTargetPos.y + rTargetVtxMax.y)
	{
		//�������Ă��锻��ɂ���
		bCollid = true;
	}
	//�������Ă��Ȃ����
	else
	{
		//�������Ă��Ȃ�����ɂ���
		bCollid = false;
	}

	//�����Ԃ�
	return bCollid;
}