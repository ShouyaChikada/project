//=================================================
//
//	light.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "main.h"

//�}�N��
#define MAX_LIGHT (5)

class CLight
{
public:
	CLight();
	~CLight();
	//�v���g�^�C�v�錾
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
private:
	static D3DLIGHT9 m_light[MAX_LIGHT];	//���C�g���
};
#endif
