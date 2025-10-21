//=================================================
//
//	number.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

class CNumber
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;//���_���W
		float rhw;		//���p�ϊ��p�W��(1.0f�ŌŒ�)
		D3DCOLOR col;	//���_�J���[
		D3DXVECTOR2 tex;//�e�N�X�`�����W

	}VERTEX_2D;

	CNumber();
	~CNumber();
	HRESULT Init(float fX1,float fX2, int nCnt,float fNum1,float fNum2,int nNum,int nAdd,const char* FileName,float fx);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CNumber* Create(D3DXVECTOR3 pos);
	void SetNumber(int nNumber, int nAdd);


private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_pos;						// �e�̈ʒu
	int m_nIdx;								// �C���f�b�N�X�ԍ�

};
#endif