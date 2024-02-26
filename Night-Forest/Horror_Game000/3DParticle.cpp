//<================================================
//2Dパーティクル処理(2DParticle.cpp)
//
//Author:kazuki watanabe
//<================================================
#include "3DParticle.h"
#include "3DEffect.h"

namespace Particle2D
{
	const int NUM_USE = 1;
	const D3DXVECTOR3 MOVE_VALUE = D3DXVECTOR3(15.0f, 15.0f, 15.0f);
}

//<==================================================
//
//<==================================================
C3DParticle::C3DParticle()
{
	//値のクリア
	m_rPos = INIT_VECTOR;
	m_rMove = INIT_VECTOR;
	m_rCol = COLOR_VALUE::COLOR_INIT;
	m_nLife = INITIAL_INT;
	m_eType = TYPE::TYPE_MAX;

	m_bDisp = false;
}
//<==================================================
//
//<==================================================
C3DParticle::~C3DParticle()
{

}
//<==================================================
//
//<==================================================
C3DParticle *C3DParticle::Create(const D3DXVECTOR3 rPos, const D3DXCOLOR rCol, const TYPE eType)
{
	C3DParticle *p3DParticle = new C3DParticle;

	assert(p3DParticle != nullptr);

	//初期化がしっかりされたかチェック
	assert(SUCCEEDED(p3DParticle->Init()));

	p3DParticle->m_rPos = rPos;
	p3DParticle->m_rCol = rCol;
	p3DParticle->m_eType = eType;

	return p3DParticle;

}
//<==================================================
//
//<==================================================
HRESULT C3DParticle::Init(void)
{
	m_nLife = 24;
	return S_OK;
}
//<==================================================
//
//<==================================================
void C3DParticle::Uninit(void)
{
	Release();
}
//<==================================================
//
//<==================================================
void C3DParticle::Update(void)
{
	//
	if (!(m_nLife <= 0))
	{
		m_nLife--;
	}
	//
	else
	{
		Uninit();

		return;
	}
	m_rPos += m_rMove;

	switch (m_eType)
	{
	case TYPE::TYPE_TEST:

		Test();

		break;

	default:

		break;


	}
}
//<==========================================================
//テスト用のパーティクル
//<==========================================================
void C3DParticle::Test(void)
{
	// 変数を宣言
	D3DXVECTOR3 move = Particle2D::MOVE_VALUE;	// 移動量の代入用
	D3DXVECTOR3 rot = INIT_VECTOR;	// 向きの代入用

	//
	if ((m_nLife + 1) % 12 == 0)
	{ 
		for (int nCntPart = 0; nCntPart < 1; nCntPart++)
		{

		  // ベクトルをランダムに設定
			m_rMove.x = sinf((float)(rand() % 629 - 314) / 100.0f) * 0.1f;
			m_rMove.y = cosf((float)(rand() % 629 - 314) / 100.0f) * 0.1f;
			m_rMove.z = cosf((float)(rand() % 629 - 314) / 100.0f) * 0.1f;

			// 移動量を設定
			m_rMove.x *= move.x;
			m_rMove.y *= move.y;
			m_rMove.z *= move.z;

			// エフェクト2Dオブジェクトの生成
			C3DEffect::Create
			( // 引数

				m_rPos,
				m_rMove,
				120,
				D3DXVECTOR2(50.0f, 50.0f),
				m_rCol
			);
		}
	}
}