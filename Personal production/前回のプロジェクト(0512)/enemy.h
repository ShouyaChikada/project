//=================================================
//
//	enemy.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "object2D.h"

//�}�N��
#define NUM_ENEMY (10)				//�G�̍ő吔

//�N���X
class CEnemy :public CObject2D
{
public:
	// �G�����
	typedef enum
	{
		TYPE_BOSS = 0,
		TYPE_CAT,
		TYPE_RED,
		TYPE_YELLOW,
		TYPE_NYORO,
		TYPE_MAX
	}TYPE;

	CEnemy();
	~CEnemy();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float SizeX,float SizeY, TYPE type);

private:

	D3DXVECTOR3 m_pos;									//�ʒu
	D3DXVECTOR3 m_move;									//�ړ�
	D3DXVECTOR3 m_rot;									//����
	static float m_SizeX;								//��
	static float m_SizeY;								//�c
	int m_nCnt;
};
#endif