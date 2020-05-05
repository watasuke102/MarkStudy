#include "main.h"

///���C���ҏW���
void WriteMain::Init() 
{
	text.clear();
	isPasted = false;
	scroll = 0;
	if (getData().isUseFile) {
		TextReader reader(getData().file.GetPath());
		reader.readAll(text);
	}
	render = MarkUpRender(Vec2(320, 250), getData().beforeMenu);
	font = Font(30);
	palette = ColorF(1.0);
	//�{�^��
	tags[0] = Button(U"B", 60, Vec2(330, 200), 70, 80, true, true);
	tags[1] = Button(U"#", 60, Vec2(400, 200), 70, 80, true, true);
	tags[2] = Button(U"H", 60, Vec2(470, 200), 70, 80, true, true);
	tags[3] = Button(U"S", 60, Vec2(540, 200), 70, 80, true, true);
	tags[4] = Button(U"U", 60, Vec2(610, 200), 70, 80, true, true);
	tags[5] = Button(U"I", 60, Vec2(680, 200), 70, 80, true, true);
	help[0] = Help(false, Vec2(330, 235), 45, U"[B text]        (Alt+B)\ntext �𑾎��ɂ��܂��B");
	help[1] = Help(false, Vec2(400, 235), 45, U"[#(color) text] (Alt+3)\ntext �ɐF��t���܂��B");
	help[2] = Help(false, Vec2(470, 235), 45, U"[H(color) text] (Alt+H)\ntext �̔w�i��ύX���܂��B");
	help[3] = Help(false, Vec2(540, 235), 45, U"[S(color) text] (Alt+S)\ntext �ɑł������������܂��B");
	help[4] = Help(false, Vec2(610, 235), 45, U"[U(color) text] (Alt+U)\ntext �ɉ��������܂��B");
	help[5] = Help(false, Vec2(680, 235), 45, U"[I(�d�v�x) text] (Alt+I)\ntext ���d�v�P��Ƃ��ă}�[�N���܂��B");
	button[0]  = Button(U"�F��}��(Ctrl+C)", 20, Vec2(930, 225), 170, 35, true, true);
	button[1]  = Button(U"���O��t���ĕۑ�", 30, Vec2(150,60), 250, 50, true, true);
	button[2]  = Button(U"�㏑���ۑ�", 30, Vec2(150,160), 250, 50, true, true);
	button[3]  = Button(U"�߂�", 30, Vec2(150, WINDOW_Y - 460), 250, 50, true, true);
	rightKey.restart();
	leftKey.restart();
}
void WriteMain::update()
{
	//�V�[���`�F���W
	if (getData().changeScene)
	{
		ScreenCapture::GetFrame(getData().data_fadeTex);
		changeScene(getData().toScene, 500, true);
		getData().changeScene = false;
	}

	int state = confScr.Update();
	if (state == CONF_NORMAL || state == CONF_NO) {
		confScr.draw();
		return;
	}
	else if(state == CONF_YES && doSave == 1) {
		doSave = 2;
		newName = confScr.GetName();
		if (newName.size() == 0) newName = U"�V�K�t�@�C��";
	}
	else if (CONF_NO && doSave == 1)
		doSave = 0;

	//�{�^��
	for (auto i : step(4))
		button[i].update();
	for (auto i : step(6))
		tags[i].update();

	bool isSave = (KeyControl.pressed() && KeyS.pressed());
	//���O��t����
	if (button[1].Click() || (isSave && KeyShift.pressed()))
		doSave = 1;
	//�㏑���ۑ�
	if (button[2].Click() || isSave)
		if (getData().isUseFile)
			 doSave = 3;
		else doSave = 1;

	//�ۑ�����
	if (doSave == 1)//���O�m�F�J�n
		confScr.setActive(CONF_STRING, U"�ۑ�����t�@�C���̖��O����͂��Ă��������B");
	if (doSave == 2) {
		String path = U"Note/" + newName + U".txt";
		TextWriter a(path);
		a.write();
		a.close();
		if (!file.open(path)) {
			doSave = 0;
			save.easing = EasingController<int>(EaseOutQuint, 0, 0, 0.5s);
			save.SetActive(U"�t�@�C���̍쐬�E�ۑ��Ɏ��s���܂����B");
		}else {
			getData().isUseFile = true;
			getData().file = FileList(FileData(path), getData().timeFormat);
			doSave = 3;
		}
	}
	if (doSave == 3) {//�㏑���ۑ����s
		doSave = 0;
		file.open(getData().file.GetPath());
		file.write(text);
		file.close();
		save.easing = EasingController<int>(EaseOutQuint, 0, 0, 0.5s);
		save.SetActive(U"�ۑ����܂����F\n"+ getData().file.GetName()+U".txt");
	}
	if (button[3].Click()) getData().ChangeStart(sceneName::Title);

	const Vec2 base(320, 270);//�����J�n�ʒu
	//���͎�t
	cursor = TextInput::UpdateText(text, cursor, TextInputMode::AllowEnterBackSpaceDelete);
	//�^�O����
	if (tags[0].Click() || (KeyAlt.pressed() && KeyB.down())) {
		text.insert(cursor, U"[B ]");
		cursor += 3;
	}
	if (tags[1].Click() || (KeyAlt.pressed() && Key3.down())) {
		text.insert(cursor, U"[#]");
		cursor += 2;
	}
	if (tags[2].Click() || (KeyAlt.pressed() && KeyH.down())) {
		text.insert(cursor, U"[H ]");
		cursor += 3;
	}
	if (tags[3].Click() || (KeyAlt.pressed() && KeyS.down())) {
		text.insert(cursor, U"[S ]");
		cursor += 3;
	}
	if (tags[4].Click() || (KeyAlt.pressed() && KeyU.down())) {
		text.insert(cursor, U"[U ]");
		cursor += 3;
	}
	if (tags[5].Click() || (KeyAlt.pressed() && KeyI.down())) {
		text.insert(cursor, U"[I]");
		cursor += 3;
	}
	//�J���[�p���b�g
	SimpleGUI::Slider(palette.r, Vec2(1070, 120), 200);
	font(U"��").draw(Vec2(1030, 115), Palette::Red);
	SimpleGUI::Slider(palette.g, Vec2(1070, 160), 200);
	font(U"��").draw(Vec2(1030, 155), Palette::Green);
	SimpleGUI::Slider(palette.b, Vec2(1070, 200), 200);
	font(U"��").draw(Vec2(1030, 195), Palette::Blue);
	Rect(850, 120, Size(160, 80)).draw(palette);
	if (button[0].Click() || (KeyAlt.pressed() && KeyC.down())) {
		Color c(palette);
		int a[3]{
			c.r,c.g,c.b
		};
		text.insert(cursor, U"{:02X}{:02X}{:02X}"_fmt(a[0], a[1], a[2]));
		cursor += 6;
	}
	//�J�[�\��
	//�O��W�����v
	if (KeyHome.down()) {

		do {
			if (cursor == 0) break;
			cursor--;
		} while (text[cursor] != '\n');
		if (cursor != 0)//�ړ��ł��Ă���Ȃ�
			cursor++;
	}
	if (KeyEnd.down())
		while (text[cursor] != '\n' && text[cursor] != '\0') cursor++;
	//���E
	if (cursor > 0)
	if (KeyLeft.down() || (KeyLeft.pressedDuration() > 0.4s && leftKey > 0.05s))
	{
		cursor--;
		leftKey.restart();
		render.CursorRestart();
	}
	if (KeyRight.down() || (KeyRight.pressedDuration() > 0.4s && rightKey > 0.05s))
	{
		cursor++;
		rightKey.restart();
		render.CursorRestart();
	}
	if (cursor > text.size()) cursor = text.size();
	//�\��t��
	if (KeyControl.pressed() && KeyV.pressed()) {
		if (!isPasted) {
			isPasted = true;
			String t;
			Clipboard::GetText(t);
			text.insert(cursor, t);
			cursor += t.size();
			render.CursorRestart();
		}
	}else isPasted = false;


	//�X�N���[��
	scroll += Mouse::Wheel();
	if (scroll < 0) scroll = 0;

	String fileInfo;
	if (getData().isUseFile)
		fileInfo = getData().file.GetName();
	else fileInfo = U"����";
	fileInfo += U"�F" + Format(text.size()) + U"����";
	font(fileInfo).draw(Vec2(300, 60));
	//�ۑ�������\��
	if (save.saved != 0) {
		Vec2 pos = Vec2(WINDOW_X+5-save.easing.easeOut(), 30);
		save.font(save.text).region(pos).drawFrame(10, ColorF(0.2)).draw(ColorF(0.2));
		save.font(save.text).draw(pos);
		if (save.time > 3s && save.saved == 1)
			save.ReActive();
		else if (save.time > 0.5s && save.saved == 2)
			save.saved = 0;
	}
	//�e�L�X�g�{�b�N�X�̕\��
	Rect box(base.x - 15, base.y - 15, WINDOW_X - (base.x - 15),
		WINDOW_Y - (base.y - 15));
	box.draw(getData().backGround);
	box.drawFrame(0, 5, ColorF(0.2));
	//����
	render.draw(text, cursor, scroll);
	for(auto i:step(4))
		button[i].draw();
	for (auto i : step(6))
		tags[i].draw();
	for (auto i : step(6))
		help[i].draw();
	confScr.draw();
}