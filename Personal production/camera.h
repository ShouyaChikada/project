//=================================================
//
//	camera.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
//#include "player.h"

class CInputMouse;

class CCamera
{
public:
	CCamera();
	~CCamera();
	//�v���g�^�C�v�錾
	HRESULT  Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	D3DXVECTOR3 GetRotasion(void);
	D3DXVECTOR3 GetPosV(void);
	D3DXVECTOR3 GetPosR(void);
	D3DXVECTOR3 GetVecU(void);
	void SetFollowing(D3DXVECTOR3 pos,D3DXVECTOR3 rotDest);

	void MouseView(CInputMouse * pMouse);

private:
	D3DXVECTOR3 m_posV;			// ���_
	D3DXVECTOR3 m_posR;			// �����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXVECTOR3 m_rot;			// ����
	D3DXVECTOR3 m_rotDest;		// �ړI�̌���
	D3DXVECTOR3 m_posVDest;		// ���_�̖ړI
	D3DXVECTOR3 m_posRDest;		// �����_�̖ړI
	D3DXVECTOR2 m_move;			// �ړ���

	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X

	D3DVIEWPORT9 m_viewport;

	float m_fDistance;			// ���_���璍���_�̋���
	bool m_bFlattery;			// �Ǐ]��ON/OFF
	bool m_bTPS;				

	//static CPlayer* m_pPlayer;
};

#endif
