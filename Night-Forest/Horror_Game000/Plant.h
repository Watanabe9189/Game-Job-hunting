#ifndef _PLANT_H_
#define _PLANT_H_

#include "main.h"
#include "manager.h"
#include "Object3D.h"

#define MAX_GRASS	(2)	//草の最大数

class CPlant : public CObject3D
{
public:

	enum TYPE
	{
		TYPE_GRASS = 0,
		TYPE_TREE,
		TYPE_MAX

	};

	CPlant(int nPriority = FIX_PRIORITY);
	~CPlant();

	static CPlant *RandCreate(CPlant *apPlant[MAX_OBJECT],const int nNum);

	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override;
	void Draw(void)		override {}
	void SetVtx(void)	override {}

	static int GetNum(void) { return m_nNumAll; }

private:

	void Swaying(void);

	static LPDIRECT3DTEXTURE9	m_apTexture[TYPE::TYPE_MAX];		//テクスチャへのポインタ
	static const char*			m_acFilename[TYPE::TYPE_MAX];				//ファイル名

	static int m_nNumAll;

	D3DXVECTOR3 m_rPos;
	D3DXVECTOR3 m_rRot;
	D3DXVECTOR3 m_rSize;
	D3DXCOLOR m_rCol;

	float m_fMove;

	TYPE m_eType;

	CObject3D *m_apGrass[MAX_GRASS];

};
#endif
