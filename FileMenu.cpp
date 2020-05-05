#include "main.h"

///新規作成・編集メニュー
void FileMenu::Init()
{
	yScroll     = 0;
	clickList   = -1;
	beforeMouse = Vec2(0,0);
	getData().isUseFile = false;
	button[0]   = Button(U"決定",          40, Vec2(180, 100), 280, 60, true, true);
	button[1]   = Button(U"削除",          40, Vec2(180, 200), 280, 60, true, true);
	button[2]   = Button(U"コピーして作成", 35, Vec2(180, 300), 280, 60, true, true);
	button[3]   = Button(U"名前の変更"    , 40, Vec2(180, 400), 280, 60, true, true);
	button[4]   = Button(U"再読み込み"   , 40, Vec2(180, 500), 280, 60, true, true);
	button[5]   = Button(U"新規作成"     , 40, Vec2(180, 600), 280, 60, true, true);
	button[6]   = Button(U"戻る"         , 40, Vec2(180, WINDOW_Y - 60),280, 60, true, true);
	button[7]   = Button(U"▲", 30, Vec2(WINDOW_X-15,         15),30, 30,false, true);
	button[8]   = Button(U"▼", 30, Vec2(WINDOW_X-15,WINDOW_Y-15),30, 30,false, true);
	upKey.restart();
	downKey.restart();
	//ファイルの取得
	Array<FilePath> path = FileSystem::DirectoryContents(U"Note/");
	size_t size = path.size();
	file = Array<FileList>(size);
	listMax = size-1;
	int listHeight = (LIST_HEIGHT+3)*size;
	int j = 0, i = 0;
	for (auto i : step(size)) {
		if (FileSystem::Extension(path[i]) == U"txt") {
			file[j] = FileList(FileData(FileSystem::FullPath(path[i])),getData().timeFormat);
			j++;
		}
	}
}
void FileMenu::update()
{
	//シーンチェンジ
	if (getData().changeScene)
	{
		ScreenCapture::GetFrame(getData().data_fadeTex);
		changeScene(getData().toScene,
			(getData().toScene==sceneName::Loading)? 0 : 500, true);
		getData().changeScene = false;
	}
	int state = confScr.Update();
	if(state == CONF_NORMAL|| state==CONF_NO)
		return;
	else if (state == CONF_YES) {
		switch (beforeButton) {
		case BUTTON_DEL://削除
			FileSystem::Remove(file[clickList].GetPath());
			break;
		case BUTTON_COP://複製
			FileSystem::Copy(file[clickList].GetPath(), file[clickList].GetPathNoName() + confScr.GetName() + U".txt");
			break;
		default:break;
		}
		if (beforeButton == BUTTON_REN)//名前の変更
			if (!(confScr.GetName() == file[clickList].GetName())) {
				TextReader a(file[clickList].GetPath());
				TextWriter b(file[clickList].GetPathNoName() + confScr.GetName() + U".txt");
				b.write(a.readAll());
				a.close();
				b.close();
				FileSystem::Remove(file[clickList].GetPath());
			}
		getData().ChangeStart(sceneName::Loading);
		return;
	}
	//ボタン
	for (auto i : step(9)) {
		if (i == 5 && getData().beforeMenu == 2)
			continue;
		button[i].update();
	}
	bool isClickedConf = false;
	if (clickList != -1) {
		if (button[0].Click()) {
			isClickedConf = true;
			getData().isUseFile = true;
			getData().file = file[clickList];
			if (getData().beforeMenu == 1)
				getData().ChangeStart(sceneName::WriteMain);
			else if (getData().beforeMenu == 2)
				getData().ChangeStart(sceneName::ReadMain);
		}
		if (button[1].Click()) {
			isClickedConf = true;
			beforeButton = BUTTON_DEL;
			confScr.setActive(CONF_YESNO, U"削除されたファイルは復元できません。\n削除を実行してよろしいですか？");
		}
		if (button[2].Click()) {
			isClickedConf = true;
			beforeButton = BUTTON_COP;
			confScr.setActive(CONF_STRING, U"複製後の名前を入力してください。");
		}
		if (button[3].Click()) {
			isClickedConf = true;
			beforeButton = BUTTON_REN;
			confScr.setActive(CONF_STRING, U"変更後の名前を入力してください。");
		}
	}
	if (button[4].Click())
		getData().ChangeStart(sceneName::Loading);
	if (button[5].Click() && getData().beforeMenu == 1)
		getData().ChangeStart(sceneName::WriteMain);
	if (button[6].Click())
		getData().ChangeStart(sceneName::Title);
	//スクロール
	yScroll += Mouse::Wheel();
	if (button[7].Click() || (KeyUp.down() || (KeyUp.pressedDuration() > 0.3s && upKey > 0.1s)))
	{
		yScroll--;
		upKey.restart();
	}
	if (button[8].Click() || (KeyDown.down() || (KeyDown.pressedDuration() > 0.3s && downKey > 0.1s)))
	{
		yScroll++;
		downKey.restart();
	}
	if (yScroll > listMax) yScroll = listMax;
	if (yScroll < 0) yScroll = 0;
	//ファイル一覧
	bool isSetList = false;
	int  y = 0;
	//注意画面ボタンが押されていないもしくは注意画面がアクティブでないなら解除
	bool doUnset = (!isClickedConf || state == CONF_NO);
	if (file.size() != 0)
		for (auto i : step(file.size())) {
			if (i < yScroll)
				continue;
			if (file[i].Update(Vec2(WINDOW_X - (LIST_WIDTH+30), y - yScroll), isSetList, doUnset)) {
				clickList = i;
				isSetList = true;
			}
			y += LIST_HEIGHT + 3;
		}
	if (clickList != -1 && isSetList == false)
		clickList = -1;
}
void FileMenu::draw() const
{
	//ボタン
	for (auto i : step(9)) {
		if (i == 5 && getData().beforeMenu == 2)
			continue;
		button[i].draw();
	}
	for (auto i : step(file.size())) {
		if (i < yScroll)
			continue;
		file[i].Draw(true);
	}
	if (clickList != -1) 
		confScr.draw(file[clickList]);
}