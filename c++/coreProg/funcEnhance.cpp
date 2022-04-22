#include <iostream>

using namespace std;
//1.函数默认参数
//	函数形参列表中的形参可以有默认值
//	某个位置有默认值，此位置从左往右必须都有默认值
//	函数声明的有默认值，则函数实现不能有默认值

int func1(int a, int b=10, int c = 20);
int func1(int a, int b, int c)
{
	return a+b+c;
}
//2.函数的占位参数
void func2(int a,int)
{
	cout << "func2 ...." << endl;
}
//3.函数重载
//条件：同一个作用域下，函数名称相同，函数参数的类型不同或者个数不同或者顺序不同
void func3(int a)
{
	cout << "int func" << endl;
}
void func3(double d)
{
	cout << "double func" << endl;
}
int main()
{
	cout << "**********func1***********" << endl;
	int ret =func1(100);
	cout << "ret = " << ret << endl;
	cout << "**********func2***********" << endl;
	func2(10,20);
	cout << "**********func3***********" << endl;
	func3(4);
	func3(3.14);

	return 0;
}
