#pragma once

struct vec2_t {
	// union allows for the same memory location to be accessed with different names ‹¤—p‘Ì...‚Á‚ÄºÄHI‚¾‚¢‚½‚¢‚ ‚Á‚Ä‚é‚µ‚å
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

// constant to convert degrees to radians
static constexpr float DEG_RAD = 180.0f / 3.1415927f; // calculates on compile

struct vec3_t {
	// union allows for the same memory location to be accessed with different names
	union {
		struct {
			float x, y, z;
		};
		float arr[3];
	};

	// constructor that initializes x, y, and z to provided values, or 0 if not provided
	vec3_t(float x = 0, float y = 0, float z = 0) {
		this->x = x; this->y = y; this->z = z;
	};

	// overload == operator to allow for comparison between two vec3_t objects
	bool operator == (vec3_t v) { return v.x == x && v.y == y && v.z == z; };

	// overload != operator to allow for comparison between two vec3_t objects
	bool operator != (vec3_t v) { return v.x != x || v.y != y || v.z != z; };

	// overload *= operator to allow for multiplication of two vec3_t objects
	vec3_t operator *= (vec3_t v) { return vec3_t(v.x * x, v.y * y, v.z * z); };

	// returns a new vec3_t object that is the difference between this vec3_t and another
	vec3_t submissive(const vec3_t& o) const { return vec3_t(x - o.x, y - o.y, z - o.z); }

	// returns the squared length of the vector (x^2 + y^2 + z^2)
	float squaredlen() const { return x * x + y * y; }

	// returns the magnitude (length) of the vector
	float magnitude() const { return sqrtf(squaredlen()); }

	// returns the magnitude of the vector ignoring the z component
	float magnitudexy() const { return sqrtf(x * x + y * y); }

	// returns the magnitude of the vector ignoring the y component
	float magnitudexz() const { return sqrtf(x * x + z * z); }

	// returns a new vec3_t object that is the result of linearly interpolating between this vec3_t and another
	vec3_t lerp(const vec3_t& pos, float x1, float y1, float z1) {
		vec3_t This;
		This.x = x + x1 * (pos.x - x);
		This.y = y + y1 * (pos.y - y);
		This.z = z + z1 * (pos.z - z);
		return This;
	}

	// returns the distance between this vec3_t and another
	float distance(vec3_t v) {
		float dX = x - v.x;
		float dY = y - v.y;
		float dZ = z - v.z;
		return std::sqrt(dX * dX + dY * dY + dZ * dZ);
	}

};
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

struct vec3_ti {
	// union allows for the same memory location to be accessed with different names
	union {
		struct {
			int x, y, z;
		};
		int arr[3];
	};

	// constructor that initializes x, y, and z to provided values, or 0 if not provided
	vec3_ti(int x = 0, int y = 0, int z = 0) {
		this->x = x; this->y = y; this->z = z;
	};

	// overload == operator to allow for comparison between two vec3_ti objects
	bool operator == (vec3_ti v) { return v.x == x && v.y == y && v.z == z; };

	// overload != operator to allow for comparison between two vec3_ti objects
	bool operator != (vec3_ti v) { return v.x != x || v.y != y || v.z != z; };

	// overload *= operator to allow for multiplication of two vec3_ti objects
	vec3_ti operator *= (vec3_ti v) { return vec3_ti(v.x * x, v.y * y, v.z * z); };

	// returns a new vec3_ti object that is the difference between this vec3_ti and another
	vec3_ti submissive(const vec3_ti& o) const { return vec3_ti(x - o.x, y - o.y, z - o.z); }

	// returns the squared length of the vector (x^2 + y^2 + z^2)
	int squaredlen() const { return x * x + y * y; }

	// returns the magnitude (length) of the vector
	int magnitude() const { return sqrtf(squaredlen()); }

	// returns the magnitude of the vector ignoring the z component
	int magnitudexy() const { return sqrtf(x * x + y * y); }

	// returns the magnitude of the vector ignoring the y component
	int magnitudexz() const { return sqrtf(x * x + z * z); }

	// returns a new vec3_ti object that is the result of linearly interpolating between this vec3_ti and another
	vec3_ti lerp(const vec3_ti& pos, int x1, int y1, int z1) {
		vec3_ti This;
		This.x = x + x1 * (pos.x - x);
		This.y = y + y1 * (pos.y - y);
		This.z = z + z1 * (pos.z - z);
		return This;
	}

	// returns the distance between this vec3_ti and another
	int distance(vec3_ti v) {
		int dX = x - v.x;
		int dY = y - v.y;
		int dZ = z - v.z;
		return std::sqrt(dX * dX + dY * dY + dZ * dZ);
	}

};