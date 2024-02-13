//<==============================================
//�����_���[�֘A�̏���(Renderer.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
//<**********************************************
//�����_���[�̃N���X��`
//<**********************************************
class CRenderer
{

	//<================================
	//�N�ł��g����悤�ɂ���
	//<================================
public:

	CRenderer();	//�R���X�g���N�^
	~CRenderer();	//�f�X�g���N�^

					//<==================================
					//�����o�֐�
					//<==================================
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	//�f�o�C�X��Ԃ�
	HWND GetHwnd(void) { return m_hWnd; }

	void ScreenShot(const char *cName);

	void SetBoolPix(const BOOL bBool);

	void SetStencil(const int nStencil) { m_nStencil = nStencil; }

private:

	void CheckPixShade(void);
	LPDIRECT3DPIXELSHADER9 LoadPixShade(void);

	void DrawStancil(void);

	//<==================================
	//�����o�ϐ�
	//<==================================
	LPDIRECT3D9 m_pD3D;					//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;				//Direct3D�f�o�C�X�ւ̃|�C���^
	HWND m_hWnd;

	LPDIRECT3DPIXELSHADER9 m_pPixShade;
	bool m_bUsePix;
	bool m_bUseStancil;
	int m_nStencil;
};

#endif