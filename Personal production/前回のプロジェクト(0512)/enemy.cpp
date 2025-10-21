//=================================================
//
//	enemy.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "enemy.h"
#include "manager.h"

// �ÓI�����o�ϐ�
float CEnemy::m_SizeX = 0.0f;
float CEnemy::m_SizeY = 0.0f;

// �R���X�g���N�^
CEnemy::CEnemy()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCnt = 0;
}

// �f�X�g���N�^
CEnemy::~CEnemy()
{

}

// �G����
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float SizeX,float SizeY,TYPE type)
{
	CEnemy* pEnemy = NULL;
	pEnemy = new CEnemy;

	if (pEnemy != nullptr)
	{
		m_SizeX = SizeX;
		m_SizeY = SizeY;
		pEnemy->Init(pos);
		//�e�N�X�`����ݒ�
		pEnemy->SetType(TYPE_ENEMY);
		return pEnemy;
	}
	else
	{
		return nullptr;
	}
}

// ����������
HRESULT CEnemy::Init(D3DXVECTOR3 Pos)
{
	//�e�̏c���̃T�C�Y�w��
	CObject2D::SetSize(m_SizeX, m_SizeY);

	//�e�̃e�N�X�`���̕\��(��,�c)
	CObject2D::SetTex(1.0f, 1.0f);

	//�ʒu��ݒ�
	CObject2D::SetPosition(Pos);

	//�I�u�W�F�N�g2D�̏�����
	CObject2D::Init();

	//�ʒu����
	m_pos = Pos;

	//������������
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�ړ��n��������
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nCnt = 0;

	return S_OK;
}

//============================
//�I������
//============================
void CEnemy::Uninit(void)
{
	CObject2D::Uninit();
}

// �X�V����
void CEnemy::Update(void)
{
	m_nCnt++;

	CObject2D::Update();

	/*if (m_nCnt >= 120)
	{
		CBullet::Create(m_pos, m_rot);
		m_nCnt = 0;
	}*/
	
	m_pos += m_move;

	CObject2D::SetPosition(m_pos);
}

// �G�̕`�揈��
void CEnemy::Draw(void)
{
	CObject2D::Draw();
}
