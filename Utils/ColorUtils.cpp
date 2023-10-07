#include "TimerUtil.h"
#include "ColorUtils.h"

UIColor ColorUtil::rainbowColor(float seconds, float saturation, float brightness, long index, float alpha) {
	float hue6 = (((TimerUtil::getCurrentMs() + index) % (int)(6000)) / (float)(6000));
	float r, g, b = 0;
	HSVtoRGB(hue6, saturation, brightness, r, g, b);

	return UIColor(r * 255, g * 255, b * 255, alpha);
}

UIColor ColorUtil::waveColor(int red, int green, int blue, int red2, int green2, int blue2, long index, float alpha) {
	double offset = ((TimerUtil::getCurrentMs() - index) / 8) / (double)120;
	double aids123 = ((TimerUtil::getCurrentMs() - index) % 1000 / 1000.000);
	int aids1234 = ((TimerUtil::getCurrentMs() - index) % 2000 / 2000.000) * 2;
	aids123 = aids1234 % 2 == 0 ? aids123 : 1 - aids123;
	double inverse_percent = 1 - aids123;
	int redPart = (int)(red * inverse_percent + red2 * aids123);
	int greenPart = (int)(green * inverse_percent + green2 * aids123);
	int bluePart = (int)(blue * inverse_percent + blue2 * aids123);

	return UIColor(redPart, greenPart, bluePart, alpha);
}

UIColor ColorUtil::astolfoRainbow(int yOffset, int yTotal, float alpha) {
	float speed = 3000;
	float hue = (float)(TimerUtil::getCurrentMs() % (int)speed) + ((yTotal - yOffset) * 9);
	while (hue > speed) { hue -= speed; } hue /= speed;
	if (hue > 0.5) { hue = 0.5F - (hue - 0.5f); } hue += 0.5f;
	float r, g, b = 0;
	HSVtoRGB(hue, 0.5, 1.f, r, g, b);

	return UIColor(r * 255, g * 255, b * 255, alpha);
}
