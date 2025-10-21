//=================================================
//
//	explosion.cpp
// 
// Author:�ߓc����
//
//=================================================
#include "explosion.h"
#include "manager.h"

//============================
// �R���X�g���N�^
//============================
CExplosion::CExplosion()
{
	//�ʒu�̃[���N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}

//============================
// �f�X�g���N�^
//============================
CExplosion::~CExplosion()
{

}

//============================
// ��������
//============================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CExplosion* pExplosion = NULL;
	pExplosion = new CExplosion;

	if (pExplosion != nullptr)
	{
		// ������
		pExplosion->Init(pos);
		return pExplosion;
	}
	else
	{
		return nullptr;
	}
}

//============================
// ����������
//============================
HRESULT CExplosion::Init(D3DXVECTOR3 Pos)
{
	// �����̃T�C�Y
	CObject2D::SetSize(160.0f, 160.0f);

	// �e�N�X�`�����̂̃T�C�Y
	CObject2D::SetTex(0.125f, 1.0f);

	// �ʒu
	CObject2D::SetPosition(Pos);

	// ������
	CObject2D::Init();

	//�ʒu����
	m_pos = Pos;

	return S_OK;
}

//============================
// �I������
//============================
void CExplosion::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//============================
// �X�V����
//============================
void CExplosion::Update(void)
{
	CObject2D::Update();

	m_nCounterAnim++;

	if ((m_nCounterAnim % 4) == 0)
	{
		m_nCounterAnim = 0;

		m_nPatternAnim = (m_nPatternAnim + 1) % 8;

		CObject2D::SetAnim(D3DXVECTOR2((float)m_nPatternAnim, 1.0f), 0.125f, 1.0f);
	}

	if (m_nPatternAnim >= 7)
	{
		CExplosion::Uninit();
	}

}

//============================
// �`�揈��
//============================
void CExplosion::Draw(void)
{
	// �`��
	CObject2D::Draw();
}