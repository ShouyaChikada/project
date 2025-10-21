//=================================================
//
//	object3D.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "main.h"
#include "object.h"

//�h���N���X
class CObject3D :public CObject
{
public:
	//���
	typedef enum
	{
		STATE_NONE = 0,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_MAX
	}STATE;

	CObject3D();
	CObject3D(int nPriority);
	~CObject3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	static CObject3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	D3DXVECTOR3 GetPosition(void);
private:

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	D3DXVECTOR3 m_SetPosition;			//�ʒu
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_pos;
	D3DXMATRIX m_mtxWorld;	//�}�g���b�N�X
};
#endif
