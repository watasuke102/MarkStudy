#include "main.h"

///タイトルシーン
void Title::Init()
{
	titleFont = Font(128);
	copyright = Font(30);
	getData().beforeMenu = 0;
	//ボタン大きさの初期化
	button[0] = Button(U"ノートの編集", 60, Vec2(WINDOW_X - W_CENTER, 330), WINDOW_X, 100, false,true);
	button[1] = Button(U"ノートの確認", 60, Vec2(WINDOW_X - W_CENTER, 480), WINDOW_X, 100, false,true);
	button[2] = Button(U"各設定"     , 60, Vec2(WINDOW_X - W_CENTER, 630), WINDOW_X, 100, false,true);
	button[3] = Button(U"終了"       , 60, Vec2(WINDOW_X - W_CENTER, WINDOW_Y-140), WINDOW_X, 100, false,true);
}
void Title::update()
{
	if (getData().changeScene)
	{
		ScreenCapture::GetFrame(getData().data_fadeTex);
		changeScene(getData().toScene, (getData().beforeMenu!=0)?0:500, true);
		getData().changeScene = false;
	}
	//ボタン
	for (auto i : step(4))
		button[i].update();
	//ボタンクリックでシーンチェンジ
	if (button[0].Click()) {
		getData().beforeMenu = 1;
		getData().ChangeStart(sceneName::Loading);
	}
	if (button[1].Click()){
		getData().beforeMenu = 2;
		getData().ChangeStart(sceneName::Loading);
	}
	if (button[2].Click())
		getData().ChangeStart(sceneName::Config);
	if (button[3].Click())
		System::Exit();
	if (MouseR.down()) {
		getData().beforeMenu = 1;
		getData().ChangeStart(sceneName::WriteMain);
	}
}
void Title::draw() const 
{
	//タイトル
	titleFont(U"MarkStudy").draw(Arg::topCenter = Vec2(W_CENTER, 50));
	copyright(COPYRIGHT).draw(Arg::bottomCenter = Vec2(W_CENTER, WINDOW_Y));
	//ボタン
	for (auto i : step(4))
		button[i].draw();
}