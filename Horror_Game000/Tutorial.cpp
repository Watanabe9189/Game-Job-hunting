//<==================================================================================
//�`���[�g���A����ʏ���(Tutorial.cpp)
//
//Author:kazuki watanabe
//<==================================================================================
#include "Tutorial.h"
#include "input.h"
#include "Texture.h"
#include "DebugProc.h"

//<*****************************************
//3D�֘A
//<*****************************************
#include "Light.h"

LPDIRECT3DTEXTURE9	CTutorial::m_apTexture[INT_VALUE::MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^

															//�t�@�C����
const char*			CTutorial::m_acFilename[TUTORIAL_STEP_MAX] =
{
	"data/TEXTURE/TUTORIAL/C++Tutorial000.png",
	"data/TEXTURE/TUTORIAL/C++Tutorial001.png",
	"data/TEXTURE/TUTORIAL/C++Tutorial002.png",
	"data/TEXTURE/TUTORIAL/C++Tutorial003.png"
};
int CTutorial::m_nTutorialStep = INITIAL_INT;

CLight *CTutorial::m_pLight;					//

LPDIRECT3DVERTEXBUFFER9 CTutorial::m_pVtxBuff = nullptr;

//<===========================================================
//�`���[�g���A���̃R���X�g���N�^
//<===========================================================
CTutorial::CTutorial()
{
	//�l�̃N���A
	m_pos = INIT_VECTOR;
	m_Size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = INIT_COL;
}
//<===========================================================
//�`���[�g���A���̃f�X�g���N�^
//<===========================================================
CTutorial::~CTutorial()
{

}
//<===========================================================
//�`���[�g���A���̏���������
//<===========================================================
HRESULT CTutorial::Init(void)
{

	for (int nCnt = 0; nCnt < sizeof(m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		if (m_apTexture[nCnt] == nullptr)
		{
			//�e�N�X�`���̓ǂݍ���
			if ((CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt])) <= -1)
			{
				return E_FAIL;
			}
		}
	}

	//���_�o�b�t�@�̐���
	if (m_pVtxBuff == nullptr &&
		CManager::GetRenderer()->GetDevice()->CreateVertexBuffer
	(sizeof(VERTEX_2D) * INT_VALUE::MAX_TOP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL) != D3D_OK)
	{
		return E_FAIL;
	}

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//�v�f�̐ݒ�
	m_pos = D3DXVECTOR3(660.0f, 620.0f, 0.0f);

	m_Size = D3DXVECTOR2(600.0f, 100.0f);

	m_nTutorialStep = INITIAL_INT;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y - m_Size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_Size.x, m_pos.y + m_Size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Size.x, m_pos.y + m_Size.y, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}
//<===========================================================
//�`���[�g���A���̏I������
//<===========================================================
void CTutorial::Uninit(void)
{
	//���_�o�b�t�@��j������
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	Release();
}
//<=========================================================
//�`���[�g���A���̍X�V����
//<=========================================================
void CTutorial::Update(void)
{
	//SPACE�L�[�������ꂽ��
	if (CManager::GetKeyboard()->bGetTrigger(DIK_RIGHTARROW) == true ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_RIGHT, 0) == true)
	{
		//�`���[�g���A���X�e�b�v��i�߂�
		m_nTutorialStep += 1;

		//�����`���[�g���A���X�e�b�v���ő�l�𒴂��Ă�����
		if (m_nTutorialStep >= TUTORIAL_STEP_MAX)
		{
			//�Q�[����ʂɑJ��
			CManager::SetMode(CScene::MODE::MODE_GAME);
		}
	}

	//SPACE�L�[�������ꂽ��
	if (CManager::GetKeyboard()->bGetTrigger(DIK_LEFTARROW) == true ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_LEFT, 0) == true)
	{
		//�`���[�g���A���X�e�b�v��i�߂�
		m_nTutorialStep -= 1;

		//�����ŏ��l�ɓ��B���悤�Ƃ�����
		if (m_nTutorialStep <= TUTORIAL_STEP_1)
		{
			m_nTutorialStep = TUTORIAL_STEP_1;
		}
	}
	//SPACE�L�[�������ꂽ��
	if (CManager::GetKeyboard()->bGetTrigger(DIK_LSHIFT) == true ||
		CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_START, 0) == true)
	{
		//�Q�[����ʂɑJ��
		CManager::SetMode(CScene::MODE::MODE_GAME);
	}
	CManager::GetDebugProc()->Print("[���݂̃`���[�g���A���X�e�b�v->%d]\n", m_nTutorialStep);

}
//<==========================================================
//�`���[�g���A���̕`�揈��
//<==========================================================
void CTutorial::Draw(void)
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
	CManager::GetRenderer()->GetDevice()->SetTexture(0, m_apTexture[m_nTutorialStep]);

	//�|���S���̕`��
	CManager::GetRenderer()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}