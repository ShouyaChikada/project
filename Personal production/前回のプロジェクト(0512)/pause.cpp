//=================================================
//
//	pause.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "pause.h"
#include "texturemanager.h"
#include "manager.h"
#include "pausemanager.h"

// �R���X�g���N�^
CPause::CPause(int nPriolity): CObject2D(nPriolity)
{

}

// �f�X�g���N�^
CPause::~CPause()
{

}

// ����
CPause* CPause::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fX, float fY, const char* aName)
{
	CPause* pPause = nullptr;
	pPause = new CPause;

	if (pPause != nullptr)
	{
		pPause->m_aName = aName;
		pPause->SetCol(col);
		pPause->Init();
		pPause->SetPosition(pos);
		pPause->SetSize(fX, fY);
		pPause->SetType(CObject2D::ANCHORTYPE_CENTER);
		return pPause;

	}
	else
	{
		return nullptr;
	}
}

// ������
HRESULT CPause::Init(void)
{
	CTextureManager* pTex = CManager::GetTexManager();
	m_nIdx = pTex->Register(m_aName);

	CObject::SetType(TYPE_PAUSE);

	CObject2D::Init();

	return S_OK;
}

// �I��
void CPause::Uninit(void)
{
	CObject2D::Uninit();
}

// �X�V����
void CPause::Update(void)
{
	CObject2D::Update();
}

// �`��
void CPause::Draw(void)
{
	if (CPauseManager::GetPause() == true)
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
}