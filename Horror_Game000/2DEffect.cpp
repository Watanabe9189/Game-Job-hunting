//<================================================
//2D�G�t�F�N�g����(2DEffect.cpp)
//
//Author:kazuki watanabe
//<================================================
#include "2DEffect.h"
#include "manager.h"
#include "Texture.h"

//<***********************************************
//�G�t�F�N�g�e�N�X�`��
//<***********************************************
LPDIRECT3DTEXTURE9 C2DEffect::m_apTexture[INT_VALUE::MAX_TEX] = {};

const char	*C2DEffect::m_acFilename[]
{
	"data/TEXTURE/effect/effect000.jpg",	//�G�t�F�N�g�P
	"data/TEXTURE/effect/effect001.png",	//�G�t�F�N�g�Q
	"data/TEXTURE/effect/effect002.jpg",	//�G�t�F�N�g�R
};

//<=====================================
//
//<=====================================
C2DEffect::C2DEffect(int nPriority)
{
	//�l�̃N���A
	m_rPos = D3DXVECTOR2(0.0f,0.0f);
	m_rmove = D3DXVECTOR2(0.0f, 0.0f);
	m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	m_nLife = INT_VALUE::NO_LIFE;
	m_rCol = INIT_COL;
	m_bAdd = true;
	m_bDisp = true;
}
//<=====================================
//
//<=====================================
C2DEffect::~C2DEffect()
{

}
//<=====================================
//
//<=====================================
C2DEffect *C2DEffect::Create(const D3DXVECTOR2 rPos, const D3DXVECTOR3 rMove, const int nLife, const D3DXVECTOR2 rSize, const D3DXCOLOR rCol)
{
	C2DEffect *p2DEffect = new C2DEffect;

	assert(p2DEffect != nullptr);

	//���������������肳�ꂽ���`�F�b�N
	assert(SUCCEEDED(p2DEffect->Init()));

	//���̐ݒ�
	p2DEffect->SetPosition(rPos);
	p2DEffect->SetSize(rSize);
	p2DEffect->SetColor(rCol);

	p2DEffect->m_rmove = D3DXVECTOR2(rMove.x, rMove.y);
	p2DEffect->m_nLife = nLife;

	/*p2DEffect->BindTexture(m_apTexture[1]);*/

	return p2DEffect;
}
//<=====================================
//
//<=====================================
HRESULT C2DEffect::Init(void)
{
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

	CObject2D::Init();

	return S_OK;
}
//<=====================================
//
//<=====================================
void C2DEffect::Uninit(void)
{
	CObject2D::Uninit();
}
//<=====================================
//
//<=====================================
void C2DEffect::Update(void)
{
	//�\����ԂɂȂ��Ă�����
	if (m_bDisp)
	{
		SetVtx();

		//���̎擾
		m_rPos = GetPosition();
		m_rSize = GetSize();
		m_rCol = GetColor();

		//���C�t������ꍇ
		if (!(m_nLife <= 0))
		{
			m_nLife--;
		}
		//�Ȃ��ꍇ
		else
		{
			//�\���������Ȃ�
			m_bDisp = false;

			return;
		}

		//�ʒu���X�V
		m_rPos += m_rmove;

		//���̐ݒ�
		SetPosition(m_rPos);
		SetSize(m_rSize);
		SetColor(m_rCol);
	}
}
//<=====================================
//
//<=====================================
void C2DEffect::Draw(void)
{
	//�\����ԂɂȂ��Ă�����
	if (m_bDisp)
	{
		// ���Z������ON�̏ꍇ
		if (m_bAdd)
		{
			//���u�����f�B���O�����Z�����ɐݒ�
			CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}


		CObject2D::Draw();

		//���u�����f�B���O�����ɖ߂�
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}
//<=====================================
//
//<=====================================
void C2DEffect::SetVtx(void)
{
	CObject2D::SetVtx();
}