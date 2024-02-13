//<================================================
//2Dパーティクル処理(2DParticle.cpp)
//
//Author:kazuki watanabe
//<================================================
#include "2DParticle.h"
#include "2DEffect.h"

namespace Particle2D
{
	const int NUM_USE = 1;
	const D3DXVECTOR2 MOVE_VALUE = D3DXVECTOR2(2.0f, 2.0f);
}

//<==================================================
//
//<==================================================
C2DParticle::C2DParticle()
{
	//値のクリア
	m_rPos = D3DXVECTOR2(0.0f,0.0f);
	m_rCol = COLOR_VALUE::COLOR_INIT;
	m_nLife = INITIAL_INT;
	m_eType = TYPE::TYPE_MAX;

	m_bDisp = false;
}
//<==================================================
//
//<==================================================
C2DParticle::~C2DParticle()
{

}
//<==================================================
//
//<==================================================
C2DParticle *C2DParticle::Create(const D3DXVECTOR2 rPos, const D3DXCOLOR rCol, const TYPE eType)
{
	C2DParticle *p2DParticle = new C2DParticle;

	assert(p2DParticle != nullptr);

	//初期化がしっかりされたかチェック
	assert(SUCCEEDED(p2DParticle->Init()));

	p2DParticle->m_rPos = rPos;
	p2DParticle->m_rCol = rCol;
	p2DParticle->m_eType = eType;

	return p2DParticle;

}
//<==================================================
//
//<==================================================
HRESULT C2DParticle::Init(void)
{
	m_nLife = 100;
	return S_OK;
}
//<==================================================
//
//<==================================================
void C2DParticle::Uninit(void)
{
	Release();
}
//<==================================================
//
//<==================================================
void C2DParticle::Update(void)
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
void C2DParticle::Test(void)
{
	// 変数を宣言
	D3DXVECTOR2 move = INIT_VECTOR;	// 移動量の代入用
	D3DXVECTOR3 rot = INIT_VECTOR;	// 向きの代入用

	for (int nCntPart = 0; nCntPart < Particle2D::NUM_USE; nCntPart++)
	{ 

		//ベクトルをランダムに設定
		move.x = sinf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;
		move.y = cosf((float)(rand() % 629 - 314) / 100.0f) * 1.0f;
		
		//移動量を設定
		move.x *= Particle2D::MOVE_VALUE.x;
		move.y *= Particle2D::MOVE_VALUE.y;
	
		
		C2DEffect::Create
		(

			m_rPos,
			D3DXVECTOR3(move.x,move.y,0.0f),
			m_nLife,
			D3DXVECTOR2(50.0f, 50.0f),
			m_rCol
		);
	}
}