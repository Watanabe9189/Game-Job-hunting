#include "Item.h"
#include "game.h"
#include "3DParticle.h"
//<*******************************************
//�ÓI�����o�ϐ��̐錾
//<*******************************************
//�e�N�X�`���֘A
//<==========================================
//�t�@�C�����w��
//<==========================================
const char		*CItem::m_acFilename[TYPE::TYPE_MAX] =
{
	"data/MODEL/Item000-V2.x",		//�A�C�e���P
	"data/MODEL/Item000-V2.x",		//�A�C�e���Q
	"data/MODEL/Item000-V2.x",		//�A�C�e���R
	"data/MODEL/Item000-V2.x",		//�A�C�e���S
	"data/MODEL/Item000-V2.x",		//�A�C�e���T
};
//<==========================================
//Int�^
//<==========================================
int CItem::m_nNumAll = NULL;									//��
int CItem::m_NumCollect = NULL;									//��
int CItem::m_MaxNum = NULL;										//�ő�̐�
int CItem::m_nLeft = NULL;

//<==========================================================
//
//<==========================================================
CItem::CItem(int nPriority)
{
	//�ő�l
	m_nNumAll++;
	m_MaxNum = m_nNumAll;

	//�l�̃N���A
	m_pos = INIT_VECTOR;
	m_rot = INIT_VECTOR;

	m_eType = TYPE::TYPE_MAX;

	m_bGet = false;
	m_bAppro = false;

	m_pPlayer = nullptr;
}
//<==========================================================
//
//<==========================================================
CItem::~CItem()
{
	//�ÓI�����o�ϐ��̏�����
	m_nNumAll--;
	m_MaxNum = INITIAL_INT;
	m_NumCollect = INITIAL_INT;
	m_nLeft = INITIAL_INT;
}
//<==========================================================
//�P�̂ł̓ǂݍ���
//<==========================================================
CItem *CItem::Create(const D3DXVECTOR3 pos, const TYPE eType)
{
	//�C���X�^���X����
	CItem *pItem = new CItem;

	//���g�`�F�b�N
	assert(pItem != nullptr);

	//���ݒ�
	pItem->SetVector3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false), pItem->m_rot, {});
	pItem->m_eType = eType;

	//�A�C�e���^�C�v�ɐݒ�
	pItem->SetType3D(TYPE_3D::TYPE_ITEM);

	return pItem;
}
//<==========================================================
//
//<==========================================================
HRESULT CItem::Init(void)
{
	//�������ƃ}�e���A���f�[�^�擾�ǂ�����������Ă��邩�̃`�F�b�N
	assert(SUCCEEDED(CXObject::Init()));

	m_sModel = BindModel(m_acFilename[m_eType]);

	return S_OK;
}
//<==========================================================
//�����_������
//<==========================================================
CItem *CItem::RandCreate(CItem *apItem[MAX_OBJECT], int nNum)
{
	//�ϐ��錾
	D3DXVECTOR3 rRandPos = INIT_VECTOR;
	int nRandType = TYPE::TYPE_MAX;

	//������������
	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		//�C���X�^���X�𐶐�����
		apItem[nCnt] = new CItem;

		//���g�`�F�b�N
		assert(apItem[nCnt] != nullptr);

		rRandPos = D3DXVECTOR3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false));
		nRandType = rand() % TYPE::TYPE_MAX + TYPE::TYPE_ITEM0;

		//���ݒ�
		apItem[nCnt]->SetVector3(rRandPos, apItem[nCnt]->m_rot, {});
		apItem[nCnt]->m_eType = (CItem::TYPE)nRandType;

		apItem[nCnt]->Init();

		//�A�C�e���^�C�v�ɐݒ�
		apItem[nCnt]->SetType3D(TYPE_3D::TYPE_ITEM);

		//<******************************************
		//�ǂ̔j��
		//<******************************************
		for (int nCntBuild = 0; nCntBuild < CBuilding::GetNum(); nCntBuild++)
		{
			//���g�������
			if (CManager::GetScene()->GetGame()->GetBuil(nCnt) != nullptr)
			{
				//
				if (Collision::CollidAll(CManager::GetScene()->GetGame()->GetBuil(nCntBuild)->GetPosition(),
					CManager::GetScene()->GetGame()->GetBuil(nCntBuild)->GetModel().rSize,
					apItem[nCnt]->GetPosition(), apItem[nCnt]->GetModel().vtxMax, apItem[nCnt]->GetModel().vtxMin)==true)
				{
					//�d�Ȃ�Ȃ��悤�Ɉʒu��ς���
					rRandPos = D3DXVECTOR3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false));
					apItem[nCnt]->SetPosition(rRandPos);
				}
			}
		}
	}

	//�c�萔��������
	m_nLeft = nNum;

	//�S���̃|�C���^��Ԃ�
	return *apItem;
}
//<==========================================================
//
//<==========================================================
void CItem::Update(void)
{
	//�Q�b�g���Ă��Ȃ���Ԃ�������
	if (!m_bGet)
	{
		//���擾
		m_pos = GetPosition();
		m_rot = GetRotation();

		m_rot.y = Correction::NormalizeRotation(m_rot.y);

	/*	m_pMat = GetMaterial();*/

		//�����擾���Ă���
		m_pPlayer = CManager::GetScene()->GetGame()->Get3DPlayer();

		m_rot.y += 0.01f;

	/*	CManager::GetDebugProc()->Print("[�A�C�e���ʒu]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_pos.x, m_pos.y, m_pos.z);*/
		/*CManager::GetDebugProc()->Print("[�A�C�e������]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_rot.x, m_rot.y, m_rot.z);*/
		//CManager::GetDebugProc()->Print("[�A�C�e���^�C�v]�F%d\n", m_eType);

		Collid();

		//���ݒ�
		SetVector3(m_pos, m_rot, {});
	}
}
//<==========================================================
//
//<==========================================================
void CItem::Collid(void)
{
	//�������Ă����
	if (Collision::CollidAll(m_pPlayer->GetPosition(), m_pPlayer->GetModel().rSize,
		m_pos, m_sModel.vtxMax, m_sModel.vtxMin))
	{
		m_bAppro = true;

		//L�{�^���������ꂽ+�Q�b�g��Ԃ�false��������
		if (CManager::GetKeyboard()->bGetTrigger(DIK_L) || CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_A, 0) && !m_bGet)
		{
			//�Q�b�g��������ɂ���
			/*C3DParticle::Create(m_pos, D3DXCOLOR(1.0f, 0.5f, 0.1f, 1.0f), C3DParticle::TYPE::TYPE_TEST);*/
			m_NumCollect++;
			m_nLeft--;
			CManager::GetSound()->PlaySound(CSound::LABEL::LABEL_SE_ITEMGET);
			m_bGet = true;
		}
	}
	//�������Ă��Ȃ����
	else
	{
		m_bAppro = false;
	}
}