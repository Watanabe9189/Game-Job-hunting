//<==============================================
//�r���{�[�h����(BillB.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "BilB.h"
#include "manager.h"
#include "Texture.h"

//<================================
//�r���{�[�h�̃R���X�g���N�^
//<================================
CBillB::CBillB(int nPriority) : CObject(nPriority)
{
	//�l�̃N���A
	m_pos = INIT_VECTOR;
	m_move = INIT_VECTOR;
	m_Size = INIT_VECTOR;
	m_col = COLOR_VALUE::COLOR_INIT;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	m_mtxview = {};

	m_pTexture = NULL;
	m_bDraw = true;
}
//<================================
//�r���{�[�h�̃f�X�g���N�^
//<================================
CBillB::~CBillB()
{

}
//<================================
//�r���{�[�h�̏���������
//<================================
CBillB *CBillB::Create(const D3DXVECTOR3 rPos, const D3DXVECTOR2 rSize,const D3DXCOLOR rColor, const LPDIRECT3DTEXTURE9 pTex)
{
	CBillB *pBillB = new CBillB;

	assert(pBillB != nullptr && pBillB->Init() == S_OK);

	pBillB->SetVector3(rPos, INIT_VECTOR, D3DXVECTOR3(rSize.x, rSize.y, 0.0f));
	pBillB->SetColor(rColor);
	pBillB->BindTexture(pTex);

	return pBillB;
}
//<================================
//�r���{�[�h�̏���������
//<================================
HRESULT CBillB::InitWith(const D3DXVECTOR3 rPos, const D3DXVECTOR2 rSize, const D3DXCOLOR rColor, const LPDIRECT3DTEXTURE9 pTex)
{
	//���_�o�b�t�@�̐���
	if (FAILED(CManager::GetRenderer()->GetDevice()->CreateVertexBuffer
	(sizeof(VERTEX_3D) * INT_VALUE::MAX_TOP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	SetVector3(rPos, INIT_VECTOR, D3DXVECTOR3(rSize.x, rSize.y, 0.0f));
	SetColor(rColor);
	BindTexture(pTex);

	SetVtx();

	return S_OK;
}
//<================================
//�r���{�[�h�̏���������
//<================================
HRESULT CBillB::Init(void)
{
	//���_�o�b�t�@�̐���
	if (FAILED(CManager::GetRenderer()->GetDevice()->CreateVertexBuffer
		(sizeof(VERTEX_3D) * INT_VALUE::MAX_TOP,
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
//<================================
//�r���{�[�h�̏I������
//<================================
void CBillB::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}
//<================================
//�r���{�[�h�̍X�V����
//<================================
void CBillB::Update(void)
{
	
}
//<================================
//�r���{�[�h�̕`�揈��
//<================================
void CBillB::Draw(void)
{
	if (m_bDraw)
	{
		D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X

								//Z�e�X�g�𖳌��ɂ���
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	//��ɕ`�悷��

																							//�r���[�}�g���b�N�X�̎擾
		CManager::GetRenderer()->GetDevice()->GetTransform(D3DTS_VIEW, &m_mtxview);

		//�J�����𐳖ʂƂ��Č���
		D3DXMatrixInverse(&m_mtxWorld, NULL, &m_mtxview);
		m_mtxWorld._41 = 0.0f;
		m_mtxWorld._42 = 0.0f;
		m_mtxWorld._43 = 0.0f;

		//<=========================================================
		//�ʒu�̔��f�͂��̃I�u�W�F�N�g���琶������ꍇ�A�g�p���Ȃ�
		//���̂܂ܐݒ肷��ꍇ�͎g�p���Ă�OK
		//<========================================================
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

		//�e�N�X�`���̕`��
		CManager::GetRenderer()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		//Z�e�X�g��L���ɂ���
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
}
//<================================
//�r���{�[�h�̒��_���ݒ菈��
//<================================
void CBillB::SetVtx(void)
{
	//2D���_���̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N
  	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�ʒu�̎擾
	m_pos = GetPos();

	//�T�C�Y�̎擾
	m_Size = GetSize();

	//�F�̎擾
	m_col = GetColor();

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f - m_Size.x, 0.0f + m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f + m_Size.x, 0.0f + m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f - m_Size.x, 0.0f - m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f + m_Size.x, 0.0f - m_Size.y, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuff->Unlock();
}
//<================================
//�r���{�[�h��Vector3�^�̐ݒ菈��
//<================================
void CBillB::SetVector3(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXVECTOR3& Size)
{
	//�����ʒu�̏�񂪂�������
	if (pos != NULL)
	{
		m_pos = pos;
	}
	//�����ړ��l�̏�񂪂�������
	if (move != NULL)
	{
		m_move = move;
	}
	//�����T�C�Y�̏�񂪂�������
	if (Size != NULL)
	{
		m_Size = Size;
	}
}