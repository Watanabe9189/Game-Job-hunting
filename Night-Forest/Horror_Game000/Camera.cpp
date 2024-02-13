//<==================================
//�J��������(Camera.cpp)
//
//Author:kazuki watanabe
//<==================================
#include "Camera.h"
#include "manager.h"
#include "input.h"
#include "DebugProc.h"

//<**************************************************
//���O�錾
//<**************************************************
namespace
{
	const float MOVE = 5.0f;					//�ړ���
	const float START_LENGTH = 800.0f;			//���̋���
	const float MAX_LENGTH = 10000.0f;			//�ő勗��
	const float MIN_LENGTH = 10.0f;				//�ŏ�����
	const float ROT_MOVE = 0.025f;				//��]�ړ���
	const float MIN_ROT = -D3DX_PI * 0.499f;	//�J�����Œ�p
	const float MAX_ROT = D3DX_PI * 0.499f;		//�J�����Œ�p

	
	const float REVISE_POSV = 0.12f;	//���_�̕␳�l
	const float REVISE_POSR = 0.8f;	//�����_�̕␳�l
	const float POSY_MAX = 90.0f;	//����(?)�̍ő�l
	const float DIS_Y = 150.0f;	//Y��������Ă���l

	const float MAX_DISTANCE = 5000.0f;
	const float MIN_DISTANCE = 1.0f;
}

//<=================================
//�J�����̃R���X�g���N�^
//<=================================
Ccamera::Ccamera()
{
	//�l�̃N���A
	m_posV = INIT_VECTOR;	//���_
	m_posR = INIT_VECTOR;	//�����_
	m_vecU = INIT_VECTOR;	//������x�N�g��
	m_rot =  INIT_VECTOR;	//����
	m_move = INIT_VECTOR;	//�ړ���

	m_fDistance = NULL;			//����

	m_rotVDiff = NULL;			//�ڕW�̎��_�̍���

	m_mtxProjection = {};		//�}�g���b�N�X�v���W�F�N�V����
	m_mtxView = {};				//�}�g���b�N�X�r���[

	m_Type = TYPE_XRAY;			//���e�^�C�v
}
//<=================================
//�J�����̃f�X�g���N�^
//<=================================
Ccamera::~Ccamera()
{

}
//<=================================
//�J�����̐�������
//<=================================
Ccamera *Ccamera::Create(void)
{
	Ccamera *pCamera = NULL;

	if (pCamera == NULL)
	{
		pCamera = new Ccamera();
	}

	if (pCamera != NULL)
	{
		pCamera->Init();
	}

	return pCamera;
}
//<=================================
//�J�����̏���������
//<=================================
HRESULT Ccamera::Init(void)
{
	m_posV = D3DXVECTOR3(-183.0f, 290.0f, 100.0f);	//���_
	m_posR = D3DXVECTOR3(0.0f, 200.0f, 0.0f);		//�����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//������x�N�g��
	m_rot = INIT_VECTOR;							//����
	m_move = INIT_VECTOR;							//�ړ���

	m_posROld = m_posR;								//�����_
	m_fDistance = START_LENGTH;						//����

	m_posVDest = m_posV;							//�ڕW�̎��_
	m_posRDest = m_posR;							//�ڕW�̒���
				
	m_rotVDest = m_rot;								//�ڕW�̌���
	m_rotVDiff = 0.0f;								//�ڕW�̎��_�̍���

	m_bFollow = false;								//�ǔ�����

	m_mtxProjection = {};
	m_mtxView = {};

	return S_OK;
}
//<=================================
//�J�����̏I������
//<=================================
void Ccamera::Uninit(void)
{

}
//<=================================
//�J�����̍X�V����
//<=================================
void Ccamera::Update(void)
{
	CManager::GetDebugProc()->Print("<=====================================================\n");
	CManager::GetDebugProc()->Print("[�J�����֘A�̃f�o�b�O�\��]\n");
	CManager::GetDebugProc()->Print("<=====================================================\n");
	CManager::GetDebugProc()->Print("[���_]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_posV.x, m_posV.y, m_posV.z);
	CManager::GetDebugProc()->Print("[�����_]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_posR.x, m_posR.y, m_posR.z);
	CManager::GetDebugProc()->Print("[����]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_rot.x, m_rot.y, m_rot.z);
	CManager::GetDebugProc()->Print("[����]�F%f\n",m_fDistance);

	//CManager::GetDebugProc()->Print("�Ǐ]�̐؂�ւ�[M�L�[]\n");
	//CManager::GetDebugProc()->Print("���e���@�̐؂�ւ�[LSHIFT]\n");

	//�Q�[����ʂ�������
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		//�W�����v���Ă����
		if (m_bFollow == true)
		{
			CManager::GetDebugProc()->Print("�Ǐ]���Ă��邩�ǂ���[���Ă���]\n\n");
			SetMoveFollow();
		}
		//���Ă��Ȃ����
		else
		{
			CManager::GetDebugProc()->Print("�Ǐ]���Ă��邩�ǂ���[���Ă��Ȃ�]\n\n");

			MoveVR();
		}
	}
	//�Q�[����ʂ�������
	if (CManager::GetMode() == CScene::MODE_TITLE)
	{
		//��]����
		m_rot.y += 0.005f;
		SetRot();
		SetV();
	}
	//�Q�[����ʂ�������
	if (CManager::GetMode() == CScene::MODE_RESULT)
	{
		//���U���g�����s��Ԃ�������
		if (CScene::GetRes() == CScene::TYPE_RESULT_FAILED)
		{
			m_posV = D3DXVECTOR3(-78.0f, 21.0f, -78.0f);
			m_posR = D3DXVECTOR3(-77.0f, 21.0f, -77.0f);
			m_rot = D3DXVECTOR3(0.0f, 0.46f, 0.17f);
			m_fDistance = 1.0f;
		}
		//���U���g��������Ԃ�������
		else if (CScene::GetRes() == CScene::TYPE_RESULT_SUCCEEDED)
		{
			m_posV = D3DXVECTOR3(6.0f, 27.0f, -113.0f);
			m_posR = D3DXVECTOR3(6.0f, 46.0f, 5.9f);
			m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.16f);
			m_fDistance = 121.0f;
		}
		/*ControllMouse();*/
	}

#ifdef _DEBUG
	////<***************************
	////���e���@�̃`�F���W
	////<***************************
	//if (CManager::GetKeyboard()->bGetTrigger(DIK_LSHIFT) == true)
	//{
	//	//�O�����Z�q
	//	m_Type == TYPE_XRAY ? m_Type = TYPE_PARALLEL : m_Type = TYPE_XRAY;

	//	//<*************************************************
	//	//�����e�F���P?���Q:���R
	//	//�������P���^�Ȃ玮�Q�����s���A�U�Ȃ玮�R�����s����
	//	//<*************************************************
	//}
#endif
}
//<=================================
//
//<=================================
void Ccamera::ControllMouse(void)
{
	m_fDistance -= CManager::GetMouse()->GetMouseMove().z;

	//
	if (CManager::GetMouse()->GetMousePress(CMouse::MOUSE_BUTTON_RIGHT))
	{
		m_rot.y += CManager::GetMouse()->GetMouseRotate().x;
		m_rot.z += CManager::GetMouse()->GetMouseRotate().y;
	}
	//
	if (CManager::GetMouse()->GetMousePress(CMouse::MOUSE_BUTTON_WHEEL))
	{
		m_posR.x += CManager::GetMouse()->GetMouseMove().x;
		m_posR.z += CManager::GetMouse()->GetMouseMove().z;
		m_posR.y += CManager::GetMouse()->GetMouseMove().y;
	}

	//
	if (m_fDistance >= MAX_DISTANCE)
	{
		m_fDistance = MAX_DISTANCE;
	}
	//
	if (m_fDistance <= MIN_DISTANCE)
	{
		m_fDistance = MIN_DISTANCE;
	}

	SetRot();
	SetV();
	SetR();
}
//<=================================
//
//<=================================
void Ccamera::SetMoveFollow(void)
{

	//<**************************************************
	//Z������]
	//<**************************************************
	//������ɉ�]����
	if (CManager::GetKeyboard()->bGetPress(DIK_R) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LX, 0) > 0)
	{

		m_rot.z += ROT_MOVE;

	}
	//�������ɉ�]����
	else if (CManager::GetKeyboard()->bGetPress(DIK_F) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LX, 0) < 0)
	{

		m_rot.z -= ROT_MOVE;

	}

	m_rot.y += CManager::GetMouse()->GetMouseRotate().x;
	m_rot.z += CManager::GetMouse()->GetMouseRotate().y;

	//<**************************************************
	//Y������]
	//<**************************************************
	//�������ɉ�]����
	if (CManager::GetKeyboard()->bGetPress(DIK_Z) == true || CManager::GetJoyPad()->XGetStickPressR(BUTTON_LY, 0) < 0)
	{
		m_rot.y -= ROT_MOVE;
	}
	//�E�����ɉ�]����
	else if (CManager::GetKeyboard()->bGetPress(DIK_C) == true || CManager::GetJoyPad()->XGetStickPressR(BUTTON_LY, 0) > 0)
	{
		m_rot.y += ROT_MOVE;
	}
	SetRot();
	SetV();
}
//<=================================
//
//<=================================
void Ccamera::MoveRot(void)
{
	CJoyPad *pJoyPad = CManager::GetJoyPad();

	//�Ǐ]���Ă��Ȃ����
	if (m_bFollow == false)
	{
		//z�������ɉ�]����
		if (CManager::GetKeyboard()->bGetPress(DIK_R) == true || pJoyPad->XGetStickPressR(BUTTON_LX, 0) < 0)
		{

			m_rot.z += ROT_MOVE;

		}
		//z�������ɋt��]����
		if (CManager::GetKeyboard()->bGetPress(DIK_F) == true || pJoyPad->XGetStickPressR(BUTTON_LX, 0) > 0)
		{

			m_rot.z -= ROT_MOVE;

		}
	}
	//Y�������ɉ�]����
	if (CManager::GetKeyboard()->bGetPress(DIK_Z) == true || pJoyPad->XGetStickPressR(BUTTON_LY, 0) < 0)
	{

		m_rot.y += ROT_MOVE;

	}
	//Y�������ɋt��]����
	if (CManager::GetKeyboard()->bGetPress(DIK_C) == true || pJoyPad->XGetStickPressR(BUTTON_LY, 0) > 0)
	{
		m_rot.y -= ROT_MOVE;
	}

	//��]�̕␳
	SetRot();

	//���_�̑������
	MoveVR();
}
//<=================================
//
//<=================================
void Ccamera::MoveVR(void)
{
	//�Ǐ]���Ă��Ȃ����
	if (m_bFollow == false)
	{
		//<**************************************
		//���ړ��֘A
		//<**************************************
		if (CManager::GetKeyboard()->bGetPress(DIK_LEFTARROW) == true || CManager::GetJoyPad()->XGetStickPressR(BUTTON_LX, 0) < 0)
		{
			//����ړ�
			if (CManager::GetKeyboard()->bGetPress(DIK_UPARROW) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LY, 0) > 0)
			{

				m_move.x += sinf(-D3DX_PI * MOVE_LRDW + m_rot.y) * MOVE;
				m_move.y += cosf(-D3DX_PI * MOVE_LRDW + m_rot.y) * MOVE;
			}
			//�����ړ�
			else if (CManager::GetKeyboard()->bGetPress(DIK_DOWNARROW) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LY, 0) < 0)
			{

				m_move.x += sinf(-D3DX_PI * MOVE_LRUP + m_rot.y) * MOVE;
				m_move.y += cosf(-D3DX_PI * MOVE_LRUP + m_rot.y) * MOVE;
			}
			//���ړ�
			else
			{

				m_move.x += sinf(-D3DX_PI * MOVE_LR + m_rot.y) * MOVE;
				m_move.y += cosf(-D3DX_PI * MOVE_LR + m_rot.y) * MOVE;
			}

		}
		//<**************************************
		//�E�ړ��֘A
		//<**************************************
		else if (CManager::GetKeyboard()->bGetPress(DIK_RIGHTARROW) == true || CManager::GetJoyPad()->XGetStickPressR(BUTTON_LX, 0) > 0)
		{

			//�E��ړ�
			if (CManager::GetKeyboard()->bGetPress(DIK_UPARROW) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LY, 0) > 0)
			{

				m_move.x += sinf(D3DX_PI * MOVE_LRDW + m_rot.y) * MOVE;
				m_move.y += cosf(D3DX_PI * MOVE_LRDW + m_rot.y) * MOVE;
			}
			//�E���ړ�
			else if (CManager::GetKeyboard()->bGetPress(DIK_DOWNARROW) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LY, 0) < 0)
			{

				m_move.x += sinf(D3DX_PI * MOVE_LRUP + m_rot.y) * MOVE;
				m_move.y += cosf(D3DX_PI * MOVE_LRUP + m_rot.y) * MOVE;
			}
			//�E�ړ�
			else
			{

				m_move.x += sinf(D3DX_PI * MOVE_LR + m_rot.y) * MOVE;
				m_move.y += cosf(D3DX_PI * MOVE_LR + m_rot.y) * MOVE;
			}

		}
		//<***************************
		//�O�ړ�
		//<***************************
		else if (CManager::GetKeyboard()->bGetPress(DIK_UPARROW) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LY, 0) > 0)
		{

			m_move.x += sinf(m_rot.y) * MOVE;
			m_move.y += cosf(m_rot.y) * MOVE;
		}

		//<***************************
		//��O�ړ�
		//<***************************
		else if (CManager::GetKeyboard()->bGetPress(DIK_DOWNARROW) == true || CManager::GetJoyPad()->YGetStickPressR(BUTTON_LY, 0) < 0)
		{

			m_move.x += sinf(D3DX_PI + m_rot.y) * MOVE;
			m_move.y += cosf(D3DX_PI + m_rot.y) * MOVE;
		}
	}
#ifdef _DEBUG
	//<***************************
	//���e���@�̃`�F���W
	//<***************************
	if (CManager::GetKeyboard()->bGetTrigger(DIK_M) == true)
	{
		m_bFollow == true ? m_bFollow = false : m_bFollow = true;
	}
#endif
	//�ړ��ʕ������Z
	m_posV.x += m_move.x;
	m_posV.y += m_move.y;
	m_posV.z += m_move.z;

	//�ړ��ʂ����Z�b�g
	m_move.x = 0.0f;
	m_move.y = 0.0f;
	m_move.z = 0.0f;
}
//<=================================
//
//<=================================
void Ccamera::SetV(void)
{
	//�Ǐ]���Ă��Ȃ����
	if (m_bFollow == false)
	{
		//���_�̑������
		m_posV.x = m_posR.x + cosf(m_rot.z) * sinf(m_rot.y) * -m_fDistance;
		m_posV.y = m_posR.y + sinf(m_rot.z) * -m_fDistance;
		m_posV.z = m_posR.z + cosf(m_rot.z) * cosf(m_rot.y) * -m_fDistance;
	}

	//<=================================
	//�Ǐ]�����͒Ǐ]�Ώۂ̏������ōs��
	//<=================================
}
//<=================================
//
//<=================================
void Ccamera::SetR(void)
{
	//�Ǐ]���Ă��Ȃ����
	if (m_bFollow == false)
	{
		//�����_�̑������
		m_posR.x = m_posV.x + cosf(m_rot.z) * sinf(m_rot.y) * m_fDistance;
		m_posR.z = m_posV.z + cosf(m_rot.z) * cosf(m_rot.y) * m_fDistance;
		m_posR.y = m_posV.y + sinf(m_rot.z) * m_fDistance;
	}

	//<=================================
	//�Ǐ]�����͒Ǐ]�Ώۂ̏������ōs��
	//<=================================
}
//<=================================
//
//<=================================
void Ccamera::SetRot(void)
{
	//<*******************
	//Y���̕␳
	//<*******************
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y = -D3DX_PI;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y = D3DX_PI;
	}

	//<*******************
	//Z���̕␳
	//<*******************
	if (m_rot.z > MAX_ROT)
	{
		m_rot.z = MAX_ROT;
	}
	else if (m_rot.z < MIN_ROT)
	{
		m_rot.z = MIN_ROT;
	}
}
//<=================================
//�J�����̒Ǐ]����
//<=================================
void Ccamera::SetFollow(const D3DXVECTOR3 rTargetPos, const D3DXVECTOR3 rTargetRot, const VISIBILITY eVisibility)
{
	//
	float PosY = INITIAL_FLOAT;			//

	if (!m_bFollow)
	{
		m_bFollow = true;
	}

	//�O�l�̎��_��������
	if (eVisibility == VISIBILITY::VISIBILITY_TPS)
	{
		//�����������ゾ������
		if (rTargetPos.y >= POSY_MAX)
		{
			PosY = rTargetPos.y - POSY_MAX;
		}
		//<*************************************************************************************
		//���_�̑������
		m_posVDest.x = (rTargetPos.x + sinf(D3DX_PI + rTargetRot.y) * POSY_MAX) + cosf(m_rot.z) *
			sinf(m_rot.y) * -m_fDistance;

		m_posVDest.y = PosY + DIS_Y + sinf(m_rot.z) * -m_fDistance;

		m_posVDest.z = (rTargetPos.z + cosf(D3DX_PI + rTargetRot.y) * POSY_MAX) + cosf(m_rot.z) *
			cosf(m_rot.y) * -m_fDistance;

		//���_�̕␳������
		m_posV += (m_posVDest - m_posV) * REVISE_POSV;
		//<*************************************************************************************
		//�����_�̑������
		m_posRDest.x = m_posV.x + cosf(m_rot.z) *
			sinf(m_rot.y) * m_fDistance;

		m_posRDest.y = m_posV.y + sinf(m_rot.z) *
			m_fDistance;

		m_posRDest.z = m_posV.z + cosf(m_rot.z) *
			cosf(m_rot.y) * m_fDistance;

		//�����_�̕␳������
		m_posR += (m_posRDest - m_posR) * REVISE_POSR;
	}
	//��l�̎��_��������
	else if (eVisibility == VISIBILITY::VISIBILITY_FPV)
	{
		//�����������ゾ������
		if (rTargetPos.y >= POSY_MAX)
		{
			PosY = rTargetPos.y - POSY_MAX;
		}
		//<*************************************************************************************
		//���_�̑������
		m_posVDest.x = (rTargetPos.x + sinf(D3DX_PI + m_rot.y));

		m_posVDest.y = PosY + DIS_Y + sinf(m_rot.z);

		m_posVDest.z = (rTargetPos.z + cosf(D3DX_PI + m_rot.y));

		//���_�̕␳������
		m_posV += (m_posVDest - m_posV) * REVISE_POSV;
		//<*************************************************************************************
		//�����_�̑������
		m_posRDest.x = m_posV.x + cosf(m_rot.z) *
			sinf(m_rot.y) * m_fDistance;

		m_posRDest.y = m_posV.y + sinf(m_rot.z) *
			m_fDistance;

		m_posRDest.z = m_posV.z + cosf(m_rot.z) *
			cosf(m_rot.y) * m_fDistance;

		//�����_�̕␳������
		m_posR += (m_posRDest - m_posR) * REVISE_POSR;
	}
}
//<=================================
//�J�����̐ݒu����
//<=================================
void Ccamera::SetCamera(void)
{
//<************************
//���̊֐�����̃}�N����`
//<************************
#define MAX_Z	(1000.0f)	//�v���W�F�N�V�����}�g���b�N�X�쐬����Z���̍ő�l
#define MIN_Z	(10.0f)		//�v���W�F�N�V�����}�g���b�N�X�쐬����Z���̍ŏ��l

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�^�C�v���������e�������ꍇ
	if (m_Type == TYPE_XRAY)
	{
		//�v���W�F�N�V�����}�g���b�N�X�̍쐬(�������e)
		//���I�u�W�F�N�g�̋����̉e�����󂯂�
		D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
			D3DXToRadian(45.0f),						//����
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//�c����
			MIN_Z,										//Z���̍ŏ��l
			MAX_Z);										//Z���̍ő�l
	}
	//�^�C�v�����s���e�������ꍇ
	else if (m_Type == TYPE_PARALLEL)
	{
		//�v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
		//���I�u�W�F�N�g�̋����̉e�����󂯂Ȃ�
		D3DXMatrixOrthoLH(&m_mtxProjection,
			SCREEN_WIDTH,	//��
			SCREEN_HEIGHT,	//����
			MIN_Z,			//Z���̍ŏ��l
			MAX_Z);			//Z���̍ő�l
	}		

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	CManager::GetRenderer()->GetDevice()->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	CManager::GetRenderer()->GetDevice()->SetTransform(D3DTS_VIEW, &m_mtxView);

}