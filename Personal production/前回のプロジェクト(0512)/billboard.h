//=================================================
//
//	billboard.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "object.h"

//�}�N��
#define MAX_BILLBOARD (128)	//�r���{�[�h�̍ő吔

class CBillboard :public CObject
{
public:
	CBillboard(int nPriority = 13);
	~CBillboard();
	//�v���g�^�C�v�錾
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillboard* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//�e�Ƃ��o�������ꍇ
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void);
	void SetColor(D3DXCOLOR col) { m_col = col; }
	void SetRadius(float fRadius) { m_fRadius = fRadius; }

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_SetPosition;			//�ʒu
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_rot;					//����
	D3DXCOLOR m_col;
	D3DXVECTOR3 m_move;					//�ړ���
	D3DXVECTOR3 m_dir;					//�����i�[
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
	bool m_bTest;
	bool m_bUse;
	float m_fRadius;
};
#endif