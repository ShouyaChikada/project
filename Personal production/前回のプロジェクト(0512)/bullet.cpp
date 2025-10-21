//=================================================
//
//	bullet.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "bullet.h"
#include "input.h"
#include "manager.h"
#include "explosion.h"
#include "enemy.h"
#include "object.h"
#include "effect.h"
#include "score.h"

//�R���X�g���N�^
CBullet::CBullet()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_lifetime = 0;
}

///�f�X�g���N�^
CBullet::~CBullet() 
{

}

//�e�̐���
CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBullet* pBullet = nullptr;
	pBullet = new CBullet;

	if (pBullet != nullptr)
	{
		pBullet->Init(pos);
		//�e�N�X�`����ݒ�
		pBullet->SetType(TYPE_BULLET);
		return pBullet;
	}
	else
	{
		return nullptr;
	}
}
HRESULT CBullet::Init(D3DXVECTOR3 Pos)
{
	// �e�̏c���̃T�C�Y�w��
	CObject2D::SetSize(60.0f, 60.0f);

	// �e�̃e�N�X�`���̕\��(��,�c)
	CObject2D::SetTex(1.0f, 1.0f);

	// �ʒu��ݒ�
	CObject2D::SetPosition(Pos);

	// �I�u�W�F�N�g2D�̏�����
	CObject2D::Init();

	// �ʒu����
	m_pos = Pos;

	// ������������
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �ړ��n��������
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �e�̎�����ݒ�
	m_lifetime = 60;

	return S_OK;
}

//============================
//�I������
//============================
void CBullet::Uninit(void)
{
	//�I��
	CObject2D::Uninit();
}

//�X�V����
void CBullet::Update(void)
{
	//�X�V
	CObject2D::Update();

	//�G�t�F�N�g
	//CEffect::Create(m_pos,D3DXCOLOR(1.0f,0.5f,0.0f,1.0f),40,15);

	//���C�t���f�N�������g
	m_lifetime--;

	//���C�t��0�ȉ��ɂȂ�����
	if (m_lifetime <= 0 || (m_pos.x > SCREEN_WIDTH || m_pos.x < 0.0f || m_pos.y > SCREEN_HEIGHT || m_pos.y < 0.0f))
	{
		//�����𐶐�
  		CExplosion::Create(m_pos, m_rot);

		//�e��j�� 
		CBullet::Uninit();

		//�G�t�F�N�g��j��
		CEffect* pEffect = NULL;
		if (pEffect != NULL)
		{
			pEffect->Uninit();
		}
	}

	////�L�[�{�[�h
	//CInputKeyboard* pInputKeyboard = CManager::GetKeyboard();
	//pInputKeyboard = CManager::GetKeyboard();

	//�e�̈ړ���
	m_move.x = -10.0f;

	//�ʒu���X�V
	m_pos += m_move;

	//�G�ƒe�̓����蔻��
	//CollisionPlayer(m_pos);

	//�v���C���[�ƒe�̓����蔻��
	CollisionEnemy(m_pos);

	//�ʒu����
	CObject2D::SetPosition(m_pos);
}

//�v���C���[�̕`�揈��
void CBullet::Draw(void)
{

	//�`��
	CObject2D::Draw();
}

//�����蔻��(�G)
bool CBullet::CollisionEnemy(D3DXVECTOR3 pos)
{
	//for (int nCntObj = 0; nCntObj < MAX_OBJECT;nCntObj++)
	//{
	//	CObject* pObj = NULL;

	//	//�I�u�W�F�N�g�̎擾
	//	pObj = Getobject(nCntObj);
	//	
	//	//pObj��NULL����Ȃ�������
	//	if (pObj != NULL)
	//	{
	//		// �G�̈ʒu
	//		D3DXVECTOR3 EnemyPos = pObj->GetPosition();
	//
	//		// �^�C�v���擾
	//		TYPE type = TYPE_NONE;

	//		// ��Ԃ��擾
	//		STATE state = STATE_NONE;

	//		//��ނ̎擾
	//		type = pObj->GetType();

	//		//��ނ��G��������
	//		if (type == TYPE_ENEMY)
	//		{
	//			//�G�Əd�Ȃ����Ƃ�
	//			if (m_pos.x >= EnemyPos.x - 50.0f && m_pos.x <= EnemyPos.x + 50.0f
	//				&& m_pos.y >= EnemyPos.y - 50.0f && m_pos.y <= EnemyPos.y + 50.0f)
	//			{	
	//				//�����𐶐�
	//				CExplosion::Create(m_pos, m_rot);

	//				//�G�̏I��
	//				pObj->Uninit();

	//				//�e��j��
	//				CBullet::Uninit();

	//				CScore::Add(100);

	//				CEffect* pEffect = NULL;

	//				// NULL����Ȃ�������
	//				if (pEffect != NULL)
	//				{
	//					// �G�t�F�N�g�̏I��
	//					pEffect->Uninit();
	//				}
	//				
	//				return true;
	//			}
	//		}
	//	}
	//}
	return false;
}