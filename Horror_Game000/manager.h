//<==============================================
//�}�l�[�W������(manager.h)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _MANAGER_H_
#define _MANAGER_H_	

#include "main.h"
#include "renderer.h"
#include "Input.h"
#include "DebugProc.h"
#include "Sound.h"
#include "Texture.h"
#include "Useful.h"

//<*********************************************
//�O���錾
//<*********************************************
class CRenderer;
class CFade;
class CPause;

//���͊֘A
class CKeyboard;
class CJoyPad;
class CMouse;
//2D�֘A
class CBG;
class CTexture;
//���̑��֘A
class CDebug;
class CSound;
//��ʑJ�ڊ֘A
class CTitle;
class CTutorial;
class CGame;
class CResult;
class COption;
//<*********************************************
//�N���X�̒�`
//<*********************************************
class CScene :public CObject
{
public:

	//<=========================================
	//
	//<=========================================
	enum MODE
	{
		MODE_TITLE = 0,
		MODE_OPTION,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX

	};
	//<=========================================
	//
	//<=========================================
	enum TYPE_RESULT
	{
		TYPE_RESULT_SUCCEEDED = 0,
		TYPE_RESULT_FAILED,
		TYPE_RESULT_MAX
	};

	CScene();
	~CScene();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CScene *Create(MODE Mode);

	//<========================================
	//
	//<========================================
	void SetVtx(void) { return; }
	CObject2D *GetObject2D(void) { return NULL; }

	static int GetCount(void) { return m_nCount; }

	static CTitle *GetTitle(void) { return m_pTitle; }
	static CTutorial *GetTutorial(void) { return m_pTutorial; }
	static CGame *GetGame(void) { return m_pGame; }
	static CResult *GetResult(void) { return m_pResult; }
	static COption *GetOption(void) { return m_pOption; }
	static MODE GetMode(void) { return m_Mode; }
	static void SetMode(CScene::MODE Mode) { m_Mode = Mode; }

	static void SetResult(TYPE_RESULT eTypeRes) { m_eTypeRes = eTypeRes; }
	static TYPE_RESULT GetRes(void) { return m_eTypeRes; }

protected:

private:
	static int m_nCount;

	static MODE m_Mode;
	static CTitle *m_pTitle;
	static CGame *m_pGame;
	static CResult *m_pResult;
	static CTutorial *m_pTutorial;
	static COption *m_pOption;

	static TYPE_RESULT m_eTypeRes;


};
//<*********************************************
//�}�l�[�W���N���X�̒�`
//<*********************************************
class CManager
{
public:

	CManager();
	~CManager();

	//<=========================================================
	//�����o�֐�
	//<=========================================================
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//<=========================================================
	//���͏����֘A�̂܂Ƃ�
	//<=========================================================
	static HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
	static void UninitInput(void);
	static void UpdateInput(void);
	//<=========================================================
	//Get�n�����o�֐�
	//<=========================================================
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CFade *GetFade(void) { return m_pFade; }
	//���͊֘A
	static CKeyboard *GetKeyboard(void) { return m_pKeyboard; }
	static CJoyPad *GetJoyPad(void) { return m_pJoyPad; }
	static CMouse *GetMouse(void) { return m_pMouse; }
	//2D�֘A
	//3D�֘A
	
	//���̑��֘A
	static CTexture *GetTex(void) { return m_pTexture; }
	static CDebug *GetDebugProc(void) { return m_pDebug; }
	static CSound *GetSound(void) { return m_pSound; }

	static void SetMode(CScene::MODE Mode);
	static CScene::MODE GetMode(void) { return CScene::GetMode(); }
	static CScene *GetScene(void) { return m_pScene; }
	static void SetFade(const CScene::MODE modeNext);
	static bool GetPause(void) { return m_bPause; }
	static CPause *GetPpause(void) { return m_pPause; }
	static HINSTANCE GetInstance(void) { return m_hInstance; }
	

private:

	static CRenderer *m_pRenderer;				//�����_���[�C���X�^���X
	static CFade *m_pFade;
	static CKeyboard *m_pKeyboard;				//�L�[�{�[�h�C���X�^���X
	static CJoyPad *m_pJoyPad;					//�W���C�p�b�h�C���X�^���X
	static CMouse *m_pMouse;
	//
	static CBG *m_pBg;							//�w�i�C���X�^���X

	static CTexture *m_pTexture;				//
	
	static CDebug *m_pDebug;
	static CSound *m_pSound;
	
	static CScene *m_pScene;					
	static CScene::MODE m_NowMode;
	static bool m_bPause;
	static CPause *m_pPause;

	static HINSTANCE m_hInstance;

};										
#endif