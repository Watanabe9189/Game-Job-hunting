//<============================================
//3D�G�l�~�[����(3DEnemy.cpp)
//
//Author:kazuki watanabe
//<============================================
#include "3DEnemy.h"
#include "game.h"
#include "Result.h"

//<**************************************************************
//���O�錾
//<**************************************************************
namespace
{
	const float SEARCH_MOVE				= 0.0045f;	//�T�����Ă��鎞�̈ړ���
	const float CHASE_VALUE				= 0.012f;	//�ǐՂ��Ă��鎞�̈ړ��l
	const float FACE_VALUE				= 0.075f;	//�����ړ��̎��̈ړ���
	const float ALPHA_VALUE				= 0.08f;	//�����x�̒l
	const float ALPHA_VALUE_HIGH		= 0.005f;	//�����^�̓����x�̒l
	const float DOUBLE_VALUE			= 1.7f;		//�{�ɂ���l
	const float ROTATE_VALUE			= 0.1f;		//��]�l

	const float RADIUSE_VALUE_NORMAL	= 800.0f;	//�ʏ�^�̔��a�̒l
	const float RADIUSE_VALUE_INVISIBLE = 700.0f;	//�����^�̔��a�̒l

	const int	MAX_INTERVAL			= 500;		//�Ԋu�̍ő�l

	const int	DEFAULT_NUM_SET			= 3;		//�G�̐��̃f�t�H���g�l
	const int	MAX_NUM_SET = 9;		//�G�̐��̃f�t�H���g�l
	const int	MIN_NUM_SET = 1;		//�G�̐��̃f�t�H���g�l
}

//<*******************************************
//�ÓI�����o�ϐ��̐錾
//<*******************************************
																//�e�N�X�`����

int C3DEnemy::m_nNumAll = NULL;			//��
#ifdef _DEBUG

int C3DEnemy::m_nNumSet = MAX_NUM_SET;

#else

int C3DEnemy::m_nNumSet = DEFAULT_NUM_SET;

#endif
int C3DEnemy::m_nNumMax = MAX_NUM_SET;
int C3DEnemy::m_nNumMin = MIN_NUM_SET;

//<==========================================
//�t�@�C�����w��
//<==========================================
const char		*C3DEnemy::m_acFilename[TYPE::TYPE_MAX] =
{
	"data/MODEL/Monster000.x",		//�ʏ�^
	"data/MODEL/Monster002.x",		//�����^
	"data/MODEL/Monster001.x",		//�����^
};

//<=======================================
//3D�G�l�~�[�̃R���X�g���N�^
//<=======================================
C3DEnemy::C3DEnemy(int nPriority)
{
	m_nNumAll++;

	//�l�̃N���A
	m_pos = INIT_VECTOR;
	m_rDestPos = INIT_VECTOR;
	m_rot = INIT_VECTOR;
	m_move = INIT_VECTOR;
 	m_fMoveValue = INITIAL_FLOAT;

	m_sState = STATE::STATE_SEARCH;
	m_sFastState = FAST_STATE::FAST_STATE_WAIT;

	m_nSoundCount = INITIAL_INT;
	m_nInterval = INITIAL_INT;
	m_nRandInter = INITIAL_INT;
	m_eType = TYPE::TYPE_MAX;

	m_fFrontDest = INIT_VECTOR;
	m_fBackDest = INIT_VECTOR;
	
	m_rTelportPos = INIT_VECTOR;
	m_sModel = {};

	m_pPlayer = nullptr;
	m_pSound = nullptr;
}
//<=======================================
//3D�G�l�~�[�̃f�X�g���N�^
//<=======================================
C3DEnemy::~C3DEnemy()
{
	m_nNumAll--;
}
//<=======================================
//3D�G�l�~�[�̐�������
//<=======================================
C3DEnemy *C3DEnemy::Create(const D3DXVECTOR3 pos ,const int nLife, const int nType, const int CoolTime)
{
	return nullptr;
}
//<=======================================
//3D�G�l�~�[�̏���������
//<=======================================
HRESULT C3DEnemy::Init(void)
{
	m_sModel = BindModel(m_acFilename[m_eType], true);
	
	SetDest();

	//�����̓G��������
	if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
	{
		//�����^�̔��a�ɂ���
		m_fSearchRad = RADIUSE_VALUE_INVISIBLE;
	}
	//�ʏ�^��������
	else if (m_eType == TYPE::TYPE_ENEMY_NORMAL)
	{
		//�ʏ�^�̔��a�ɂ���
		m_fSearchRad = RADIUSE_VALUE_NORMAL;
	}

	m_nRandInter = Calculate::CalculeteRandInt(3500, 1000);
	m_nSoundMax = Calculate::CalculeteRandInt(200, 100);

	//���[�h���Q�[���̎��̂�
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		//���_�����J��Ԃ�
		for (int nCntMaxMat = 0; nCntMaxMat < (int)m_sModel.dwNumMat; nCntMaxMat++)
		{
			//�����̓G��������
			if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
			{
				//�����̓����x�𓧖��F�ɂ���
				m_sModel.pMat[nCntMaxMat].MatD3D.Diffuse.a = COLOR_VALUE::ALPHA_CLEANNESS;
				m_sModel.pMat[nCntMaxMat].MatD3D.Ambient.a = COLOR_VALUE::ALPHA_CLEANNESS;
			}
		}
	}

	//���[�h���Q�[���̎��̂�
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		//�����̐���
		m_pSound = CSound::Create();

		assert(m_pSound != nullptr);
	}

return S_OK;
}
//<=======================================
//3D�G�l�~�[�̏I������
//<=======================================
void C3DEnemy::Uninit(void)
{
	//�������Ȃ����ƃ��������[�N����������
	CXObject::Uninit();

	//�T�E���h�j��
	if (m_pSound != nullptr)
	{
		//�j��
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}
}
//<=======================================
//3D�G�l�~�[�̍X�V����
//<=======================================
void C3DEnemy::Update(void)
{		
	//���[�h���Q�[���̎��̂�
	if (CManager::GetMode() == CScene::MODE_GAME)
	{
		//�܂��Q�[�����I����Ă��Ȃ����
		if (CManager::GetScene()->GetGame()->GetGame()->GetState() == CGame::STATE_NONE)
		{
			m_pPlayer = CScene::GetGame()->Get3DPlayer();
			//<***********************************
			//���ꂼ��̏��̎擾
			//<***********************************
			m_pos = GetPosition();
			m_rot = GetRotation();
			m_move = GetMove();

			//���Z���Ă���
			m_pos += m_move;

			//CManager::GetDebugProc()->Print("[�ʒu]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_pos.x, m_pos.y, m_pos.z);
			//CManager::GetDebugProc()->Print("[����]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_rDis.x, m_rDis.y, m_rDis.z);
			//CManager::GetDebugProc()->Print("[�ړI�̈ʒu]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_rDestPos.x, m_rDestPos.y, m_rDestPos.z);
			//CManager::GetDebugProc()->Print("[�O�ړI�̈ʒu]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_fFrontDest.x, m_fFrontDest.y, m_fFrontDest.z);
			//CManager::GetDebugProc()->Print("[���ƖړI�̈ʒu]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_fBackDest.x, m_fBackDest.y, m_fBackDest.z);

			//CManager::GetDebugProc()->Print("[���̃C���^�[�o��]�F%d\n", m_nInterval);
			//CManager::GetDebugProc()->Print("[���̃����_���C���^�[�o��]�F%d\n", m_nRandInter);
			//CManager::GetDebugProc()->Print("[���̃X�e�[�g]�F%d\n", m_sState);
			CManager::GetDebugProc()->Print("[�G�^�C�v]�F%d\n", m_eType);
			//CManager::GetDebugProc()->Print("[�o�b�t�@]�F%d\n", m_sModel.pBuffMat);

			MoveMent();

			ChangeRot();

			m_move.x += (0.0f - m_move.x) *0.1f;
			m_move.z += (0.0f - m_move.z) *0.1f;

			//�x�N�g���̎O�v�f�̐ݒ�
			SetVector3(m_pos, m_rot, m_move);
		}
	}
	else
	{
		//<***********************************
		//���ꂼ��̏��̎擾
		//<***********************************
		m_pos = GetPosition();
		m_rot = GetRotation();
		m_move = GetMove();

		//���Z���Ă���
		m_pos += m_move;

		//�x�N�g���̎O�v�f�̐ݒ�
		SetVector3(m_pos, m_rot, m_move);
	}
}
//<=======================================
//3D�G�l�~�[�̕`�揈��
//<=======================================
void C3DEnemy::Draw(void)
{
	CXObject::Draw();
}
//<=======================================
//3D�G�l�~�[�̍s������
//<=======================================
void C3DEnemy::MoveMent(void)
{
	D3DXVECTOR3 rRotDest = Calculate::CalculateDest(m_pos, m_rDestPos);

	//�����^��������
	if (m_eType == TYPE::TYPE_ENEMY_HIGHSPEED)
	{
		//�ҋ@��Ԃ�������
		if (m_sFastState == FAST_STATE::FAST_STATE_WAIT)
		{
			CManager::GetSound()->StopSound(CSound::LABEL_BGM_APPROACH);

			//�Ԋu�����l�𒴂��Ă�����
			if (m_nInterval >= m_nRandInter)
			{
				//�v���C���[���B��Ă��Ȃ����
				if (m_pPlayer->GetState() != C3DPlayer::STATE_HIDE)
				{
					//�s���X�e�[�g�Ɉڍs������
					m_sFastState = FAST_STATE::FAST_STATE_INTERVAL;
					CManager::GetSound()->PlaySound(CSound::LABEL::LABLE_SE_MOAN2);

					//�����Ă����
					if (Bool::bMove(m_pPlayer->GetMove()))
					{
						//�v���C���[�̓����Ă���ʒu�Ƀe���|�[�g����
						m_rTelportPos = D3DXVECTOR3(m_pPlayer->GetPosition().x + 150.0f
							* m_pPlayer->GetMove().x, 
							+m_pPlayer->GetPosition().y,
							m_pPlayer->GetPosition().z + 
							150.0f*m_pPlayer->GetMove().z);

						//���̃e���|�[�g�ʒu�ɍs��
						m_pos = m_rTelportPos;
					}
					//�����Ă��Ȃ����
					else
					{
						m_pos = m_pPlayer->GetPosition();
					}
					CScene::GetGame()->GetCamera()->Shake();
				}

				//����������
				m_nInterval = 0;

			}
			//���Ȃ����
			else
			{
				//�����Ă����
				if (Bool::bMove(m_pPlayer->GetMove()))
				{
					//���Z������
					m_nInterval++;
				}
			}

			//���_�����J��Ԃ�
			for (int nCntMaxMat = 0; nCntMaxMat < (int)m_sModel.dwNumMat; nCntMaxMat++)
			{
				if (m_sModel.pMat[nCntMaxMat].MatD3D.Diffuse.a <= COLOR_VALUE::ALPHA_CLEANNESS
					&&m_sModel.pMat[nCntMaxMat].MatD3D.Ambient.a <= COLOR_VALUE::ALPHA_CLEANNESS)
				{
					m_sModel.pMat[nCntMaxMat].MatD3D.Diffuse.a = COLOR_VALUE::ALPHA_CLEANNESS;
					m_sModel.pMat[nCntMaxMat].MatD3D.Ambient.a = COLOR_VALUE::ALPHA_CLEANNESS;
				}
				else
				{
					//�ԐF�ɕς���
					m_sModel.pMat[nCntMaxMat].MatD3D.Diffuse.a -= ALPHA_VALUE_HIGH;
					m_sModel.pMat[nCntMaxMat].MatD3D.Ambient.a -= ALPHA_VALUE_HIGH;
				}
			}
		}
		//ugoku��Ԃ�������
		else if (m_sFastState == FAST_STATE::FAST_STATE_MOVE)
		{

			m_rot.y = Calculate::RotateToDest(m_rot.y, rRotDest, ROTATE_VALUE);
		
			//�v���C���[�̈ʒu��ړI�n�Ƃ���
			SetDest(m_pPlayer->GetPosition());

			m_fMoveValue = 0.085f;

			//�ړ�����
			m_move.x = (m_rDestPos.x - m_pos.x - m_move.x)*m_fMoveValue;//X��
			m_move.z = (m_rDestPos.z - m_pos.z - m_move.z)*m_fMoveValue;//Z��

			 //�v���C���[���B��Ă����
			if (m_pPlayer->GetState() == C3DPlayer::STATE_HIDE)
			{
				//�Ԋu��ݒ肷��
				m_nInterval = MAX_INTERVAL;
			}

			 //�Ԋu�����l�𒴂��Ă�����
			if (m_nInterval >= MAX_INTERVAL)
			{
				//�s���X�e�[�g�Ɉڍs������
				m_sFastState = FAST_STATE_WAIT;
				m_nInterval = 0;
				m_nRandInter = Calculate::CalculeteRandInt(4000, 1000);
			}
			//���Ȃ����
			else
			{
				//���Z������
				m_nInterval++;
			}

			CollidPlayer();
		}
		//ugoku��Ԃ�������
		else if (m_sFastState == FAST_STATE::FAST_STATE_INTERVAL)
		{
			 //����
			 m_rot.y =Calculate::RotateToDest(m_rot.y,rRotDest, ROTATE_VALUE);

			//�v���C���[�̈ʒu��ړI�n�Ƃ���
			SetDest(m_pPlayer->GetPosition());

			CManager::GetSound()->SetBgm(2.0f, CSound::LABEL_BGM_APPROACH);
			CManager::GetSound()->PlaySound(CSound::LABEL_BGM_APPROACH);

			//�v���C���[���B��Ă����
			if (m_pPlayer->GetState() == C3DPlayer::STATE_HIDE)
			{
				//�s���X�e�[�g�Ɉڍs������
				m_sFastState = FAST_STATE_WAIT;
				m_nInterval = 0;
				m_nRandInter = Calculate::CalculeteRandInt(4000,1000);
			}

			//�Ԋu�����l�𒴂��Ă�����
			if (m_nInterval >= MAX_INTERVAL)
			{
				//�s���X�e�[�g�Ɉڍs������
				m_sFastState = FAST_STATE_MOVE;
				m_nInterval = 0;
			}
			//���Ȃ����
			else
			{
				//���Z������
				m_nInterval++;
			}
		}
		//�ҋ@��ԈȊO��������
		if (m_sFastState != FAST_STATE::FAST_STATE_WAIT)
		{
			//���_�����J��Ԃ�
			for (int nCntMaxMat = 0; nCntMaxMat < (int)m_sModel.dwNumMat; nCntMaxMat++)
			{
				//���ʂȏ��������Ȃ��悤�ɂ���
				if (m_sModel.pMat[nCntMaxMat].MatD3D.Diffuse.a != COLOR_VALUE::ALPHA_OPACITY
					&&m_sModel.pMat[nCntMaxMat].MatD3D.Ambient.a != COLOR_VALUE::ALPHA_OPACITY)
				{
					m_sModel.pMat[nCntMaxMat].MatD3D.Diffuse.a = COLOR_VALUE::ALPHA_OPACITY;
					m_sModel.pMat[nCntMaxMat].MatD3D.Ambient.a = COLOR_VALUE::ALPHA_OPACITY;
				}
			}

		}
	}
	//����ȊO�̎�ނ�������
	else
	{
		//�T���֐�
		Search();
		CollidPlayer();
	}
#ifdef _DEBUG

	//<========================================================
	//����^�C�v�ύX����
	//<========================================================
	//SPACE�L�[�������ꂽ��
	if (CManager::GetKeyboard()->bGetTrigger(DIK_F2) == true ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_BACK, 0) == true)
	{
		m_nInterval = m_nRandInter;
	}

#endif
}
//<=======================================
//3D�G�l�~�[
//<=======================================
void C3DEnemy::ChangeRot(void)
{

}
//<=======================================
//3D�G�l�~�[��
//<=======================================
void C3DEnemy::Search(void)
{
	D3DXVECTOR3 rRotDest = Calculate::CalculateDest(m_pos, m_rDestPos);

	//�������v�Z����(���̈ʒu-�ړI�Ƃ���ʒu)
	m_rDis = Calculate::CalculateDest(m_pos, m_pPlayer->GetPosition());

	Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false);

	//2000�܂Ő������A1000������
	D3DXVECTOR3 rRandDest = Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false);

	//�����̓G��������
	if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
	{
		//�T�E���h�Z�b�g
		SetSound(CSound::LABEL_SE_MOAN1, m_nSoundMax, m_pPlayer->GetPosition());
	}
	//�ʏ�^��������
	else if (m_eType == TYPE::TYPE_ENEMY_NORMAL)
	{
		//�T�E���h�Z�b�g
		SetSound(CSound::LABEL_SE_MOAN0, m_nSoundMax, m_pPlayer->GetPosition());
	}

	m_move.x = (m_rDestPos.x -m_pos.x - m_move.x) *m_fMoveValue;//X��
	m_move.z = (m_rDestPos.z - m_pos.z - m_move.z) *m_fMoveValue;//Z��

	 
	//�ǐՏ�Ԃ�������
	if (m_sState == STATE::STATE_CHASE)
	{
		SetDest(m_pPlayer->GetPosition());

		m_fMoveValue = CHASE_VALUE;

		//����
		m_rot.y = Calculate::RotateToDest(m_rot.y, rRotDest, ROTATE_VALUE);

		//��������Ă�����
		if (m_rDis.x >= m_fSearchRad
			|| m_rDis.x <= -m_fSearchRad
			|| m_rDis.z >= m_fSearchRad
			|| m_rDis.z <= -m_fSearchRad)
		{
			//�T�����[�h�Ɉڍs����
			m_sState = STATE_SEARCH;
			SetDest(rRandDest);
		}
		//�v���C���[���B��Ă�����
		if (m_pPlayer->GetState() == C3DPlayer::STATE_HIDE)
		{
			//�T�����[�h�Ɉڍs����
			SerachRot(rRandDest);
		}

		//�����^��������
		if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
		{
			m_sModel.pMat = Color::AlphaChangeMaterial(m_sModel.pMat, ALPHA_VALUE, m_sModel.dwNumMat);
		}
	}
	//�T�����[�h��������
	else if (m_sState == STATE_SEARCH)
	{
		m_fMoveValue = SEARCH_MOVE;

		//����
		m_rot.y = Calculate::RotateToDest(m_rot.y, rRotDest, ROTATE_VALUE);

		//�ړI�̈ʒu�ɂ�����
		if (m_pos.x >= m_fFrontDest.x&&m_pos.x <= m_fBackDest.x
			|| m_pos.x <= m_fFrontDest.x&&m_pos.x >= m_fBackDest.x
			&&m_pos.z >= m_fFrontDest.z&&m_pos.z <= m_fBackDest.z
			|| m_pos.z <= m_fFrontDest.z&&m_pos.z >= m_fBackDest.z)
		{
			SetDest(rRandDest);
		}
		if (m_pPlayer->GetState() != C3DPlayer::STATE_HIDE)
		{
			//�����߂Â��Ă�����
			if (m_rDis.x <= m_fSearchRad
				&& !(-m_rDis.x >= m_fSearchRad)
				&& m_rDis.z <= m_fSearchRad
				&& !(-m_rDis.z >= m_fSearchRad))
			{
				//�����̓G��������
				if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
				{
					m_pSound->PlaySoundWithVolume(CSound::LABEL_SE_NOTICED2, 2.0f);
				}
				//�ʏ�^��������
				else if (m_eType == TYPE::TYPE_ENEMY_NORMAL)
				{
					//�T�E���h�Z�b�g
					m_pSound->PlaySoundWithVolume(CSound::LABEL_SE_NOTICED1, 2.0f);
				}

				//�ǐՃ��[�h�ɂ���
				m_sState = STATE_CHASE;
			}
		}
		//�����^��������
		if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
		{
			m_sModel.pMat = Color::AlphaChangeMaterial(m_sModel.pMat, -ALPHA_VALUE, m_sModel.dwNumMat);
		}
	}
}
//<==========================================================================================================
//��������̖ړI�n�ݒ�
//<==========================================================================================================
void C3DEnemy::SetDest(const D3DXVECTOR3 rDestPos)
{
	//�ʒu�����߂�
	m_rDestPos = rDestPos;

	//��O�ƌ��̈ʒu��ݒ�
	m_fFrontDest = D3DXVECTOR3(m_rDestPos.x + 10.0f, m_rDestPos.y + 10.0f, m_rDestPos.z + 10.0f);
	m_fBackDest = D3DXVECTOR3(m_rDestPos.x - 10.0f, m_rDestPos.y - 10.0f, m_rDestPos.z - 10.0f);
	
}
//<========================================================
//�����Ȃ��̖ړI�n�ݒ�
//<========================================================
void C3DEnemy::SetDest(void)
{
	//2000�܂Ő������A1000������
	D3DXVECTOR3 rRandDest = Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false);

	//�ʒu�������_���Ō��߂�
	m_rDestPos = rRandDest;

	//��O�ƌ��̈ʒu��ݒ�
	m_fFrontDest = D3DXVECTOR3(m_rDestPos.x + 10.0f, m_rDestPos.y + 10.0f, m_rDestPos.z + 10.0f);
	m_fBackDest = D3DXVECTOR3(m_rDestPos.x - 10.0f, m_rDestPos.y - 10.0f, m_rDestPos.z - 10.0f);
}
//<=======================================
//3D�G�l�~�[�̃T�E���h�ݒ�
//<=======================================
void C3DEnemy::SetSound(const CSound::LABEL Label, const int nMaxCount, const D3DXVECTOR3 rTargetPos)
{
	//
	if (m_nSoundCount >= nMaxCount)
	{
		m_pSound->PlaySoundWithDis(Label, m_pos, rTargetPos);
		m_nSoundCount = 0;
	}
	//
	else
	{
		m_nSoundCount++;
	}
}
//<=======================================
//�t�@�C���ǂݍ��݂��g�p������������
//<=======================================
void C3DEnemy::SerachRot(const D3DXVECTOR3 rRandPos)
{
	m_fMoveValue = 0.0f;
	if (m_nInterval >= 500)
	{
		m_sState = STATE_SEARCH;
		SetDest(rRandPos);
		m_nInterval = 0;
	}
	if (m_nInterval >= 150
		&& !(m_nInterval >= 350))
	{
		m_rot.y = Calculate::RotateToDest(m_rot.y, D3DXVECTOR3(0.0f, 1.56f, 0.0f), 0.045f);
	}
	if (!(m_nInterval >= 150)
		&& m_nInterval >= 350)
	{
		m_rot.y = Calculate::RotateToDest(m_rot.y, D3DXVECTOR3(0.0f, 3.14f, 0.0f), 0.045f);
	}
	if (!(m_nInterval >= 500))
	{
		m_nInterval++;
	}
}
//<=======================================
//�t�@�C���ǂݍ��݂��g�p������������
//<=======================================
C3DEnemy *C3DEnemy::ReadCreate(C3DEnemy *apEnemy[MAX_OBJECT])
{
	//�K�v�ȊO�̕�����ǂݍ��ݗp�f�[�^
	char aChar[INT_VALUE::MAX_CHAR] = { NULL };

	//���ڂ��̏��
	int nCntMax = 0;

	//�t�@�C�����
	FILE *pFile = fopen("data/TEXT/SetEnemy.txt", "r");

	//�t�@�C�����J������
	if (pFile != NULL)
	{
		//�����ƌJ��Ԃ�
		while (strcmp(aChar, "EndFile") != 0)
		{
			//�󎚂�ǂݍ���
			(void)fscanf(pFile, "%s", &aChar[0]);

			//ENEMY-SET�Ƃ��������񂪑��݂�����
			if (strcmp(aChar, "ENEMY-SET") == 0)
			{
				//�������g���Ȃ����
				if (apEnemy[nCntMax] == nullptr)
				{
					apEnemy[nCntMax] = new C3DEnemy;
				}
			
				//End-Set�Ƃ���������F������܂ŌJ��Ԃ�
				while (strcmp(aChar, "End-Set"))
				{
					//�󎚂�ǂݍ���
					(void)fscanf(pFile, "%s", &aChar[0]);

					//�������m�ۂ���Ă�����
					if (apEnemy[nCntMax] != nullptr)
					{
						//TYPE�Ƃ��������񂪑��݂�����
						if (strcmp(aChar, "TYPE") == 0)
						{
							//�󎚂�ǂݍ���
							(void)fscanf(pFile, "%s", &aChar[0]);

							//�^�C�v��ǂݍ���
							(void)fscanf(pFile, "%d", &apEnemy[nCntMax]->m_eType);

						}
						apEnemy[nCntMax]->Init();

						//POS�Ƃ��������񂪑��݂�����
						if (strcmp(aChar, "POS") == 0)
						{
							//�󎚂�ǂݍ���
							(void)fscanf(pFile, "%s", &aChar[0]);

							//�ʒu��ǂݍ���
							(void)fscanf(pFile, "%f", &apEnemy[nCntMax]->m_pos.x);
							(void)fscanf(pFile, "%f", &apEnemy[nCntMax]->m_pos.y);
							(void)fscanf(pFile, "%f", &apEnemy[nCntMax]->m_pos.z);

							//�ʒu����
							apEnemy[nCntMax]->SetPosition(apEnemy[nCntMax]->m_pos);

							//�O��̈ʒu��ۑ����Ă���
							apEnemy[nCntMax]->m_OldPos = apEnemy[nCntMax]->m_pos;
						}
					}
					//
					apEnemy[nCntMax]->SetType3D(TYPE_3D::TYPE_ENEMY3D);
				}
				//���𑝂₷
				nCntMax++;
			}
		}
		//�t�@�C�������
		fclose(pFile);

	}
	return *apEnemy;
}
//<=================================================
//
//<=================================================
C3DEnemy *C3DEnemy::RandCreate(C3DEnemy *apEnemy[MAX_OBJECT])
{
	int nRandType = INITIAL_INT;
	D3DXVECTOR3 rRandPos = INIT_VECTOR;

	//�Z�b�g���鐔����
	for (int nCnt = 0; nCnt < m_nNumSet; nCnt++)
	{
		//
		apEnemy[nCnt] = new C3DEnemy;

		assert(apEnemy[nCnt] != nullptr);

		//�ő�̎�O�܂ōs���Ă����
		if (nCnt == m_nNumSet - 1)
		{
			apEnemy[nCnt]->m_eType = TYPE::TYPE_ENEMY_HIGHSPEED;
		}
		//�܂��ő�̎�O�܂ōs���Ă��Ȃ����
		else
		{
			nRandType = Calculate::CalculeteRandInt(TYPE::TYPE_ENEMY_INVISIBLE,
				TYPE::TYPE_ENEMY_NORMAL);

			apEnemy[nCnt]->m_eType = (TYPE)nRandType;
		}

		apEnemy[nCnt]->Init();

		rRandPos = D3DXVECTOR3(Calculate::CalculateRandfloat(4000, -4000), 0.0f, Calculate::CalculateRandfloat(2500, -4000));

		//�ʒu����
		apEnemy[nCnt]->SetPosition(rRandPos);

		//�O��̈ʒu��ۑ����Ă���
		apEnemy[nCnt]->m_OldPos = apEnemy[nCnt]->GetPosition();

		//
		apEnemy[nCnt]->SetType3D(TYPE_3D::TYPE_ENEMY3D);
	}

	return *apEnemy;
}
//<================================================
//
//<================================================
void C3DEnemy::CollidPlayer(void)
{
	//�B���Ԃł͖������
	if (m_pPlayer->GetState() != C3DPlayer::STATE_HIDE)
	{
		//�������Ă�����
		if (Collision::CollidAll(m_pPlayer->GetPosition(), m_pPlayer->GetModel().vtxMax,
			m_pos, m_sModel.vtxMax, m_sModel.vtxMin))
		{
			DeathSound();
		}
	}
}
//<================================================
//
//<================================================
void C3DEnemy::DeathSound(void)
{
	//���S�X�e�[�g�ɂ���
	m_pPlayer->SetState(C3DPlayer::STATE_DEATH);

	//���ׂẲ��y���~�߂�
	CManager::GetSound()->StopSound();
	m_pSound->StopSound();

	//�ʏ�^��������
	if (m_eType == TYPE::TYPE_ENEMY_NORMAL)
	{
		//����炷
		CManager::GetSound()->SetSE(1.2f, CSound::LABEL::LABEL_SE_DEATH0);
		CManager::GetSound()->PlaySound(CSound::LABEL::LABEL_SE_DEATH0);
		CResult::SetName(m_acFilename[m_eType]);
	}
	//�����^��������
	else if (m_eType == TYPE::TYPE_ENEMY_INVISIBLE)
	{
		//����炷
		CManager::GetSound()->SetSE(1.2f, CSound::LABEL::LABEL_SE_DEATE1);
		CManager::GetSound()->PlaySound(CSound::LABEL::LABEL_SE_DEATE1);
		CResult::SetName(m_acFilename[m_eType]);
	}
	//�����^��������
	else if (m_eType == TYPE::TYPE_ENEMY_HIGHSPEED)
	{	
		//����炷
		CManager::GetSound()->SetSE(1.2f, CSound::LABEL::LABEL_SE_DEATE2);
		CManager::GetSound()->PlaySound(CSound::LABEL::LABEL_SE_DEATE2);
		CResult::SetName(m_acFilename[m_eType]);
	}
}