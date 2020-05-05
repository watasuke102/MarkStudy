#pragma once

///GUIボタン（アニメーション）
class Button {
	private:
		bool           f;
		RoundRect button;//ボタン用の図形
		ColorF     color,basicC,basicHighC;//ボタンの色、通常色
		Vec2        pos;//文字の位置
		String      text;//文字の内容
		Font        font;//文字
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
		//表示するテキスト、フォントの大きさ、位置(中心)、横、縦、trueで角を丸ませる,trueでポイント時に反転
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
				//マウスオーバーのアニメーション
				if (button.mouseOver() && color.r <= basicHighC.r)//カーソルと接触かつ色が明るすぎなければ
					color += ColorF(0.1);//明るくする
				else if (color.r >= basicC.r)//カーソルがなく暗すぎなければ
					color -= ColorF(0.1);//暗くする
			}
		}
		//クリックされたかどうか
		bool Click() {
			return button.leftClicked();
		}
		bool Pressed() {
			return button.leftPressed();
		}
};