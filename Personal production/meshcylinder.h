//=================================================
//
//	meshcylinder.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

#include "main.h"
#include "object.h"

#define MESHFIELD_V_BLOCK (1)		//X�����̃u���b�N��
#define MESHFIELD_H_BLOCK (24)		//Z�����̃u���b�N��
#define MESHFIELD_MAX_VTX ((MESHFIELD_V_BLOCK + 1) * (MESHFIELD_H_BLOCK + 1))		//���_��
#define MESHFIELD_MAX_POLYGON (MESHFIELD_V_BLOCK * MESHFIELD_H_BLOCK * 2 + (MESHFIELD_H_BLOCK - 1) * 2)	//�|���S����
#define MESHFIELD_MAX_INDEX (MESHFIELD_MAX_POLYGON + 2/*(MESHFIELD_X_BLOCK + 1) * 2 * MESHFIELD_Z_BLOCK + (MESHFIELD_Z_BLOCK - 1) + 2*/)		//�C���f�b�N�X��

class CMeshCylinder :public CObject
{
public:
	CMeshCylinder(int nPriority = 1);
	~CMeshCylinder();
	//�v���g�^�C�v�錾
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static	CMeshCylinder* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_rot;					//����
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	float m_fRadius;						//���a
	int m_nIdx;
};

#endif
