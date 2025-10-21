//=================================================
//
//	HumanManager.cpp
// 
//	Author:�ߓc����
//
//=================================================
#include "humanmanager.h"
#include "game.h"
#include "debugproc.h"
#include "input.h"
#include "manager.h"
#include "scene.h"

// �R���X�g���N�^
CHumManager::CHumManager()
{
	for (int nCnt = 0; nCnt < MAX_HUMAN; nCnt++)
	{
		m_pHuman[nCnt] = nullptr;
	}
}

// �f�X�g���N�^
CHumManager::~CHumManager()
{

}

//=========================
//�@����������
//=========================
HRESULT CHumManager::Init(void)
{
	CScene::MODE mode = CScene::GetMode();

	if (mode != CScene::MODE_TUTORIAL)
	{
		for (int nCnt = 0; nCnt < MAX_HUMAN; nCnt++)
		{
			m_pHuman[nCnt] = CHuman::Create(D3DXVECTOR3(0.0f + (25.0f * nCnt), 100.0f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
	}

	if (mode == CScene::MODE_TUTORIAL)
	{
		CHuman::Create(D3DXVECTOR3(0.0f, 100.0f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return S_OK;
}
//=========================
//�@�u���b�N�I������
//=========================
void CHumManager::Uninit(void)
{

}
//=========================
//�@�u���b�N�X�V����
//=========================
void CHumManager::Update(void)
{
	CScene::MODE mode = CScene::GetMode();

	if (mode != CScene::MODE_TUTORIAL)
	{
		for (int nCnt = 0; nCnt < MAX_HUMAN; nCnt++)
		{
			if (m_pHuman[nCnt] != nullptr)
			{
				D3DXVECTOR3 pos = m_pHuman[nCnt]->GetPos();
				m_pHuman[nCnt]->AutoWand(pos);
			}
		}
	}
}