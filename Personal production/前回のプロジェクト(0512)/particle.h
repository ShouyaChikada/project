//=================================================
//
//	particle.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "object.h"
#include "effect.h"

//�}�N����`
#define MAX_PARTICLE (128)																//�p�[�e�B�N���̍ő吔

class CParticle :public CObject
{
public:

	CParticle();
	~CParticle();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CParticle* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; }


private:
	D3DXVECTOR3 m_pos;	//�e�̈ʒu
	D3DXVECTOR3 m_move;	//�e�̈ړ�
	D3DXCOLOR m_col;
	int m_nLife;
	int m_nCnt;
};
#endif