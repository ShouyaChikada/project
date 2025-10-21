//==============================================
//
// BlockManager.h �u���b�N���܂Ƃ߂�
// 
// Author:�ߓc����
//
//==============================================

#ifndef _BLOCKMANAGER_H_
#define _BLOCKMANAGER_H_

#include "main.h"
#include "block.h"
#include <vector>

class CBlockManager
{
public:
	CBlockManager();
	~CBlockManager();
	static CBlockManager* Create(const char* FileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CBlock** GetBlock();

private:
	static std::vector<CBlock*> m_BlockList;	// �x�N�^�[�^���I�z��
	static int m_ModelCount;						//�����Ă��鐔�̃J�E���g�ϐ�
	static CBlock* m_pBlock[MAX_BLOCK];

};

#endif
