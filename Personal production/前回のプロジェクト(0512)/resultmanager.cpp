//=================================================
//
//	resultmanager.cpp
// 
//	Author:�ߓc����
//
//=================================================
#include "resultmanager.h"
#include "manager.h"
#include "texturemanager.h"

// �R���X�g���N�^
CResultManager::CResultManager(int nPriolity) : CObject2D(nPriolity)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nIdx = NULL;
	m_aName = nullptr;
}

// �f�X�g���N�^
CResultManager::~CResultManager()
{

}

// ����
CResultManager* CResultManager::Create(D3DXVECTOR3 pos, const char* aName)
{
	CResultManager* pResultManager = new CResultManager;

	if (pResultManager != nullptr)
	{
		pResultManager->SetPosition(pos);
		pResultManager->SetTxt(aName);
		pResultManager->Init();
		pResultManager->SetSize(640.0f, 360.0f);
		pResultManager->SetType(CObject2D::ANCHORTYPE_CENTER);

		return pResultManager;
	}
	else
	{
		return nullptr;
	}
}

// ������
HRESULT CResultManager::Init(void)
{
	CTextureManager* pTex = CManager::GetTexManager();
	m_nIdx = pTex->Register(m_aName);

	CObject2D::Init();

	return S_OK;
}

// �I��
void CResultManager::Uninit(void)
{
	CObject2D::Uninit();
}

// �X�V
void CResultManager::Update(void)
{
	CObject2D::Update();
}

// �`��
void CResultManager::Draw(void)
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