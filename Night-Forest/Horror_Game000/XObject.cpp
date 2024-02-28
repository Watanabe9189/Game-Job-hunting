//<===============================================
//3D�I�u�W�F�N�g���̏���[X�t�@�C��](XObject.cpp)
//
//Author:kazuki watanabe
//<===============================================
#include "XObject.h"
#include "manager.h"
#include "Texture.h"

int CXObject::m_nNumAll = INITIAL_INT;
const char *CXObject::m_apFileName[INT_VALUE::MAX_SIZE] = {};
CXObject::DataModel CXObject::m_asaveModel[INT_VALUE::MAX_SIZE] = {};

//<====================================
//X�t�@�C���I�u�W�F�N�g�̃R���X�g���N�^
//<====================================
CXObject::CXObject(int nPriority) : CObject(nPriority)
{
	//�l�̃N���A
	m_mtxWorld = {};

	//�ʒu���֘A
	m_pos		=	INIT_VECTOR;
	m_rot		=	INIT_VECTOR;
	m_move		=	INIT_VECTOR;

	m_pMat = nullptr;

	m_asModel = {};
}
//<====================================
//X�t�@�C���I�u�W�F�N�g�̃f�X�g���N�^
//<====================================
CXObject::~CXObject()
{
	
}
//<====================================
//X�t�@�C���I�u�W�F�N�g�̏���������
//<====================================
HRESULT CXObject::Init(void)
{
	return S_OK;
}
//<====================================
//X�t�@�C���I�u�W�F�N�g�̏I������
//<====================================
void CXObject::Uninit(void)
{
	Release();
}
//<====================================
//X�t�@�C���I�u�W�F�N�g�̕`�揈��
//<====================================
void CXObject::Draw(void)
{
	//���̊֐��ł����g��Ȃ��ϐ��錾
	D3DXMATRIX			mtxRot = {}, mtxTrans = {};		//�v�Z�p�}�g���b�N�X�錾
	D3DMATERIAL9		matDef = {};					//���݂̃}�e���A���ۑ��p�ϐ�

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f����
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f����
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	CManager::GetRenderer()->GetDevice()->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A�����擾
	CManager::GetRenderer()->GetDevice()->GetMaterial(&matDef);
	
	//���_�����J��Ԃ�
	for (DWORD nCntMat = 0; nCntMat < m_asModel.dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		CManager::GetRenderer()->GetDevice()->SetMaterial(&m_asModel.pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		CManager::GetRenderer()->GetDevice()->SetTexture(0, m_asModel.apTexture[nCntMat]);

		//���f���̕`��
		m_asModel.pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	CManager::GetRenderer()->GetDevice()->SetMaterial(&matDef);
}
//<====================================
//
//<====================================
CXObject::DataModel CXObject::BindModel(const char *pFileName, const bool bMatChange)
{
	int nNum = m_nNumAll;

	//�����J��Ԃ�
	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		if (m_apFileName[nCnt] != nullptr)
		{
			//�����ۑ����ꂽ�t�@�C�����ƈ����̃t�@�C�������ꏏ��������
			if (strcmp(m_apFileName[nCnt], pFileName) == 0)
			{
				//���̔ԍ���Ԃ��A���łɓo�^����Ă���e�N�X�`��
				m_asModel = m_asaveModel[nCnt];

				//�����}�e���A����ύX�������ꍇ
				if (bMatChange)
				{
					//<==========================================
					//�F�ς��̂��߂ɂ�����x���f����ǂݍ���
					//(pBuffMat�ȊO�͂��łɕۑ�����Ă���f�[�^���g�p)
					//<==========================================
					if (FAILED(D3DXLoadMeshFromX(m_apFileName[nCnt],
						D3DXMESH_SYSTEMMEM,
						CManager::GetRenderer()->GetDevice(),
						NULL,
						&m_asModel.pBuffMat,			//���������ύX���郂�f���̈����ɂ���
						NULL,
						&m_asaveModel[nCnt].dwNumMat,
						&m_asaveModel[nCnt].pMesh)))
					{
						return{};
					}

					assert((m_asModel.pMat =
						(D3DXMATERIAL*)m_asModel.pBuffMat->GetBufferPointer()) != nullptr);

					m_asModel.pOriginMat = m_asaveModel[nCnt].pOriginMat;
					//<==========================================
					//
					//<==========================================
				}
				m_nModelId = nCnt;
				return m_asModel;
			}
		}
	}

	m_apFileName[nNum] = pFileName;

	//���f���̐ݒ���s��
	LoadModel();
	CheckVtxNo();

	m_nModelId = m_nNumAll;

	m_asModel = m_asaveModel[nNum];

	m_nNumAll++;

	return m_asModel;
}
//<====================================
//�T�C�Y�̐ݒ�
//<====================================
void CXObject::LoadModel(void)
{
	//X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(m_apFileName[m_nNumAll],
		D3DXMESH_SYSTEMMEM,
		CManager::GetRenderer()->GetDevice(),
		NULL,
		&m_asaveModel[m_nNumAll].pBuffMat,
		NULL,
		&m_asaveModel[m_nNumAll].dwNumMat,
		&m_asaveModel[m_nNumAll].pMesh)))
	{
		
	}

	assert((m_asaveModel[m_nNumAll].pMat =
		(D3DXMATERIAL*)m_asaveModel[m_nNumAll].pBuffMat->GetBufferPointer()) != nullptr);

	m_asaveModel[m_nNumAll].pOriginMat = m_asaveModel[m_nNumAll].pMat;

	//���_�����J��Ԃ�
	for (DWORD nCntMat = 0; nCntMat < m_asaveModel[m_nNumAll].dwNumMat; nCntMat++)
	{
		//�t�@�C�������݂��Ă�����
		if (m_asaveModel[m_nNumAll].pMat[nCntMat].pTextureFilename != NULL &&
			m_asaveModel[m_nNumAll].apTexture[nCntMat] == nullptr)
		{
			//�e�N�X�`�������蓖�Ă�
			CManager::GetTex()->Regist(
				m_asaveModel[m_nNumAll].pMat[nCntMat].pTextureFilename,
				m_asaveModel[m_nNumAll].apTexture[nCntMat]);
		}
	}
}
//<====================================
//�T�C�Y�̐ݒ�
//<====================================
void CXObject::CheckVtxNo(void)
{
	//���_�m�F�p�̃o�[�e�b�N�X�ϐ�
	D3DXVECTOR3 rVtx = INIT_VECTOR;

	//���f���̒��_�����擾
	m_asaveModel[m_nNumAll].nNumVtx = m_asaveModel[m_nNumAll].pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	m_asaveModel[m_nNumAll].dwSizeFVF = D3DXGetFVFVertexSize(m_asaveModel[m_nNumAll].pMesh->GetFVF());

	//���_�o�b�t�@�����b�N
	m_asaveModel[m_nNumAll].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_asaveModel[m_nNumAll].pVtxBuff);

	//�S�Ă̒��_���`�F�b�N����
	for (int nCntVtx = 0; nCntVtx < m_asaveModel[m_nNumAll].nNumVtx; nCntVtx++)
	{
		//����̃f�[�^
		rVtx = *(D3DXVECTOR3*)m_asaveModel[m_nNumAll].pVtxBuff;

		//<***********************************
		//X������
		//<***********************************
		//���̍ŏ��l��������̒l��������������
		if (m_asaveModel[m_nNumAll].vtxMin.x > rVtx.x)
		{
			m_asaveModel[m_nNumAll].vtxMin.x = rVtx.x;
		}
		//���̍ő�l��������̒l���傫��������
		if (m_asaveModel[m_nNumAll].vtxMax.x < rVtx.x)
		{
			m_asaveModel[m_nNumAll].vtxMax.x = rVtx.x;
		}
		//<***********************************
		//Y������
		//<***********************************
		//���̍ŏ��l��������̒l��������������
		if (m_asaveModel[m_nNumAll].vtxMin.y > rVtx.y)
		{
			m_asaveModel[m_nNumAll].vtxMin.y = rVtx.y;
		}
		//���̍ő�l��������̒l���傫��������
		if (m_asaveModel[m_nNumAll].vtxMax.y < rVtx.y)
		{
			m_asaveModel[m_nNumAll].vtxMax.y = rVtx.y;
		}
		//<***********************************
		//Z������
		//<***********************************
		//���̍ŏ��l��������̒l��������������
		if (m_asaveModel[m_nNumAll].vtxMin.z > rVtx.z)
		{
			m_asaveModel[m_nNumAll].vtxMin.z = rVtx.z;
		}
		//���̍ő�l��������̒l���傫��������
		if (m_asaveModel[m_nNumAll].vtxMax.z < rVtx.z)
		{
			m_asaveModel[m_nNumAll].vtxMax.z = rVtx.z;
		}

		//�T�C�Y���|�C���^���ړ�������
		m_asaveModel[m_nNumAll].pVtxBuff += m_asaveModel[m_nNumAll].dwSizeFVF;

	}

	//���_�o�b�t�@���A�����b�N
	m_asaveModel[m_nNumAll].pMesh->UnlockVertexBuffer();

	//�T�C�Y�̐ݒ�
	m_asaveModel[m_nNumAll].rSize = m_asaveModel[m_nNumAll].vtxMax - m_asaveModel[m_nNumAll].vtxMin;

	//���
	m_asaveModel[m_nNumAll].rSizeX = m_asaveModel[m_nNumAll].rSize;
	m_asaveModel[m_nNumAll].rSizeZ = m_asaveModel[m_nNumAll].rSize;

	//����p�ɔ�������
	m_asaveModel[m_nNumAll].rSizeX.z = m_asaveModel[m_nNumAll].rSizeX.z / 2.1f;
	m_asaveModel[m_nNumAll].rSizeZ.x = m_asaveModel[m_nNumAll].rSizeZ.x / 2.1f;
}
//<====================================
//�T�C�Y�̐ݒ�
//<====================================
CXObject *CXObject::Create(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rRot, const char *pFileName)
{
	CXObject *pXObject = new CXObject;

	assert(pXObject != nullptr);

	pXObject->BindModel(pFileName);

	pXObject->Init();

	pXObject->SetVector3(rPos, rRot, INIT_VECTOR);

	return pXObject;
}

