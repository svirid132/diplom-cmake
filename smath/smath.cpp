#include "smath.h"

float smath::roundFloat(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}
