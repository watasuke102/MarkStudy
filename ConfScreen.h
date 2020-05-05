#pragma once

class ConfScreen {
private:
	bool f;
	int kind;
	String text;
	String name;//入力された中身（なまえ）
	Button yes, no;
	Font font;
public:
	ConfScreen() {
		font = Font(50);
		Vec2 winCenter = Scene::Center();
		   f = false;
		kind = CONF_YESNO;
		text = U"";
		 yes = Button(U"決定(Ctrl+Enter)", 30, Vec2(winCenter.x - 175, winCenter.y + 200), 300, 50, true, true);
		  no = Button(U"キャンセル(ESC)", 30, Vec2(winCenter.x + 175, winCenter.y + 200), 300, 50, true, true);
	};
	String GetName() { return name; }
	void setActive(int i, String t)
	{
		f = true;
		name = U"";
		text = t;
		kind = i;
	}
	int Update() {
		if (!f) return CONF_NOT_ACTIVE;
		int w = 0;
		for (const auto& text : font(name)) {
			    w += text.xAdvance;
		}
		TextInput::UpdateText(name, TextInputMode::AllowBackSpaceDelete);//入力受付
		if (w > CONF_WIDTH - 70 && name.count() != 0) name.pop_back();
		yes.update();
		 no.update();
		 if (yes.Click() || (KeyControl.pressed() && KeyEnter.pressed())) {
			 f = false;
			return CONF_YES;
		 }
		 if (no.Click() || KeyEscape.down()) {
			 f = false;
			 return CONF_NO;
		 }
		return CONF_NORMAL;
	}
	void draw(FileList file) const {
		if (!f) return;
		Point cent = Scene::Center();
		Scene::Rect().draw(ColorF(0.1,0.8));
		Rect(Arg::center=cent,CONF_WIDTH,500).draw(ColorF(0.3));
		font(text).draw(Arg::topCenter = Point(cent.x,cent.y-250));
		file.SetPos(Vec2(cent.x-LIST_WIDTH/2,cent.y-175));
		file.Draw(false);
		if (kind == CONF_STRING) {
			Rect(Arg::topCenter = cent, CONF_WIDTH-50, 60).draw(ColorF(1));//テキストボックス
			font(name).draw(Arg::topLeft = Vec2(cent.x - (CONF_WIDTH-70)/2,cent.y-10), ColorF(0));
		}
		yes.draw();
		 no.draw();
	}
	void draw() const {
		if (!f) return;
		Point cent = Scene::Center();
		Scene::Rect().draw(ColorF(0.1,0.8));
		Rect(Arg::center=cent,CONF_WIDTH,500).draw(ColorF(0.3));
		font(text).draw(Arg::topCenter = Point(cent.x,cent.y-250));
		if (kind == CONF_STRING) {
			Rect(Arg::topCenter = cent, CONF_WIDTH-50, 60).draw(ColorF(1));//テキストボックス
			font(name).draw(Arg::topLeft = Vec2(cent.x - (CONF_WIDTH-70)/2,cent.y-10), ColorF(0));
		}
		yes.draw();
		 no.draw();
	}
};