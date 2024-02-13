//<=============================================================================
//ライト処理(light.cpp)
//
//Author:kazuki watanabe
//<=============================================================================
#include "Light.h"
#include "manager.h"
#include "DebugProc.h"
#include "input.h"
//<=================================
//ライトのコンストラクタ
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
//ライトのデストラクタ
//<=================================
CLight::~CLight()
{

}
//<=================================
//ライトの生成処理
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
//ライトの初期化処理
//<=================================
HRESULT CLight::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//ライトの情報をクリアする
		if (FAILED(ZeroMemory(&m_aLight[nCnt], sizeof(D3DLIGHT9))))
		{
			return E_FAIL;
		}
		
		//指向性ライトだったら
		if (m_eMode == MODE_DIRECTIONAL)
		{
			//ライトの種類を設定
			m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

			switch (nCnt)
			{
			case 0:
				//ライトの拡散光を設定
				m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//ライトの方向を設定
				m_vecDir[nCnt] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
				break;

			case 1:
				//ライトの拡散光を設定
				m_aLight[nCnt].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);

				//ライトの方向を設定
				m_vecDir[nCnt] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
				break;

			case 2:
				//ライトの拡散光を設定
				m_aLight[nCnt].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

				//ライトの方向を設定
				m_vecDir[nCnt] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);
				break;
			}

			//ベクトルを正規化する(1.0にする)
			if (FAILED(D3DXVec3Normalize(&m_vecDir[nCnt], &m_vecDir[nCnt])))
			{
				return E_FAIL;
			}

			m_aLight[nCnt].Direction = m_vecDir[nCnt];
		}
		//指向性ライトだったら
		if (m_eMode == MODE_POINT)
		{
			switch (nCnt)
			{
			case 0:

				//ライトの位置設定(Y座標はそのオブジェクトの上にいないと暗い&あまり遠すぎても暗くなる)
				m_aLight[nCnt].Position = D3DXVECTOR3(0.0f, 500.0f, 0.0f);

				//ライトの色設定
				m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//ライトの範囲設定
				m_aLight[nCnt].Range = 750.0f;

				//ライトの減衰0の設定(ライト自体の明るさ[?])
				m_aLight[nCnt].Attenuation0 = 0.3f;

				//ライトの減衰1の設定(高くなる程暗くなり、低くなる程明るくなる)
				m_aLight[nCnt].Attenuation1 = 0.0f;

				//ライトの減衰2の設定(変更すると暗くなる)
				m_aLight[nCnt].Attenuation2 = 0.0f;

				//ライトの種類を設定
				m_aLight[nCnt].Type = D3DLIGHT_POINT;

				break;
			}
		
		}

		//ライトを設定する
		if (FAILED(CManager::GetRenderer()->GetDevice()->SetLight(nCnt, &m_aLight[nCnt])))
		{
			return E_FAIL;
		}

		//ライトを有効にする
		if (FAILED(CManager::GetRenderer()->GetDevice()->LightEnable(nCnt, TRUE)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}
//<=================================
//ライトの終了処理
//<=================================
void CLight::Uninit(void)
{
	//アンビエントライト（環境光）を設定する
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_AMBIENT, 0x0);

	//スペキュラ（鏡面反射）を有効にする
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
}
//<=================================
//ライトの更新処理
//<=================================
void CLight::Update(void)
{
	//ポイントライトだった場合
	if (m_eMode == MODE::MODE_POINT)
	{
		//位置の設定を行う
		m_rPos = D3DXVECTOR3(m_rTargetPos.x, m_rTargetPos.y + 500.0f, m_rTargetPos.z);

		//ライトの位置設定(Y座標はそのオブジェクトの上にいないと暗い&あまり遠すぎても暗くなる)
		m_aLight[0].Position = m_rPos;

		//ライトの色設定
		m_aLight[0].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		//ライトの範囲設定
		m_aLight[0].Range = 850.0f;

		//ライトの減衰0の設定(ライト自体の明るさ[?])
		m_aLight[0].Attenuation0 = 0.65f;

		//ライトの減衰1の設定(高くなる程暗くなり、低くなる程明るくなる)
		m_aLight[0].Attenuation1 = 0.0f;

		//ライトの減衰2の設定(変更すると暗くなる)
		m_aLight[0].Attenuation2 = 0.0f;

		//ライトを設定する
		CManager::GetRenderer()->GetDevice()->SetLight(0, &m_aLight[0]);
	}
}