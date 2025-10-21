//=================================================
//
//	time.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "object.h"
#include "number.h"

#define MAX_COUNTTIME (300)	//�Q�[�����̎���
#define MAX_TIME (2)		//�`�掞��0�̐�
#define MAX_MIN (2)

class CTime :public CObject
{
public:
	CTime(int nPriolity = 13);
	~CTime();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	static CTime* Create(D3DXVECTOR3 pos);

	void SetTime(int ntime);
	void SubNs(int nValue);
	void SubMin(int nValue);
	int GetNs(void);
	int GetMin(void);
	bool GetbTime(void) { return m_bTime; }
	static int GetTime(void) { return m_nTime; }
private:
	static CNumber* m_pNumber1[MAX_TIME];	//�i���o�[�̃|�C���^(�b)
	static CNumber* m_pNumber2[MAX_TIME];	//�i���o�[�̃|�C���^(��)
	static CNumber* m_pNumber3;				//�i���o�[�̃|�C���^(�F)
	D3DXVECTOR3 m_pos;						// �^�C�}�[�̈ʒu
	D3DXVECTOR3 m_SetPosition;				//�ʒu
	int m_ntime;							// �^�C�}�[�̒l
	int m_ns;								// �b
	int m_min;								// ��
	bool m_bTime;							// �G���h���ǂ����m�F
	static int m_nTime;
};

#endif