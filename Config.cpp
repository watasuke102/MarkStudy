#include"main.h"

void Config::LoadINI() {
	INIData ini;
	if (!ini.load(U"Config.ini")) {
		MakeDefaultINI();
		ini.load(U"Config.ini");
	}
	state_window  = ini.get<bool>(U"ScableWindowSize");
	state[0].text = ini.get<String>(U"WindowSize");
	state[1].text = ini.get<String>(U"BackGround");
	state[2].text = ini.get<String>(U"TimeFormat");
	state[3].text = ini.get<String>(U"FontSize");
	state[4].text = ini.get<String>(U"WriteBackGround");
}
void Config::Init() {
	LoadINI();
	font = Font(40);
	  help[0] = Help(true, Vec2(450, baseY+ 70), 15, U"画面のサイズを指定します。\n書式詳細：（横幅,高さ）\n例：(1280,960)等");
	  help[1] = Help(true, Vec2(450, baseY+130), 15, U"背景色を設定します。\n書式詳細：HTML表記、（赤,緑,青）\n例：「 #ff00ff 」,「 (0.1,0.6,0.3) 」 等");
	  help[2] = Help(true, Vec2(450, baseY+190), 15, U"時刻の表示を変更します。\n書式詳細：Readme.txtを参照してください。\n例：「 yyyy/MM/dd HH:mm:ss 」等");
	  help[3] = Help(true, Vec2(450, baseY+250), 15, U"編集画面のフォントサイズを指定します。\n書式詳細：フォントサイズ（整数）\n例：「 40 」等");
	  help[4] = Help(true, Vec2(450, baseY+310), 15, U"編集画面の背景色を設定します。\n書式詳細：HTML表記（赤,緑,青[,不透明度]）\n例：「 #ff00ff 」,「 (0.1,0.6,0.3) 」 等");
	button[0] = Button(U"設定初期化"  , 40, Vec2(200, WINDOW_Y - 360), 300, 60, true, true);
	button[1] = Button(U"保存して適用", 40, Vec2(200, WINDOW_Y - 260), 300, 60, true, true);
	button[2] = Button(U"保存して戻る", 40, Vec2(200, WINDOW_Y -  160), 300, 60, true, true);
	button[3] = Button(U"保存せず戻る", 40, Vec2(200, WINDOW_Y -  60), 300, 60, true, true);
}
void Config::update() {
	if (getData().changeScene)
	{
		ScreenCapture::GetFrame(getData().data_fadeTex);
		changeScene(getData().toScene, 500, true);
		getData().changeScene = false;
	}
	for(auto i:step(4))
		button[i].update();
	if (button[0].Click()) {
		MakeDefaultINI();
		LoadInitFile();
		LoadINI();
	}
	if (button[1].Click()) SaveINI();
	if (button[2].Click()) {
		SaveINI();
		getData().ChangeStart(sceneName::Title);
	}
	if (button[3].Click()) {
		LoadInitFile();
		getData().ChangeStart(sceneName::Title);
	}
	///draw
	//ウィンドウサイズ
	SimpleGUI::CheckBox(state_window, U"ウィンドウのサイズを変更可能にする", Vec2(500, baseY));
	font(U"・ウィンドウのサイズ:").draw(Arg::rightCenter = Vec2(920, baseY+70));
	SimpleGUI::TextBox(state[0], Vec2(930, baseY+70-15), 300, 20);
	//背景色
	font(U"・背景色:").draw(Arg::rightCenter=Vec2(920, baseY+130));
	SimpleGUI::TextBox(state[1], Vec2(930, baseY+130-15),300,20);
	font(U"・時刻のフォーマット:").draw(Arg::rightCenter=Vec2(920, baseY+190));
	SimpleGUI::TextBox(state[2], Vec2(930, baseY+190-15),300,20);
	font(U"・編集画面のフォントサイズ:").draw(Arg::rightCenter=Vec2(920, baseY+250));
	SimpleGUI::TextBox(state[3], Vec2(930, baseY+250-15),300,20);
	font(U"・編集画面の背景色:").draw(Arg::rightCenter=Vec2(920, baseY+310));
	SimpleGUI::TextBox(state[4], Vec2(930, baseY+310-15),300,20);
	//
	for (auto i : step(4))
		button[i].draw();
	for(int i=4;i>=0;i--)
		help[i].draw();
}
void Config::SaveINI() {
	INIData ini;
	ini[U"ScableWindowSize"] = Format(state_window);
	ini[U"WindowSize"]       = state[0].text;
	ini[U"BackGround"]       = state[1].text;
	ini[U"TimeFormat"]       = state[2].text;
	ini[U"FontSize"]         = state[3].text;
	ini[U"WriteBackGround"]  = state[4].text;
	ini.save(U"Config.ini");
	LoadInitFile();
}