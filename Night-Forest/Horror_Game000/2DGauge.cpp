//<==============================================
//2D�Q�[�W����(2DGauge.ch)
//
//Author:kazuki watanabe
//<==============================================
#include "2DGauge.h"
#include "manager.h"
#include "Texture.h"
#include "DebugProc.h"

//<**********************************************************
//���O�錾(�����o�ϐ����g�����Ƃ͂ł��Ȃ�)
//<**********************************************************
namespace
{

	const D3DXVECTOR2 SIZEPOS_X = D3DXVECTOR2(130.0f, 15.0f);	//�������������ꍇ�̈ʒu
	const D3DXVECTOR2 SIZEPOS_Y = D3DXVECTOR2(150.0f, 50.0f);	//�c�����������ꍇ�̈ʒu
	const D3DXVECTOR2 SIZEMAX_X = D3DXVECTOR2(125.0f, 15.0f);	//�������̏ꍇ�̃T�C�Y�̍ő�l
	const D3DXVECTOR2 SIZEMAX_Y = D3DXVECTOR2(15.0f, 100.0f);	//�c�����̏ꍇ�̃T�C�Y�̍ő�l
	const float		VALUE_ALPHA = 0.05f;						//�����x�ύX�l		
	const int		INIT_MAX	= 500;							//�ÓI�����o�ϐ��̏����l
	const int MAX_VALUE = 1000;
	const int MIN_VALUE = 0;
}
int C2DGauge::m_nFixedMax = INIT_MAX;		//�ݒ�p�̍ő�l

int C2DGauge::m_nMaxLimit = MAX_VALUE;		//�ő�l
int C2DGauge::m_nMinLimit = MIN_VALUE;		//�ŏ��l
float C2DGauge::m_StaAddValue = INITIAL_FLOAT;
//<===============================================================
//
//<===============================================================
C2DGauge::C2DGauge(int nPriority)
{
	//�l�̃N���A
	m_rPos = D3DXVECTOR2(0.0f,0.0f);
	m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	m_rCol = COLOR_VALUE::COLOR_GREEN;
	m_fAddValue =INITIAL_FLOAT;
	m_fOldAdd = INITIAL_FLOAT;
	m_fChange = INITIAL_FLOAT;
	m_fCurrent = INITIAL_FLOAT;
	m_nNum = INITIAL_INT;
	m_nMax = INITIAL_INT;
	m_eVer = VERTEX_MAX;

	m_pVtxBuff = nullptr;
}
//<===============================================================
//
//<===============================================================
C2DGauge::~C2DGauge()
{
	
}
//<===============================================================
//
//<===============================================================
C2DGauge *C2DGauge::Create(const D3DXVECTOR2 pos,const int nMaxNum, const VERTEX eVer, const MODE eMode)
{
	C2DGauge *p2DGauge = new C2DGauge;

	assert(p2DGauge != nullptr);

	//�񋓌^�ϐ�
	p2DGauge->m_eVer = eVer;
	p2DGauge->m_eMode = eMode;

	//�l�̐ݒ�
	p2DGauge->m_rPos = pos;
	p2DGauge->m_nMax = nMaxNum;

	//������
	assert(SUCCEEDED(p2DGauge->Init()));

	p2DGauge->SetNum(nMaxNum);

	return p2DGauge;
}
//<===============================================================
//
//<===============================================================
HRESULT C2DGauge::Init(void)
{
	//���^��������
	if (m_eVer == VERTEX_X)
	{
		//�T�C�Y�̐ݒ�
		m_rSize = D3DXVECTOR2(SIZEMAX_X.x, SIZEMAX_X.y);
	}
	//�c�^��������
	else if (m_eVer == VERTEX_Y)
	{
		//�T�C�Y�̐ݒ�
		m_rSize = D3DXVECTOR2(SIZEMAX_Y.x, SIZEMAX_Y.y);
	}

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

	SetVtx();

	return S_OK;
}
//<===============================================================
//
//<===============================================================
void C2DGauge::Uninit(void)
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
//<===============================================================
//
//<===============================================================
void C2DGauge::Update(void)
{
	//��ɕ\�������郂�[�h
	if (m_eMode == MODE::MODE_ALWAYS)
	{
		//���̃Q�[�W���ő�Q�[�W�̔����ɂȂ��Ă�����
		if (m_fCurrent <= m_nMax/2)
		{
			m_rCol = COLOR_VALUE::COLOR_RED;
		}
		//����ȊO�̏ꍇ
		else
		{
			m_rCol = COLOR_VALUE::COLOR_INIT;
		}
	}
	//�g���Ă��鎞�����\�������郂�[�h
	else if (m_eMode == MODE::MODE_ONLY_USE)
	{
	
	}

	CManager::GetDebugProc()->Print("[m_fOldAdd]�F%f\n", m_fOldAdd);
	CManager::GetDebugProc()->Print("[m_fAddValue]�F%f\n", m_fAddValue);
	CManager::GetDebugProc()->Print("[m_fCurrent]�F%f\n", m_fCurrent);
	CManager::GetDebugProc()->Print("[m_nNum]�F%d\n", m_nNum);

	SetVtx();
}
//<===============================================================
//
//<===============================================================
void C2DGauge::Draw(void)
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
	CManager::GetRenderer()->GetDevice()->SetTexture(0, NULL);
		
	//�`�悷��
	CManager::GetRenderer()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	
}
//<===============================================================
//���Z����
//<===============================================================
void C2DGauge::Add(const int nValue)
{
	m_fCurrent = (float)m_nNum;

	m_fChange = ((float)nValue / 5.0f);

	m_nNum += nValue;
}
//<===============================================================
//�ݒ菈��
//<===============================================================
void C2DGauge::SetNum(const int nNum)
{
	m_nNum = nNum;

	m_fCurrent = (float)m_nNum;

	//���^��������
	if (m_eVer == VERTEX_X)
	{
		//�ő�l�̌��E�l����Ƃ��ĉ��������肳����
		m_fAddValue = (m_fCurrent * ((m_rSize.x * 2) / (float)m_nMaxLimit)) - m_rSize.x;
	}
	//�c�^��������
	else if (m_eVer == VERTEX_Y)
	{
		//�ő�l�̌��E�l����Ƃ��ĉ��������肳����
		m_fAddValue = (m_fCurrent * ((m_rSize.y * 2) / (float)m_nMaxLimit)) - m_rSize.y;
	}
}
//<===============================================================
//
//<===============================================================
void C2DGauge::SetVtx(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃`�F�b�N
	assert(m_pVtxBuff != nullptr);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���^��������
	if (m_eVer == VERTEX_X)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_rPos.x - m_rSize.x, m_rPos.y - m_rSize.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_rPos.x - m_rSize.x, m_rPos.y + m_rSize.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_rPos.x + m_fAddValue, m_rPos.y - m_rSize.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_rPos.x + m_fAddValue, m_rPos.y + m_rSize.y, 0.0f);
	}
	//�c�^��������
	else if (m_eVer == VERTEX_Y)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_rPos.x - m_rSize.x, m_rPos.y - m_fAddValue, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_rPos.x - m_rSize.x, m_rPos.y + m_rSize.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_rPos.x + m_rSize.x, m_rPos.y - m_fAddValue, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_rPos.x + m_rSize.x, m_rPos.y + m_rSize.y, 0.0f);
	}
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}