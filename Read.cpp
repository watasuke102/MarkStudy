#include "main.h"

///���C���ҏW���
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
	//�{�^��
	button[0] = Button(U"�S�ċ����\��", 30, Vec2(150, 80), 250, 50, true, true);
	button[1] = Button(U"�����̑I�𔽓]", 30, Vec2(150, 180), 250, 50, true, true);
	button[2] = Button(U"�߂�", 50, Vec2(150, WINDOW_Y - 60), 150, 70, true, true);
}
void ReadMain::update() 
{
	//�V�[���`�F���W
	if (getData().changeScene)
	{
		ScreenCapture::GetFrame(getData().data_fadeTex);
		changeScene(getData().toScene, 500, true);
		getData().changeScene = false;
	}
	//�{�^��
	for(auto i:step(3))
		button[i].update(); 
	if (button[0].Click())
		for (auto i : step(5))
			checked[i] = true;
	if (button[1].Click())
		for (auto i : step(5))
			checked[i] = !checked[i];
	if (button[2].Click()) getData().ChangeStart(sceneName::Title);
	//�X�N���[��
	scroll += Mouse::Wheel();
	if (scroll < 0) scroll = 0;
	//�ʒu
	const Vec2 base(320, 10);//�����J�n�ʒu
	//�e�L�X�g�{�b�N�X�̕\��
	SimpleGUI::CheckBoxAt(isInvisible, U"�d�v�P��𓧖��ɂ���", Vec2(150, 250));
	SimpleGUI::CheckBoxAt(checked[0], U"�d�v�P��P�������\��", Vec2(150, 300));
	SimpleGUI::CheckBoxAt(checked[1], U"�d�v�P��Q�������\��", Vec2(150, 350));
	SimpleGUI::CheckBoxAt(checked[2], U"�d�v�P��R�������\��", Vec2(150, 400));
	SimpleGUI::CheckBoxAt(checked[3], U"�d�v�P��S�������\��", Vec2(150, 450));
	SimpleGUI::CheckBoxAt(checked[4], U"�d�v�P��T�������\��", Vec2(150, 500));
	Rect box(base.x - 15, base.y - 15, WINDOW_X - (base.x - 15),
		WINDOW_Y - (base.y - 15));
	box.draw(getData().backGround);
	box.drawFrame(0, 5, ColorF(0.2));
	for (auto i : step(3))
		button[i].draw();
	render.draw(text, 0, scroll,checked, isInvisible);
}