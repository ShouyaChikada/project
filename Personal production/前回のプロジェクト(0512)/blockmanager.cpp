//==============================================
//
// BrockManager.cpp �u���b�N���܂Ƃ߂�
// 
// Author:�ߓc����
//
//==============================================
#include "blockmanager.h"
#include  "json.hpp"
#include "scene.h"

// �W�F�C�\��
using json = nlohmann::json;

// �ÓI�����o�ϐ�
//std::vector<CBlock*> CBlockManager::m_BlockList = {};
int CBlockManager::m_ModelCount = NULL;
CBlock* CBlockManager::m_pBlock[MAX_BLOCK] = {};

// �R���X�g���N�^
CBlockManager::CBlockManager()
{
	//// �N���A
	//m_BlockList.clear();
}

// �f�X�g���N�^
CBlockManager::~CBlockManager()
{

}

// �u���b�N�̐���
CBlockManager* CBlockManager::Create(const char* FileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �u���b�N�̃|�C���^
	CBlockManager* pBlockManager = nullptr;

	// �u���b�N�̐���
	// pBlock = CBlock::Create(FileName,pos,rot);

	// �u���b�N�̃|�C���^�ɏ�񂪓����Ă�����
	if (pBlockManager != nullptr)
	{
		//// �ǉ�
		//m_BlockList.push_back(pBlock);

		////���f���J�E���g�̉��Z
		//m_ModelCount++;

		pBlockManager->Init();

		return pBlockManager;
	}
	else
	{
		return nullptr;
	}
}

// ����������
HRESULT CBlockManager::Init(void)
{
	//// �N���A
	//m_BlockList.clear();

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		m_pBlock[nCnt] = nullptr;
	}

	CScene::MODE mode = CScene::GetMode();

	if (mode != CScene::MODE_TUTORIAL)
	{
#if 1
		m_pBlock[0] = CBlock::Create("data\\MODEL\\GRAND\\road.x", D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// �΃����K
		m_pBlock[1] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(775.0f, 310.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[2] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(525.0f, 230.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[3] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(275.0f, 260.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// ��
		m_pBlock[4] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(-25.0f, 360.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[5] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(-275.0f, 310.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[6] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(-525.0f, 260.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// ��
		m_pBlock[7] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(-775.0f, 360.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[8] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(-1025.0f, 230.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[9] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(-1275.0f, 230.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[10] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(-1525.0f, 360.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[11] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(-1775.0f, 260.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// ��
		m_pBlock[12] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(-2025.0f, 230.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[13] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(-2275.0f, 230.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[14] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(1025.0f, 360.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[15] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(1275.0f, 260.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// ��
		m_pBlock[16] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(1525.0f, 360.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[17] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(1775.0f, 230.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[18] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(2025.0f, 230.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[19] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(2275.0f, 360.0f, 2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��

		m_pBlock[20] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(2400.0f, 360.0f, 2150.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[21] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(2400.0f, 230.0f, 1900.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[22] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(2400.0f, 230.0f, 1650.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[23] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(2400.0f, 260.0f, 1400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[24] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(2400.0f, 230.0f, 1150.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[25] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(2400.0f, 230.0f, 900.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[26] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(2400.0f, 360.0f, 650.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[27] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(2400.0f, 230.0f, 400.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[28] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(2400.0f, 260.0f, 150.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[29] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(2400.0f, 230.0f, -150.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[30] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(2400.0f, 230.0f, -400.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[31] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(2400.0f, 230.0f, -650.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[32] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(2400.0f, 360.0f, -900.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[33] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(2400.0f, 260.0f, -1150.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[34] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(2400.0f, 230.0f, -1400.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[35] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(2400.0f, 260.0f, -1650.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[36] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(2400.0f, 230.0f, -1900.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[37] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(2400.0f, 360.0f, -2150.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��

		m_pBlock[38] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(2275.0f, 360.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[39] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(2025.0f, 230.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[40] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(1775.0f, 230.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[41] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(1525.0f, 360.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[42] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(1275.0f, 260.0f, -2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// ��
		m_pBlock[43] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(1025.0f, 360.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[44] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(-2275.0f, 230.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[45] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(-2025.0f, 230.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[46] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(-1775.0f, 260.0f, -2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// ��
		m_pBlock[47] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(-1525.0f, 360.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[48] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(-1275.0f, 230.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[49] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(-1025.0f, 230.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[50] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(-775.0f, 360.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[51] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(-525.0f, 260.0f, -2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// ��
		m_pBlock[52] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(-275.0f, 310.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[53] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(-25.0f, 360.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[54] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(275.0f, 260.0f, -2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// ��
		m_pBlock[56] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(525.0f, 230.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[57] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(775.0f, 310.0f, -2400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��

		m_pBlock[58] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(-2400.0f, 360.0f, -2150.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[59] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(-2400.0f, 230.0f, -1900.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[60] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(-2400.0f, 260.0f, -1650.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[61] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(-2400.0f, 230.0f, -1400.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[62] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(-2400.0f, 260.0f, -1150.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[63] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(-2400.0f, 360.0f, -900.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[64] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(-2400.0f, 230.0f, -650.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[65] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(-2400.0f, 230.0f, -400.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[66] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(-2400.0f, 230.0f, -150.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[67] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(-2400.0f, 260.0f, 150.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[68] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(-2400.0f, 230.0f, 400.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[69] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(-2400.0f, 360.0f, 650.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[70] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(-2400.0f, 230.0f, 900.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[71] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(-2400.0f, 230.0f, 1150.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[72] = CBlock::Create("data\\MODEL\\GRAND\\ie2.x", D3DXVECTOR3(-2400.0f, 260.0f, 1400.0f), D3DXVECTOR3(90, 0.0f, 0.0f));		// ��
		m_pBlock[73] = CBlock::Create("data\\MODEL\\GRAND\\ie.x", D3DXVECTOR3(-2400.0f, 230.0f, 1650.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[74] = CBlock::Create("data\\MODEL\\GRAND\\ie1.x", D3DXVECTOR3(-2400.0f, 230.0f, 1900.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
		m_pBlock[75] = CBlock::Create("data\\MODEL\\GRAND\\ie3.x", D3DXVECTOR3(-2400.0f, 360.0f, 2150.0f), D3DXVECTOR3(0, 0.0f, 0.0f));		// ��
	}

	if (mode == CScene::MODE_TUTORIAL)
	{
		m_pBlock[0] = CBlock::Create("data\\MODEL\\GRAND\\road.x", D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// �΃����K

	}

#endif
	return S_OK;
}

// �I���E�j������
void CBlockManager::Uninit(void)
{
	//// �N���A
	//m_BlockList.clear();
}

//�X�V����
void CBlockManager::Update(void)
{
	// ���̂Ƃ���͂Ȃ�
}

CBlock** CBlockManager::GetBlock()
{
	return &m_pBlock[0];
}