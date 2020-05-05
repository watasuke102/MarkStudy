#include "main.h"

///�^�C�g���V�[��
void Title::Init()
{
	titleFont = Font(128);
	copyright = Font(30);
	getData().beforeMenu = 0;
	//�{�^���傫���̏�����
	button[0] = Button(U"�m�[�g�̕ҏW", 60, Vec2(WINDOW_X - W_CENTER, 330), WINDOW_X, 100, false,true);
	button[1] = Button(U"�m�[�g�̊m�F", 60, Vec2(WINDOW_X - W_CENTER, 480), WINDOW_X, 100, false,true);
	button[2] = Button(U"�e�ݒ�"     , 60, Vec2(WINDOW_X - W_CENTER, 630), WINDOW_X, 100, false,true);
	button[3] = Button(U"�I��"       , 60, Vec2(WINDOW_X - W_CENTER, WINDOW_Y-140), WINDOW_X, 100, false,true);
}
void Title::update()
{
	if (getData().changeScene)
	{
		ScreenCapture::GetFrame(getData().data_fadeTex);
		changeScene(getData().toScene, (getData().beforeMenu!=0)?0:500, true);
		getData().changeScene = false;
	}
	//�{�^��
	for (auto i : step(4))
		button[i].update();
	//�{�^���N���b�N�ŃV�[���`�F���W
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
	//�^�C�g��
	titleFont(U"MarkStudy").draw(Arg::topCenter = Vec2(W_CENTER, 50));
	copyright(COPYRIGHT).draw(Arg::bottomCenter = Vec2(W_CENTER, WINDOW_Y));
	//�{�^��
	for (auto i : step(4))
		button[i].draw();
}