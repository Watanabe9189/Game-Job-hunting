//<============================================
//3D�v���C���[����(3DPlayer.cpp)
//
//Author:kazuki watanabe
//<============================================
#include "3DPlayer.h"
#include "Camera.h"
#include "Title.h"
#include "Light.h"
#include "game.h"
#include "Building.h"
#include "2DGauge.h"
//<*******************************************
//�ÓI�����o�ϐ��̐錾
//<*******************************************
//�}�e���A���֘A
//�e�N�X�`���֘A

namespace
{
	const float VALUE_REVISE	= 0.15f;	//�␳�̒l
	const float GROUND			= 0.0f;		//�n�ʂ̈ʒu
	const float ROTATE_VALUE	= 0.05f;	//��]��
	const float REVISE_ROT		= 0.5f;
	const float NO_DASH_VALUE	= 0.3f;		//�΂߈ړ����݂̈ړ���(1.0f�����傤�ǂ���)
	const float DASH_VALUE		= 1.0f;		//�΂߈ړ����݂̈ړ���(1.0f�����傤�ǂ���)
	const int	MAX_STAMINA		= 500;		//�X�^�~�i�̍ő�l
}

//<==================================
//3D�v���C���[�̃R���X�g���N�^
//<==================================
C3DPlayer::C3DPlayer(int nPriority)
{
	//�l�̃N���A
	m_pos = INIT_VECTOR;
	m_rot = INIT_VECTOR;
	m_move = INIT_VECTOR;

	//�p�x�֘A
	m_fRotMove = NULL;
	m_fRotDest = NULL;
	m_fRotDiff = NULL;

	//�t�@�C����
	m_bJump = false;
	m_bDash = false;
	m_bMove = false;
	m_rRad = INIT_VECTOR;
	m_fMoveValue = INITIAL_FLOAT;
	m_sState = STATE_NONE;
	m_fCollidRad = INITIAL_FLOAT;

	m_nStamina = INITIAL_INT;

	m_sModel = {};
}
//<==================================
//3D�v���C���[�̃f�X�g���N�^
//<==================================
C3DPlayer::~C3DPlayer()
{
	
}
//<==================================
//3D�v���C���[�̐�������
//<==================================
C3DPlayer *C3DPlayer::Create(const D3DXVECTOR3 pos)
{
	//�C���X�^���X�����p�̃I�u�W�F�N�g
	C3DPlayer *pPlayer3D = new C3DPlayer;

	//�����������m�ۂɐ���������
	if (pPlayer3D != NULL)
	{
		pPlayer3D->Init();

		//�ʒu����
		pPlayer3D->SetPosition(pos);

		//
		pPlayer3D->SetType3D(TYPE_3D::TYPE_PLAYER3D);
	}
	//
	else
	{
		return NULL;

	}

	return pPlayer3D;
}
//<==================================
//3D�v���C���[�̏���������
//<==================================
HRESULT C3DPlayer::Init(void)
{
	//�X�^�~�i�̒l�ݒ�
	m_nStamina = C2DGauge::GetFixed();
	m_fCollidRad = 50.0f;
	m_sModel = BindModel("data\\MODEL\\Enemy001.x");

	return S_OK;
}
//<==================================
//3D�v���C���[�̍X�V����
//<==================================
void C3DPlayer::Update(void)
{
	//�܂��Q�[�����I����Ă��Ȃ����
	if (CManager::GetScene()->GetGame()->GetGame()->GetState() == CGame::STATE_NONE)
	{
		//�O��̈ʒu��ۑ�
		m_posOld = m_pos;

		//�ʒu���擾
		m_pos = GetPosition();

		//�ړ��ʂ̎擾
		m_move = GetMove();

		//�������擾
		m_rot = GetRotation();

		//�A�N�V�������̑���
		Controll();

		//���E�ʒu��ݒ肷��
		m_pos = Correction::LimitPos(m_pos, D3DXVECTOR3(4000.0f, 0.0f, 4000.0f),true,true,true);

		SetVector3(m_pos, m_rot, m_move);

		CScene::GetGame()->GetLight()->SetPosition(m_pos);

	}
	//�������g�ւ̃|�C���^��NULL�ł͂Ȃ����
	if (this != NULL)
	{
		//<====================================================
		//�f�o�b�O�֘A
		//<====================================================
		/*CManager::GetDebugProc()->Print("<=====================================================\n");
		CManager::GetDebugProc()->Print("[�v���C���[�֘A�̃f�o�b�O�\��]\n");
		CManager::GetDebugProc()->Print("<=====================================================\n");
		CManager::GetDebugProc()->Print("[�ʒu]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_pos.x, m_pos.y, m_pos.z);
		CManager::GetDebugProc()->Print("[����]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_rot.x, m_rot.y, m_rot.z);
		CManager::GetDebugProc()->Print("[�ړ���]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_move.x, m_move.y, m_move.z);
		CManager::GetDebugProc()->Print("[�X�^�~�i]�F%d\n", m_nStamina);*/
	}
}
//<==================================
//3D�v���C���[�̃A�N�V�������̑���
//<==================================
void C3DPlayer::Controll(void)
{

	//�����֘A�̒l�̑}��
	m_fRotMove = m_rot.y;	//���݂̊p�x
	m_fRotDest = m_rot.y;	//�ڕW�̊p�x
	m_fRotDiff = 0.0f;		//�p�x�̕␳

	Dash();

	//�B��Ă���X�e�[�g�ȊO�̏ꍇ
	if (m_sState != STATE_HIDE)
	{
		Movement();
	}

	Hide();
	
#if 1

	//�Ǐ]����
	CManager::GetScene()->GetGame()->GetCamera()->SetFollow(m_pos,m_rot,Ccamera::VISIBILITY_FPV);

#endif
	//���݂ƖڕW�̍��������߁A
	m_fRotDiff = m_fRotDest - m_fRotMove;

	//�p�x�̕␳������
	m_rot.y += m_fRotDiff * REVISE_ROT;

	//�ʒu���X�V
	m_pos += m_move;

	//����������
	m_move.x += (0.0f - m_move.x) *VALUE_REVISE;//X��
	m_move.y += (0.0f - m_move.y) *VALUE_REVISE;//Y��
	m_move.z += (0.0f - m_move.z) *VALUE_REVISE;//Z��

}
//<===================================================================
//�_�b�V��
//<===================================================================
void C3DPlayer::Dash(void)
{
	//�B��Ă����ԈȊO��������
	if (m_sState != STATE_HIDE)
	{
		//�����Ă�����
		if (!CManager::GetKeyboard()->bGetPress(DIK_LSHIFT)
			&& !CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_LB, 0))
		{
			//�_�b�V�����Ă��Ȃ���Ԃɂ���
			m_bDash = false;

		}
	}
	//�B��Ă����Ԃ�������
	else if (m_sState == STATE_HIDE)
	{
		//�X�^�~�i���ő�l�ȏ�ɂȂ�����
		if (m_nStamina >= C2DGauge::GetFixed())
		{
			//���̒l�ɂ���
			m_nStamina = C2DGauge::GetFixed();
		}
		//�ő�l�ȏ�ł͂Ȃ����
		else
		{
			//�X�^�~�i�𑝂₵�Ă���
			m_nStamina++;
		}
	}
	//�_�b�V�����Ă����
	if (m_bDash == true)
	{
		//�X�^�~�i��0�ȉ��ɂȂ�����
		if (m_nStamina <= 0)
		{
			//���̒l�ɂ���
			m_nStamina = 0;
		}
		//0�ȉ��ł͂Ȃ����
		else
		{
			//�X�^�~�i�����炵�Ă���
			m_nStamina--;
		}
	}
	//�_�b�V�����Ă��Ȃ����
	else
	{
		//�X�^�~�i���ő�l�ȏ�ɂȂ�����
		if (m_nStamina >= C2DGauge::GetFixed())
		{
			//���̒l�ɂ���
			m_nStamina = C2DGauge::GetFixed();
		}
		//�ő�l�ȏ�ł͂Ȃ����
		else
		{
			//�X�^�~�i�𑝂₵�Ă���
			m_nStamina++;
		}
	}

	//�Q�[�W�̒l�ݒ�
	CManager::GetScene()->GetGame()->GetGauge()->SetNum(m_nStamina);
}
//<===================================================================
//�B���ۂ̋���
//<===================================================================
void C3DPlayer::Hide(void)
{
	//�����̐�����
	for (int nCnt = 0; nCnt < CBuilding::GetNum(); nCnt++)
	{
		Collision::CollidXZ
		(CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetPosition(),
			CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetModel().rSizeX,
			CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetModel().rSizeZ,
			CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetModel().vtxMax,
			CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetModel().vtxMin,
			&m_pos, m_posOld, &m_move, m_sModel.vtxMax, m_sModel.vtxMin);

		//<****************************************
		//�B��鏈��
		//<****************************************
		//�������Ă�����
		if (Collision::CollidAll(CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetPosition(),
			CManager::GetScene()->GetGame()->GetBuil(nCnt)->GetHideRad(), m_pos, m_sModel.vtxMax, m_sModel.vtxMin))
		{
			//�B���Ԃ�������
			if (m_sState == STATE_HIDE)
			{
				//�\����������
				CManager::GetScene()->GetGame()->Get2DChar(CGame::CHAR2D_COMEOUT)->SetDisptrue();

				//�\���������Ȃ�
				CManager::GetScene()->GetGame()->Get2DChar(CGame::CHAR2D_HIDE)->SetDispfalse();
			}
			//�B���Ԃł͖������
			else if (m_sState == STATE_NONE)
			{

				//�\����������
				CManager::GetScene()->GetGame()->Get2DChar(CGame::CHAR2D_HIDE)->SetDisptrue();

				//�\�������Ȃ�
				CManager::GetScene()->GetGame()->Get2DChar(CGame::CHAR2D_COMEOUT)->SetDispfalse();
			}

			//�͈͓��ɓ����Ă���ۂɃL�[��������
			if (CManager::GetKeyboard()->bGetTrigger(DIK_SPACE) == true
				|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_B, 0))
			{
			
				//�X�e�[�g�������Ȃ��Ȃ�B���ԂɂȂ�A�B���ԂȂ牽���Ȃ��ɂ���
				m_sState == STATE_NONE ? m_sState = STATE_HIDE : m_sState = STATE_NONE;
				CManager::GetSound()->PlaySound(CSound::LABEL_SE_HIDE);
			}

			break;
		}
		//���Ȃ����
		else
		{
			//�\���������Ȃ�
			CManager::GetScene()->GetGame()->Get2DChar(CGame::CHAR2D_HIDE)->SetDispfalse();

			//�\�������Ȃ�
			CManager::GetScene()->GetGame()->Get2DChar(CGame::CHAR2D_COMEOUT)->SetDispfalse();
		}
	}
}
//<==================================
//3D�v���C���[�̃A�N�V�������̓���
//<==================================
void C3DPlayer::MoveAction(void)
{
//<************************
//���̊֐�����̃}�N����`
//<************************

#define GRAVITY			(3.14f)		//�d�͒l
#define JUMP_VALUE		(55.0f)		//�W�����v�̒l	

	//<*****************************************************
	//�W�����v�A�N�V�����֘A
	//<*****************************************************
	if (CManager::GetKeyboard()->bGetTrigger(DIK_SPACE) == true)//����A�L�[��������Ă����牺�̏��������s
	{
		//�����W�����v���Ă��Ȃ����
		if (m_bJump == false)
		{
			//�W�����v����
			m_move.y += JUMP_VALUE;

			//�W�����v��������ɂ���
			m_bJump = true;
		}
	}

#if 1
	//�����n�ʂ̉��ɗ���������������
	if (m_pos.y <= GROUND)
	{
		//�n�ʂ̈ʒu�ɕ␳
		m_pos.y = GROUND;
	
		//�W�����v�\�ɂ���
		m_bJump = false;

	}
	//����ȊO
	else
	{
		//�d�͂�t��
		m_move.y -= GRAVITY;

		//�W�����v���Ă��锻��ɂ���
		m_bJump = true;
	}
#else

#endif

}
//<===================================================
//3D�v���C���[�̈ړ�����
//<===================================================
void C3DPlayer::Movement(void)
{
	//�_�b�V�����Ă��Ȃ����
	if (m_bDash == false
		||m_nStamina <= 0)
	{
		//�_�b�V�����Ă��Ȃ��l�ɂ���
		m_fMoveValue = NO_DASH_VALUE;
	}
	//���Ă�����
	else if(m_bDash == true
		|| !(m_nStamina <= 0))
	{
		//�_�b�V�����Ă���l�ɂ���
		m_fMoveValue = DASH_VALUE;
	}

	//<***************************************************
	//�ړ��֘A
	//<***************************************************
	//��ړ�
	if (CManager::GetKeyboard()->bGetPress(DIK_W) == true || CManager::GetJoyPad()->YGetStickPressL(BUTTON_LY, 0) > 0)
	{
		//�J�����̌����ɍ��킹�Ĉړ�����
		m_move.x += sinf(-D3DX_PI * MOVE_DOWN + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;
		m_move.z += cosf(-D3DX_PI * MOVE_DOWN + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;

		m_fRotDest = D3DX_PI * MOVE_UP + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y;

		//RSHIFT��������Ă����Ԃ�������
		if (CManager::GetKeyboard()->bGetPress(DIK_LSHIFT)
			|| CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_LB, 0))
		{

			//�_�b�V�����Ă��Ȃ���Ԃ�������
			if (m_bDash == false)
			{
				//�_�b�V�����Ă����Ԃɂ���
				m_bDash = true;
			}
		}

	}
	//�����Ă�����
	else if (!(CManager::GetKeyboard()->bGetPress(DIK_W) == true || CManager::GetJoyPad()->YGetStickPressL(BUTTON_LY, 0) > 0))
	{
		//W������LSHIFT�������܂܃_�b�V��������h��
		m_bDash = false;
	}
	//<===================================================
	//���ړ�
	//<===================================================
	if (CManager::GetKeyboard()->bGetPress(DIK_S) == true || CManager::GetJoyPad()->YGetStickPressL(BUTTON_LY, 0) < 0)
	{
		//�J�����̌����ɍ��킹�Ĉړ�����
		m_move.x += sinf(-D3DX_PI * MOVE_UP + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;
		m_move.z += cosf(-D3DX_PI * MOVE_UP + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;

		m_fRotDest = D3DX_PI * MOVE_DOWN + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y;

		//RSHIFT��������Ă����Ԃ�������
		if (CManager::GetKeyboard()->bGetPress(DIK_LSHIFT)
			|| CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_LB, 0))
		{

			//�_�b�V�����Ă��Ȃ���Ԃ�������
			if (m_bDash == false)
			{
				//�_�b�V�����Ă����Ԃɂ���
				m_bDash = true;
			}
		}
	
	}
	//<=======================================
	//�L�[����(D�L�[)
	//<=======================================
	if (CManager::GetKeyboard()->bGetPress(DIK_D) == true || CManager::GetJoyPad()->XGetStickPressL(BUTTON_LX, 0) > 0)//����A�L�[��������Ă����牺�̏��������s
	{
		//���Ɉړ�
		m_move.x -= sinf(-D3DX_PI * MOVE_LR + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;
		m_move.z -= cosf(-D3DX_PI * MOVE_LR + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;

		//���f���̍����ɃJ������������
		m_fRotDest = -D3DX_PI * MOVE_LR + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y;

		//RSHIFT��������Ă����Ԃ�������
		if (CManager::GetKeyboard()->bGetPress(DIK_LSHIFT)
			|| CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_LB, 0))
		{
			//�_�b�V�����Ă��Ȃ���Ԃ�������
			if (m_bDash == false)
			{
				//�_�b�V�����Ă����Ԃɂ���
				m_bDash = true;
			}
		}

	}
	//<=======================================
	//�L�[����(A�L�[)
	//<=======================================
	if (CManager::GetKeyboard()->bGetPress(DIK_A) == true || CManager::GetJoyPad()->XGetStickPressL(BUTTON_LX, 0) < 0)//����A�L�[��������Ă����牺�̏��������s
	{
		//���Ɉړ�
		m_move.x += sinf(-D3DX_PI * MOVE_LR + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;
		m_move.z += cosf(-D3DX_PI * MOVE_LR + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y) * m_fMoveValue;

		//���f���̉E���ɃJ������������
		m_fRotDest = D3DX_PI * MOVE_LR + CManager::GetScene()->GetGame()->GetCamera()->m_rot.y;

		//RSHIFT��������Ă����Ԃ�������
		if (CManager::GetKeyboard()->bGetPress(DIK_LSHIFT)
			|| CManager::GetJoyPad()->bGetPress(BUTTON::BUTTON_LB, 0))
		{

			//�_�b�V�����Ă��Ȃ���Ԃ�������
			if (m_bDash == false)
			{
				//�_�b�V�����Ă����Ԃɂ���
				m_bDash = true;
			}
		}
	}
}