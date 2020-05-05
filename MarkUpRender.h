#pragma once

class MarkUpRender {
private:
	//タグ
	bool isReadTag;
	bool isBold;
	bool isLine[3];
	bool isImportant[5];

	bool isDrawCursor;
	bool isScrolled;
	int beforeMenu;//読み取りか書き込みか
	Vec2 base, drawPos;
	Font font,boldFont;
	ColorF col, lineCol[3];
	String tag;
	Stopwatch cursorTimer;
public:
	MarkUpRender() {};
	MarkUpRender(Vec2 pos,int bMenu) {
		isBold = false;
		isReadTag = false;
		isDrawCursor = true;
		font     = Font(manager.get()->fontSize);
		boldFont = Font(manager.get()->fontSize, Typeface::Regular, FontStyle::Bold);
		beforeMenu = bMenu;
		base = pos;
		 col = ColorF(0.1);
		 cursorTimer.start();
	}
	ColorF ParseColor(String s) {
		ColorF c;
		try	{
			c = Parse<ColorF>(s);
		}
		catch (const ParseError& e){
			c = Palette::Black;
		}
		return c;
	}
	void CursorRestart() {
		isDrawCursor = true;
		cursorTimer.restart();
	}
	void draw(String string, size_t cursor, int scroll, bool important[5]=false, bool isInvisible = false) {
		int enterNum=0;
		//tag初期化
		isBold = false;
		for (auto i : step(5))
			isLine[i] = false;
		for (auto i : step(5))
			isImportant[i] = false;
		col = ColorF(0.1);
		tag.clear();
		//そのほか
		isScrolled = false;
		int width = 0;
		int cnt = 0;
		Vec2 cursorPos(base),linePos(base);
		drawPos = base;
		//メイン
		for (const auto& text : font(string))
		{
			if (beforeMenu == 1 || (!isReadTag && text.codePoint != U'[' && text.codePoint != U']'))
				width += text.xAdvance;
			cnt++;
			//改行
			if (text.codePoint == '\n' || width >= WINDOW_X - (base.x + 50))
			{
				enterNum++;
				width = 0;
				if (scroll >= enterNum && scroll != 0) {
					isScrolled = true;
					continue;
				}
				drawPos.x = base.x;
				drawPos.y += font.height();
			}
			if (scroll > enterNum) {
				isScrolled = true;
				continue;
			}
			if (isReadTag && text.codePoint != '[')
			{
				if (text.codePoint == ']')
					isReadTag = false;
				if (text.codePoint == ' ' || text.codePoint == '　') {
					//太字
					if (tag.starts_with('B')) {
						isBold = true;
					}
					//いろつける
					if (tag.starts_with('#')) {
						String color = tag;
						col = ParseColor(color);
					}
					//重要単語
					if (tag.starts_with('I') && manager.get()->beforeMenu == 2) {
						tag.pop_front();
						int num;
						try {
							num = Parse<int>(tag);
						}
						catch (const ParseError& e) {
							num = 1;
						}
						if(!(num<0 || num > 5) && important[num - 1]) {
							if (isInvisible) {
								col = AlphaF(0);
							}else col = HSV(num * 50);
						}
					}
					//打ち消し・下線・背景ハイライト
					char c[3] = { 'H','S','U' };
					for (auto i : step(3))
						if (tag.starts_with(c[i])) {
							String color = tag;
							color.replace(c[i], '#');
							switch (c[i]) {
							case 'H':
								isLine[0] = true;
								lineCol[0] = ParseColor(color);
								break;
							case 'S':
								isLine[1] = true;
								lineCol[1] = ParseColor(color);
								break;
							case 'U':
								isLine[2] = true;
								lineCol[2] = ParseColor(color);
								break;
							default:break;
							}
						}
					isReadTag = false;
					tag.clear();
				}
				else {
					tag += text.codePoint;
				}
				if (beforeMenu == 2) continue;
			}
			if (text.codePoint == '[') {
				isReadTag = true;
				col = ColorF(0.1);
				for(auto i : step(5))
					isLine[i] = false;
				for (auto i : step(5))
					isImportant[i] = false;
				isBold = false;
				if (beforeMenu == 2) continue;
			}
			if (text.codePoint == ']'){
				col = ColorF(0.1);
				for (auto i : step(5))
					isLine[i] = false;
				isBold = false;
				if (beforeMenu == 2) continue;
			}
			//メイン描画
			Rect markLine[3];
			int height;
			int fontH = font.height();
			if (isLine[0])
				markLine[0] = Rect(drawPos.x, drawPos.y + 7, text.xAdvance, fontH - 7);
			if (isLine[1])
				markLine[1] = Rect(drawPos.x, drawPos.y + fontH / 2, text.xAdvance, 2);
			if (isLine[2])
				markLine[2] = Rect(drawPos.x, drawPos.y + (fontH - 7), text.xAdvance, 2);

			if (isLine[0])markLine[0].draw(lineCol[0]);
			if (isLine[2])markLine[2].draw(lineCol[2]);

			//文字
			if (isBold) {
				const auto bold = boldFont.getGlyph(text.codePoint);
				bold.texture.draw(drawPos + bold.offset, col);
				drawPos.x += bold.xAdvance;
			}
			else {
				text.texture.draw(drawPos + text.offset, col);
				drawPos.x += text.xAdvance;
			}
			
			if (isLine[1])markLine[1].draw(lineCol[1]);

			//点滅で消えてなく編集中ならカーソル位置にたてぼう
			//cnt++;
			cursorPos = drawPos;
			if (cnt == cursor && beforeMenu == 1 && isDrawCursor)
				Line(cursorPos.x, cursorPos.y + 10, cursorPos.x, cursorPos.y + font.height())
				.draw(ColorF(0));
		}
		if (cursor == 0 && !isScrolled && isDrawCursor && beforeMenu == 1)
			Line(base.x, base.y + 10, base.x, base.y + font.height())
			.draw(ColorF(0));
		
		//カーソル点滅
		if (cursorTimer >= 0.5s) {
			cursorTimer.restart();
			isDrawCursor = !isDrawCursor;
		}

	}
};