//=================================================
//
//	gauge.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "gauge.h"
#include "manager.h"
#include "texturemanager.h"
#include "gimmickmanager.h"

//�R���X�g���N�^
CGauge::CGauge(int nPriolity) : CObject2D(nPriolity)
{
	m_nIdx = 0;
	m_pBaseUI = nullptr;
	m_fCnt = 0.0f;
	m_fCnt1 = 0.0f;
	m_aName = nullptr;
}
//�f�X�g���N�^
CGauge::~CGauge()
{

}

// ����
CGauge* CGauge::Create(D3DXVECTOR3 pos, const char* aTxt,D3DXCOLOR col)
{
	CGauge* pGauge = nullptr;
	pGauge = new CGauge;

	if (pGauge != nullptr)
	{
		pGauge->SetCol(col);
		pGauge->SetPosition(pos);
		pGauge->Init();
		pGauge->SetSize(0.0f, 55.0f);
		pGauge->SetType(CObject2D::ANCHORTYPE_LEFT);
		return pGauge;
	}
	else
	{
		return nullptr;
	}
}

// ������
HRESULT CGauge::Init(void)
{
	CObject2D::Init();

	return S_OK;
}

//	�I��
void CGauge::Uninit(void)
{
	//�������g�̔j��
	CObject2D::Uninit();
}

//===================
//	�X�V����
//===================
void CGauge::Update(void)
{
	// m_pBaseUI->Update();
	CObject2D::Update();
}

//===================
//	�`�揈��
//===================
void CGauge::Draw(void)
{

	bool bUse = CGimmickManager::GetRange();
	bool bPush = CGimmickManager::GetPush();

	// FOG�̐ݒ�
	CManager::GetRenderer()->SetupVertexFog(D3DCOLOR_XRGB(255, 255, 255), D3DFOG_LINEAR, TRUE, 0.005f);

	// �f�o�C�X�ւ̃|�C���^
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (bUse == true)
	{
		CObject2D::Draw();
	}

	// FOG������
	CManager::GetRenderer()->GetDevice()->SetRenderState(D3DRS_FOGENABLE, FALSE);

}

//===============================
// �Q�[�W�̒����ݒ菈��
//===============================
void CGauge::SetGageLength(const int nMaxLife, const int nCurrentLife, float fValue, float Height)
{
	// �ő�䗦���o��
	float fRatio = 1.0f;

	// 0�ȏ�Ȃ�
	if (nMaxLife > NULL)
	{
		// �������v�Z����
		fRatio = static_cast<float>(nCurrentLife) / static_cast<float>(nMaxLife);
	}

	// �\������̗̓o�[�̍ő啝
	const float fMaxWidth = SCREEN_WIDTH * fValue;

	// �T�C�Y��䗦�Ŕ��f
	CObject2D::SetSize(fMaxWidth * fRatio, Height);
}
//===============================
// �Q�[�W�̒����ݒ菈�� ( float )
//===============================
void CGauge::FSetGageLength(float fMax, float fCurrent, float fMaxWidth, float fHeight)
{
	// �����l
	float fRatio = 1.0f;

	// 0�ȏ�
	if (fMax > 0.0f)
	{
		// �����v�Z
		fRatio = fCurrent / fMax;
	}

	// �ő啝 �~ ����
	CObject2D::SetSize(fMaxWidth * fRatio, fHeight);
}
