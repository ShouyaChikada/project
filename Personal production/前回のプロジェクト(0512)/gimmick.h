//=================================================
//
//	gimmick.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef GIMMICK_H_
#define GIMMICK_H_

#include "main.h"
#include "objectx.h"
#include "meshcylinder.h"
#include "gauge.h"
#include "baseUI.h"

class CGimmick :public CObjectX
{
public:

	//�M�~�b�N�̎��
	typedef enum
	{
		TYPE_METEORITE,	// 覐�
		TYPE_THUNDER,	// ��
		TYPE_TREE,		// ��
		TYPE_MAX,
	}TYPE;


	CGimmick(int nPriority = 6);
	~CGimmick();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CGimmick* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPE type);
	bool Collision(D3DXVECTOR3* pos, D3DXVECTOR3* posOld, D3DXVECTOR3* move, D3DXVECTOR3* size);
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	static bool GetUse(void) { return m_bUse; }
	TYPE GetType(void) { return m_type; }
	static CMeshCylinder* GetMeshCylinder(void) { return m_pMeshCylinder; }
	static CGauge* GetGauge(void) { return m_pGauge; }
	static CBaseUI* GetBaseUI(void) { return m_pBaseUI; }
private:

	const char* GIMMICK_FILE[TYPE_MAX] =
	{
		"data\\MODEL\\GIMMICK\\inseki.x",		//�ʏ�
		"data\\MODEL\\GIMMICK\\kaminari.x",		//�S�[��
		"data\\MODEL\\GIMMICK\\tutorial.x",		//�`���[�g���A��
	};

	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	D3DXVECTOR3 m_move;
	TYPE m_type;			// �^�C�v
	D3DXVECTOR3 m_Vtxmax;	// �Œ��_
	D3DXVECTOR3 m_Vtxmin;	// ��ԏ��������_
	D3DXVECTOR3 m_size;		// �T�C�Y
	bool m_bLanding;		// ����Ă��邩�ǂ���
	static bool m_bUse;			// �g���Ă��邩�ǂ���

	static CMeshCylinder* m_pMeshCylinder;	// �V�����_�[�̃|�C���^
	static CGauge* m_pGauge;	//�Q�[�W�ւ̃|�C���^
	static CBaseUI* m_pBaseUI;
	float m_fAddCharge;			// �Q�[�W�̉��Z��

};

#endif