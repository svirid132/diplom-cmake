#ifndef MATHLOGICFUNC_H
#define MATHLOGICFUNC_H

namespace math {
    template<typename Type>
    Type maxValue(const Type *const array, int length) {
        Type max = 0;
        for (int i = 0; i < length; ++i) {
            if (max < array[i]) {
                max = array[i];
            }
        }
        return max;
    }


    template<typename Type>
    Type minValue(const Type *const array, int length) {
        Type min = 2147483647;
        for (int i = 0; i < length; ++i) {
            if (min > array[i]) {
                min = array[i];
            }
        }
        return min;
    }
}

#endif // MATHLOGICFUNC_H
