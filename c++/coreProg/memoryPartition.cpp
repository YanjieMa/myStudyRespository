#include <iostream>

using namespace std;
/*总结*/
/*
 * 高地址		栈区（向下增长）	:存放函数的局部变量，形参和函数的返回值
 *				堆区（向上增长）	:注意内存泄露
 *				静态区（全局区）	:静态变量和全局变量的存储区域是一起的，一旦静态区的内存被分配，直到程序运行结束才释放
 *									 未初始化数据段（RAM）	
 *				常量区	:存放常量
 *低地址		代码区	:存放程序执行的代码，即CPU执行的机器指令，只读 共享
				程序运行前：代码区+全局区	total: Code + RO Data + RW Data
				程序运行后：栈区+堆区+全局区(RAM)  程序运行中会将RW Data搬运到RAM中；将未初始化数据段在RAM的区域全部初始化为零
*/
//1.全局变量
int global_val_a = 10;
int global_val_b = 20;
//1.1未初始化全局变量
int global_val_c;
int global_val_d;

//2.全局常量
const int global_const_val_a = 1;
const int global_const_val_b = 2;

void test()
{
	//3.局部变量
	int a = 10;
	int b = 20;

	//4.静态变量
	static int static_a = 100;
	static int static_b = 200;

	//5.局部常量
	const int const_a = 1;
	const int const_b = 2;

	cout<< "global_val_a = " << &global_val_a << endl;
	cout<< "global_val_b = " << &global_val_b << endl;
	cout<< "global_val_c = " << &global_val_c << endl;
	cout<< "global_val_d = " << &global_val_d << endl;
	cout<< "global_const_val_a = " << &global_const_val_a << endl;
	cout<< "global_const_val_b = " << &global_const_val_b << endl;
	cout<< "a = " << &a << endl;
	cout<< "b = " << &b << endl;
	cout<< "static_a = "<< &static_a << endl;
	cout<< "static_b = "<< &static_b << endl;
	cout<< "const_a = "<< &const_a << endl;
	cout<< "const_b = "<< &const_b << endl;
}

int main(int argc, char **argv)
{
	test();
	return 0;
}
