//<==============================================
//2D��������(2DChar.cpp)
//
//Author:kazuki watanabe
//<==============================================
#include "2DChar.h"
#include "Texture.h"
#include "manager.h"

int C2DChar::m_nNumAll = INITIAL_INT;

LPDIRECT3DTEXTURE9 C2DChar::m_apTexture[INT_VALUE::MAX_TEX] = {};
const char			*C2DChar::m_acFilename[CHAR_TYPE_MAX] =
{

	"data/TEXTURE/HORROR_TITLE.png",						//�ړI
	"data/TEXTURE/HORROR_INFO000.png",
	"data/TEXTURE/HORROR_INFO002.png",
	"data/TEXTURE/HORROR_INFO003.png"

};
//<======================================
//
//<======================================
C2DChar::C2DChar(int nPriority)
{
	m_nNumAll++;
	m_pos = D3DXVECTOR2(0.0f,0.0f);

	//�ړI�ʒu�̍ő�l��
	for (int nCnt = 0; nCnt < MAX_DEST; nCnt++)
	{
		m_posDest[nCnt] = D3DXVECTOR2(0.0f, 0.0f);
	}
	m_bArrived = false;

	m_Size = D3DXVECTOR2(0.0f, 0.0f);

	m_eCType = CHAR_TYPE_MAX;
	m_bDisp = true;

	m_nLiveTime = INITIAL_INT;

	m_eFromMove = MOVE_FROM_MAX;
}
//<======================================
//
//<======================================
C2DChar::~C2DChar()
{
	m_nNumAll--;
}
//<======================================
//
//<======================================
C2DChar *C2DChar::Create(const D3DXVECTOR2 pos, const D3DXVECTOR2 Size, const int CType, const MOVE_FROM eMoveFrom, const bool bDisp)
{
	C2DChar *p2DChar = new C2DChar;

	assert(p2DChar != nullptr);

	assert(SUCCEEDED(p2DChar->Init()));

	p2DChar->m_eFromMove = eMoveFrom;

	//�ړ����@�ɂ���ď����𕪂���
	switch (eMoveFrom)
	{
		//�ړ����Ȃ��ꍇ
	case MOVE_FROM_NONE:

		//���̈ʒu�ɂ���
		p2DChar->SetPosition(pos);

		break;

		//�ォ�炭��ꍇ
	case MOVE_FROM_UP:

		//�ړI��Y���W��ݒ肷��
		p2DChar->m_posDest[0].y = pos.y;

		//�ʒu�̐ݒ�
		p2DChar->SetPosition(pos);

		break;

		//�����炭��ꍇ
	case MOVE_FROM_DOWN:

		//�ړI��Y���W��ݒ肷��
		p2DChar->m_posDest[0].y = pos.y;

		//�ʒu�̐ݒ�
		p2DChar->SetPosition(pos);

		break;

		//�E���炭��ꍇ
	case MOVE_FROM_RIGHT:

		//�ړI��X���W��ݒ肷��
		p2DChar->m_posDest[0].x = pos.x;

		//�ʒu�̐ݒ�
		p2DChar->SetPosition(pos);

		break;					   
				
		//�����炭��ꍇ
	case MOVE_FROM_LEFT:		   
				
		//�ړI��X���W��ݒ肷��
		p2DChar->m_posDest[0].x = pos.x;

		//�ʒu�̐ݒ�
		p2DChar->SetPosition(pos);

		break;
	}

	p2DChar->SetSize(Size);
	p2DChar->m_bDisp = bDisp;

	p2DChar->BindTexture(m_apTexture[CType]);

	return p2DChar;
}
//<======================================
//
//<======================================
HRESULT C2DChar::Init(void)
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
//<======================================
//
//<======================================
void C2DChar::Update(void)
{
	if (m_bDisp != false)
	{
		m_pos = GetPosition();

		//������Ԗڂ̖ړI�̈ʒu��
		if (m_pos.x != m_posDest[1].x)
		{
			SetVtx();

			//�ړ����@�ɂ���Ēʂ邩
			MoveVer();
			MoveSide();

			SetPosition(m_pos);
		}
	}
}
//<======================================
//
//<======================================
void C2DChar::SetVtx(void)
{ 
	CObject2D::SetVtx();

	VERTEX_2D *pVtx;

	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	GetVtxBuff()->Unlock();

}
//<======================================
//������ړ��̏���
//<======================================
void C2DChar::MoveSide(void)
{
	//�}�W�b�N�i���o�[�h�~�p	
	const float MAX_INATIA = 0.015f;	//�����̍ő�l
	const int MAX_LIVE = 170;			//�؍ݎ��Ԃ̍ő�l

	//�E���炭��ꍇ
	if (m_eFromMove == MOVE_FROM_RIGHT)
	{
		//�܂��������Ă��Ȃ����
		if (m_bArrived == false)
		{
			//�ړI�̈ʒu�ɍs���܂ŉ��Z�������A�~�܂肻���ɂȂ����犵���Ŏ~�܂�
			m_pos.x -= (m_posDest[0].x + m_pos.x) * MAX_INATIA;

			//�����ړI�̈ʒu�𒴂������ɂȂ�����
			if (m_pos.x <= m_posDest[0].x)
			{
				//���̈ʒu�ɂ���
				m_pos.x = m_posDest[0].x;
			}

			//�ړI�̈ʒu�ɓ������Ă�����
			if (m_pos.x == m_posDest[0].x)
			{
				//�؍݂��Ă��鎞�Ԃ����Z����
				m_nLiveTime++;

				//�؍ݎ��Ԃ̍ő�l�𒴂��Ă�����
				if (m_nLiveTime >= MAX_LIVE)
				{
					//���̖ړI�n�����߂�
					m_posDest[1].x = 500.0f;

					//���Ă��锻�������
					m_bArrived = true;

					//���������Ă���
					m_nLiveTime = 0;
				}
			}
		}
		//�����������Ă����
		else if (m_bArrived == true)
		{
			//�ړI�̈ʒu�ɍs���܂ŉ��Z�������A�~�܂肻���ɂȂ����犵���Ŏ~�܂�
			m_pos.x -= (m_posDest[1].x + m_pos.x) * MAX_INATIA;

			//�����ړI�̈ʒu�𒴂������ɂȂ�����
			if (m_pos.x <= -m_posDest[1].x)
			{
				//���̈ʒu�ɂ���
				m_pos.x = -m_posDest[1].x;
			}
		}

	}
	//�����炭��ꍇ
	else if (m_eFromMove == MOVE_FROM_LEFT)
	{
		//�܂��������Ă��Ȃ����
		if (m_bArrived == false)
		{
			//�ړI�̈ʒu�ɍs���܂ŉ��Z�������A�~�܂肻���ɂȂ����犵���Ŏ~�܂�
			m_pos.x += (m_posDest[0].x + m_pos.x) * MAX_INATIA;

			//�����ړI�̈ʒu�𒴂������ɂȂ�����
			if (m_pos.x >= m_posDest[0].x)
			{
				//���̈ʒu�ɂ���
				m_pos.x = m_posDest[0].x;
			}

			//�ړI�̈ʒu�ɓ������Ă�����
			if (m_pos.x == m_posDest[0].x)
			{
				//�؍݂��Ă��鎞�Ԃ����Z����
				m_nLiveTime++;

				//�؍ݎ��Ԃ̍ő�l�𒴂��Ă�����
				if (m_nLiveTime >= MAX_LIVE)
				{
					//���̖ړI�n�����߂�
					m_posDest[1].x = 1700.0f;

					//���Ă��锻�������
					m_bArrived = true;

					//���������Ă���
					m_nLiveTime = 0;
				}
			}
		}
		//�����������Ă����
		else if (m_bArrived == true)
		{
			//�ړI�̈ʒu�ɍs���܂ŉ��Z�������A�~�܂肻���ɂȂ����犵���Ŏ~�܂�
			m_pos.x += (m_posDest[1].x + m_pos.x) * MAX_INATIA;

			//�����ړI�̈ʒu�𒴂������ɂȂ�����
			if (m_pos.x >= m_posDest[1].x)
			{
				//���̈ʒu�ɂ���
				m_pos.x = m_posDest[1].x;
			}
		}
	}
}
//<======================================
//�c����ړ��̏���
//<======================================
void C2DChar::MoveVer(void)
{
	//�}�W�b�N�i���o�[�h�~�p	
	const float MAX_INATIA = 0.015f;	//�����̍ő�l
	const int MAX_LIVE = 170;			//�؍ݎ��Ԃ̍ő�l

	//�ォ�炭��ꍇ
	if (m_eFromMove == MOVE_FROM_UP)
	{
		//�܂��������Ă��Ȃ����
		if (m_bArrived == false)
		{
			//�ړI�̈ʒu�ɍs���܂ŉ��Z�������A�~�܂肻���ɂȂ����犵���Ŏ~�܂�
			m_pos.y += (m_posDest[0].y + m_pos.y) * MAX_INATIA;

			//�����ړI�̈ʒu�𒴂������ɂȂ�����
			if (m_pos.y >= m_posDest[0].y)
			{
				//���̈ʒu�ɂ���
				m_pos.y = m_posDest[0].y;
			}

			//�ړI�̈ʒu�ɓ������Ă�����
			if (m_pos.y == m_posDest[0].y)
			{
				//�؍݂��Ă��鎞�Ԃ����Z����
				m_nLiveTime++;

				//�؍ݎ��Ԃ̍ő�l�𒴂��Ă�����
				if (m_nLiveTime >= MAX_LIVE)
				{
					//���̖ړI�n�����߂�
					m_posDest[1].y = 1000.0f;

					//���Ă��锻�������
					m_bArrived = true;

					//���������Ă���
					m_nLiveTime = 0;
				}
			}
		}
		//�����������Ă����
		else if (m_bArrived == true)
		{
			//�ړI�̈ʒu�ɍs���܂ŉ��Z�������A�~�܂肻���ɂȂ����犵���Ŏ~�܂�
			m_pos.y += (m_posDest[1].y + m_pos.y) * MAX_INATIA;

			//�����ړI�̈ʒu�𒴂������ɂȂ�����
			if (m_pos.y >= m_posDest[1].y)
			{
				//���̈ʒu�ɂ���
				m_pos.y = m_posDest[1].y;
			}
		}
	}
	//�����炭��ꍇ
	else if (m_eFromMove == MOVE_FROM_DOWN)
	{
		//�܂��������Ă��Ȃ����
		if (m_bArrived == false)
		{
			//�ړI�̈ʒu�ɍs���܂ŉ��Z�������A�~�܂肻���ɂȂ����犵���Ŏ~�܂�
			m_pos.y -= (m_posDest[0].y + m_pos.y) * MAX_INATIA;

			//�����ړI�̈ʒu�𒴂������ɂȂ�����
			if (m_pos.y <= m_posDest[0].y)
			{
				//���̈ʒu�ɂ���
				m_pos.y = m_posDest[0].y;
			}

			//�ړI�̈ʒu�ɓ������Ă�����
			if (m_pos.y == m_posDest[0].y)
			{
				//�؍݂��Ă��鎞�Ԃ����Z����
				m_nLiveTime++;

				//�؍ݎ��Ԃ̍ő�l�𒴂��Ă�����
				if (m_nLiveTime >= MAX_LIVE)
				{
					//���̖ړI�n�����߂�
					m_posDest[1].y = 100.0f;

					//���Ă��锻�������
					m_bArrived = true;

					//���������Ă���
					m_nLiveTime = 0;
				}
			}
		}
		//�����������Ă����
		else if (m_bArrived == true)
		{
			//�ړI�̈ʒu�ɍs���܂ŉ��Z�������A�~�܂肻���ɂȂ����犵���Ŏ~�܂�
			m_pos.y -= (m_posDest[1].y + m_pos.y) * MAX_INATIA;

			//�����ړI�̈ʒu�𒴂������ɂȂ�����
			if (m_pos.y <= -m_posDest[1].y)
			{
				//���̈ʒu�ɂ���
				m_pos.y = -m_posDest[1].y;
			}
		}
	}
}