//<==================================
//�J��������(Camera.h)
//
//Author:kazuki watanabe
//<==================================
#ifndef _CAMERA_H_		//���̃}�N����`������Ă��Ȃ�������
#define _CAMERA_H_		//��d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "object.h"
//<************************************************
//�J�����̃N���X��`
//<************************************************
class Ccamera
{
public:

	//<=====================================
	//���e�^�C�v�̗񋓌^
	//<=====================================
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_XRAY,		//�������e
		TYPE_PARALLEL,	//���s���e
		TYPE_MAX

	};
	//<=====================================
	//���E�̗񋓌^
	//<=====================================
	enum VISIBILITY
	{
		VISIBILITY_FPV = 0,		//��l��
		VISIBILITY_TPS,			//�O�l��
		VISIBILITY_MAX	
	};

	Ccamera();
	~Ccamera();

	static Ccamera *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetCamera(void);
	void MoveRot(void);

	void MoveVR(void);
	void SetV(void);
	void SetR(void);
	void SetRot(void);
	void SetMoveFollow(void);
	void SetFollow(const D3DXVECTOR3 rTargetPos, const D3DXVECTOR3 rTargetRot,const VISIBILITY eVisibility);


	//<===========================================
	//�g��Ȃ��֐�
	//<===========================================
	void Draw(void) { return; }
	void SetVtx(void) { return; }
	CObject2D *GetObject2D(void) { return NULL; }

	//<==========================================
	//Get����ہA�Ăяo�����������o�ϐ���錾
	//<==========================================
	D3DXVECTOR3 m_posV;		//���_(�J�����̈ʒu)
	D3DXVECTOR3 m_posR;		//�����_(�������ꏊ)
	D3DXVECTOR3 m_rot;		//����
	float m_fDistance;		//����
	bool m_bFollow;			//�ǔ����邩�ǂ���
	int m_nShakeCount;

	void Shake(void);

	//���̊֐�����̃����o�ϐ�
private:

	void ControllMouse(void);

	D3DXVECTOR3 m_posVDest;			//�ڕW�̎��_
	D3DXVECTOR3 m_posVOld;			//���_(�J�����̈ʒu)
	D3DXVECTOR3 m_posROld;			//�����_(�������ꏊ)
	D3DXVECTOR3 m_posRDest;			//�ڕW�̒����_

	D3DXVECTOR3 m_move;				//�ړ���
	D3DXVECTOR3 m_rotVDest;			//�ڕW�̎��_�̌���

	D3DXVECTOR3 m_vecU;				//������x�N�g��

	D3DXMATRIX	m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX	m_mtxView;			//�r���[�}�g���b�N�X

	float m_rotVDiff;				//�ڕW�̎��_�̍���

	TYPE m_Type;					//���e�^�C�v

};
//class CTitleCamera : public Ccamera
//{
//public:
//
//	CTitleCamera();
//	~CTitleCamera();
//
//	CTitleCamera *Crete(void);
//
//private:
//};

#endif