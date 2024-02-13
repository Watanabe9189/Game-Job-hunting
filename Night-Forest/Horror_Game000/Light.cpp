//<=============================================================================
//���C�g����(light.cpp)
//
//Author:kazuki watanabe
//<=============================================================================
#include "Light.h"
#include "manager.h"
#include "DebugProc.h"
#include "input.h"
//<=================================
//���C�g�̃R���X�g���N�^
//<=================================
CLight::CLight()
{
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		m_aLight[nCnt] = {};

		m_rTargetPos = INIT_VECTOR;
		m_rPos = INIT_VECTOR;
		m_fRange = INITIAL_FLOAT;
		m_eMode = MODE::MODE_NONE;
	}
	
}
//<=================================
//���C�g�̃f�X�g���N�^
//<=================================
CLight::~CLight()
{

}
//<=================================
//���C�g�̐�������
//<=================================
CLight *CLight::Create(const MODE mode)
{
	CLight *pLight = new CLight;

	assert(pLight != nullptr);

	pLight->m_eMode = mode;

	assert(SUCCEEDED(pLight->Init()));

	return pLight;
}
//<=================================
//���C�g�̏���������
//<=================================
HRESULT CLight::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//���C�g�̏����N���A����
		if (FAILED(ZeroMemory(&m_aLight[nCnt], sizeof(D3DLIGHT9))))
		{
			return E_FAIL;
		}
		
		//�w�������C�g��������
		if (m_eMode == MODE_DIRECTIONAL)
		{
			//���C�g�̎�ނ�ݒ�
			m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

			switch (nCnt)
			{
			case 0:
				//���C�g�̊g�U����ݒ�
				m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//���C�g�̕�����ݒ�
				m_vecDir[nCnt] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
				break;

			case 1:
				//���C�g�̊g�U����ݒ�
				m_aLight[nCnt].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);

				//���C�g�̕�����ݒ�
				m_vecDir[nCnt] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
				break;

			case 2:
				//���C�g�̊g�U����ݒ�
				m_aLight[nCnt].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

				//���C�g�̕�����ݒ�
				m_vecDir[nCnt] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
				break;
			}

			//�x�N�g���𐳋K������(1.0�ɂ���)
			if (FAILED(D3DXVec3Normalize(&m_vecDir[nCnt], &m_vecDir[nCnt])))
			{
				return E_FAIL;
			}

			m_aLight[nCnt].Direction = m_vecDir[nCnt];
		}
		//�w�������C�g��������
		if (m_eMode == MODE_POINT)
		{
			switch (nCnt)
			{
			case 0:

				//���C�g�̈ʒu�ݒ�(Y���W�͂��̃I�u�W�F�N�g�̏�ɂ��Ȃ��ƈÂ�&���܂艓�����Ă��Â��Ȃ�)
				m_aLight[nCnt].Position = D3DXVECTOR3(0.0f, 500.0f, 0.0f);

				//���C�g�̐F�ݒ�
				m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//���C�g�͈̔͐ݒ�
				m_aLight[nCnt].Range = 750.0f;

				//���C�g�̌���0�̐ݒ�(���C�g���̖̂��邳[?])
				m_aLight[nCnt].Attenuation0 = 0.3f;

				//���C�g�̌���1�̐ݒ�(�����Ȃ���Â��Ȃ�A�Ⴍ�Ȃ�����邭�Ȃ�)
				m_aLight[nCnt].Attenuation1 = 0.0f;

				//���C�g�̌���2�̐ݒ�(�ύX����ƈÂ��Ȃ�)
				m_aLight[nCnt].Attenuation2 = 0.0f;

				//���C�g�̎�ނ�ݒ�
				m_aLight[nCnt].Type = D3DLIGHT_POINT;

				break;
			}
		
		}

		//���C�g��ݒ肷��
		if (FAILED(CManager::GetRenderer()->GetDevice()->SetLight(nCnt, &m_aLight[nCnt])))
		{
			return E_FAIL;
		}

		//���C�g��L���ɂ���
		if (FAILED(CManager::GetRenderer()->GetDevice()->LightEnable(nCnt, TRUE)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}
//<=================================
//���C�g�̏I������
//<=================================
void CLight::Uninit(void)
{
	//�A���r�G���g���C�g�i�����j��ݒ肷��
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_AMBIENT, 0x0);

	//�X�y�L�����i���ʔ��ˁj��L���ɂ���
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
}
//<=================================
//���C�g�̍X�V����
//<=================================
void CLight::Update(void)
{
	//�|�C���g���C�g�������ꍇ
	if (m_eMode == MODE::MODE_POINT)
	{
		//�ʒu�̐ݒ���s��
		m_rPos = D3DXVECTOR3(m_rTargetPos.x, m_rTargetPos.y + 500.0f, m_rTargetPos.z);

		//���C�g�̈ʒu�ݒ�(Y���W�͂��̃I�u�W�F�N�g�̏�ɂ��Ȃ��ƈÂ�&���܂艓�����Ă��Â��Ȃ�)
		m_aLight[0].Position = m_rPos;

		//���C�g�̐F�ݒ�
		m_aLight[0].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		//���C�g�͈̔͐ݒ�
		m_aLight[0].Range = 850.0f;

		//���C�g�̌���0�̐ݒ�(���C�g���̖̂��邳[?])
		m_aLight[0].Attenuation0 = 0.65f;

		//���C�g�̌���1�̐ݒ�(�����Ȃ���Â��Ȃ�A�Ⴍ�Ȃ�����邭�Ȃ�)
		m_aLight[0].Attenuation1 = 0.0f;

		//���C�g�̌���2�̐ݒ�(�ύX����ƈÂ��Ȃ�)
		m_aLight[0].Attenuation2 = 0.0f;

		//���C�g��ݒ肷��
		CManager::GetRenderer()->GetDevice()->SetLight(0, &m_aLight[0]);
	}
}