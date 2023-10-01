#pragma once

struct vec4_t {
	// union allows for the same memory location to be accessed with different names
	union {
		struct {
			float w, x, y, z;
		};
		float arr[4];
	};

	// constructor that initializes w, x, y, and z to provided values, or 0 if not provided
	vec4_t(float w = 0, float x = 0, float y = 0, float z = 0) {
		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
	};

	// constructor that initializes the vector based on a position and size (w and y are position, x and z are size)
	vec4_t(vec2_t position, vec2_t size) {
		this->w = position.x;
		this->x = position.x + size.x;
		this->y = position.y;
		this->z = position.y + size.y;
	};

	// overload == operator to allow for comparison between two vec4_t objects
	bool operator == (vec4_t v) { return v.w == w && v.x == x && v.y == y && v.z == z; };

	// overload != operator to allow for comparison between two vec4_t objects
	bool operator != (vec4_t v) { return v.w != w || v.x != x || v.y != y || v.z != z; };
};