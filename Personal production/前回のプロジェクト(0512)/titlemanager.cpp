//=================================================
//
//	titlemanager.cpp
// 
//	Author:�ߓc����
//
//=================================================
#include "titlemanager.h"
#include "manager.h"
#include "texturemanager.h"

// �R���X�g���N�^
CTitleManager::CTitleManager(int nPriolity) : CObject2D(nPriolity)
{
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_nIdx = NULL;
	m_aName = nullptr;
}

// �f�X�g���N�^
CTitleManager::~CTitleManager()
{

}

// ����
CTitleManager* CTitleManager::Create(D3DXVECTOR3 pos,const char* aName)
{
	CTitleManager* pTitleManager = new CTitleManager;

	if (pTitleManager != nullptr)
	{
		pTitleManager->SetPosition(pos);
		pTitleManager->SetTxt(aName);
		pTitleManager->Init();
		pTitleManager->SetSize(640.0f, 360.0f);
		pTitleManager->SetType(CObject2D::ANCHORTYPE_CENTER);

		return pTitleManager;
	}
	else
	{
		return nullptr;
	}
}

// ������
HRESULT CTitleManager::Init(void)
{
	CTextureManager* pTex = CManager::GetTexManager();
	m_nIdx = pTex->Register(m_aName);

	CObject2D::Init();

	return S_OK;
}

// �I��
void CTitleManager::Uninit(void)
{
	CObject2D::Uninit();
}

// �X�V
void CTitleManager::Update(void)
{
	CObject2D::Update();
}

// �`��
void CTitleManager::Draw(void)
{
	// FOG������

	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CTextureManager* pTex = CManager::GetTexManager();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTex->GetAddress(m_nIdx));

	CObject2D::Draw();

	// FOG�̐ݒ�
	CManager::GetRenderer()->SetupVertexFog(D3DCOLOR_XRGB(255, 255, 255), D3DFOG_LINEAR, TRUE, 0.005f);
}