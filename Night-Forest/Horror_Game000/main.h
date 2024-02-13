//<=============================================================================
//���C������(main.h)
//
//Author:kazuki watanabe
//<=============================================================================
#ifndef _MAIN_H_	//���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_	//��d�C���N���[�h�h�~�̃}�N�����`����

//<***********************************************************
//�w�b�_�[�t�@�C���̃C���N���[�h
//<***********************************************************

#include <Windows.h>
#include <stdio.h>
#include <assert.h>
#include "time.h"
#include "d3dx9.h"						//�`�揈���ɕK�v 
#define DIRECTINPUT_VERSION	(0x0800)	//build���̌x���p�}�N��
#include "dinput.h"						//���͏����ɕK�v
#include "Xinput.h"						//Xinput�֘A�̃w�b�_�[
#include "xaudio2.h"					//�T�E���h�����ɕK�v
#include <dsound.h>
#include <cstdlib>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new(s)          _new_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)

#include <stdlib.h>
#include "Renderer.h"
#include "Object.h"
#include <string>   

//<***********************************************************
//���C�u�����̃����N
//<***********************************************************
#pragma comment(lib, "d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")		//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib, "dxguid.lib")		//DirectX�R���|�l�[�g(���i)�g�p�ɕK�v
#pragma comment(lib, "winmm.lib")		//�V�X�e�������擾�ɕK�v
#pragma comment(lib, "dinput8.lib")		//���͏����ɕK�v
#pragma comment(lib, "dsound.lib")		//�T�E���h�ɕK�v
#pragma comment(lib, "xinput.lib")		//�R���g���[���[�ɕK�v

//<***********************************************************
//�}�N����`�W
//<***********************************************************
#define SCREEN_WIDTH		(1280)		//�E�C���h�E�̕�
#define SCREEN_HEIGHT		(720)		//�E�C���h�E�̍���
#define MAX_COMMENT			(256)		//�R�����g�̍ő吔

//<***********************************************************
//�O���[�o���֐�
//<***********************************************************
int GetFPS(void);
void SetD_SPEED(void);
void SetS_SPEED(void);

#endif
