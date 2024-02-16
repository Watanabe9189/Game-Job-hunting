#ifndef _USEFUL_H_
#define _USEFUL_H_

#include "main.h"
//<============================================================================================================
//�R���W����(�����蔻��)�֘A�̖��O�錾
//<============================================================================================================
namespace Collision
{
	//<*****************************************************************************************************
	//����
	//rOwnerPos				= �����҂̈ʒu
	//rOwnerSizeX			= �����҂̃T�C�YX
	//rOwnerSizeZ			= �����҂̃T�C�YZ
	//rOwnerVtxMax			= �����҂̒��_�ő�l
	//rOwnerVtxMin			= �����҂̒��_�ŏ��l
	//rTargetPos			= �ΏۂƂȂ�I�u�W�F�N�g�̈ʒu
	//rTargetPosOld			= �ΏۂƂȂ�I�u�W�F�N�g�̉ߋ��ʒu
	//rTargetMove			= �ΏۂƂȂ�I�u�W�F�N�g�̈ړ��l
	//rTargetVtxMax			= �ΏۂƂȂ�I�u�W�F�N�g�̒��_�ő�l
	//rTargetVtxMin			= �ΏۂƂȂ�I�u�W�F�N�g�̒��_�ŏ��l
	//bDecay				= �������邩�ǂ���
	//<*****************************************************************************************************
	void CollidXZ(const D3DXVECTOR3 rOwnerPos, const D3DXVECTOR3 rOwnerSizeX, const D3DXVECTOR3 rOwnerSizeZ,
		const D3DXVECTOR3 rOwnerVtxMax, const D3DXVECTOR3 rOwnerVtxMin,
		D3DXVECTOR3 *rTargetPos, const D3DXVECTOR3 rTargetPosOld, D3DXVECTOR3 *rTargetMove
		, const D3DXVECTOR3 rTargetVtxMax, const D3DXVECTOR3 rTargetVtxMin, const bool bDecay = true);

	//<*****************************************************************************************************
	//����
	//rTargetPos			= �ΏۂƂȂ�I�u�W�F�N�g�̈ʒu
	//rOwnerSizeX			= �ΏۂƂȂ�I�u�W�F�N�g�̃T�C�YX
	//rOwnerSizeZ			= �ΏۂƂȂ�I�u�W�F�N�g�̃T�C�YZ
	//rTargetVtxMax			= �ΏۂƂȂ�I�u�W�F�N�g�̒��_�ő�l
	//rTargetVtxMin			= �ΏۂƂȂ�I�u�W�F�N�g�̒��_�ŏ��l
	//rOwnerPos				= �����҂̈ʒu
	//rOwnerVtxMax			= �����҂̒��_�ő�l
	//rOwnerVtxMin			= �����҂̒��_�ŏ��l
	//<*****************************************************************************************************
	bool OnlyCollid(const D3DXVECTOR3 rTargetPos, const D3DXVECTOR3 rTargetSizeX, const D3DXVECTOR3 rTargetSizeZ,
		const D3DXVECTOR3 rTargetVtxMax, const D3DXVECTOR3 rTargetVtxMin, 
		const D3DXVECTOR3 rOwnerPos,const D3DXVECTOR3 rOwnerVtxMax, const D3DXVECTOR3 rOwnerVtxMin);


	//<*****************************************************************************************************
	//����
	//rOwnerPos				= �����҂̈ʒu
	//rOwnerSize			= �����҂̃T�C�Y
	//rTargetPos			= �ΏۂƂȂ�I�u�W�F�N�g�̈ʒu
	//rTargetVtxMax			= �ΏۂƂȂ�I�u�W�F�N�g�̒��_�ő�l
	//rTargetVtxMin			= �ΏۂƂȂ�I�u�W�F�N�g�̒��_�ŏ��l
	//<*****************************************************************************************************
	bool CollidAll(const D3DXVECTOR3 rOwnerPos,const D3DXVECTOR3 rOwnerSize, const D3DXVECTOR3 rTargetPos, 
					const D3DXVECTOR3 rTargetVtxMax, const D3DXVECTOR3 rTargetVtxMin);
}
//<============================================================================================================
//�␳�֘A�̖��O�錾
//<============================================================================================================
namespace Correction
{
	float NormalizeRotation(const float fRotY);
	D3DXVECTOR3 LimitPos(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rLimitPos, const bool bBoolX, const bool bBoolY, const bool bBoolZ);
}
//<============================================================================================================
//�ύX�֘A�̖��O�錾
//<============================================================================================================
namespace Change
{
	static int m_nCounter = 0;
	static bool m_bEnd = false;

	D3DXCOLOR ChangeColInter(const D3DXCOLOR pColor, const float MAX_COLOR, const float MIN_COLOR, const float fValueChange);//�ς���F�E�ő�F�l�E�ŏ��F�l�E�ύX�l
	bool Changebool(bool bBool, const BOOL nBool);
}
//<============================================================================================================
//�v�Z�֘A�̖��O�錾
//<============================================================================================================
namespace Calculate
{
	D3DXVECTOR3 CalculateDest(const D3DXVECTOR3 rOwnerPos,const D3DXVECTOR3 rTargetPos);
	//<********************************************************************************************
	//�����_���֘A�̊֐�
	//<********************************************************************************************
	//fMax = �ő�l
	//fMin = �ŏ��l
	//<********************************************************************************************
	float CalculateRandfloat(const float fMax, const float fMin);
	//<********************************************************************************************
	//nMax = �ő�l
	//nMin = �ŏ��l
	//<********************************************************************************************
	int CalculeteRandInt(const int nMax, const int nMin);
	//<********************************************************************************************
	//rMax = �ő�l
	//rMin = �ŏ��l
	//bUseY= Y���W���g�p���邩
	//<********************************************************************************************
	D3DXVECTOR3 CalculteRandVec3(const D3DXVECTOR3 rMax, const D3DXVECTOR3 rMin, const bool bUseY);

	float RotateToDest(const float rOwnerRot,const D3DXVECTOR3 fDestRot, const float fRotateValue);
}
//<============================================================================================================
//bool�^����֘A�̖��O�錾
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
