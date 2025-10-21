//=================================================
//
//	effect.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef EFFECT_H_
#define EFFECT_H_

#include "main.h"
#include "billboard.h"

#define MAX_EFFECT (128)

class CEffect :public CBillboard
{
public:
	CEffect();
	~CEffect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife);

private:
	int m_nIdx;
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_move; //�ړ���
	D3DXCOLOR m_col;	//�ړ���
	int m_nLife;			//����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;

};
#endif