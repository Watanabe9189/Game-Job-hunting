//<===============================================
//3D�I�u�W�F�N�g���̏���[X�t�@�C��](XObject.cpp)
//
//Author:kazuki watanabe
//<===============================================
#include "XObject.h"
#include "manager.h"
#include "Texture.h"

int CXObject::m_nNumAll = INITIAL_INT;

//<====================================
//X�t�@�C���I�u�W�F�N�g�̃R���X�g���N�^
//<====================================
CXObject::CXObject(int nPriority) : CObject(nPriority)
{
	//�l�̃N���A
	m_pMat = {};
	m_pVtxBuff = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_dwNumMat = NULL;
	m_mtxWorld = {};

	//�ʒu���֘A
	m_pos		=	INIT_VECTOR;
	m_rot		=	INIT_VECTOR;
	m_move		=	INIT_VECTOR;
	m_nNumVtx	=	INITIAL_INT;

	m_vtxMin = INIT_VECTOR;					//���_�̍ŏ��l
	m_vtxMax = INIT_VECTOR;					//���_�̍ő�l

	//
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_TEX; nCnt++)
	{
		m_apTexture[nCnt] = nullptr;
	}
	m_bDraw = true;
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

	//�`�悷��Ȃ�
	if (m_bDraw)
	{
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
		for (DWORD nCntMat = 0; nCntMat < m_dwNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			CManager::GetRenderer()->GetDevice()->SetMaterial(&m_pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			CManager::GetRenderer()->GetDevice()->SetTexture(0, m_apTexture[nCntMat]);

			//���f���̕`��
			m_pMesh->DrawSubset(nCntMat);
		}

		//�ۑ����Ă����}�e���A����߂�
		CManager::GetRenderer()->GetDevice()->SetMaterial(&matDef);
	}
}
//<====================================
//X�t�@�C���I�u�W�F�N�g�̕`�揈��
//<====================================
HRESULT CXObject::CheckVtx(D3DXVECTOR3 *VtxMax, D3DXVECTOR3 *VtxMin, float fRot)
{
	//���_�m�F�p�̃o�[�e�b�N�X�ϐ�
	D3DXVECTOR3 rVtx = INIT_VECTOR;

	//���f���̒��_�����擾
	if (FAILED(m_nNumVtx = m_pMesh->GetNumVertices()))
	{
		return E_FAIL;
	}

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	if (FAILED(m_dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF())))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N
	if (FAILED(m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&m_pVtxBuff)))
	{
		return E_FAIL;
	}

	//�S�Ă̒��_���`�F�b�N����
	for (int nCntVtx = 0; nCntVtx < m_nNumVtx; nCntVtx++)
	{
		//����̃f�[�^
		rVtx = *(D3DXVECTOR3*)m_pVtxBuff;

		//<***********************************
		//X������
		//<***********************************
		//���̍ŏ��l��������̒l��������������
		if (VtxMin->x > rVtx.x)
		{
			VtxMin->x = rVtx.x;
			m_vtxMin.x = rVtx.x;
		}
		//���̍ő�l��������̒l���傫��������
		if (VtxMax->x < rVtx.x)
		{
			VtxMax->x = rVtx.x;
			m_vtxMax.x = rVtx.x;
		}
		//<***********************************
		//Y������
		//<***********************************
		//���̍ŏ��l��������̒l��������������
		if (VtxMin->y > rVtx.y)
		{
			VtxMin->y = rVtx.y;
			m_vtxMin.y = rVtx.y;
		}
		//���̍ő�l��������̒l���傫��������
		if (VtxMax->y < rVtx.y)
		{
			VtxMax->y = rVtx.y;
			m_vtxMax.y = rVtx.y;
		}
		//<***********************************
		//Z������
		//<***********************************
		//���̍ŏ��l��������̒l��������������
		if (VtxMin->z > rVtx.z)
		{
			VtxMin->z = rVtx.z;
			m_vtxMin.z = rVtx.z;
		}
		//���̍ő�l��������̒l���傫��������
		if (VtxMax->z < rVtx.z)
		{
			VtxMax->z = rVtx.z;
			m_vtxMax.z = rVtx.z;
		}

		//�T�C�Y���|�C���^���ړ�������
		if (FAILED(m_pVtxBuff += m_dwSizeFVF))
		{
			return E_FAIL;
		}
	}

	//���_�o�b�t�@���A�����b�N
	if (FAILED(m_pMesh->UnlockVertexBuffer()))
	{
		return E_FAIL;
	}

	return S_OK;
}
//<====================================
//X�t�@�C���ǂݍ��݂̏���
//<====================================
HRESULT CXObject::LoadMesh(const char *pFileName, LPD3DXBUFFER *pBuffMat, DWORD *pDwNumMat, LPD3DXMESH *pMesh,
	D3DXMATERIAL *pMat, LPDIRECT3DTEXTURE9 const *pTex)
{
	//X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(pFileName,
		D3DXMESH_SYSTEMMEM,
		CManager::GetRenderer()->GetDevice(),
		NULL,
		pBuffMat,
		NULL,
		pDwNumMat,
		pMesh)))
	{
		return E_FAIL;
	}
	//�������蓖�Ăɂ����ꂩ�����s������
	if ((m_pBuffMat = *pBuffMat) == 0 || (m_dwNumMat = *pDwNumMat) == 0 || (m_pMesh = *pMesh) == 0)
	{
		//�x������\��
		MessageBox(NULL, "FAILED TO QUOTA POINTER", "ERROR", MB_ICONWARNING);

		return E_FAIL;
	}

	assert((m_pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer()) != nullptr);

	pMat = m_pMat;

	//���_�����J��Ԃ�
	for (DWORD nCntMat = 0; nCntMat < m_dwNumMat; nCntMat++)
	{
		//�t�@�C�������݂��Ă�����
		if (m_pMat[nCntMat].pTextureFilename != NULL && m_apTexture[nCntMat] == nullptr)
		{
			//�e�N�X�`�������蓖�Ă�
			CManager::GetTex()->Regist(
				m_pMat[nCntMat].pTextureFilename, m_apTexture[nCntMat]);
		}
	}

	//
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_TEX; nCnt++)
	{
		//������̃e�N�X�`���Ɋ��蓖�Ă�
		pTex = &m_apTexture[nCnt];

		//���ʂȏ������Ȃ�����
		if (m_apTexture[nCnt] == nullptr)
		{
			break;
		}
	}

	return S_OK;
}
//<====================================
//�}�e���A���̊��蓖��
//<====================================
void CXObject::BindMat(D3DXMATERIAL *pMat, LPDIRECT3DTEXTURE9 const *pTex)
{
	//���_�����J��Ԃ�
	for (DWORD nCntMat = 0; nCntMat < m_dwNumMat; nCntMat++)
	{
		//�t�@�C�������݂��Ă�����
		if (m_pMat[nCntMat].pTextureFilename != NULL && m_apTexture[nCntMat] == nullptr)
		{
			//�e�N�X�`�������蓖�Ă�
			CManager::GetTex()->Regist(
				m_pMat[nCntMat].pTextureFilename, m_apTexture[nCntMat]);
		}
	}

	//
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_TEX; nCnt++)
	{
		//������̃e�N�X�`���Ɋ��蓖�Ă�
		pTex = &m_apTexture[nCnt];

		//���ʂȏ������Ȃ�����
		if (m_apTexture[nCnt] == nullptr)
		{
			break;
		}
	}

}
//<====================================
//�T�C�Y�̐ݒ�
//<====================================
void CXObject::SetSize(D3DXVECTOR3 &rSize, D3DXVECTOR3 &rSizeX, D3DXVECTOR3 &rSizeZ)
{
	//�T�C�Y�̐ݒ�
	m_rSize = m_vtxMax - m_vtxMin;
	rSize = m_rSize;

	//���
	m_rSizeX = m_rSize;
	m_rSizeZ = m_rSize;

	//����p�ɔ�������
	m_rSizeX.z = m_rSizeX.z / 2.1f;
	m_rSizeZ.x = m_rSizeZ.x / 2.1f;
	rSizeX = m_rSizeX;
	rSizeZ = m_rSizeZ;
}
//<====================================
//�T�C�Y�̐ݒ�
//<====================================
CXObject *CXObject::Create(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rRot, const char *pFileName)
{
	CXObject *pXObject = new CXObject;

	assert(pXObject != nullptr);

	pXObject->LoadMesh(pFileName, &pXObject->m_pBuffMat, &pXObject->m_dwNumMat,
		&pXObject->m_pMesh, pXObject->m_pMat, pXObject->m_apTexture);

	pXObject->Init();

	pXObject->SetVector3(rPos, rRot, INIT_VECTOR);

	return pXObject;
}