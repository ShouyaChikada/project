//=================================================
//
//	fade.h
// 
// Author:�ߓc ����
//
//=================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "object2D.h"
#include "scene.h"

class CFade
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;//���_���W
		float rhw;		//���p�ϊ��p�W��(1.0f�ŌŒ�)
		D3DCOLOR col;	//���_�J���[
		D3DXVECTOR2 tex;//�e�N�X�`�����W

	}VERTEX_2D;

	//�t�F�[�h�̏��
	typedef enum
	{
		FADE_NONE = 0,	//�������Ă��Ȃ����
		FADE_IN,		//�t�F�[�h�C�����
		FADE_OUT,		//�t�F�[�h�A�E�g���
		FADE_MAX
	}FADE;

	CFade();
	~CFade();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetFade(CScene* pScene);
	FADE GetFadeState(void);

	static CFade* Create(void);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@
	FADE m_Fade;						//�t�F�C�h
	D3DXCOLOR m_col;					//�J���[
	CScene* m_pScene;
};

#endif