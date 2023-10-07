#pragma once
#include "../SDK/Maths/UIColor.h"
#include <corecrt_math.h>


static inline float IamFmod(float x, float y) { return fmodf(x, y); }
static inline float IamFabs(float x) { return fabsf(x); }
template <typename T>
static inline void IamSwap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = tmp;
}

class ColorUtil {
public:
	static UIColor waveColor(int red, int green, int blue, int red2, int green2, int blue2, long index, float alpha);
	static UIColor rainbowColor(float seconds, float saturation, float brightness, long index, float alpha);
	static UIColor astolfoRainbow(int yOffset, int yTotal, float alpha);
	// Convert rgb floats ([0-1],[0-1],[0-1]) to hsv floats ([0-1],[0-1],[0-1]), from Foley & van Dam p592
	// Optimized http://lolengine.net/blog/2013/01/13/fast-rgb-to-hsv
	static inline void ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v) {
		float K = 0.f;
		if (g < b) {
			IamSwap(g, b);
			K = -1.f;
		}
		if (r < g) {
			IamSwap(r, g);
			K = -2.f / 6.f - K;
		}

		const float chroma = r - (g < b ? g : b);
		out_h = IamFabs(K + (g - b) / (6.f * chroma + 1e-20f));
		out_s = chroma / (r + 1e-20f);
		out_v = r;
	};

	// Convert hsv floats ([0-1],[0-1],[0-1]) to rgb floats ([0-1],[0-1],[0-1]), from Foley & van Dam p593
	// also http://en.wikipedia.org/wiki/HSL_and_HSV
	static inline void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b) {
		if (s == 0.0f) {
			// gray
			out_r = out_g = out_b = v;
			return;
		}

		h = IamFmod(h, 1.0f) / (60.0f / 360.0f);
		int i = (int)h;
		float f = h - (float)i;
		float p = v * (1.0f - s);
		float q = v * (1.0f - s * f);
		float t = v * (1.0f - s * (1.0f - f));

		switch (i) {
		case 0:
			out_r = v;
			out_g = t;
			out_b = p;
			break;
		case 1:
			out_r = q;
			out_g = v;
			out_b = p;
			break;
		case 2:
			out_r = p;
			out_g = v;
			out_b = t;
			break;
		case 3:
			out_r = p;
			out_g = q;
			out_b = v;
			break;
		case 4:
			out_r = t;
			out_g = p;
			out_b = v;
			break;
		case 5:
		default:
			out_r = v;
			out_g = p;
			out_b = q;
			break;
		}
	};

	static int HSBtoRGB(float hue, float saturation, float brightness) {
		int r = 0, g = 0, b = 0;
		if (saturation == 0) r = g = b = (int)(brightness * 255.0f + 0.5f);
		else {
			float h = (hue - (float)floor(hue)) * 6.0f;
			float f = h - (float)floor(h);
			float p = brightness * (1.0f - saturation);
			float q = brightness * (1.0f - saturation * f);
			float t = brightness * (1.0f - (saturation * (1.0f - f)));
			switch ((int)h) {
			case 0:
				r = (int)(brightness * 255.0f + 0.5f);
				g = (int)(t * 255.0f + 0.5f);
				b = (int)(p * 255.0f + 0.5f);
				break;
			case 1:
				r = (int)(q * 255.0f + 0.5f);
				g = (int)(brightness * 255.0f + 0.5f);
				b = (int)(p * 255.0f + 0.5f);
				break;
			case 2:
				r = (int)(p * 255.0f + 0.5f);
				g = (int)(brightness * 255.0f + 0.5f);
				b = (int)(t * 255.0f + 0.5f);
				break;
			case 3:
				r = (int)(p * 255.0f + 0.5f);
				g = (int)(q * 255.0f + 0.5f);
				b = (int)(brightness * 255.0f + 0.5f);
				break;
			case 4:
				r = (int)(t * 255.0f + 0.5f);
				g = (int)(p * 255.0f + 0.5f);
				b = (int)(brightness * 255.0f + 0.5f);
				break;
			case 5:
				r = (int)(brightness * 255.0f + 0.5f);
				g = (int)(p * 255.0f + 0.5f);
				b = (int)(q * 255.0f + 0.5f);
				break;
			}
		}
		return 0xff000000 | (r << 16) | (g << 8) | (b << 0);
	};

	static inline void HSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b) {
		if (s == 0.0f) {
			out_r = out_g = out_b = v;
			return;
		}
		h = IamFmod(h, 1.0f) / (60.0f / 360.0f);
		int i = (int)h;
		float f = h - (float)i;
		float p = v * (1.0f - s);
		float q = v * (1.0f - s * f);
		float t = v * (1.0f - s * (1.0f - f));
		switch (i) {
		case 0:
			out_r = v;
			out_g = t;
			out_b = p;
			break;
		case 1:
			out_r = q;
			out_g = v;
			out_b = p;
			break;
		case 2:
			out_r = p;
			out_g = v;
			out_b = t;
			break;
		case 3:
			out_r = p;
			out_g = q;
			out_b = v;
			break;
		case 4:
			out_r = t;
			out_g = p;
			out_b = v;
			break;
		case 5:
		default:
			out_r = v;
			out_g = p;
			out_b = q;
			break;
		}
	}
};
//