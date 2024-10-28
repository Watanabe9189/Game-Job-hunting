//<==================================================
//2Dでのコンティニュー表示に特化した処理(2DContinue.cpp)
//
//Author:kazuki watanabe
//<==================================================
#include "2DContinue.h"
#include "manager.h"

//<*************************************************************************
//静的メンバ変数宣言
//<*************************************************************************
LPDIRECT3DTEXTURE9	C2DContinue::m_apTexture[TYPE::TYPE_MAX] = {};
const char*			C2DContinue::m_acFilename[TYPE::TYPE_MAX] =
{	
	NULL,								//フレーム
	"data\\TEXTURE\\GameOver001.png",	//CONTINUE?
	"data\\TEXTURE\\GameOver-Yes.png",	//YES
	"data\\TEXTURE\\GameOver-No.png",	//NO
};
//<*************************************************************************
//名前宣言
//<*************************************************************************
namespace
{
	const float			DISTANCE_VALUE	= 250.0f;								//距離の値
	const D3DXCOLOR		FRAME_COL		= D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.6f);	//フレームの色
	const D3DXVECTOR2	FRAME_POS		= D3DXVECTOR2(625.0f, 375.0f);			//フレームの位置
	const D3DXVECTOR2	FRAME_SIZE		= D3DXVECTOR2(300.0f, 300.0f);			//フレームのサイズ
	const D3DXVECTOR2	CONTINUE_POS	= D3DXVECTOR2(625.0f, 175.0f);			//コンティニュー文字の位置
	const D3DXVECTOR2	CONTINUE_SIZE	= D3DXVECTOR2(300.0f, 200.0f);			//コンティニュー文字のサイズ
	const D3DXVECTOR2	YESNO_POS		= D3DXVECTOR2(500.0f, 500.0f);			//YESNO文字の位置
	const D3DXVECTOR2	YESNO_SIZE		= D3DXVECTOR2(150.0f, 150.0f);			//YESNO文字のサイズ
}
//<======================================================================
//
//<======================================================================
C2DContinue::C2DContinue(int nPriority)
{
	for (int nCnt = 0; nCnt < TYPE::TYPE_MAX; ++nCnt)
	{
		m_apObject2D[nCnt] = {nullptr};
	}

	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; ++nCnt)
	{
		m_apSelect[nCnt] = { nullptr };
	}
	
	m_nNumSelect = INITIAL_INT;
	m_nSelect = INITIAL_INT;
	m_nOldSelect = INITIAL_INT;

	m_rPos = D3DXVECTOR2(0.0f, 0.0f);
	m_rSize = D3DXVECTOR2(0.0f, 0.0f);
	m_rCol = INIT_COL;
	m_bUpdate = false;
	m_pChangeCol = nullptr;
}
//<======================================================================
//
//<======================================================================
C2DContinue::~C2DContinue()
{

}
//<======================================================================
//
//<======================================================================
C2DContinue *C2DContinue::Create(void)
{
	C2DContinue *p2DSelect = new C2DContinue;

	assert(p2DSelect );

	p2DSelect->Init();

	return p2DSelect;
}
//<======================================================================
//
//<======================================================================
HRESULT C2DContinue::Init(void)
{
	m_pChangeCol = ChangeCol::Create();

	assert(m_pChangeCol );

	//テクスチャの初期化
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); ++nCnt)
	{
		//最初だけ読み込む
		if (!m_apTexture[nCnt])
		{
			//テクスチャの読み込み
			if (CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt]) <= -1)
			{
				return E_FAIL;
			}
		}
	}

	m_rPos = FRAME_POS;

	//セレクトの数分繰り返す
	for (int nCnt = 0; nCnt < TYPE::TYPE_SELECT_YES; ++nCnt)
	{
		//フレーム
		if (nCnt == TYPE::TYPE_FRAME)
		{
			m_rCol = FRAME_COL;
			m_rSize = FRAME_SIZE;
		}
		//フレーム以外
		else if (nCnt != TYPE::TYPE_FRAME)
		{
			m_rPos = CONTINUE_POS;
			m_rCol = INIT_COL;
			m_rSize = CONTINUE_SIZE;
		}

		//生成する
		m_apObject2D[nCnt] = CObject2D::Create(D3DXVECTOR2(m_rPos.x, m_rPos.y), m_rSize, m_rCol,m_apTexture[nCnt]);

		assert(m_apObject2D[nCnt] );
	}
	//セレクトの数分繰り返す
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; ++nCnt)
	{
		m_rSize = YESNO_SIZE;
		m_rPos = YESNO_POS;

		//生成する
		m_apSelect[nCnt] = CObject2D::Create(D3DXVECTOR2(m_rPos.x + DISTANCE_VALUE *nCnt, m_rPos.y), m_rSize, m_pChangeCol->GetColor(), m_apTexture[nCnt+2]);

		assert(m_apSelect[nCnt] );
	}

	return S_OK;
}
//<======================================================================
//
//<======================================================================
void C2DContinue::Uninit(void)
{
	//セレクトの数分繰り返す
	for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; ++nCnt)
	{
		//
		if (m_apObject2D[nCnt] )
		{
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
		//
		if (m_apSelect[nCnt] )
		{
			m_apSelect[nCnt]->Uninit();
			m_apSelect[nCnt] = nullptr;
		}
	}
	if (m_pChangeCol)
	{
		delete m_pChangeCol;
		m_pChangeCol = nullptr;
	}
	Release();
}
//<======================================================================
//
//<======================================================================
void C2DContinue::Update(void)
{
	if (m_bUpdate)
	{
		//セレクト更新
		SelectUpdate();

		//セレクトの数分繰り返す
		for (int nCnt = 0; nCnt < SELECT::SELECT_MAX; ++nCnt)
		{
			if (m_apSelect[nCnt] )
			{
				m_apSelect[nCnt]->SetVtx();

				//情報の取得
				m_rPos = m_apSelect[nCnt]->GetPosition();
				m_rSize = m_apSelect[nCnt]->GetSize();

				//設定
				m_apSelect[nCnt]->SetPosition(m_rPos);
				m_apSelect[nCnt]->SetSize(m_rSize);

			}
		}

		//セレクトの数分繰り返す
		for (int nCnt = 0; nCnt < TYPE::TYPE_MAX; ++nCnt)
		{
			if (m_apObject2D[nCnt] )
			{
				m_apObject2D[nCnt]->SetVtx();

				//情報の取得
				m_rPos = m_apObject2D[nCnt]->GetPosition();
				m_rSize = m_apObject2D[nCnt]->GetSize();

				//設定
				m_apObject2D[nCnt]->SetPosition(m_rPos);
				m_apObject2D[nCnt]->SetSize(m_rSize);
			}

		}
	}
}
//<======================================================================
//
//<======================================================================
void C2DContinue::SelectUpdate(void)
{
	//前回の選択を保存する
	m_nOldSelect = m_nSelect;

	m_pChangeCol->ChangeColAdd();

	//左キーが押されていたら
	if (CManager::GetKeyboard()->bGetTrigger(DIK_LEFTARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_LEFT, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + (SELECT::SELECT_MAX - 1)) % SELECT::SELECT_MAX;
		m_pChangeCol->SetColor(INIT_COL);
	}
	//右キーが押されていたら
	else if (CManager::GetKeyboard()->bGetTrigger(DIK_RIGHTARROW)
		|| CManager::GetJoyPad()->GetTrigger(BUTTON::BUTTON_RIGHT, 0))
	{
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + 1) % SELECT::SELECT_MAX;
		m_pChangeCol->SetColor(INIT_COL);
	}

	//カラーを設定する
	m_apSelect[m_nOldSelect]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_pChangeCol->GetMinAlpha()));
	m_apSelect[m_nSelect]->SetColor(m_pChangeCol->GetColor());
}