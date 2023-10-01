#pragma once

struct vec2_t {
	// union allows for the same memory location to be accessed with different names 共用体...ってｺﾄ？！だいたいあってるしょ
	union {
		struct {
			float x, y;
		};
		float arr[2];
	};

	// constructor that initializes x and y to provided values, or 0 if not provided
	vec2_t(float x = 0, float y = 0) {
		this->x = x; this->y = y;
	};
};