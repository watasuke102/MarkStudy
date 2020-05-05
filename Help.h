#pragma once
class Help {
private:
	  bool isDraw;
	double color;
	  Vec2 pos;
	Circle circle;
	String text;
	  Font font,helpFont;
public:
	Help() {};
	Help(bool f, Vec2 tempPos, int r, String t) {
		isDraw = f;
		color = 0;
		pos = tempPos;
		circle = Circle(pos, r);
		text = t;
		font = Font(20);
		helpFont = Font(25);
	}
	void draw() {
		if (circle.mouseOver()) color += 0.1;
		else color -= 0.1;
		if (color < 0)color = 0;
		if (color > 1)color = 1;

		if (isDraw) {
			circle.draw(Palette::White);
			font(U"ÅH").drawAt(pos, Palette::Black);
		}
		Point cursor = Cursor::Pos();
		cursor.y += 20;
		helpFont(text).region(cursor).drawFrame(0,10, ColorF(0.2, color)).draw(ColorF(0.2, color));
		helpFont(text).draw(cursor.x, cursor.y, ColorF(0.8, color));
	}
};