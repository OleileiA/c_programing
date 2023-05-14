#include <stdio.h>

/*
 * gcc预编译：      gcc -E main.c -o main.i
 * gcc预编译到汇编： gcc -S main.i -o main.s
 * gcc汇编到二进制： gcc -c main.s -o main.o
 * 目标文件：        gcc main.o -o main
 *
 * 直接编译：gcc main.c -o main
 *
 * 编译两个文件：gcc main.c test.c -o main
 * */
int main() {
    printf("Hello, World!\n");
    return 0;
}
