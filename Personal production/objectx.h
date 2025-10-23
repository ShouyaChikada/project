//=================================================
//
// ObjectX.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"
#include "model.h"

#define MAX_LOAD (128)
#define MAX_SPEED (4.0f)
#define MAX_ROT (0.175f)

class CObjectX :public CObject
{
public:
	CObjectX(int nPriolty = 3);
	~CObjectX();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CObjectX* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* txt);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetXfile(const char* txt) { m_txt = txt; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	LPD3DXMESH GetMesh(void);
	void SetInput(void);
	//bool Collision(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 move);
private:
	LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	// �e�N�X�`���̃|�C���^
	LPD3DXMESH m_pMesh;							// ���b�V���̃|�C���^
	LPD3DXBUFFER m_pBuffMat;					// �}�e���A���̃|�C���^
	DWORD m_dwNumMat;							// �}�e���A����
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXMATRIX m_mtxRot;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_SetPosition;					// �ʒu
	D3DXVECTOR3 m_rot;							// ����
	D3DXVECTOR3 m_rotDest;						// �ړI�̌���
    D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_posOld;						// �ړI�̈ʒu
	D3DXVECTOR3 m_move;							// �ړ���
	D3DXVECTOR3 m_VecAxis;						// ��]��
	float m_fValueRot;							// ��]�p(��]��)
	CModel* m_pModel;							// ���f���̃|�C���^
	//CShadowS* m_pShadowS;						// �V���h�E�̃|�C���^
	static const char* m_txt;					// �e�L�X�g
	int m_nIdx[MAX_LOAD];						// �C���f�b�N�X
	float m_Diff;								// ����

};
#endif
