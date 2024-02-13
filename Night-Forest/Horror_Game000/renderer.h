//<==============================================
//レンダラー関連の処理(Renderer.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"
//<**********************************************
//レンダラーのクラス定義
//<**********************************************
class CRenderer
{

	//<================================
	//誰でも使えるようにする
	//<================================
public:

	CRenderer();	//コンストラクタ
	~CRenderer();	//デストラクタ

					//<==================================
					//メンバ関数
					//<==================================
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	//デバイスを返す
	HWND GetHwnd(void) { return m_hWnd; }

	void ScreenShot(const char *cName);

	void SetBoolPix(const BOOL bBool);

	void SetStencil(const int nStencil) { m_nStencil = nStencil; }

private:

	void CheckPixShade(void);
	LPDIRECT3DPIXELSHADER9 LoadPixShade(void);

	void DrawStancil(void);

	//<==================================
	//メンバ変数
	//<==================================
	LPDIRECT3D9 m_pD3D;					//Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;				//Direct3Dデバイスへのポインタ
	HWND m_hWnd;

	LPDIRECT3DPIXELSHADER9 m_pPixShade;
	bool m_bUsePix;
	bool m_bUseStancil;
	int m_nStencil;
};

#endif