//=================================================
//
//	gimmickmanager.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef GIMMICKMANAGER_H_
#define GIMMICKMANAGER_H_

#include "main.h"
#include "gimmick.h"
#include "particle.h"
#include "baseUI.h"
#include "gauge.h"

#define MAX_COUNT (2)
#define MAX_GIMMICK (128)

class CGimmickManager
{
public:

	CGimmickManager();
	~CGimmickManager();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGimmick** GetGimmick(void) { return &m_pGimmick[0]; }
	static bool GetRange(void) { return m_bRange; }
	static bool GetPush(void) { return m_bPush; }
	static CParticle* GetParticle(void) { return m_pParticle; }
	static int GetCntGimmick(void) { return m_nCntGimmick; }
	static bool GetbCheck(void) { return m_bCheck; }

private:
	static bool m_bRange;			// �͈͂ɓ����Ă��邩�ǂ���
	static bool m_bPush;			// �{�^���������Ă��邩�ǂ���
	static bool m_bCheck;					// ��Ƃ��I���Ă��邩�ǂ���
	static CGimmick* m_pGimmick[MAX_GIMMICK];	// �M�~�b�N�̃|�C���^
	static CParticle* m_pParticle;
	static int m_nCntGimmick;			// ������or�j�󂵂��M�~�b�N�̃J�E���g
	bool m_bUse;
	bool m_bTime;
	int m_nCnt[MAX_COUNT];

};

#endif