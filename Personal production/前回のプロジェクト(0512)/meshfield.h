//=================================================
//
//	meshfield.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "object.h"

#define MESHFIELD_V_BLOCK (1)		//X�����̃u���b�N��
#define MESHFIELD_H_BLOCK (24)		//Z�����̃u���b�N��
#define MESHFIELD_MAX_VTX ((MESHFIELD_V_BLOCK + 1) * (MESHFIELD_H_BLOCK + 1))		//���_��

class CMeshField :public CObject
{
public:
	struct Vertex 
	{
		float x, y, z;  // ���W
		DWORD color;    // �F
	};

	CMeshField(int nPriority = 1);
	~CMeshField();
	//�v���g�^�C�v�錾
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static	CMeshField* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	void GenerateSphereVertices(float radius, int slices, int stacks, vector<Vertex>& vertices);
	void RenderSphere(LPDIRECT3DDEVICE9 pDevice,const vector<Vertex>& vertices,int slices, int stacks);

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
