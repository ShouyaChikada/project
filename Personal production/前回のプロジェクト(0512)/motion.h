//=================================================
//
//	motion.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "model.h"

#define MAX_MOTIONINFO (6)
#define NUM_MOTION (32)
#define MAX_WORD (256)
#define MAX_OMIT (3)
class CMotion
{
public:
	//���[�V�����̎��
	typedef enum
	{
		MOTIONTYPE_NEUTRAL = 0,	//�ҋ@
		MOTIONTYPE_MOVE,		//�ړ�
		MOTIONTYPE_ACTION,		//�A�N�V����
		MOTIONTYPE_JUMP,		//�W�����v
		MOTIONTYPE_LANDING,		//���n
		MOTIONTYPE_MAX
	}MOTIONTYPE;

	//���[�V�����̏��
	typedef enum
	{
		MOTIONSTATE_NEUTRAL = 0,	//�ҋ@
		MOTIONSTATE_MOVE,			//�ړ�
		MOTIONSTATE_ACTION,			//�A�N�V����
		MOTIONSTATE_JUMP,			//�W�����v
		MOTIONSTATE_LANDING,		//���n
		MOTIONSTATE_MAX
	}MOTIONSTATE;

	//�L�[�̍\����
	typedef struct
	{
		float m_fPosX;	//�ʒuX
		float m_fPosY;	//�ʒuY
		float m_fPosZ;	//�ʒuZ
		float m_fRotX;	//����X
		float m_fRotY;	//����Y
		float m_fRotZ;	//����Z
	}KEY;

	//�L�[���̍\����
	typedef struct
	{
		int m_nFrame;		//�Đ��t���[��
		KEY m_aKey[NUM_MOTION];	//�e�p�[�c�̃L�[�v�f
	}KEY_INFO;

	//���[�V�������̍\����
	typedef struct
	{
		bool m_bLoop;				//���[�v���邩�ǂ���
		int m_nNumKey;			//�L�[����
		KEY_INFO m_aKeyInfo[NUM_MOTION];	//�L�[���
	}INFO;

	CMotion();
	~CMotion();
	HRESULT Init(const char* txt,CModel **ppModel);
	void Uninit(void);
	void Set(MOTIONTYPE nType);
	void Update(CModel** ppModel);
	int GetType(void);
	//bool bFinish(void);
	void SetInfo(INFO info);
	void SetModel(const char* txt,CModel** ppModel);
	static CMotion* Create(const char* txt, CModel** ppModel);
private:
	D3DXVECTOR3 pos;
	int nCounterState;
	bool bJump;						//�W�����v���Ă��邩�ǂ���
	bool bUse;

	INFO m_aInfo[NUM_MOTION];	//���[�V�������1
	int nNumAll;					//���[�V��������1
	MOTIONTYPE MotionType;			//���[�V�����̎��
	//bool bLoopMotion;				//��[�Ղ��邩�ǂ���
	int m_nCounterMotion;				//���[�V�����J�E���^�[
	int m_nNext;						//���̃L�[
	int m_nType;
	MOTIONSTATE MotionState;		//���[�V�����̏��

	int m_PartsCount;
	int m_nFrame;
	int m_nNumKey;
	int m_Loop;
	int m_nMotion;
	int m_nKey;
	int m_nCount;
	bool m_aMotionLoop[MAX_MOTIONINFO];
	CModel** m_ppModel;	//���f���̃|�C���^
	int m_nNumModel;	//���f���̑���
};
#endif