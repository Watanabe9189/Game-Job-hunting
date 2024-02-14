//<======================================================================================
//
//
//
//<======================================================================================
#include "Plant.h"

LPDIRECT3DTEXTURE9	CPlant::m_apTexture[TYPE::TYPE_MAX] = {};		//�e�N�X�`���ւ̃|�C���^
const char*			CPlant::m_acFilename[TYPE::TYPE_MAX] =
{

	"data\\TEXTURE\\Grass.png",
	"data\\TEXTURE\\Tree000.png",
};

int CPlant::m_nNumAll = INITIAL_INT;

namespace
{
	const D3DXVECTOR3 GRASS_SIZE = D3DXVECTOR3(75.0f, 75.0f,0.0f);
	const D3DXVECTOR3 TREE_SIZE = D3DXVECTOR3(75.0f, 125.0f, 0.0f);
	const float GRASS_POSY = 25.0f;
	const float TREE_POSY = TREE_SIZE.y/2.0f;
}
CPlant::CPlant(int nPriority)
{
	//�l�̃N���A
	m_nNumAll++;

	m_rPos = INIT_VECTOR;
	m_rRot = INIT_VECTOR;
	m_rSize = INIT_VECTOR;
	m_rCol = INIT_COL;

	m_fMove = INITIAL_FLOAT;
}
CPlant::~CPlant()
{
	m_nNumAll--;
}
void CPlant::Swaying(void)
{

}
CPlant *CPlant::RandCreate(CPlant *apPlant[MAX_OBJECT], const int nNum)
{
	//�����ł����g��Ȃ��ϐ��̐錾
	D3DXVECTOR3 rRandPos = INIT_VECTOR;
	int nRandType = INITIAL_INT;

	//������
	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		apPlant[nCnt] = new CPlant;

		assert(apPlant[nCnt] != nullptr);

		nRandType = rand() % TYPE::TYPE_MAX + TYPE::TYPE_GRASS;

		if (nRandType == TYPE::TYPE_TREE)
		{
			rRandPos = D3DXVECTOR3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, TREE_POSY, 4000.0f), D3DXVECTOR3(-4000.0f, TREE_POSY, -4000.0f), true));
		}
		else
		{
			rRandPos = D3DXVECTOR3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, GRASS_POSY, 4000.0f), D3DXVECTOR3(-4000.0f, GRASS_POSY, -4000.0f), true));
		}

		apPlant[nCnt]->m_rPos = rRandPos;
		apPlant[nCnt]->m_eType = (TYPE)nRandType;

		apPlant[nCnt]->Init();
	}

	return *apPlant;
}

HRESULT CPlant::Init(void)
{
	if (m_eType == TYPE::TYPE_GRASS)
	{
		m_rSize = GRASS_SIZE;
	}
	else if (m_eType == TYPE::TYPE_TREE)
	{
		m_rSize = TREE_SIZE;
	}

	//�e�N�X�`���̏�����
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		//�ŏ������ǂݍ���
		if (m_apTexture[nCnt] == nullptr)
		{
			//�e�N�X�`���̓ǂݍ���
			if ((CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt])) <= -1)
			{
				return E_FAIL;
			}
		}
	}

	CObject3D::InitWith(m_rPos, m_rSize, INIT_VECTOR, m_rCol, CObject3D::TYPE::TYPE_PLANE_Y, m_apTexture[m_eType]);

	return S_OK;
}
void CPlant::Update(void)	
{
	CObject3D::SetVtx();

	//���̎擾
	m_rPos = GetPosition();
	m_rSize = GetSize();

	//���̐ݒ�
	SetPosition(m_rPos);
	SetSize(m_rSize);
	/*CManager::GetDebugProc()->Print("[�A���ʒu]�F{X��:%f},{Y��:%f},{Z��:%f}\n", m_rPos.x, m_rPos.y, m_rPos.z);*/
	//CManager::GetDebugProc()->Print("[�A���^�C�v]�F%d\n", m_eType);
}