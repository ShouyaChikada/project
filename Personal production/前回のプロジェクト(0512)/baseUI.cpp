//=================================================
//
//	BaseUI.cpp	UI�̓y��
// 
//	Author:�ߓc����
//
//=================================================
#include "baseUI.h"
#include "manager.h"
#include "texturemanager.h"
#include "gimmickmanager.h"
#include "scene.h"
#include "input.h"

//============================
//�R���X�g���N�^
//============================
CBaseUI::CBaseUI(int nPriolity) : CObject2D(nPriolity)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdx = NULL;
	m_nIndx = NULL;
	m_aName = nullptr;
	m_bUse = false;
	m_bTutorial = false;
}

//============================
//�f�X�g���N�^
//============================
CBaseUI::~CBaseUI()
{

}

//============================
// ����
//============================
CBaseUI* CBaseUI::Create(D3DXVECTOR3 pos, const char* aTxt)
{
	CScene::MODE mode = CScene::GetMode();

	CBaseUI* pBaseUI = nullptr;
	pBaseUI = new CBaseUI;

	if (pBaseUI != nullptr)
	{
		pBaseUI->m_aName = aTxt;
		pBaseUI->m_Name = "data\\TEXTURE\\tutorial.jpg";
		pBaseUI->Init();
		pBaseUI->SetPosition(pos);

		if (mode != CScene::MODE_TUTORIAL)
		{
			pBaseUI->SetSize(345.0f, 30.0f);
		}

		if (mode == CScene::MODE_TUTORIAL)
		{
			pBaseUI->SetSize(250.0f, 150.0f);
		}

		pBaseUI->SetType(CObject2D::ANCHORTYPE_CENTER);
		return pBaseUI;
	}
	else
	{
		return nullptr;
	}
}
//============================
//����������
//============================
HRESULT CBaseUI::Init(void)
{
	CScene::MODE mode = CScene::GetMode();
	CTextureManager* pTex = CManager::GetTexManager();

	if (mode != CScene::MODE_TUTORIAL)
	{
		m_nIdx = pTex->Register(m_aName);
	}

	if (mode == CScene::MODE_TUTORIAL)
	{
		m_nIndx = pTex->Register(m_Name);
	}
	CObject2D::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CBaseUI::Uninit(void)
{
	CObject2D::Uninit();
}

//============================
//�X�V����
//============================
void CBaseUI::Update(void)
{
	CScene::MODE mode = CScene::GetMode();

	// �L�[�{�[�h
	CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();

	CObject2D::Update();

	if (mode == CScene::MODE_TUTORIAL)
	{
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
		{
			Uninit();
		}
	}
}

//============================
//�`�揈��
//============================
void CBaseUI::Draw(void)
{
	CScene::MODE mode = CScene::GetMode();

	bool bUse = CGimmickManager::GetRange();

	// FOG������
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (mode != CScene::MODE_TUTORIAL)
	{
		if (bUse == true)
		{
			CTextureManager* pTex = CManager::GetTexManager();

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, pTex->GetAddress(m_nIdx));

			CObject2D::Draw();

		}
	}

	if (mode == CScene::MODE_TUTORIAL)
	{
		CTextureManager* pTex = CManager::GetTexManager();

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, pTex->GetAddress(m_nIndx));

		CObject2D::Draw();

	}
	
		// FOG�̐ݒ�
	CManager::GetRenderer()->SetupVertexFog(D3DCOLOR_XRGB(255, 255, 255), D3DFOG_LINEAR, TRUE, 0.005f);

}
