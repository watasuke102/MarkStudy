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
	  help[0] = Help(true, Vec2(450, baseY+ 70), 15, U"��ʂ̃T�C�Y���w�肵�܂��B\n�����ڍׁF�i����,�����j\n��F(1280,960)��");
	  help[1] = Help(true, Vec2(450, baseY+130), 15, U"�w�i�F��ݒ肵�܂��B\n�����ڍׁFHTML�\�L�A�i��,��,�j\n��F�u #ff00ff �v,�u (0.1,0.6,0.3) �v ��");
	  help[2] = Help(true, Vec2(450, baseY+190), 15, U"�����̕\����ύX���܂��B\n�����ڍׁFReadme.txt���Q�Ƃ��Ă��������B\n��F�u yyyy/MM/dd HH:mm:ss �v��");
	  help[3] = Help(true, Vec2(450, baseY+250), 15, U"�ҏW��ʂ̃t�H���g�T�C�Y���w�肵�܂��B\n�����ڍׁF�t�H���g�T�C�Y�i�����j\n��F�u 40 �v��");
	  help[4] = Help(true, Vec2(450, baseY+310), 15, U"�ҏW��ʂ̔w�i�F��ݒ肵�܂��B\n�����ڍׁFHTML�\�L�i��,��,��[,�s�����x]�j\n��F�u #ff00ff �v,�u (0.1,0.6,0.3) �v ��");
	button[0] = Button(U"�ݒ菉����"  , 40, Vec2(200, WINDOW_Y - 360), 300, 60, true, true);
	button[1] = Button(U"�ۑ����ēK�p", 40, Vec2(200, WINDOW_Y - 260), 300, 60, true, true);
	button[2] = Button(U"�ۑ����Ė߂�", 40, Vec2(200, WINDOW_Y -  160), 300, 60, true, true);
	button[3] = Button(U"�ۑ������߂�", 40, Vec2(200, WINDOW_Y -  60), 300, 60, true, true);
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
	//�E�B���h�E�T�C�Y
	SimpleGUI::CheckBox(state_window, U"�E�B���h�E�̃T�C�Y��ύX�\�ɂ���", Vec2(500, baseY));
	font(U"�E�E�B���h�E�̃T�C�Y:").draw(Arg::rightCenter = Vec2(920, baseY+70));
	SimpleGUI::TextBox(state[0], Vec2(930, baseY+70-15), 300, 20);
	//�w�i�F
	font(U"�E�w�i�F:").draw(Arg::rightCenter=Vec2(920, baseY+130));
	SimpleGUI::TextBox(state[1], Vec2(930, baseY+130-15),300,20);
	font(U"�E�����̃t�H�[�}�b�g:").draw(Arg::rightCenter=Vec2(920, baseY+190));
	SimpleGUI::TextBox(state[2], Vec2(930, baseY+190-15),300,20);
	font(U"�E�ҏW��ʂ̃t�H���g�T�C�Y:").draw(Arg::rightCenter=Vec2(920, baseY+250));
	SimpleGUI::TextBox(state[3], Vec2(930, baseY+250-15),300,20);
	font(U"�E�ҏW��ʂ̔w�i�F:").draw(Arg::rightCenter=Vec2(920, baseY+310));
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