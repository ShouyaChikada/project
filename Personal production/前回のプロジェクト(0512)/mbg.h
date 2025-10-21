//================================================
// 
// MultipleBackGround.h
// 
// Author:�ߓc ����
//
//================================================
#ifndef _MBG_H_
#define _MBG_H_

#include "main.h"
#include "object.h"
#include "object2D.h"

class CMbg :public CObject
{
public:
	CMbg();
	~CMbg();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	CMbg* Create(D3DXVECTOR3 pos);
	static CObject2D* GetObject2D(void);

private:
	static CObject2D* pObject2D;	//�I�u�W�F�N�g2D�̃|�C���^
	D3DXVECTOR3 m_pos;	//�ʒu
	D3DXVECTOR3 m_rot;	//��]
};

#endif