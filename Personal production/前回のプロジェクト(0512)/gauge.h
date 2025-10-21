//=================================================
//
//	Gauge.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef _CGAUGE_H_
#define _CGAUGE_H_

#include "object2D.h"
#include "baseUI.h"

class CGauge : public CObject2D
{
public:
	CGauge(int nPriolity = 15);
	~CGauge();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetGageLength(const int nMaxLife, const int nCurrentLife, float fValue, float Height); // �ő�̒����A���̒����A�{���A����
	void FSetGageLength(float fMax, float fCurrent, float fMaxWidth, float fHeight);			// �ő�l�A���݂̒l�A�ő�̉����A����

	static CGauge* Create(D3DXVECTOR3 pos,const char* aTxt,D3DXCOLOR col);

private:
	CBaseUI* m_pBaseUI;
	int m_nIdx;
	float m_fCnt;
	float m_fCnt1;
	const char* m_aName;
	//D3DXCOLOR m_col;
};

#endif