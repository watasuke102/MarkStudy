#pragma once

///00.�^�C�g�����
class Title : public App::Scene
{
private:
	  Font titleFont, copyright;//�^�C�g�������̑傫��
	Button button[4];
public:
	Title(const InitData& init) : IScene(init) { Init(); };
	void Init();
	void update() override;
	void draw() const override;
	void updateFadeIn(double t)override { update(); }
	void   drawFadeIn(double t)const override 
	{
		draw();
	}
	void drawFadeOut(double) const override{};
};
///01.�ݒ���
class Config : public App::Scene
{
private:
	int baseY = 250;
	Font font;//�^�C�g�������̑傫��
	Button button[4];
	bool state_window=false;
	TextEditState state[5];
	Help help[5];
public:
	Config(const InitData& init) : IScene(init) { Init(); };
	void Init();
	void update() override;
	void draw() const override {};
	void LoadINI();
	void SaveINI();
	void updateFadeIn(double t)override { update(); }
	void   drawFadeIn(double t)const override 
	{
		draw();
	}
	void drawFadeOut(double) const override{};
};
///02.�t�@�C���ꗗ�擾�̍ۂ̉�ʒ�~�����
class Loading : public App::Scene
{
private:
	Font font;
	Texture texture;
	int cnt;
public:
	Loading(const InitData& init) : IScene(init) { Init(); };
	void Init() { cnt = 0; font = Font(50); };
	void update() override {
		if (getData().changeScene)
		{
			ScreenCapture::GetFrame(getData().data_fadeTex);
			changeScene(getData().toScene, 500, true);
			getData().changeScene = false;
		}
		if (cnt > 10)
			getData().ChangeStart(sceneName::FileMenu);
		else cnt++;
	}
	void draw() const override {
		texture.draw(Vec2(0,0));
		Scene::Rect().draw(ColorF(0, 0.8));
		font(U"Loading...").drawAt(Scene::Center());
	}
	void updateFadeIn(double t)override { update(); }
	void   drawFadeIn(double t)const override
	{
		draw();
	}
	void drawFadeOut(double) const override {};
};
///03.�V�K�쐬�E�ҏW�E�{���t�@�C���I�����j���[
class FileMenu : public App::Scene
{
private:
	int listMax;
	int clickList;
	int beforeButton;//���O�ɉ����ꂽ�{�^���͂Ȃɂ�
	double yScroll;
	Stopwatch upKey, downKey;
	ConfScreen confScr;
	Button scrollBar;
	Vec2 beforeMouse;
	Array<FileList> file;
	Button button[9];
public:
	FileMenu(const InitData& init) : IScene(init) { Init(); };
	void Init();
	void update() override;
	void draw() const override;
	void updateFadeIn(double t)override { update(); }
	void   drawFadeIn(double t)const override
	{
		draw();
	}
	void drawFadeOut(double) const override {};
};

///04.�ҏW
class WriteMain : public App::Scene
{
private:
	struct {
		int saved = 0;//0:���� 1:�J�n 2:�I��
		Font font;
		String text;
		Stopwatch time;
		EasingController<int> easing;
		void SetActive(String t) {
			font = Font(25);
			saved = 1;
			text = t;
			int width = font(t).region().w + 25;
			easing.setB(width);
			easing.start();
			time.restart();
		}
		void ReActive() {
			saved = 2;
			time.restart();
			easing.start();
		}
	}save;
	bool isPasted;
	int doSave = 0;//1:���O�m�F 2=���O�ݒ�I�� 3:�㏑���ۑ����� 
	int scroll;
	TextWriter file;
	  Font font;
	String newName;
	String text;//�e�L�X�g�{�b�N�X�̓��e
	size_t cursor = 0;
	Button button[4];
	Button tags[6];
	  Help help[6];
	ColorF palette;
	Stopwatch leftKey, rightKey;
	ConfScreen confScr;
	MarkUpRender render;
public:
	WriteMain(const InitData& init) : IScene(init) { Init(); };
	void Init();
	void update() override;
	void draw() const override {};
	void updateFadeIn(double t)override { update(); }
	void   drawFadeIn(double t)const override
	{
		draw();
	}
	void drawFadeOut(double) const override {};
};
///05.�{��
class ReadMain : public App::Scene
{
private:
	bool isInvisible;
	bool checked[5];
	int scroll;
	Font font;
	Button button[3];//�{�^��
	String text;//�e�L�X�g�{�b�N�X�̓��e
	MarkUpRender render;
public:
	ReadMain(const InitData& init) : IScene(init) { Init(); };
	void Init();
	void update() override;
	void draw() const override {};
	void updateFadeIn(double t)override { update(); }
	void   drawFadeIn(double t)const override
	{
		draw();
	}
	void drawFadeOut(double) const override {};
};