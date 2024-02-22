//<==============================================
//2D�Q�[�W����(2DGauge.ch)
//
//Author:kazuki watanabe
//<==============================================
#ifndef _2DGAUGE_H_
#define _2DGAUGE_H_

#include "main.h"
#include "object.h"
#include "object2D.h"

//<****************************************
//�N���X��`
//<****************************************
class C2DGauge : public CObject
{
public:

	//<===================================
	//
	//<===================================
	enum VERTEX
	{
		VERTEX_X = 0,
		VERTEX_Y,
		VERTEX_MAX
	};

	//<===================================
	//
	//<===================================
	enum TYPE
	{
		TYPE_GAUGE = 0,
		TYPE_FRAME,
		TYPE_MAX
	};
	//<===================================
	//
	//<===================================
	enum MODE
	{
		MODE_ALWAYS = 0,
		MODE_ONLY_USE,
		MODE_MAX
	};

	C2DGauge(int nPriority = FIX_PRIORITY);
	~C2DGauge();

	static C2DGauge *Create(const D3DXVECTOR2 pos,const int nMaxNum,const VERTEX eVer,const MODE eMode);

	HRESULT Init(void)	override;
	void Uninit(void)	override;
	void Update(void)	override;
	void Draw(void)		override;
	void SetVtx(void)	override;

	void Add(const int nValue);
	void SetNum(const int nNum);
	static void SetFixed(const int nFixed) 
	{ m_nFixedMax = nFixed; }
	static int GetFixed(void) { return m_nFixedMax; }
	static int GetLimitMax(void) { return m_nMaxLimit; }
	static int GetLimitMin(void) { return m_nMinLimit; }

	void NoUseFrame(void) { m_apObject2D[TYPE::TYPE_FRAME]->SetDrawfalse(); }

private:

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_apTexture[INT_VALUE::MAX_TEX];
	static const char*			m_acFilename[];				//�t�@�C����

	D3DXVECTOR2 m_rPos;					//�ʒu
	D3DXVECTOR2 m_rSize;				//�T�C�Y
	D3DXCOLOR m_rCol;					//�F
	static int m_nFixedMax;
	static int m_nMaxLimit;
	static int m_nMinLimit;
	static float m_StaAddValue;
	float m_fAddValue;					//���Z����l
	float m_fOldAdd;
	float m_fChange;					//�ϓ���
	float m_fCurrent;					//���̃Q�[�W��
	float m_fGaugeSize;
	int m_nNum;							//�Q�[�W��
	int m_nMax;							//�ő�Q�[�W��
	VERTEX m_eVer;						//�����񋓌^
	MODE m_eMode;						//���[�h�񋓌^

	CObject2D *m_apObject2D[TYPE::TYPE_MAX];

};

#endif
