//<=============================================================================
//ライト処理(light.h)
//
//Author:kazuki watanabe
//<=============================================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//<*************************************
//ライトのクラス定義
//<*************************************
class CLight
{
public:

#define MAX_LIGHT	(4)	//ライトの最大数

	//<=================================
	//モードの設定
	//<=================================
	enum MODE
	{
		MODE_NONE = 0,
		MODE_DIRECTIONAL,
		MODE_POINT,
		MODE_MAX,
	};

	CLight();
	~CLight();

	static CLight *Create(const MODE mode);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	//セット系
	void SetPosition(const D3DXVECTOR3 rPos) { if (m_eMode == MODE_POINT) { m_rTargetPos = rPos; } }


private:

	D3DXVECTOR3 m_rPos;
	D3DXVECTOR3 m_rTargetPos;
	float m_fRange;
	MODE m_eMode;
	D3DLIGHT9 m_aLight[MAX_LIGHT];	//ライトの情報
	D3DXVECTOR3 m_vecDir[MAX_LIGHT];//設定用方向ベクトル

};

#endif
