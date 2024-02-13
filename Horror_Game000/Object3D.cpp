//<==============================================
//3D�I�u�W�F�N�g���̏���[X�t�@�C���Ȃ�](Object3D.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "Object3D.h"
#include "manager.h"
#include "input.h"
#include "Texture.h"

//<=================================
//3D�I�u�W�F�N�g�̃R���X�g���N�^
//<=================================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_mtxWorld = {};

	m_pos	=	INIT_VECTOR;
	m_rot	=	INIT_VECTOR;
	m_move	=	INIT_VECTOR;
	m_Size	=	INIT_VECTOR;
	m_rCol = INIT_COL;
	m_eType = TYPE::TYPE_MAX;
	m_bDraw = true;
}
//<=================================
//3D�I�u�W�F�N�g�̃f�X�g���N�^
//<=================================
CObject3D::~CObject3D()
{

}
//<=================================
//
//<=================================
CObject3D *CObject3D::Create(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rSize,  const D3DXVECTOR3 rRot,const D3DXCOLOR rColor,
	const TYPE eType,const LPDIRECT3DTEXTURE9 pTexture)
{
	CObject3D *pObject3D = new CObject3D;

	assert(pObject3D != nullptr && pObject3D->Init() == S_OK);

	//���ݒ�
	pObject3D->SetPosition(rPos);
	pObject3D->SetSize(rSize);
	pObject3D->SetRotation(rRot);
	pObject3D->SetColor(rColor);
	pObject3D->BindTexture(pTexture);
	pObject3D->m_eType = eType;

	return pObject3D;
}
//<=================================
//3D�I�u�W�F�N�g�̏���������
//<=================================
HRESULT CObject3D::Init(void)
{

	//���_�o�b�t�@�̐���
	if (FAILED(CManager::GetRenderer()->GetDevice()->
		CreateVertexBuffer(sizeof(VERTEX_3D) *INT_VALUE::MAX_TOP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	SetVtx();

	return S_OK;
}
//<=========================================================================
//
//<=========================================================================
HRESULT CObject3D::InitWith(const D3DXVECTOR3 rPos, const D3DXVECTOR3 rSize,
	const D3DXVECTOR3 rRot, const D3DXCOLOR rColor, const TYPE eType, const LPDIRECT3DTEXTURE9 pTexture)
{
	//���_�o�b�t�@�̐���
	if (FAILED(CManager::GetRenderer()->GetDevice()->
		CreateVertexBuffer(sizeof(VERTEX_3D) *INT_VALUE::MAX_TOP,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,
			D3DPOOL_MANAGED,
			&m_pVtxBuff,
			NULL)))
	{
		return E_FAIL;
	}

	//���ݒ�
	SetPosition(rPos);
	SetSize(rSize);
	SetRotation(rRot);
	SetColor(rColor);
	BindTexture(pTexture);
	m_eType = eType;

	SetVtx();

	return S_OK;
}
//<=================================
//3D�I�u�W�F�N�g�̏I������
//<=================================
void CObject3D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}
//<=================================
//3D�I�u�W�F�N�g�̍X�V����
//<=================================
void CObject3D::Update(void)
{

}
//<=================================
//3D�I�u�W�F�N�g�̕`�揈��
//<=================================
void CObject3D::Draw(void)
{
	if (m_bDraw)
	{
		D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X(���̕ϐ��̓O���[�o���ϐ��ɂ͓���Ȃ�)

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//�����𔽉f������
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);//���̏��Ԃ͏d�v�ł���

																		   //���[���h�}�g���b�N�X���|����(��Z)
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f������
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		//���[���h�}�g���b�N�X���|����(��Z)
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		CManager::GetRenderer()->GetDevice()->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		CManager::GetRenderer()->GetDevice()->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		CManager::GetRenderer()->GetDevice()->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		CManager::GetRenderer()->GetDevice()->SetTexture(0, m_pTexture);

		CManager::GetRenderer()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//<=================================
//3D�I�u�W�F�N�g�̒��_�ݒ菈��
//<=================================
void CObject3D::SetVtx(void)
{
	VERTEX_3D *pVtx;//���_���ւ̃|�C���^

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//
	m_pos = GetPosition();
	m_rot = GetRotation();
	m_Size = GetSize();
	m_rCol = GetColor();
	m_fAngle = GetAngle();
	m_fLength = GetLength();

	//���ʌ^��������
	if (m_eType == TYPE::TYPE_PLANE)
	{
		////���_���W�̐ݒ�
		//pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y, m_pos.z + m_Size.z);
		//pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y, m_pos.z + m_Size.z);
		//pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y, m_pos.z - m_Size.z);
		//pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y, m_pos.z - m_Size.z);

		//����
		pVtx[0].pos.x = 0.0f + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
		pVtx[0].pos.y = 0.0f;
		pVtx[0].pos.z = 0.0f + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;

		//�E��
		pVtx[1].pos.x = 0.0f + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
		pVtx[1].pos.y = 0.0f;
		pVtx[1].pos.z = 0.0f + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;

		//����
		pVtx[2].pos.x = 0.0f + sinf(m_rot.z - m_fAngle) * m_fLength;
		pVtx[2].pos.y = 0.0f;
		pVtx[2].pos.z = 0.0f + cosf(m_rot.z - m_fAngle) * m_fLength;

		//�E��
		pVtx[3].pos.x = 0.0f + sinf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.y = 0.0f;
		pVtx[3].pos.z = 0.0f + cosf(m_rot.z + m_fAngle) * m_fLength;


		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	}
	//�c�^��������
	else if (m_eType == TYPE::TYPE_PLANE_Y)
	{
		//����
		pVtx[0].pos.x = 0.0f + sinf(m_rot.z + D3DX_PI + m_fAngle) * m_fLength;
		pVtx[0].pos.y = m_pos.y - cosf(m_rot.z + D3DX_PI + m_fAngle) * m_fLength;
		pVtx[0].pos.z = 0.0f;

		//�E��
		pVtx[1].pos.x = 0.0f + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
		pVtx[1].pos.y = m_pos.y - cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
		pVtx[1].pos.z = 0.0f;

		//����
		pVtx[2].pos.x = 0.0f + sinf(m_rot.z - m_fAngle) * m_fLength;
		pVtx[2].pos.y = m_pos.y - cosf(m_rot.z - m_fAngle) * m_fLength;
		pVtx[2].pos.z = 0.0f;

		//�E��
		pVtx[3].pos.x = 0.0f + sinf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.y = m_pos.y - cosf(m_rot.z + m_fAngle) * m_fLength;
		pVtx[3].pos.z = 0.0f;

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_rCol;
	pVtx[1].col = m_rCol;
	pVtx[2].col = m_rCol;
	pVtx[3].col = m_rCol;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();
}

