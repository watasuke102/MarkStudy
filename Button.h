#pragma once

///GUI�{�^���i�A�j���[�V�����j
class Button {
	private:
		bool           f;
		RoundRect button;//�{�^���p�̐}�`
		ColorF     color,basicC,basicHighC;//�{�^���̐F�A�ʏ�F
		Vec2        pos;//�����̈ʒu
		String      text;//�����̓��e
		Font        font;//����
	public:
		Button(){
			color  = ColorF(0.2);
			basicC = ColorF(0.2);
			basicHighC = ColorF(1.0);
			pos    = Vec2(100, 50);
			text   = U"text";
			font   = Font(50);
			button = RoundRect(Arg::center = pos, 200,100, 10);
		}
		//�\������e�L�X�g�A�t�H���g�̑傫���A�ʒu(���S)�A���A�c�Atrue�Ŋp���ۂ܂���,true�Ń|�C���g���ɔ��]
		Button(String tempText,int size, Vec2 tempPos, int width, int height, bool cornerF,bool anmF) {
			f      =        anmF;
			color  = ColorF(0.2);
			basicC = ColorF(0.2);
			basicHighC = ColorF(1.0);
			pos    = tempPos;
			text   = tempText;
			font   = Font(size);
			button = RoundRect(Arg::center = pos, width, height,(cornerF)? 10 : 0);
		}
		void colorSet(ColorF c) { color = c; basicC = c; }
		void highColorSet(ColorF c) { basicHighC = c; }
		void ySet(int y) {
			if (y < button.h/2 || y > WINDOW_Y - button.h/2) return;
			pos.y = y;
		}
		void draw() const {
			button.draw(color);
			font(text).drawAt(pos,ColorF(1.0)-color);
		}
		void update() {
			button = RoundRect(Arg::center = pos,button.w,button.h,button.r);
			if (f) {
				//�}�E�X�I�[�o�[�̃A�j���[�V����
				if (button.mouseOver() && color.r <= basicHighC.r)//�J�[�\���ƐڐG���F�����邷���Ȃ����
					color += ColorF(0.1);//���邭����
				else if (color.r >= basicC.r)//�J�[�\�����Ȃ��Â����Ȃ����
					color -= ColorF(0.1);//�Â�����
			}
		}
		//�N���b�N���ꂽ���ǂ���
		bool Click() {
			return button.leftClicked();
		}
		bool Pressed() {
			return button.leftPressed();
		}
};