#define GLOBAL_SET
#include "main.h"
struct Click : IEffect {
	Vec2 pos;
	Click(const Vec2& mouse) {
		pos = mouse;
	}
	bool update(double t) override {
		Circle(pos, t * 100).drawFrame(4, AlphaF(1.0 - t * 2));
		return t < 0.5;
	}
};
void MakeDefaultINI() {
	INIData ini;
	ini[U"ScableWindowSize"] = U"false";
	ini[U"WindowSize"] = U"(640, 480)";
	ini[U"BackGround"] = U"(0.1,0.6,0.3)";
	ini[U"TimeFormat"] = U"yyyy/MM/dd HH:mm:ss";
	ini[U"FontSize"]   = U"40";
	ini[U"WriteBackGround"] = U"(0.3,0.4,0.3,0.8)";

	ini.save(U"Config.ini");
}
void LoadInitFile() {
	INIData ini;
	if (!ini.load(U"Config.ini")) {
		MakeDefaultINI();
		ini.load(U"Config.ini");
	}
	if (ini.get<bool>(U"ScableWindowSize"))
		Window::SetStyle(WindowStyle::Sizable);
	else Window::SetStyle(WindowStyle::Fixed);
	Window::Resize(ini.get<Size>(U"WindowSize"), WindowResizeOption::KeepSceneSize);
	Scene::SetBackground(ini.get<ColorF>(U"BackGround"));
	manager.get()->timeFormat = ini.get<String>(U"TimeFormat");
	manager.get()->fontSize   = ini.get<int>   (U"FontSize");
	manager.get()->backGround = ini.get<ColorF>(U"WriteBackGround");
}
/**/
void FirstInit()
{
	//FileMenu用
	FontAsset::Register(U"Font40", 40);
	FontAsset::Register(U"Font20", 20);
	//ウィンドウ
	Scene::Resize(Size (WINDOW_X, WINDOW_Y) );
	Window::SetTitle(WINDOW_TITLE);
	//背景色などiniファイル読み込み初期化
	LoadInitFile();
	//シーン
	Image a(WINDOW_X, WINDOW_Y);
	a.fill(Palette::Black);
	manager.add<Title>(sceneName::Title);
	manager.add<Config>(sceneName::Config);
	manager.add<Loading>(sceneName::Loading);
	manager.add<FileMenu>(sceneName::FileMenu);
	manager.add<WriteMain>(sceneName::WriteMain);
	manager.add<ReadMain> (sceneName::ReadMain);
}
/**
void Main(){
}
/*/
void Main()
{
	Profiler::EnableAssetCreationWarning(false);
	FirstInit();//初期化を行う
	Effect effect;
	while (System::Update())
	{
		ClearPrint();
		if ( !manager.update() ) break;
		//クリックエフェクト
		if (MouseL.down())
			effect.add<Click>(Cursor::Pos());
		effect.update();
	}
}
/**/