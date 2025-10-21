//=================================================
//
//	particle.cpp
// 
// Author:�ߓc ����
//
//=================================================

#include "particle.h"

// �R���X�g���N�^
CParticle::CParticle()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_nCnt = 0;
}

// �f�X�g���N�^
CParticle::~CParticle()
{

}

// ����
CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife)
{
	CParticle* pParticle = nullptr;
	pParticle = new CParticle;

	if (pParticle != nullptr)
	{

		pParticle->m_pos = pos;
		pParticle->m_move = move;
		pParticle->m_col = col;
		pParticle->m_nLife = nLife;
		pParticle->Init();
		return pParticle;
	}
	else
	{
		return nullptr;
	}

}

// ������
HRESULT CParticle::Init(void)
{
	return S_OK;
}

// �I������
void CParticle::Uninit(void)
{
	CObject::Release();
}

// �X�V����
void CParticle::Update(void)
{
	if (m_nCnt == 60)
	{
		int nLife = 0;

		if (m_nLife > 0)
		{
			nLife = rand() % m_nLife + 60;
		}

		//���C�t�̌���
		m_nLife--;

		if (m_nLife <= 0)
		{
			Uninit();
			return;
		}

		CEffect::Create(m_pos, m_col, m_move, nLife);

		m_nCnt = 0;
	}
	else
	{
		m_nCnt++;
	}
}

// �`�揈��
void CParticle::Draw(void)
{

}

void CParticle::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}