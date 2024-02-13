#include "LandMark.h"
#include "game.h"

LPDIRECT3DTEXTURE9	CLandMark::m_apTexture[INT_VALUE::MAX_TEX] = {};		//�e�N�X�`���ւ̃|�C���^

const char*			CLandMark::m_acFilename[TYPE::TYPE_MAX]
{
	"data\\MODEL\\LandMark\\SignBoard000.x",
	"data\\MODEL\\LandMark\\TrunkTable000.x",
	"data\\MODEL\\LandMark\\Car000.x",
	"data\\MODEL\\LandMark\\House001.x",
};
int CLandMark::m_nNumAll = INITIAL_INT;
//<================================================
//
//<================================================
CLandMark::CLandMark(int nPriority)
{
	m_nNumAll++;

	//�l�̃N���A
	m_pos = INIT_VECTOR;
	m_rot = INIT_VECTOR;
	m_move = INIT_VECTOR;

	m_vtxMax = INIT_VECTOR;
	m_vtxMin = INIT_VECTOR;
	m_rSize = INIT_VECTOR;
	m_rSizeX = INIT_VECTOR;
	m_rSizeZ = INIT_VECTOR;

	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	m_pMat = NULL;

	m_eType = TYPE::TYPE_MAX;

	m_pBillBIcon = nullptr;
}
//<================================================
//
//<================================================
CLandMark::~CLandMark()
{
	m_nNumAll--;
}
//<================================================
//
//<================================================
CLandMark *CLandMark::FixedCreate(CLandMark *apLandMark[MAX_OBJECT])
{
	//�v���C���[�����擾����
	C3DPlayer *pPlayer = CManager::GetScene()->GetGame()->Get3DPlayer();

	//�G���A�̌��E�͈�
	const float MAX_AREA = 4000.0f;

	//�^�C�v�}�b�N�X���J��Ԃ�
	for (int nCnt = 0; nCnt < TYPE::TYPE_MAX; nCnt++)
	{
		apLandMark[nCnt] = new CLandMark;

		assert(apLandMark[nCnt] != nullptr);

		//���f���̓ǂݍ��݂�����
		apLandMark[nCnt]->LoadMesh(m_acFilename[nCnt], &apLandMark[nCnt]->m_pBuffMat,
			&apLandMark[nCnt]->m_dwNumMat,
			&apLandMark[nCnt]->m_pMesh, apLandMark[nCnt]->m_pMat, m_apTexture);

		//�����𕪂���
		switch (nCnt)
		{
			//��Ԗ�
		case TYPE::TYPE_FIRST:

			//�v���C���[�̏����ʒu�ɐݒ肷��
			apLandMark[nCnt]->SetPosition(D3DXVECTOR3(pPlayer->GetPosition().x, pPlayer->GetPosition().y, pPlayer->GetPosition().z + 200.0f));

			break;

			//��Ԗ�
		case TYPE::TYPE_SECOND:

			//���_�ɐݒ肷��
			apLandMark[nCnt]->SetPosition(INIT_VECTOR);

			break;

			//�O�Ԗ�
		case TYPE::TYPE_THIRD:


			//���_�ɐݒ肷��
			apLandMark[nCnt]->SetPosition(D3DXVECTOR3(Calculate::CalculateRandfloat(4000, -4000.0f), 0.0f, -2500.0f));

			break;

			//�l�Ԗ�
		case TYPE::TYPE_FOURTH:

			//���_�ɐݒ肷��
			apLandMark[nCnt]->SetPosition(D3DXVECTOR3(-2500.0f, 0.0f, Calculate::CalculateRandfloat(4000, -4000.0f)));

			break;
		}
	
		//�\��������
		apLandMark[nCnt]->m_pBillBIcon = CBilBIcon::Create(D3DXVECTOR3(apLandMark[nCnt]->GetPosition().x,
			apLandMark[nCnt]->GetPosition().y + 125.0f ,
			apLandMark[nCnt]->GetPosition().z),
			nCnt);

		//����������
		apLandMark[nCnt]->Init();

		//�������_�m�F�Ɏ��s������
		if (FAILED(apLandMark[nCnt]->CheckVtx(&apLandMark[nCnt]->m_vtxMax, &apLandMark[nCnt]->m_vtxMin, apLandMark[nCnt]->m_rot.y)))
		{
			return NULL;
		}

		//�T�C�Y�ݒ�
		apLandMark[nCnt]->SetSize(apLandMark[nCnt]->m_rSize, apLandMark[nCnt]->m_rSizeX, apLandMark[nCnt]->m_rSizeZ);

		//�^�C�v��ݒ肷��
		apLandMark[nCnt]->m_eType = (TYPE)nCnt;
	}


	return *apLandMark;
}
//<================================================
//
//<================================================
HRESULT CLandMark::Init(void)
{
	//�����������Ɏ��s������
	if (FAILED(CXObject::Init()))
	{
		return E_FAIL;
	}

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	if (FAILED(m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer()))
	{
		return E_FAIL;
	}

	return S_OK;
}
//<================================================
//
//<================================================
void CLandMark::Update(void)
{
	//�ʒu���擾
	m_pos = GetPosition();

	//�ړ��ʂ̎擾
	m_move = GetMove();

	//�������擾
	m_rot = GetRotation();

	m_pMat = GetMaterial();

	CManager::GetDebugProc()->Print("[�ʒu]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_pos.x, m_pos.y, m_pos.z);

	Collid();

	SetVector3(m_pos, m_rot, m_move);
}
//<================================================
//
//<================================================
void CLandMark::Collid(void)
{
	//�������Ă�����
	if (Collision::CollidAll(m_pos, m_rSize, CManager::GetScene()->GetGame()->Get3DPlayer()->GetPosition(),
		CManager::GetScene()->GetGame()->Get3DPlayer()->GetVtxMax(), CManager::GetScene()->GetGame()->Get3DPlayer()->GetVtxMin()))
	{
		//�������g�������
		if (m_pBillBIcon != nullptr)
		{
			//�\��������
			m_pBillBIcon->SetDrawtrue();
		}
	}
	else
	{
		//�������g�������
		if (m_pBillBIcon != nullptr)
		{
			//�\��������
			m_pBillBIcon->SetDrawfalse();
		}
	}
}