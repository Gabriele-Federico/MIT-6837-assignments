#ifndef COLOR_H
#define COLOR_H

#include "Vector4f.h"

struct Color
{
	Vector4f RGBA;
	float* asFloatArr()
	{
        float arr[4];
        arr[0] = RGBA.x();
        arr[1] = RGBA.y();
        arr[2] = RGBA.z();
        arr[3] = RGBA.w();
        return arr;
	}
};

#endif