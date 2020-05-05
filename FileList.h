#pragma once

class FileData {
public:
	int    size;//�t�@�C���T�C�Y
	bool isDraw;
	String name;//�t�@�C����
	String path;//�t�@�C���p�X
	String text;//�t�@�C�����g�ꕔ
	DateTime time;
	FileData() {
		for (auto i : step(4)){
			name.clear();
			text.clear();
		}
	};
	void ChangeName(String newName) { name = newName; };
	FileData(bool isDraw, String name) { this->isDraw = isDraw; this->name = name; }
	FileData(String fpath) {
		name.clear();
		text.clear();
		isDraw = true;
		//���e�擾
		path = fpath;
		name = FileSystem::BaseName(path);//�t�@�C����
		size = FileSystem::Size(path);//�t�@�C����
		time = Optional<DateTime>(FileSystem::WriteTime(path)).value();//�X�V����
		//���g
		TextReader inText(path);
		char32 c;
		int width=0;
		Font font(20);
		while(width < LIST_WIDTH - 100){//�������傫����Δ�����
			if (!inText.readChar(c)) return;
			if (c == '\n') {
				text.push_back(' ');
				continue;
			}
			width += font.getGlyph(c).xAdvance;
			text.push_back(c);
		}
		text += U" ...";
	}
};

class FileList {
private:
	bool isClick;
	FileData fData;
	Rect box,edge;
	String timeFormat;
	String printName;
public:
	FileList() {}
	FileList(FileData text, String timeF) {
		isClick = false;
		fData = text;
		timeFormat = timeF;
		int i = 0;
		int width = 0;
		while (width < LIST_WIDTH - 100) {//�������傫����Δ�����
			if (i == fData.name.size())
				return;
			width += FontAsset(U"Font40").getGlyph(fData.name[i]).xAdvance;
			printName += fData.name[i];
			i++;
		}
		printName += U" ...";
	}
	FileData GetFileData() { return fData; };
	String GetPath() { return fData.path; };
	String GetName() { return fData.name; };
	String GetPathNoName() { return FileSystem::ParentPath(fData.path); };
	bool Update(Vec2 pos, bool f, bool doUnSet) {
		box  = Rect(pos.x, pos.y  , LIST_WIDTH, LIST_HEIGHT);
		edge = Rect(pos.x, pos.y-3, LIST_WIDTH, LIST_HEIGHT+6);
		if (MouseL.down())
			if (box.leftClicked() && !f)
				isClick = !isClick;
		else if(doUnSet)
				isClick = false;
		return isClick;
	}
	void SetPos(Vec2 p){
		 box = Rect(p.x, p.y  , LIST_WIDTH, LIST_HEIGHT);
		edge = Rect(p.x, p.y-3, LIST_WIDTH, LIST_HEIGHT + 6);
	}
	void Draw(bool isDrawFrame) const {
		if (!fData.isDraw) return;
		edge.draw(Palette::Black);
		box.draw(ColorF(0.2));
		if (isClick && isDrawFrame) box.drawFrame(5,0, Palette::White);
		FontAsset(U"Font40")(printName)//�薼
		.draw( Arg::topLeft    = (box.pos + Vec2( 10, 0)) );
		FontAsset(U"Font20")(fData.text)//���g
		.draw(box.pos + Vec2( 35, 60));
		FontAsset(U"Font20")(fData.time.format(timeFormat))
		.draw(Arg::bottomRight = (box.pos + Vec2(LIST_WIDTH-5, LIST_HEIGHT)) );
	}
};