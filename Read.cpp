#include "main.h"

///メイン編集画面
void ReadMain::Init() 
{
	isInvisible = false;
	text.clear();
	font = Font(20);
	scroll = 0;
	if (getData().isUseFile) {
		TextReader reader(getData().file.GetPath());
		reader.readAll(text);
	}
	render = MarkUpRender(Vec2(320, 10),getData().beforeMenu);
	//ボタン
	button[0] = Button(U"全て強調表示", 30, Vec2(150, 80), 250, 50, true, true);
	button[1] = Button(U"強調の選択反転", 30, Vec2(150, 180), 250, 50, true, true);
	button[2] = Button(U"戻る", 50, Vec2(150, WINDOW_Y - 60), 150, 70, true, true);
}
void ReadMain::update() 
{
	//シーンチェンジ
	if (getData().changeScene)
	{
		ScreenCapture::GetFrame(getData().data_fadeTex);
		changeScene(getData().toScene, 500, true);
		getData().changeScene = false;
	}
	//ボタン
	for(auto i:step(3))
		button[i].update(); 
	if (button[0].Click())
		for (auto i : step(5))
			checked[i] = true;
	if (button[1].Click())
		for (auto i : step(5))
			checked[i] = !checked[i];
	if (button[2].Click()) getData().ChangeStart(sceneName::Title);
	//スクロール
	scroll += Mouse::Wheel();
	if (scroll < 0) scroll = 0;
	//位置
	const Vec2 base(320, 10);//文字開始位置
	//テキストボックスの表示
	SimpleGUI::CheckBoxAt(isInvisible, U"重要単語を透明にする", Vec2(150, 250));
	SimpleGUI::CheckBoxAt(checked[0], U"重要単語１を強調表示", Vec2(150, 300));
	SimpleGUI::CheckBoxAt(checked[1], U"重要単語２を強調表示", Vec2(150, 350));
	SimpleGUI::CheckBoxAt(checked[2], U"重要単語３を強調表示", Vec2(150, 400));
	SimpleGUI::CheckBoxAt(checked[3], U"重要単語４を強調表示", Vec2(150, 450));
	SimpleGUI::CheckBoxAt(checked[4], U"重要単語５を強調表示", Vec2(150, 500));
	Rect box(base.x - 15, base.y - 15, WINDOW_X - (base.x - 15),
		WINDOW_Y - (base.y - 15));
	box.draw(getData().backGround);
	box.drawFrame(0, 5, ColorF(0.2));
	for (auto i : step(3))
		button[i].draw();
	render.draw(text, 0, scroll,checked, isInvisible);
}