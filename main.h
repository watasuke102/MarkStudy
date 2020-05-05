#pragma once
#ifdef  GLOBAL_SET
#define GL
#else
#define GL extern
#endif

///インクルードA
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

//ファイルリスト
#define LIST_WIDTH  900
#define LIST_HEIGHT 120

//直前のボタン
#define BUTTON_DEL 1
#define BUTTON_COP 2
#define BUTTON_REN 3

//確認画面
#define CONF_WIDTH 1200
#define CONF_YESNO    0
#define CONF_STRING   1
//戻り値
#define CONF_NOT_ACTIVE 0
#define CONF_NORMAL     1
#define CONF_YES        2
#define CONF_NO         3

///シーン
//シーン管理用
enum class sceneName {
	Title,
	Config,
	Loading,
	FileMenu,
	WriteMain,
	ReadMain
};
//ファイル一覧用
#include "FileList.h"
struct data{
	//編集画面のフォントサイズ、背景色
	int fontSize;
	ColorF backGround;
	//時刻フォーマット
	String timeFormat;
	//0.無効 1.編集 2.閲覧
	int beforeMenu;
	//ファイル情報
	bool isUseFile;//ファイルを開いているか（false:新規作成)
	FileList file;
	//シーンチェンジ用
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

///インクルードB
//GUIボタン
#include "Button.h"
//マークアップ読み込み、レンダリング
#include "MarkUpRender.h"
//名前・削除・複製確認画面の表示
#include "ConfScreen.h"
//マウスを置かれるとヘルプを表示
#include "Help.h"
//シーンのクラス宣言
#include "Scene.h"