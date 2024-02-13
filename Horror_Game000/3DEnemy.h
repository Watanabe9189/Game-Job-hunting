//<============================================
//3D�G�l�~�[����(3DEnemy.h)
//
//Author:kazuki watanabe
//<============================================
#ifndef _3DENEMY_H_
#define _3DENEMY_H_

#include "XObject.h"
#include "3DPlayer.h"

//<**********************************************
//3D�G�l�~�[�̃N���X��`
//<**********************************************
class C3DEnemy : public CXObject
{
public:

	//<=========================================
	//�G�^�C�v�̗񋓌^
	//<=========================================
	enum TYPE
	{
		TYPE_ENEMY_NORMAL = 0,	//�ʏ�^
		TYPE_ENEMY_INVISIBLE,	//�����^
		TYPE_ENEMY_HIGHSPEED,	//�����^
		TYPE_MAX

	};
	//<=========================================
	//�G�X�e�[�g�̗񋓌^
	//<=========================================
	enum STATE
	{
		STATE_NORMAL = 0,		//�����Ȃ����
		STATE_SEARCH,			//�T�����
		STATE_WAIT,				//�ҋ@���
		STATE_CHASE,			//�ǐՏ��
		STATE_MAX

	};
	//<=========================================
	//�G�X�e�[�g�̗񋓌^
	//<=========================================
	enum FAST_STATE
	{
		FAST_STATE_NORMAL = 0,			//�ʏ���
		FAST_STATE_MOVE,				//�ړ����
		FAST_STATE_INTERVAL,			//�����܂ł̏��
		FAST_STATE_WAIT,				//�ҋ@���
		FAST_STATE_MAX
	};

	C3DEnemy(int nPriority = FIX_PRIORITY);
	~C3DEnemy();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static C3DEnemy *Create(const D3DXVECTOR3 pos, const int nLife, const int nType, const int CoolTime);
	static C3DEnemy *ReadCreate(C3DEnemy *apEnemy[MAX_OBJECT]);
	static C3DEnemy *RandCreate(C3DEnemy *apEnemy[MAX_OBJECT]);
	void Search(void);
	static int GetNum(void) { return m_nNumAll; }

	static void SetNumSet(const int nNumSet) { m_nNumSet = nNumSet; }
	static int GetNumSet(void) { return m_nNumSet; }
	static int GetNumMax(void) { return m_nNumMax; }
	static int GetNumMin(void) { return m_nNumMin; }
	//<============================================
	//����g�p���Ȃ��I�[�o�[���[�h�����o�֐�
	//<============================================
	void SetVtx(void) { return; }

	//
	STATE GetState(void) { return m_sState; }
	TYPE GetType(void) { return m_eType; }

	/*bool CollisionDestroy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, bool bJump, TYPE_3D Type3D);*/

private:


	//�����o�֐�
	void ChangeRot(void);
	void MoveMent(void);
	void SetSound(const CSound::LABEL Label, const int nMaxCount, const D3DXVECTOR3 rTargetPos);
	void SetDest(void);
	void SetDest(const D3DXVECTOR3 rDestPos);
	void CollidPlayer(void);
	void DeathSound(void);

	//�����o�ϐ�
	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rDestPos;	//�ړI�̈ʒu
	D3DXVECTOR3 m_OldPos;	//�O��̈ʒu
	D3DXVECTOR3 m_rot;		//����
	D3DXVECTOR3 m_move;		//�ړ��l
	float m_fSearchRad;		//�T���~
	D3DXVECTOR3 m_rDis;
	static int m_nNumAll;	//����
	static int m_nNumSet;		//
	static int m_nNumMax;
	static int m_nNumMin;

	STATE m_sState;
	FAST_STATE m_sFastState;
	//<==============
	//�}�e���A���֘A
	//<==============
	LPD3DXMESH	m_pMesh;							//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER	m_pBuffMat;							//�}�e���A���ւ̃|�C���^
	DWORD		m_dwNumMat;							//�}�e���A���̐�
	D3DXMATERIAL*	m_pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

															//<==============
															//�e�N�X�`���֘A
															//<==============
	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];		//�e�N�X�`���ւ̃|�C���^
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//�t�@�C����

															//<=============
															//���_���֘A
															//<=============
	D3DXVECTOR3			m_vtxMin;					//���_�̍ŏ��l
	D3DXVECTOR3			m_vtxMax;					//���_�̍ő�l

	int m_nSoundCount;
	int m_nSoundMax;
	int m_nInterval;
	int m_nRandInter;

	float m_fMoveValue;

	D3DXVECTOR3 m_rRandDest;

	D3DXVECTOR3 m_fFrontDest;
	D3DXVECTOR3 m_fBackDest;

	D3DXVECTOR3 m_rSize;
	D3DXVECTOR3 m_rSizeX;
	D3DXVECTOR3 m_rSizeZ;

	C3DPlayer *m_pPlayer;
	CSound *m_pSound;
	D3DXVECTOR3 m_rTelportPos;

	TYPE m_eType;
};
#endif
