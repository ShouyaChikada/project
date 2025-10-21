//=================================================
//
//	bullet.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "object2D.h"

//�}�N��
#define BULLET_WIDTH (60.0f)	//�e�̉��̃T�C�Y
#define BULLET_HEIGHT (60.0f)	//�e�̏c�̃T�C�Y
#define MAX_BULLET (128)

//�N���X�݌v
class CBullet:public CObject2D 
{
public:

	CBullet();
	~CBullet();
	HRESULT Init(D3DXVECTOR3 Pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	bool CollisionEnemy(D3DXVECTOR3 pos);

private:

	D3DXVECTOR3 m_pos;						// �e�̈ʒu
	D3DXVECTOR3 m_rot;						// �e�̌���
	D3DXVECTOR3 m_move;						// �e�̈ړ�
	int m_lifetime;							// �e�̎���
};

#endif