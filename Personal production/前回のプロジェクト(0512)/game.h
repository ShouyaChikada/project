//=================================================
//
//	game.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "player.h"
#include "bullet.h"
#include "score.h"
#include "object3D.h"
#include "billboard.h"
#include "objectx.h"
#include "motion.h"
#include "model.h"
#include "meshfield.h"
#include "object.h"
#include "block.h"
#include "blockmanager.h"
#include "shadows.h"
#include "scene.h"
#include "fade.h"
#include "jimen.h"
#include "gimmickmanager.h"
#include "humanmanager.h"
#include "time.h"
#include "pausemanager.h"

class CGame :public CScene
{
public:
	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScore* GetScore(void);
	static CObject3D* GetObject3D(void);
	static CBillboard* GetBillboard(void);
	static CObjectX* GetObjectX(void);
	static CMeshField* GetMeshField(void);
	static CBlockManager* GetBlockManager(void);
	static CPlayer* GetPlayer(void);
	static CShadowS* GetShadowS(void);
	static CGrand* GetGrand(void);
	static CGimmickManager* GetGimmickManager(void);
	static CHumManager* GetHumManamger(void);
	static CTime* GetTime(void);
	static CPauseManager* GetPauseManager(void) {return m_pPauseManager; }
	static bool GetCheck(void) { return m_bCheck; }
	static CModel** GetModel1(void);
	static CMotion* GetMotion1(void);

private:
	static CPlayer* m_pPlayer;					// �v���C���[�̃|�C���^
	static CScore* m_pScore;					// �X�R�A�̃|�C���^
	static CObject3D* m_pObject3D;				// �I�u�W�F�N�g3D�̃|�C���^
	static CBillboard* m_pBillboard;			// �r���{�[�h�̃|�C���^
	static CObjectX* m_pObjectX;				// �I�u�W�F�N�gX�̃|�C���^
	static CMeshField* m_pMeshField;			// ���b�V���t�B�[���h�̃|�C���^
	static CBlockManager* m_pBlockManager;		// �u���b�N�}�l�[�W���[�ւ̃|�C���^
	static CShadowS* m_pShadowS;				// �V���h�E�ւ̃|�C���^
	static CGrand* m_pGrand;					// �n�ʂւ̃|�C���^
	static CGimmickManager* m_pGimmickManager;	// �M�~�b�N�}�l�[�W���[�̃|�C���^
	static CHumManager* m_pHumManager;			// �q���[�}���}�l�[�W���[�̃|�C���^
	static CTime* m_pTime;						// �^�C���̃|�C���^
	static CPauseManager* m_pPauseManager;
	static CMotion* m_pMotion1;					// ���[�V�����̃|�C���^
	static CModel* m_pModel1[MAX_HMODEL];		// ���f���̃|�C���^
	static bool m_bCheck;
};

#endif

