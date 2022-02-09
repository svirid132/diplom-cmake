#ifndef MATHLOGICFUNC_H
#define MATHLOGICFUNC_H
#include <algorithm>
#include <limits>

// smath - standart(easy) math
namespace smath {
    template<typename Type>
    Type maxValue(const Type *const array, int length) {
        Type maxVal = std::numeric_limits<Type>::min();
        for (int i = 0; i < length; ++i) {
            maxVal = std::max<Type>(maxVal, array[i]);
        }
        return maxVal;
    }


    template<typename Type>
    Type minValue(const Type *const array, int length) {
        Type minVal = std::numeric_limits<Type>::max();
        for (int i = 0; i < length; ++i) {
            minVal = std::min<Type>(minVal, array[i]);
        }
        return minVal;
    }

//    float roundFloat(float var){
//        float value = (int)(var * 100 + .5);
//        return (float)value / 100;
//    }
}

#endif // MATHLOGICFUNC_H
