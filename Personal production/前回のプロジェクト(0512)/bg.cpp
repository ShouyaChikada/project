//=================================================
//
//	bg.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "bg.h"
#include "manager.h"

//�R���X�g���N�^
CBg::CBg()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//�f�X�g���N�^
CBg::~CBg()
{

}

CBg* CBg::create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBg* pBg = nullptr;
	pBg = new CBg;

	if (pBg != nullptr)
	{
		pBg->Init(pos);
		return pBg;
	}
	else
	{
		return nullptr;
	}
}

HRESULT CBg::Init(D3DXVECTOR3 Pos)
{
	CObject2D::SetSize(1280.0f, 720.0f);
	CObject2D::SetTex(1.0f, 1.0f);
	CObject2D::Init();
	CObject2D::SetPosition(Pos);
	m_pos = Pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//============================
//�I������
//============================
void CBg::Uninit(void)
{
	CObject2D::Uninit();
}

//�v���C���[�̍X�V����
void CBg::Update(void)
{
	CObject2D::Update();
}

//�v���C���[�̕`�揈��
void CBg::Draw(void)
{
	CObject2D::Draw();
}