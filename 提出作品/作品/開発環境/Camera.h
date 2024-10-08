//<==================================
//カメラ処理(Camera.h)
//
//Author:kazuki watanabe
//<==================================
#ifndef _CAMERA_H_		//このマクロ定義がされていなかったら
#define _CAMERA_H_		//二重インクルード防止のマクロを定義する

#include "main.h"
#include "object.h"
//<************************************************
//カメラのクラス定義
//<************************************************
class Ccamera
{
public:

	//<=====================================
	//投影タイプの列挙型
	//<=====================================
	enum TYPE
	{
		TYPE_NONE = 0,
		TYPE_XRAY,		//透視投影
		TYPE_PARALLEL,	//平行投影
		TYPE_MAX

	};
	//<=====================================
	//視界の列挙型
	//<=====================================
	enum VISIBILITY
	{
		VISIBILITY_FPV = 0,		//一人称
		VISIBILITY_TPS,			//三人称
		VISIBILITY_MAX	
	};

	Ccamera();
	~Ccamera();

	static Ccamera *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void SetCamera(void);
	void MoveRot(void);

	void MoveVR(void);
	void SetV(void);
	void SetR(void);
	void SetRot(void);
	void SetMoveFollow(void);
	void SetFollow(const D3DXVECTOR3 rTargetPos, const D3DXVECTOR3 rTargetRot,const VISIBILITY eVisibility);


	//<===========================================
	//使わない関数
	//<===========================================
	void Draw(void) { return; }
	void SetVtx(void) { return; }
	CObject2D *GetObject2D(void) { return NULL; }

	//<==========================================
	//Getする際、呼び出したいメンバ変数を宣言
	//<==========================================
	D3DXVECTOR3 m_posV;		//視点(カメラの位置)
	D3DXVECTOR3 m_posR;		//注視点(見たい場所)
	D3DXVECTOR3 m_rot;		//向き
	float m_fDistance;		//距離
	bool m_bFollow;			//追尾するかどうか
	int m_nShakeCount;

	void Shake(void);

	//この関数限定のメンバ変数
private:

	void ControllMouse(void);

	D3DXVECTOR3 m_posVDest;			//目標の視点
	D3DXVECTOR3 m_posVOld;			//視点(カメラの位置)
	D3DXVECTOR3 m_posROld;			//注視点(見たい場所)
	D3DXVECTOR3 m_posRDest;			//目標の注視点

	D3DXVECTOR3 m_move;				//移動量
	D3DXVECTOR3 m_rotVDest;			//目標の視点の向き

	D3DXVECTOR3 m_vecU;				//上方向ベクトル

	D3DXMATRIX	m_mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX	m_mtxView;			//ビューマトリックス

	float m_rotVDiff;				//目標の視点の差分

	TYPE m_Type;					//投影タイプ

};
//class CTitleCamera : public Ccamera
//{
//public:
//
//	CTitleCamera();
//	~CTitleCamera();
//
//	CTitleCamera *Crete(void);
//
//private:
//};

#endif