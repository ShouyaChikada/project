//=================================================
//
//	main.h
// 
//	Author:�ߓc����
//
//=================================================
#ifndef _PCH_H_
#define _PCH_H_

// �r���h���̌x���p�}�N��
#define DIRECTINPUT_VERSION (0x0800)

//========================================
//�C���N���[�h
//========================================
#include <stdio.h>
#include<windows.h>
#include"d3dx9.h"
#include "dinput.h"		//�L�[�{�[�h���͏����ɕK�v
#include "Xinput.h"		//�W���C�p�b�h���͏����ɕK�v
#include "xaudio2.h"	//�T�E���h�����ɕK�v
#include <iostream>
#include <vector>

//========================================
//���C�u�����̃����N
//========================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")	//�L�[�{�[�h���͏����ɕK�v
#pragma comment(lib,"xinput.lib")	//�W���C�p�b�h���͏����ɕK�v

//========================================
//�}�N����`
//========================================
#define CLASS_NAME "WindowsClass"													//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "DirectX�̊�{����"												//�E�B���h�E�̖��O(�L���v�V�����ɕ\��)
#define SCREEN_WIDTH (1280)															//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)															//�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				//���_�t�H�[�}�b�g[2D]
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//���W�E�@���E�J���[�E�e�N�X�`��
#define D3DFVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)										
#define MAX_TEXTURE (128)															//�e�N�X�`���̍ő吔
#define MAX_BLOCK (128)																//�u���b�N�̍ő吔
#define MAX_MODEL (32)																// �ő僂�f����
#define MAX_PMODEL (16)																//�v���C���[�̍ő僂�f����
#define MAX_HMODEL (15)																//�l�̍ő僂�f����

typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//���p�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W

}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	D3DXVECTOR3 nor;	//�@���x�N�g��
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_3D;

#endif