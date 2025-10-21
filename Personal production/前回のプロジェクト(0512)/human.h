//=================================================
//
//	human.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef _HUMAN_H_
#define _HUMAN_H_

#include "main.h"
#include "object.h"
#include "model.h"
#include "motion.h"
#include "objectx.h"
#include "shadows.h"

//�}�N��
#define MAX_SPEED (15.0f)
#define MAX_RANDPOINT (32)

class CHuman :public CObject
{
public:

	CHuman(int nPriority = 5);
	~CHuman();
	static CHuman* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetRotDest(void);
	D3DXVECTOR3 GetPos(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetPosOld(void);
	D3DXVECTOR3 GetSize(void);
	void SetPosition(D3DXVECTOR3 pos);
	void AutoWand(D3DXVECTOR3 pos);		//	Automatedwandering	�����p�j
private:
	D3DXVECTOR3 m_pos;						//�ʒu
	D3DXVECTOR3 m_posOld;
	D3DXVECTOR3 m_move;						//�ړ�
	D3DXVECTOR3 m_rot;						//����
	D3DXVECTOR3 m_rotDest;					//�ړI�̌���
	D3DXVECTOR3 m_SetPosition;
	D3DXVECTOR3 m_size;
	D3DXMATRIX m_mtxWorld;					//�}�g���b�N�X
	float m_Diff;
	CModel* m_apModel[MAX_HMODEL];			//���f���̃|�C���^
	CMotion* m_pMotion;
	bool m_bJump;
	bool m_bLeave;
	int m_nCnt;
	bool m_bCnt;

};

#endif
