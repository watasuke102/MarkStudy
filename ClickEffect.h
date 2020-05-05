#pragma once

struct Click : IEffect {
	Vec2 pos;
	Click(const Vec2& mouse) {
		pos = mouse;
	}
	bool update(double t) override {
		Circle(pos, t*100).drawFrame(4, AlphaF(1.0-t*2));
		//return t < 1.0;
		return t < 0.5;
	}
};