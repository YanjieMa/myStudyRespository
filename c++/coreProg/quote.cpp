#include <iostream>

using namespace std;

//1.引用基本使用
void test1()
{
	int a = 10;
	int &b = a;//必须初始化
	
	cout << "a=" << a << "\tb=" << b << endl;
	cout << "&a=" << &a << "\t&b=" << &b << endl;
}
//2.应用做函数参数
void mySwap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
//3.引用做函数返回值
int &test3()
{
	static int a = 30;
	cout<< "引用的地址=" << &a << endl;
	return a;	
}
//4.引用的本质
//发现是引用，转换为int * const ref = &a;	指针常量是指针的指向不可改，这也说明了为什么引用不可更改
void test4()
{
	int a = 10;
	int * const b = &a;
	int &c = a;
	cout << "&a="<< &a << "\t&b="<< &b << "\t&c="<< &c<< endl;
	*b = 200;
	cout << "a=" <<a << "\tb="<< *b << "\tc="<< c << endl;
}
//5.常量的引用
void test5(const int &a)
{
//	const int tmp = 10;
	const int &ref = 10;
	cout << "ref = " << ref << endl;
	//tmp =100;
	cout << "ref = " << ref << endl;
	//a = 200;
	cout << "a = " << a << endl;
}
int main(int argc,char **argv)
{
	test1();
	
	int a=10,b=20;
	mySwap(a,b);
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;		

	int &ret = test3();
	cout << "所引用的地址=" << &ret << endl;

	test3() = 1000;
	cout << "ret = " << ret << endl;	
	cout << "**************test4******************"<<endl;
	test4();
	cout << "**************test5******************"<<endl;
	test5(20);
	return 0;
}
