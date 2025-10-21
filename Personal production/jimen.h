//=================================================
//
//	jimen.h
// 
// Author:�ߓc ����
//
//=================================================

#ifndef _JIMEN_H_
#define _JIMEN_H_

#include "main.h"
#include "object.h"

//�}�N����`
#define GRAND_X_BLOCK (10)		//X�����̃u���b�N��
#define GRAND_Z_BLOCK (10)		//Z�����̃u���b�N��
#define GRAND_VERTEX_NUM ((GRAND_X_BLOCK + 1) * (GRAND_Z_BLOCK + 1))		//���_��
#define GRAND_INDEX_NUM (GRAND_X_BLOCK * GRAND_Z_BLOCK * 2 + (GRAND_Z_BLOCK - 1) * 12)	//�|���S����
#define GRAND_PRIMITVE_NUM (GRAND_X_BLOCK * GRAND_Z_BLOCK * 2 + (GRAND_Z_BLOCK + (GRAND_Z_BLOCK - 1) * 4)		//�C���f�b�N�X��

class CGrand :public CObject
{
public:
	CGrand(int nPriolity = 2); 
	~CGrand();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static	CGrand* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);

private:
	D3DXVECTOR3 m_pos;							//�ʒu
	D3DXVECTOR3 m_rot;							//����
	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;			//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	float m_aPosTexU;
	int m_nIdx;

};

#endif
