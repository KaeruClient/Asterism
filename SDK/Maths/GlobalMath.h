#pragma once
#include <utility>

__forceinline double smoothLerp(double endPoint, double current, double speed) {
    if (speed < 0.0) speed = 0.0;
    else if (speed > 1.0) speed = 1.0;

    double diff = max(endPoint, current) - min(endPoint, current);
    double factor = diff * speed;
    return current + (endPoint > current ? factor : -factor);
}