//=================================================
//
//	model.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

class CModel
{
public:

	CModel();
	~CModel();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt);
	void SetParent(CModel* pModel);
	D3DXMATRIX GetMtxWorld(void);
	void SetPos(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetPosOld(D3DXVECTOR3 PosOld);
	void SetSize(D3DXVECTOR3 Size);
	void SetMove(D3DXVECTOR3 Move);
	//void SetX(const char* txt);
	void SetPosX(float posX) { m_pos.x = posX; };
	static D3DXVECTOR3 GetSize(void);

private:

	int*  m_pTexture;								// �e�N�X�`���̃|�C���^
	D3DXVECTOR3 m_pos;								// �ʒu
	D3DXVECTOR3 m_posOld;								// �O�̈ʒu
	D3DXVECTOR3 m_rot;								// ��]
	D3DXVECTOR3 m_move;								// �ړ�
	D3DXVECTOR3 m_VtxMax;							// ���_�ő�l
	D3DXVECTOR3 m_VtxMin;							// ���_�ŏ��l
	static D3DXVECTOR3 m_Size;						// �T�C�Y
	LPD3DXMESH m_pMesh;								// ���b�V���̃|�C���^
	LPD3DXBUFFER m_pBuffMat;						// �}�e���A���̃|�C���^
	DWORD m_dwNumMat;								// �}�e���A����
	D3DXMATRIX m_mtxWorld;							// ���[���h�}�g���b�N�X
	CModel* m_pParent;								//�e���f���̃|�C���^
};
#endif