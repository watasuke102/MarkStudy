#pragma once
#ifdef  GLOBAL_SET
#define GL
#else
#define GL extern
#endif

///�C���N���[�hA
#include <Siv3D.hpp>
#include <HamFramework.hpp>
#include <sstream>

///define,extern
extern  void LoadInitFile();
extern  void MakeDefaultINI();
//1280x960
#define WINDOW_X 1280
#define WINDOW_Y  960
#define W_CENTER WINDOW_X/2
#define WINDOW_TITLE U"MarkStudy v1.00"
#define COPYRIGHT  U"CopyRight(C) 2019 Watasuke, All Right Reserved."

//�t�@�C�����X�g
#define LIST_WIDTH  900
#define LIST_HEIGHT 120

//���O�̃{�^��
#define BUTTON_DEL 1
#define BUTTON_COP 2
#define BUTTON_REN 3

//�m�F���
#define CONF_WIDTH 1200
#define CONF_YESNO    0
#define CONF_STRING   1
//�߂�l
#define CONF_NOT_ACTIVE 0
#define CONF_NORMAL     1
#define CONF_YES        2
#define CONF_NO         3

///�V�[��
//�V�[���Ǘ��p
enum class sceneName {
	Title,
	Config,
	Loading,
	FileMenu,
	WriteMain,
	ReadMain
};
//�t�@�C���ꗗ�p
#include "FileList.h"
struct data{
	//�ҏW��ʂ̃t�H���g�T�C�Y�A�w�i�F
	int fontSize;
	ColorF backGround;
	//�����t�H�[�}�b�g
	String timeFormat;
	//0.���� 1.�ҏW 2.�{��
	int beforeMenu;
	//�t�@�C�����
	bool isUseFile;//�t�@�C�����J���Ă��邩�ifalse:�V�K�쐬)
	FileList file;
	//�V�[���`�F���W�p
	Image data_fadeTex;
	bool changeScene = false;
	sceneName toScene;
	void ChangeStart(sceneName name)
	{
		changeScene = true;
		toScene = name;
		ScreenCapture::RequestCurrentFrame();
	}
};
using App = SceneManager<sceneName, data>;
GL App manager;

///�C���N���[�hB
//GUI�{�^��
#include "Button.h"
//�}�[�N�A�b�v�ǂݍ��݁A�����_�����O
#include "MarkUpRender.h"
//���O�E�폜�E�����m�F��ʂ̕\��
#include "ConfScreen.h"
//�}�E�X��u�����ƃw���v��\��
#include "Help.h"
//�V�[���̃N���X�錾
#include "Scene.h"