//<=====================================================
//�n�ʏ���(Field.cpp)
//
//Author:kazuki watanabe
//<=====================================================
#include "Field.h"
#include "manager.h"
#include "Texture.h"

int CField::m_nNumAll = NULL;
LPDIRECT3DTEXTURE9 CField::m_pTexture = nullptr;

//<==========================
//�n�ʂ̃R���X�g���N�^
//<==========================
CField::CField()
{
	m_nNumAll++;
	//�l�̃N���A
	m_pos = INIT_VECTOR;
	m_rot = INIT_VECTOR;
	m_Size = INIT_VECTOR;
	m_mtxWorld = {};
	m_Depth = INITIAL_INT;
	m_width = INITIAL_INT;
	m_nNumIndex = INITIAL_INT;
	m_NumVtx = INITIAL_INT;
}
//<==========================
//�n�ʂ̃f�X�g���N�^
//<==========================
CField::~CField()
{
	m_nNumAll--;
}
//<==========================
//�n�ʂ̐�������
//<==========================
CField *CField::Create(const D3DXVECTOR3 pos)
{
	CField *pField = new CField;

	if (pField != NULL)
	{
		pField->m_pos = pos;

		//����������
		pField->Init();
	}

	return pField;
}
//<==========================
//�n�ʂ̏���������
//<==========================
HRESULT CField::Init(void)
{
	if (m_pTexture == nullptr)
	{
		if (FAILED(CManager::GetTex()->Regist("data/TEXTURE/Grass001.png", m_pTexture)))
		{
			return E_FAIL;
		}
	}

	//�l�̐ݒ�
	m_NumVtx = (m_width + 1) * (m_Depth + 1);								//���_��
	m_nNumIndex = (m_Depth * ((m_width + 1) * 2)) + (2 * (m_Depth - 1));	//�C���f�b�N�X��

	SetVtx();

	SetIndex();

	return S_OK;
}
//<==========================
//�n�ʂ̏I������
//<==========================
void CField::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	Release();
}
//<==========================
//�n�ʂ̍X�V����(���͎g��Ȃ�)
//<==========================
void CField::Update(void)
{
	
}
//<==========================
//�n�ʂ̕`�揈��
//<==========================
void CField::Draw(void)
{
	//���̊֐��ł����g��Ȃ��ϐ��錾
	D3DXMATRIX	mtxRot = {}, mtxTrans = {};		//�v�Z�p�}�g���b�N�X�錾

	//�A���t�@�e�X�g�̐ݒ�
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 255);					//0x000000FF[�����Ō���255�܂�]
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);			//�L���ɂ���
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);	//�l�����݂̃s�N�Z���̒l�ȏ�̏ꍇ�A�V�����s�N�Z�����󂯓����B

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

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	CManager::GetRenderer()->GetDevice()->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	CManager::GetRenderer()->GetDevice()->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	CManager::GetRenderer()->GetDevice()->SetFVF(FVF_VERTEX_3D_MULTI);

	//�e�N�X�`���̐ݒ�
	CManager::GetRenderer()->GetDevice()->SetTexture(0, m_pTexture);

	if (m_NumVtx != NULL && m_nNumIndex != NULL)
	{
		//�|���S���̕`��
		CManager::GetRenderer()->GetDevice()->DrawIndexedPrimitive(
			D3DPT_TRIANGLESTRIP,
			NULL,
			NULL,
			m_NumVtx,
			NULL,
			m_nNumIndex);

	}

	//�A���t�@�e�X�g�̐ݒ����
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0);//0�ɂ���
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);//�����ɂ���
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NEVER);//��Ɏ��s����

}
//<==========================
//�n�ʂ̒��_���ݒ菈��
//<==========================
void CField::SetVtx(void)
{
	if (m_pVtxBuff == nullptr)
	{
		//���_�o�b�t�@�̐���
		CManager::GetRenderer()->GetDevice()->CreateVertexBuffer(sizeof(VERTEX_3D) * m_NumVtx,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D_MULTI,
			D3DPOOL_MANAGED,
			&m_pVtxBuff,
			NULL);
	}
	
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(NULL, NULL, (void**)&pVtx, NULL);

	//���̃f�[�^����
	for (int nCntDepth = 0; nCntDepth < m_Depth; nCntDepth++)
	{
		for (int nCntWidth = 0; nCntWidth < m_width + 1; nCntWidth++)
		{//���̒��_�����J��Ԃ�

		 //���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(
				(m_Size.x * nCntWidth) - ((m_Size.x * m_width) * 0.5f),
				NULL,
				-((m_Size.z * nCntDepth) - ((m_Size.z * m_Depth) * 0.5f)));

			//�@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2
			(
				((float)nCntWidth / (1.0f / (float)(m_width + 1))) * (1.0f / (float)(m_width + 1)),
				((float)nCntDepth / (1.0f / (float)(m_Depth + 1))) * (1.0f / (float)(m_Depth + 1))
			);

			pVtx += 1;
		}


	}
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//<==========================
//�n�ʂ̃C���f�b�N�X���ݒ�
//<==========================
void CField::SetIndex(void)
{
	if (m_pIdxBuff == nullptr)
	{
		//�C���f�b�N�X�o�b�t�@�̐���
		CManager::GetRenderer()->GetDevice()->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&m_pIdxBuff,
			NULL);
	}

	//�C���f�b�N�X�o�b�t�@�̗v�f�ԍ�
	int nNumIdx = 0;

	//�C���f�b�N�X���ւ̃|�C���^
	WORD *pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//���̃f�[�^����
	for (int nCntDepth = 0; nCntDepth < m_Depth; nCntDepth++)
	{
		//���̒��_�����J��Ԃ�
		for (int nCntWidth = 0; nCntWidth < m_width + 1; nCntWidth++)
		{

			pIdx[nNumIdx + 0] = nCntWidth + (m_width + 1) * (nCntDepth + 1);
			pIdx[nNumIdx + 1] = nCntWidth + ((m_width + 1) * nCntDepth);

			//2���`�F�b�N
			nNumIdx += 2;
		}

		if (nCntDepth + 1 < m_Depth)
		{

			//��ł�2��
			pIdx[nNumIdx + 0] = ((m_width + 1) * (nCntDepth + 1)) - 1;
			pIdx[nNumIdx + 1] = (m_width + 1) * (nCntDepth + 2);

			//2���`�F�b�N
			nNumIdx += 2;

		}

	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
}
//<==========================
//�n�ʂ̓����蔻��
//<==========================
bool CField::CollisionField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, TYPE_3D Type3D)
{
	//�t�B�[���h�͈͓̔��ɂ���ꍇ
	if (pPos->x + vtxMax->x	  >=	m_pos.x - (m_Size.x  * m_width)
		&& pPos->x + vtxMin->x <= m_pos.x + (m_Size.x * m_width)
		&& pPos->z + vtxMax->z >= m_pos.z - (m_Size.z * m_Depth)
		&& pPos->z + vtxMin->z <= m_pos.z + (m_Size.z * m_Depth))
	{

	 //�������̉��ɍs�������ɂȂ�����
		if (-pPosOld->y >= m_pos.y &&
			pPos->y < m_pos.y)
		{
			pPos->y = m_pos.y;
			return true;
		}

	}
	return false;
}
//<==========================
//�n�ʂ̐���
//<==========================
CField *CField::ReadCreate(CField *apField[MAX_OBJECT])
{
	//�K�v�ȊO�̕�����ǂݍ��ݗp�f�[�^
	char aChar[INT_VALUE::MAX_CHAR] = { NULL };

	//���ڂ��̏��
	int nCntMax = 0;

	//�t�@�C�����
	FILE *pFile = nullptr;

	pFile = fopen("data/TEXT/SetField.txt", "r");

	//�t�@�C�����J������
	if (pFile != NULL)
	{
		//�����ƌJ��Ԃ�
		while (strcmp(aChar, "EndFile") != 0)
		{
			//�󎚂�ǂݍ���
			(void)fscanf(pFile, "%s", &aChar[0]);

			//ENEMY-SET�Ƃ��������񂪑��݂�����
			if (strcmp(aChar, "FIELD-SET") == 0)
			{

				//�������g���Ȃ����
				if (apField[nCntMax] == nullptr)
				{
					apField[nCntMax] = new CField;
				}

				//End-Set�Ƃ���������F������܂ŌJ��Ԃ�
				while (strcmp(aChar, "End-Set"))
				{
					//�󎚂�ǂݍ���
					(void)fscanf(pFile, "%s", &aChar[0]);

					//�������m�ۂ���Ă�����
					if (apField[nCntMax] != nullptr)
					{
						//POS�Ƃ��������񂪑��݂�����
						if (strcmp(aChar, "POS") == 0)
						{
							//�󎚂�ǂݍ���
							(void)fscanf(pFile, "%s", &aChar[0]);

							//�ʒu��ǂݍ���
							(void)fscanf(pFile, "%f", &apField[nCntMax]->m_pos.x);
							(void)fscanf(pFile, "%f", &apField[nCntMax]->m_pos.y);
							(void)fscanf(pFile, "%f", &apField[nCntMax]->m_pos.z);
						}
						//SIZE�Ƃ��������񂪑��݂�����
						if (strcmp(aChar, "SIZE") == 0)
						{
							//�󎚂�ǂݍ���
							(void)fscanf(pFile, "%s", &aChar[0]);

							//�T�C�Y��ǂݍ���
							(void)fscanf(pFile, "%f", &apField[nCntMax]->m_Size.x);
							(void)fscanf(pFile, "%f", &apField[nCntMax]->m_Size.y);
							(void)fscanf(pFile, "%f", &apField[nCntMax]->m_Size.z);
						}
						//DEPTH�Ƃ��������񂪑��݂�����
						if (strcmp(aChar, "DEPTH") == 0)
						{
							//�󎚂�ǂݍ���
							(void)fscanf(pFile, "%s", &aChar[0]);

							//���̕�������ǂݍ���
							(void)fscanf(pFile, "%d", &apField[nCntMax]->m_Depth);
						}
						//WIDTH�Ƃ��������񂪑��݂�����
						if (strcmp(aChar, "WIDTH") == 0)
						{
							//�󎚂�ǂݍ���
							(void)fscanf(pFile, "%s", &aChar[0]);

							//��O�̕�������ǂݍ���
							(void)fscanf(pFile, "%d", &apField[nCntMax]->m_width);
						}
					}

					//�������̕������Ǝ�O�̕������̒��g�����������
					if (apField[nCntMax]->m_width != NULL &&apField[nCntMax]->m_Depth != NULL)
					{
						//����������
						if (FAILED(apField[nCntMax]->Init()))
						{
							delete apField[nCntMax];
							apField[nCntMax] = nullptr;

							return *apField;
						}

					}
					
					//�^�C�v�̐ݒ�
					apField[nCntMax]->SetType3D(TYPE_3D::TYPE_FIELD);
				}
				//���𑝂₷
				nCntMax++;
			}
		}
		//�t�@�C�������
		fclose(pFile);

	}

	return *apField;
}
