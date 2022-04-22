#include <iostream>

using namespace std;
//封装的意义
//1.属性和行为写在一起，表现事物
const double pi = 3.14;
class Circle
{
public:
	int m_r;
	double calcuZC()
	{
		return 2*pi*m_r;
	}
};
void test1()
{
	Circle c1;
	c1.m_r = 5;
	cout << " 周长是：" << c1.calcuZC() << endl;
}

//2.属性和行为放在不同权限下，加以控制
class Person
{
public:
	void setName(string name)
	{
		m_name = name;
	}
	string getName()
	{
		return m_name;
	}
	
	void setPasswd(int passwd)
	{
		m_passwd = passwd;
	}
	int getPasswd()
	{
		return m_passwd;
	}


public:
	string m_name;
protected:
	string m_car;
private:
	int m_passwd;	
};
void test2()
{
	int passwd= 123;
	Person ma;
	ma.m_name = "mayanjie";
	cout << ma.getName() << endl;
	ma.setPasswd(123);
	cout << ma.getPasswd() << endl;	
}
//对象的初始化和清理
//构造函数和析构函数
class House
{
public:
	House()
	{
		m_num = 0;
		m_height = NULL;
		cout << "House无参构造函数" << endl;
	}
	/*House(int num,int height)
	{
		m_num = num;
		m_height = new int(height);
		cout << "House有参构造函数" << endl;
	}*/
	//初始化列表
	House(int num,int height):m_num(num),m_height(new int(height)) {cout << "House有参构造函数" << endl;}
	House(const House &house)
	{
		m_num = house.m_num;
		m_height = new int(*house.m_height);//深拷贝
		cout << "House拷贝构造函数" << endl;
	}
	~House()
	{
		if(m_height != NULL){
			delete m_height;
		}
		cout << "House析构函数" << endl;
	}
public:
	int m_num;
	int *m_height;
};
void test3()
{
	//无参构造
	House house1;
	
	//有参构造
	House house2(20,30);
	House house3 = House(30,40);
	//House house4 = 10;

	//拷贝构造
	House house4(house3);
	House house5 = house4;

}
//自定义高级构造函数，就不再提供低级的构造函数
//深拷贝与浅拷贝
//浅拷贝：简单的赋值拷贝操作
//深拷贝：在堆区重新申请空间，进行拷贝操作



//类对象作为类成员
//当类中的成员是其他类对象时，称该成员为 对象成员。
//构造顺序是：先调用对象成员的构造，再调用本类的构造。
//析构顺序是：先调用本类的析构，再调用成员对象的析构。


//静态成员
//静态成员变量：所有对象共享一份数据，在编译阶段分配内存，类内生命 类外初始化
//静态成员你函数：所有对象共享同一份函数，静态成员函数只能访问静态成员变量
class People
{
public:
	int getM_B()
	{
		return m_b;
	}
	void setM_B(int b)
	{
		m_b = b;
	}
	
	static void func()
	{
		cout << "static func " << endl;
		//m_m = 100;	//只能访问静态成员变量
		m_a = 999;
	}

public:
	int m_m;
	static int m_a;
private:
	static int m_b;
};
int People::m_a = 10;
int People::m_b = 20;
void test4()
{
	int tmp = 1000;
	//访问
	People people1;
	people1.m_a = 100;
	
	People people2;
	cout << people2.m_a << endl;

	//People::m_b = 200;
	cout << people1.getM_B() << endl;
	people1.setM_B(tmp);
	cout << people2.getM_B() << endl;

	People::func();
	people1.func();
}
int main(int argc, char **argv)
{
	cout << "***************test1***************" << endl;
	test1();
	cout << "***************test2***************" << endl;
	test2();
	cout << "***************test3***************" << endl;
	test3();
	cout << "***************test4***************" << endl;
	test4();
	return 0;
}
