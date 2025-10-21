//=================================================
//
//	manager.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "fade.h"
#include "debugproc.h"
#include "camera.h"
#include "light.h"
#include "title.h"
#include "texturemanager.h"
#include "motion.h"

class CManager
{
public:
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCamera* GetCamera(void);
	static CLight* GetLight(void);
	static CDebugProc* GetDebugProc(void);
	static CRenderer* GetRenderer(void);
	static CInputKeyboard* GetKeyboard(void);
	static CInputJoypad* GetJoypad(void);
	static CInputMouse* GetMouse(void);
	static void SetMode(CScene* pNewScene);
	static CScene::MODE GetMode(void);
	static CObject* getobject(void);
	static CFade* GetFade(void);
	static CTextureManager* GetTexManager(void);
	static CScene* GetScene(void) { return m_pScene; }
	static CMotion* GetMotion(void);
	static CMotion* GetMotion1(void);
	static CModel** GetModel(void);
	static CModel** GetModel1(void);

private:
	static CRenderer* m_pRenderer;				// �����_���[�ւ̃|�C���^
	static CInputKeyboard* m_pInputKeyboard;	// �L�[�{�[�h�ւ̃|�C���^
	static CInputJoypad* m_pInputJoypad;		// �p�b�h�ւ̃|�C���^
	static CInputMouse* m_pInputMouse;			// �}�E�X�̃|�C���^
	static CObject* m_pObject;					// �I�u�W�F�N�g�̃|�C���^
	static CScene* m_pScene;					// �V�[���ւ̃|�C���^
	static CFade* m_pFade;						// �t�F�[�h�ւ̃|�C���^
	static CDebugProc* m_pDebugProc;			// �f�o�b�O�t�H���g�̃|�C���^
	static CCamera* m_pCamera;					// �J�����̃|�C���^
	static CLight* m_pLight;					// ���C�g�̃|�C���^
	static CTextureManager* m_pTexManager;		// �e�N�X�`���}�l�[�W���̃|�C���^
	static CMotion* m_pMotion;					// ���[�V�����̃|�C���^
	static CMotion* m_pMotion1;					// ���[�V�����̃|�C���^
	static CModel* m_pModel[MAX_PMODEL];					// ���f���̃|�C���^
	static CModel* m_pModel1[MAX_HMODEL];					// ���f���̃|�C���^

};
#endif
