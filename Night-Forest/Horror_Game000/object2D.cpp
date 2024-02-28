//<==============================================
//2D�I�u�W�F�N�g���̏���(2DObject.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "object2D.h"
#include "manager.h"
#include "renderer.h"
#include "Texture.h"

//<*************************************************************************
// �}�N����`
//<*************************************************************************

//<**********************************************
//�ÓI�����o�ϐ��̐錾
//<**********************************************

//<==================================================================================
//�I�u�W�F�N�g2D�̃R���X�g���N�^
//<==================================================================================
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	//�l�̃N���A
	m_aObj.pos = D3DXVECTOR2(0.0f,0.0f);
	m_aObj.rot = INIT_VECTOR;
	m_aObj.move = D3DXVECTOR2(0.0f, 0.0f);
	m_aObj.Size = D3DXVECTOR2(0.0f, 0.0f);
	m_aObj.Col = COLOR_VALUE::COLOR_INIT;
	m_aObj.fAngle = INITIAL_FLOAT;
	m_aObj.fLength = INITIAL_FLOAT;

	m_pTexture = NULL;							//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;							//���_�o�b�t�@
}
//<==================================================================================
//�I�u�W�F�N�g2D�̃f�X�g���N�^
//<==================================================================================
CObject2D::~CObject2D()
{

}
//<==================================================================================
//�I�u�W�F�N�g2D�̐�������
//<==================================================================================
CObject2D *CObject2D::Create(const D3DXVECTOR2 rPos, const D3DXVECTOR2 rSize, const D3DXCOLOR rColor,const LPDIRECT3DTEXTURE9 pTexture)
{
	//�C���X�^���X����
	CObject2D *pObject2D = new CObject2D;

	//���g�Ə������`�F�b�N
	assert(pObject2D != nullptr && pObject2D->Init() == S_OK);

	pObject2D->SetPosition(rPos);

	pObject2D->SetSize(rSize);

	pObject2D->SetColor(rColor);

	pObject2D->BindTexture(pTexture);

	return pObject2D;

}
//<==================================================================================
//2D�I�u�W�F�N�g�̏���������
//<==================================================================================
HRESULT CObject2D::Init(void)
{
	//���_�o�b�t�@�̐���
	if (CManager::GetRenderer()->GetDevice()->CreateVertexBuffer
		(sizeof(VERTEX_2D) * INT_VALUE::MAX_TOP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)!= D3D_OK)
	{
		return E_FAIL;
	}

	//���_���ݒ�
	SetVtx();

	return S_OK;
}
//<==================================================================================
//2D�I�u�W�F�N�g�̏I������
//<==================================================================================
HRESULT CObject2D::InitWith(const D3DXVECTOR2 rPos, const D3DXVECTOR2 rSize,
	const D3DXCOLOR rColor, const LPDIRECT3DTEXTURE9 pTexture)
{
	//���_�o�b�t�@�̐���
	if (CManager::GetRenderer()->GetDevice()->CreateVertexBuffer
	(sizeof(VERTEX_2D) * INT_VALUE::MAX_TOP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL) != D3D_OK)
	{
		return E_FAIL;
	}

	SetPosition(rPos);

	SetSize(rSize);

	SetColor(rColor);

	BindTexture(pTexture);

	SetVtx();

	return S_OK;

}
//<==================================================================================
//2D�I�u�W�F�N�g�̏I������
//<==================================================================================
void CObject2D::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
 		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}
//<==================================================================================
//2D�I�u�W�F�N�g�̍X�V����
//<==================================================================================
void CObject2D::Update(void)
{

}
//<==================================================================================
//2D�I�u�W�F�N�g�̕`�揈��
//<==================================================================================
void CObject2D::Draw(void)
{
	//<======================================================
	//���_�o�b�t�@���f�[�^�X�g���[���ɓo�^
	//<======================================================
	CManager::GetRenderer()->GetDevice()->SetStreamSource(0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	CManager::GetRenderer()->GetDevice()->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	CManager::GetRenderer()->GetDevice()->SetTexture(0, m_pTexture);
	//<======================================================
	//�`����@���w��
	//<======================================================
	CManager::GetRenderer()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//<==================================================================================
//2D�I�u�W�F�N�g�̒��_���W�ݒ菈��
//<==================================================================================
void CObject2D::SetVtx(void)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	assert(m_pVtxBuff != NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���ꂼ��̏��̎擾
	m_aObj.pos = GetPosition();
	m_aObj.rot = GetRotation();
	m_aObj.fAngle = GetAngle();
	m_aObj.fLength = GetLength();

	//����
	pVtx[0].pos.x = m_aObj.pos.x + sinf(m_aObj.rot.z - D3DX_PI + m_aObj.fAngle) * m_aObj.fLength;
	pVtx[0].pos.y = m_aObj.pos.y + cosf(m_aObj.rot.z - D3DX_PI + m_aObj.fAngle) * m_aObj.fLength;
	pVtx[0].pos.z = 0.0f;

	//�E��
	pVtx[1].pos.x = m_aObj.pos.x + sinf(m_aObj.rot.z + D3DX_PI - m_aObj.fAngle) * m_aObj.fLength;
	pVtx[1].pos.y = m_aObj.pos.y + cosf(m_aObj.rot.z + D3DX_PI - m_aObj.fAngle) * m_aObj.fLength;
	pVtx[1].pos.z = 0.0f;

	//����
	pVtx[2].pos.x = m_aObj.pos.x + sinf(m_aObj.rot.z - m_aObj.fAngle) * m_aObj.fLength;
	pVtx[2].pos.y = m_aObj.pos.y + cosf(m_aObj.rot.z - m_aObj.fAngle) * m_aObj.fLength;
	pVtx[2].pos.z = 0.0f;

	//�E��
	pVtx[3].pos.x = m_aObj.pos.x + sinf(m_aObj.rot.z + m_aObj.fAngle) * m_aObj.fLength;
	pVtx[3].pos.y = m_aObj.pos.y + cosf(m_aObj.rot.z + m_aObj.fAngle) * m_aObj.fLength;
	pVtx[3].pos.z = 0.0f;


	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_aObj.Col;
	pVtx[1].col = m_aObj.Col;
	pVtx[2].col = m_aObj.Col;
	pVtx[3].col = m_aObj.Col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//<==========================================================================
//�T�C�Y�ݒ�
//<==========================================================================
void CObject2D::SetSize(const D3DXVECTOR2& size)
{
	//�T�C�Y�̐ݒ�
	m_aObj.Size = size;	
	SetLength(sqrtf(m_aObj.Size.x * m_aObj.Size.x + m_aObj.Size.y * m_aObj.Size.y));
	SetAngle(atan2f(m_aObj.Size.x, m_aObj.Size.y));	
}