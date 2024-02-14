//<========================================
//3D�v���C���[����(3DPlayer.h)
//
//Author:kazuki watanabe
//<========================================
#ifndef _3DPLAYER_H_//��d�C���N���[�h�h�~
#define _3DPLAYER_H_

#include "XObject.h"

//<****************************************
//3D�v���C���[�̃N���X��`
//<****************************************
class C3DPlayer : public CXObject
{
public:

	//<======================================
	//�v���C���[�X�e�[�g
	//<======================================
	enum STATE
	{
		STATE_NONE = 0,	//�����Ȃ����
		STATE_HIDE,		//�B��Ă�����
		STATE_DEATH,
		STATE_MAX
	};



	C3DPlayer(int nPriority = FIX_PRIORITY);
	~C3DPlayer();

	//<==========================
	//�I�[�o�[���[�h�����o�֐�
	//<==========================
	HRESULT Init(void);
	void Uninit(void) { CXObject::Uninit(); }
	void Update(void);
	void Draw(void) 
	{ 
		//�B��Ă��Ȃ����
		if (m_sState != STATE_DEATH&& m_sState != STATE_HIDE)
		{
			CXObject::Draw();
		}
	}

	static C3DPlayer *Create(const D3DXVECTOR3 pos);
	int GetStamina(void) { return m_nStamina; }
	float GetCollidRad(void) {return m_fCollidRad;}

	void SetState(const STATE sState) { m_sState = sState; }
	STATE GetState(void) { return m_sState; }

	void SetStateHide(void) { m_sState == STATE_NONE ? m_sState = STATE_HIDE : m_sState = STATE_NONE; ; }

	void Controll(void);

private:

	void MoveAction(void);
	void Movement(void);
	//void Collision(void);
	void Hide(void);
	void Dash(void);

	//<==============
	//�ʒu���֘A
	//<==============
	D3DXVECTOR3 m_pos;										//�ʒu
	D3DXVECTOR3 m_posOld;									//�O��̈ʒu
	D3DXVECTOR3 m_rot;										//����
	D3DXVECTOR3 m_move;										//�ړ��l

	D3DXVECTOR3 m_rRad;

	float m_fRotMove;
	float m_fRotDest;
	float m_fRotDiff;
	float m_fCollidRad;

	float m_fMoveValue;

	int m_nStamina;

	STATE m_sState;

	bool m_bJump;
	bool m_bDash;
	bool m_bMove;

	DataModel m_sModel;

};
#endif
