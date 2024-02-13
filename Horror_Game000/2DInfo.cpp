//<===========================================
//
//
//
//<===========================================
#include "2DInfo.h"
#include "game.h"

//<*************************************************************************
//
//<*************************************************************************
LPDIRECT3DTEXTURE9	C2DInfo::m_apTexture[INT_VALUE::MAX_TEX] = {};
const char*			C2DInfo::m_acFilename[] =
{
	"data\\TEXTURE\\HORROR_INFO001.png",
	"data\\TEXTURE\\number_02.png",
	
};

//<*************************************************************************
//
//<*************************************************************************
namespace
{
	const D3DXVECTOR2 INFO_POS = D3DXVECTOR2(125.0f, 85.0f);
	const D3DXVECTOR2 INFO_SIZE = D3DXVECTOR2(100.0f, 100.0f);

	const D3DXVECTOR2 NUMBER_POS = D3DXVECTOR2(INFO_POS.x+125.0f , INFO_POS.y);
	const D3DXVECTOR2 NUMBER_SIZE = D3DXVECTOR2(50.0f, 50.0f);

}
//<===========================================
//
//<===========================================
C2DInfo::C2DInfo(int nPriority)
{
	//�l�̃N���A
	m_pObject2D = nullptr;
	m_pNumber = nullptr;
	m_nNum = INITIAL_INT;
	m_rCol = INIT_COL;

}
//<===========================================
//
//<===========================================
C2DInfo::~C2DInfo()
{

}
//<===========================================
//
//<===========================================
C2DInfo *C2DInfo::Create(void)
{
	//�C���X�^���X����
	C2DInfo *p2DInfo = new C2DInfo;

	//���g�Ə������`�F�b�N
	assert(p2DInfo != nullptr && p2DInfo->Init() == S_OK);

	return p2DInfo;
}
//<===========================================
//
//<===========================================
HRESULT C2DInfo::Init(void)
{
	//�e�N�X�`���̏�����
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		//�ŏ������ǂݍ���
		if (m_apTexture[nCnt] == nullptr)
		{
			//�e�N�X�`���̓ǂݍ���
			if (CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt]) <= -1)
			{
				return E_FAIL;
			}
		}
	}

	//��������������
	m_pObject2D = CObject2D::Create(INFO_POS,INFO_SIZE, INIT_COL, m_apTexture[0]);
	m_pNumber = CNumber::Create(NUMBER_POS, NUMBER_SIZE, m_apTexture[1]);

	//���g�`�F�b�N
	assert(m_pObject2D != nullptr && m_pNumber != nullptr);

	return S_OK;
}
//<===========================================
//
//<===========================================
void C2DInfo::Uninit(void)
{
	//���g��j������
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Uninit();
		m_pObject2D = nullptr;
	}

	//���g��j������
	if (m_pNumber != nullptr)
	{
		m_pNumber->Uninit();
		m_pNumber = nullptr;
	}

	Release();
}
//<===========================================
//
//<===========================================
void C2DInfo::Update(void)
{
	//�c�萔���擾���Ă���
	m_nNum = CItem::GetNumLeft();

	//����ݒ肷��
	m_pNumber->SetNum(&m_nNum);

	//�X�V����
	m_pObject2D->SetVtx();
	m_pNumber->Update();
}
//<===========================================
//
//<===========================================
void C2DInfo::Draw(void)		
{

}
