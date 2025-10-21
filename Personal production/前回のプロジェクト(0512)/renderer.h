//=================================================
//
//	renderer.h
// 
//	Author:�ߓc����
//
//=================================================

#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//�}�N��
#define NUM_TEXTURE (2)

class CRenderer
{
public:

	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetupVertexFog(DWORD Color, DWORD Mode, BOOL UseRange, FLOAT Density);
	LPDIRECT3DDEVICE9 GetDevice(void);
	void onWireFrame(void);
	void offWireFrame(void);
	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU);
	LPDIRECT3DTEXTURE9 GetTextureMT(void);

private:
	LPDIRECT3D9 m_pD3D;								//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;					//Direct3D�f�o�C�X�ւ̃|�C���^
	static int m_nCountFPS;							//FPS�̕`��p�ϐ�
	LPDIRECT3DTEXTURE9 m_apTextureMT[NUM_TEXTURE];	//�����_�����O�p�e�N�X�`��
	LPDIRECT3DSURFACE9 m_apRenderMT[NUM_TEXTURE];	//�e�N�X�`�������_�����O�p�C���^�[�t�F�[�X
	LPDIRECT3DSURFACE9 m_pZBuffMT;					//�e�N�X�`�������_�����O�pZ�o�b�t�@
	D3DVIEWPORT9 m_pViewportMT;						//�e�N�X�`�������_�����O�p�r���[�|�[�g
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMT;			//�t�B�[�h�o�b�N�p�|���S���̒��_�o�b�t�@
};
#endif
