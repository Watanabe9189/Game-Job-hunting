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
LPDIRECT3DTEXTURE9	C2DInfo::m_apTexture[TYPE_MAX] = {};
const char*			C2DInfo::m_acFilename[TYPE_MAX] =
{
	"data\\TEXTURE\\Item001.png",
	"data\\TEXTURE\\number_02.png",
	"data\\TEXTURE\\Item000.png",
};
//<*************************************************************************
//
//<*************************************************************************
namespace Number
{
	const D3DXVECTOR2 INFO_POS = D3DXVECTOR2(70.0f, 660.0f);
	const D3DXVECTOR2 INFO_SIZE = D3DXVECTOR2(75.0f, 75.0f);

	const D3DXVECTOR2 NUMBER_POS = D3DXVECTOR2(INFO_POS.x+100.0f , INFO_POS.y);
	const D3DXVECTOR2 NUMBER_SIZE = D3DXVECTOR2(50.0f, 50.0f);

}
//<*************************************************************************
//
//<*************************************************************************
namespace Figure
{
	const D3DXVECTOR2 INFO_POS = D3DXVECTOR2(125.0f, 85.0f);					//情報位置
	const D3DXVECTOR2 INFO_SIZE = D3DXVECTOR2(100.0f, 100.0f);					//情報サイズ

	const D3DXVECTOR2 FIGURE_POS = D3DXVECTOR2(25.0f, 675.0f);//図位置
	const D3DXVECTOR2 FIGURE_SIZE = D3DXVECTOR2(50.0f, 50.0f);					//図サイズ

	const float DISTANCE = 75.0f;												//距離
	const D3DXCOLOR FIGURE_COL = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);				//図色
}
//<===========================================
//
//<===========================================
C2DInfo::C2DInfo(int nPriority)
{
	m_eClass = Class::CLASS_MAX;
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
C2DInfo *C2DInfo::Create(const Class eClass)
{
	//インスタンス生成
	C2DInfo *p2DInfo = nullptr;

	if (eClass == Class::CLASS_NUMBER)
	{
		p2DInfo = new CInfoNum;

		p2DInfo->Init();
	}
	else if (eClass == Class::CLASS_FIGURE)
	{
		p2DInfo = new CInfoFigure;

		p2DInfo->Init();
	}

	//中身と初期化チェック
	assert(p2DInfo != nullptr);

	p2DInfo->m_eClass = eClass;

	return p2DInfo;
}
//<===========================================
//
//<===========================================
HRESULT C2DInfo::Init(void)
{
	//テクスチャの初期化
	for (int nCnt = 0; nCnt < (sizeof m_acFilename) / sizeof(*m_acFilename); nCnt++)
	{
		//最初だけ読み込む
		if (m_apTexture[nCnt] == nullptr)
		{
			//テクスチャの読み込み
			if (CManager::GetTex()->Regist(m_acFilename[nCnt], m_apTexture[nCnt]) <= -1)
			{
				return E_FAIL;
			}
		}
	}

	return S_OK;
}
//<===========================================
//
//<===========================================
void C2DInfo::Uninit(void)
{
	Release();
}
//<********************************************
//番号での情報
//<===========================================
//
//<===========================================
CInfoNum::CInfoNum(int nPriority)
{
	//値のクリア
	m_pObject2D = nullptr;
	m_pNumber = nullptr;
	m_nNum = INITIAL_INT;
}
//<===========================================
//
//<===========================================
CInfoNum::~CInfoNum()
{

}
//<===========================================
//
//<===========================================
HRESULT CInfoNum::Init(void)
{
	C2DInfo::Init();

	//生成処理をする
	m_pObject2D = CObject2D::Create(Number::INFO_POS, Number::INFO_SIZE, INIT_COL, m_apTexture[TYPE::TYPE_INFO_CHAR]);
	m_pNumber = CNumber::Create(Number::NUMBER_POS, Number::NUMBER_SIZE, m_apTexture[TYPE::TYPE_INFO_NUMBER]);

	//中身チェック
	assert(m_pObject2D != nullptr && m_pNumber != nullptr);

	return S_OK;
}
//<===========================================
//
//<===========================================
void CInfoNum::Uninit(void)
{
	//中身を破棄する
	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Uninit();
		m_pObject2D = nullptr;
	}

	//中身を破棄する
	if (m_pNumber != nullptr)
	{
		m_pNumber->Uninit();
		m_pNumber = nullptr;
	}
	C2DInfo::Uninit();
}
//<===========================================
//
//<===========================================
void CInfoNum::Update(void)
{
	//残り数を取得してくる
	m_nNum = CItem::GetNumLeft();

	//0個だったら
	if (m_nNum == 0)
	{
		m_pNumber->SetDrawfalse();
	}

	//数を設定する
	m_pNumber->SetNum(&m_nNum);

	//更新処理
	m_pObject2D->SetVtx();
	m_pNumber->Update();
}
//
//<********************************************
//<********************************************
//番号での情報
//<===========================================
//
//<===========================================
CInfoFigure::CInfoFigure(int nPriority)
{
	//値のクリア
	m_nNum = INITIAL_INT;

	//
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_SIZE; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}
	m_rCol = INIT_COL;

}
//<===========================================
//
//<===========================================
CInfoFigure::~CInfoFigure()
{

}
//<===========================================
//
//<===========================================
HRESULT CInfoFigure::Init(void)
{
	C2DInfo::Init();

	//
	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		m_apObject2D[nCnt] = CObject2D::Create(
			D3DXVECTOR2(Figure::FIGURE_POS.x + Figure::DISTANCE *nCnt, Figure::FIGURE_POS.y),
			Figure::FIGURE_SIZE,
			Figure::FIGURE_COL,m_apTexture[TYPE::TYPE_INFO_FIGURE]);

		//中身チェック
		assert(m_apObject2D[nCnt] != nullptr);
	}
	return S_OK;
}
//<===========================================
//
//<===========================================
void CInfoFigure::Uninit(void)
{
	//
	for (int nCnt = 0; nCnt < INT_VALUE::MAX_SIZE; nCnt++)
	{
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
		else
		{
			break;
		}
	}

	C2DInfo::Uninit();
}
//<===========================================
//
//<===========================================
void CInfoFigure::Update(void)
{
	//番号ごとに
	for (int nCnt = 0; nCnt < CItem::GetNum(); nCnt++)
	{
		//アイテムをゲットしていなければ
		if (CScene::GetGame()->GetItem(nCnt)->bGet() == false)
		{
			//初期値に戻す
			m_apObject2D[nCnt]->SetColor(Figure::FIGURE_COL);
		}
		//アイテムをゲットしていたら
		else
		{
			//初期値に戻す
			m_apObject2D[nCnt]->SetColor(INIT_COL);
		}
		//初期値に戻す
		m_apObject2D[nCnt]->SetVtx();
	}
}
//
//<********************************************