////<======================================================
//X�I�u�W�F�N�g�ł̌�������
//
//Author:Kazuki Watanabe
//<======================================================
#include "Building.h"

//<*******************************************
//�ÓI�����o�ϐ��̐錾
//<*******************************************
//�e�N�X�`���֘A
LPDIRECT3DTEXTURE9	CBuilding::m_apTexture[INT_VALUE::MAX_TEX] = { NULL };	//�e�N�X�`�����

int CBuilding::m_nNumAll = NULL;									//��
//<==========================================
//�t�@�C�����w��
//<==========================================
const char		*CBuilding::m_acFilename[TYPE::TYPE_MAX] =
{
	"data/MODEL/House.x",		//�G�Q
	"data/MODEL/Tent000.x",		//�G�R

};
//<==========================================
//�R���X�g���N�^
//<==========================================
CBuilding::CBuilding()
{
	m_nNumAll++;

	//�l�̃N���A
	m_pos = INIT_VECTOR;
	m_rot = INIT_VECTOR;
	m_move = INIT_VECTOR;

	m_pBuffMat = {};
	m_dwNumMat = {};
	m_pMesh = {};

	m_vtxMax = INIT_VECTOR;
	m_vtxMin = INIT_VECTOR;
	m_rSize = INIT_VECTOR;
	m_rSizeX = INIT_VECTOR;
	m_rSizeZ = INIT_VECTOR;

	m_pMat = nullptr;

	m_rHideRad = INIT_VECTOR;

}
//<==========================================
//�f�X�g���N�^
//<==========================================
CBuilding::~CBuilding()
{
	m_nNumAll--;
}
//<==========================================
//����������
//<==========================================
HRESULT CBuilding::Init(void)
{
	//�B�����͈͂�ݒ�
	m_rHideRad = D3DXVECTOR3(150.0f, 150.0f, 150.0f);

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
//<==========================================
//�X�V����
//<==========================================
void CBuilding::Update(void)
{
	//���擾
	m_pos = GetPosition();
	m_rot = GetRotation();

	//���ݒ�
	SetVector3(m_pos, m_rot, {});
}
//<==========================================
//��������
//<==========================================
CBuilding *CBuilding::Create(const D3DXVECTOR3 pos, const TYPE eType)
{
	CBuilding *pBuilding = new CBuilding;

	assert(pBuilding != nullptr);

	//���f���̓ǂݍ��݂�����
	assert(SUCCEEDED(pBuilding->LoadMesh(m_acFilename[eType], &pBuilding->m_pBuffMat, &pBuilding->m_dwNumMat, 
		&pBuilding->m_pMesh, pBuilding->m_pMat, m_apTexture)));
	
	//����������
	assert(SUCCEEDED(pBuilding->Init()));

	//�x�N�^�[����
	pBuilding->SetVector3(pos, pBuilding->m_rot, {});

	//
	pBuilding->SetType3D(TYPE_3D::TYPE_BUILDING);

	//�������_�m�F�Ɏ��s������
	if (FAILED(pBuilding->CheckVtx(&pBuilding->m_vtxMax, &pBuilding->m_vtxMin, pBuilding->m_rot.y)))
	{
		return nullptr;
	}

	//�T�C�Y�ݒ�
	pBuilding->SetSize(pBuilding->m_rSize, pBuilding->m_rSizeX, pBuilding->m_rSizeZ);

	return pBuilding;
}
//<==========================================
//��������(X�t�@�C������)
//<==========================================
CBuilding *CBuilding::ReadCreate(CBuilding *apBuilding[MAX_OBJECT])
{
	//�K�v�ȊO�̕�����ǂݍ��ݗp�f�[�^
	char aChar[INT_VALUE::MAX_CHAR] = { NULL };

	//���ڂ��̏��
	int nCntMax = 0;

	//�t�@�C�����
	FILE *pFile = fopen("data/TEXT/SetBuilding.txt", "r");

	//�t�@�C�����J������
	if (pFile != NULL)
	{
		//�����ƌJ��Ԃ�
		while (strcmp(aChar, "EndFile") != 0)
		{
			//�󎚂�ǂݍ���
			(void)fscanf(pFile, "%s", &aChar[0]);

			//ENEMY-SET�Ƃ��������񂪑��݂�����
			if (strcmp(aChar, "BUILDING-SET") == 0)
			{
				//�������g���Ȃ����
				if (apBuilding[nCntMax] == nullptr)
				{
					apBuilding[nCntMax] = new CBuilding;
				}

				//End-Set�Ƃ���������F������܂ŌJ��Ԃ�
				while (strcmp(aChar, "End-Set"))
				{
					//�󎚂�ǂݍ���
					(void)fscanf(pFile, "%s", &aChar[0]);

					//�������m�ۂ���Ă�����
					if (apBuilding[nCntMax] != nullptr)
					{
						//TYPE�Ƃ��������񂪑��݂�����
						if (strcmp(aChar, "TYPE") == 0)
						{
							//�󎚂�ǂݍ���
							(void)fscanf(pFile, "%s", &aChar[0]);

							//�^�C�v��ǂݍ���
							(void)fscanf(pFile, "%d", &apBuilding[nCntMax]->m_eType);

							assert(SUCCEEDED(apBuilding[nCntMax]->LoadMesh(
								m_acFilename[apBuilding[nCntMax]->m_eType],
								&apBuilding[nCntMax]->m_pBuffMat,
								&apBuilding[nCntMax]->m_dwNumMat,
								&apBuilding[nCntMax]->m_pMesh, apBuilding[nCntMax]->m_pMat, m_apTexture)));

							//�������������s��
							if ((apBuilding[nCntMax]->Init()) == 0xC0000005)
							{
								delete apBuilding[nCntMax];
								apBuilding[nCntMax] = nullptr;

								return *apBuilding;
							}

						}

						//POS�Ƃ��������񂪑��݂�����
						if (strcmp(aChar, "POS") == 0)
						{
							//�󎚂�ǂݍ���
							(void)fscanf(pFile, "%s", &aChar[0]);

							//�ʒu��ǂݍ���
							(void)fscanf(pFile, "%f", &apBuilding[nCntMax]->m_pos.x);
							(void)fscanf(pFile, "%f", &apBuilding[nCntMax]->m_pos.y);
							(void)fscanf(pFile, "%f", &apBuilding[nCntMax]->m_pos.z);

							//�ʒu����
							apBuilding[nCntMax]->SetPosition(apBuilding[nCntMax]->m_pos);
						}
					}
					//
					apBuilding[nCntMax]->SetType3D(TYPE_3D::TYPE_BUILDING);

					//�������_�m�F�Ɏ��s������
					if (FAILED(apBuilding[nCntMax]->CheckVtx(&apBuilding[nCntMax]->m_vtxMax, &apBuilding[nCntMax]->m_vtxMin, apBuilding[nCntMax]->m_rot.y)))
					{
						return nullptr;
					}

					//�T�C�Y�ݒ�
					apBuilding[nCntMax]->SetSize(apBuilding[nCntMax]->m_rSize, apBuilding[nCntMax]->m_rSizeX, apBuilding[nCntMax]->m_rSizeZ);
				}
				//���𑝂₷
				nCntMax++;
			}
		}
		//�t�@�C�������
		fclose(pFile);

	}
	return *apBuilding;
}
//<==========================================
//��������(X�t�@�C������)
//<==========================================
CBuilding *CBuilding::RandCreate(CBuilding *apBuilding[MAX_OBJECT], const int nNum)
{
	//�����ł����g��Ȃ��ϐ��̐錾
	D3DXVECTOR3 rRandPos = INIT_VECTOR;
	int nRandType = TYPE::TYPE_MAX;
	float nCollidRange = INITIAL_FLOAT;	

	//�����̐�����
	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		apBuilding[nCnt] = new CBuilding;

		assert(apBuilding[nCnt] != nullptr);

		//�����_���Œl�����߂�
		rRandPos = rRandPos = D3DXVECTOR3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false));
		nRandType = rand() % TYPE::TYPE_MAX + TYPE::TYPE_CABIN;

		//���f���̓ǂݍ��݂�����
		assert(SUCCEEDED(apBuilding[nCnt]->LoadMesh(m_acFilename[nRandType], &apBuilding[nCnt]->m_pBuffMat,
			&apBuilding[nCnt]->m_dwNumMat, &apBuilding[nCnt]->m_pMesh, apBuilding[nCnt]->m_pMat, m_apTexture)));

		//����������
		assert(SUCCEEDED(apBuilding[nCnt]->Init()));

		//�x�N�^�[����
		apBuilding[nCnt]->SetVector3(rRandPos, apBuilding[nCnt]->m_rot, {});
		apBuilding[nCnt]->m_eType = (CBuilding::TYPE)nRandType;

		//
		apBuilding[nCnt]->SetType3D(TYPE_3D::TYPE_BUILDING);

		//�������_�m�F�Ɏ��s������
		if (FAILED(apBuilding[nCnt]->CheckVtx(&apBuilding[nCnt]->m_vtxMax, &apBuilding[nCnt]->m_vtxMin, apBuilding[nCnt]->m_rot.y)))
		{
			return nullptr;
		}

		//�T�C�Y�ݒ�
		apBuilding[nCnt]->SetSize(apBuilding[nCnt]->m_rSize, apBuilding[nCnt]->m_rSizeX, apBuilding[nCnt]->m_rSizeZ);

		//�����̐�����
		for (int nCntBefore = -1; nCntBefore < m_nNumAll-1; nCntBefore++)
		{
			//������O�̌����̒��g�������
			if (nCntBefore != -1 && apBuilding[nCntBefore] != nullptr)
			{
				nCollidRange = 350.0f;

				//<****************************************
				//�B��鏈��
				//<****************************************
				//�ǂ̎��ɂ��������Ă�����
				if (apBuilding[nCntBefore]->GetPosition().z + nCollidRange > apBuilding[nCnt]->GetPosition().z + apBuilding[nCnt]->GetVtxMin().z&&
					apBuilding[nCntBefore]->GetPosition().z + -nCollidRange < apBuilding[nCnt]->GetPosition().z + apBuilding[nCnt]->GetVtxMax().z&&
					apBuilding[nCntBefore]->GetPosition().x + nCollidRange > apBuilding[nCnt]->GetPosition().x + apBuilding[nCnt]->GetVtxMin().x&&
					apBuilding[nCntBefore]->GetPosition().x + -nCollidRange< apBuilding[nCnt]->GetPosition().x + apBuilding[nCnt]->GetVtxMax().x&&
					apBuilding[nCntBefore]->GetPosition().y + nCollidRange > apBuilding[nCnt]->GetPosition().y + apBuilding[nCnt]->GetVtxMin().y&&
					apBuilding[nCntBefore]->GetPosition().y + -nCollidRange < apBuilding[nCnt]->GetPosition().y + apBuilding[nCnt]->GetVtxMax().y)
				{
					rRandPos = D3DXVECTOR3(Calculate::CalculteRandVec3(D3DXVECTOR3(4000.0f, 0.0f, 4000.0f), D3DXVECTOR3(-4000.0f, 0.0f, -4000.0f), false));
					apBuilding[nCntBefore]->SetPosition(rRandPos);
				}
			}
		}
	}
	return *apBuilding;
}