#pragma once

struct BlockPos {
	// union allows for the same memory location to be accessed with different names
	union {
		struct {
			int x, y, z;
		};
		int arr[3];
	};

	// constructor that initializes x, y, and z to provided values, or 0 if not provided
	BlockPos(int x = 0, int y = 0, int z = 0) {
		this->x = x; this->y = y; this->z = z;
	};

	// overload == operator to allow for comparison between two BlockPos objects
	bool operator == (BlockPos v) { return v.x == x && v.y == y && v.z == z; };

	// overload != operator to allow for comparison between two BlockPos objects
	bool operator != (BlockPos v) { return v.x != x || v.y != y || v.z != z; };

	// overload *= operator to allow for multiplication of two BlockPos objects
	BlockPos operator *= (BlockPos v) { return BlockPos(v.x * x, v.y * y, v.z * z); };

	// returns a new BlockPos object that is the difference between this BlockPos and another
	BlockPos submissive(const BlockPos& o) const { return BlockPos(x - o.x, y - o.y, z - o.z); }

	// returns the squared length of the vector (x^2 + y^2 + z^2)
	int squaredlen() const { return x * x + y * y; }

	// returns the magnitude (length) of the vector
	int magnitude() const { return sqrtf(squaredlen()); }

	// returns the magnitude of the vector ignoring the z component
	int magnitudexy() const { return sqrtf(x * x + y * y); }

	// returns the magnitude of the vector ignoring the y component
	int magnitudexz() const { return sqrtf(x * x + z * z); }

	// returns a new BlockPos object that is the result of linearly interpolating between this BlockPos and another
	BlockPos lerp(const BlockPos& pos, int x1, int y1, int z1) {
		BlockPos This;
		This.x = x + x1 * (pos.x - x);
		This.y = y + y1 * (pos.y - y);
		This.z = z + z1 * (pos.z - z);
		return This;
	}

	// returns the distance between this BlockPos and another
	int distance(BlockPos v) {
		int dX = x - v.x;
		int dY = y - v.y;
		int dZ = z - v.z;
		return std::sqrt(dX * dX + dY * dY + dZ * dZ);
	}

};