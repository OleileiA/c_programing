#include <stdio.h>

int main() {
    short s = 10;
    int i = s; // 直接赋值的形式相当于隐式类型转换，适合范围小的类型自动转换为大范围的类型。

    float a = 2;
    int b = 3;
    double c = a / b; // 这里的计算也包含隐式类型转换, int 转换为 float

    /* 计算中关于隐式类型转换的规则：
     * 1. 不同类型的优先级不同根据长度而定。
     * 2. char和short在参与运算的时候一律转换为int再计算。
     * 3. 浮点数默认使用双精度计算。
     * 4. 高优先级和低优先级一起运算的时候，转换为高优先级一起计算。
     * 5.
     */


    double pi = 3.14;
    int in = (int) pi; // 强制类型转换
    printf("in = %d", in);
    return 0;
}