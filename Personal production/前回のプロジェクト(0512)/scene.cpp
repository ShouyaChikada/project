//=================================================
//
//	scene.cpp
// 
// Author:�ߓc ����
//
//=================================================
#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"

CScene::MODE CScene::m_Mode = MODE_NONE;

// �R���X�g���N�^
CScene::CScene(MODE mode)
{
	m_mode = mode;
	m_Mode = mode;
}
// �f�X�g���N�^
CScene::~CScene()
{

}