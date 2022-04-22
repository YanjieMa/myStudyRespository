#include <iostream>
#include <string>

using namespace std;

//1.继承方式 公共 保护 私有
class Parent
{
public:
		//Parent(int a,int b,int c): m_a(a), m_b(b), m_c(c) {} 
	/*	Parent(int a,int b, int c)
		{
			m_a = a;
			m_b = b;
			m_c = c;
		}	*/
public:
	int m_a;
protected:
	int m_b;
private:
	int m_c;
};
class Chid_Pub: public Parent
{
public:
	void func()
	{
		//m_a 公共	m_b 保护 m_c 不可访问
		cout << "chid_pub\t" << m_a << " " << m_b << endl; 
	}
};
class Chid_Pro: protected Parent
{
public:
	void func()
	{
		//m_a 保护	m_b 保护 m_c 不可访问
		cout << "chid_pro\t" << m_a << " " << m_b << endl;
	}
};
class Chid_Pri: private Parent
{
public:
	void func()
	{
		//m_a 私有	m_b 私有	m_c不可访问
		cout << "chid_pri\t" << m_a << " " << m_b << endl;
	}
};
//继承中 先调用父类的构造 再调用子类的构造
//		析构与之相反
void test1()
{
	Chid_Pub c1;
	Chid_Pro c2;
	Chid_Pri c3;
	c1.func();
	c2.func();
	c3.func();

	c1.m_a = 20;//只能访问到公共权限
//	c2.m_a = 100;	//不可访问
//	c3.m_a = 300;	//不可访问
}


//子类和父类出现同名成员时，访问子类成员直接访问，访问父类成员需要加上作用域
//	s.m_a		s.Base::m_a
//访问静态成员和 非静态成员一样 多一种方式
//	s.m_a		s.Base::m_a		Son::m_a	Son::Base::m_a
//	s.func()	s.Base::func()	Son::func()	Son::Basw::m_a

//菱形继承 虚继承
class Animal
{
public:
	int age;
};

class Yang: virtual public Animal 
{
};
class Tuo: virtual public Animal 
{
};
class Yangtuo: public Yang, public Tuo
{

};

void test2()
{
	Yangtuo yt;
	yt.Yang::age = 100;
	yt.Tuo::age = 200;
	
	cout << "yang" << yt.Yang::age << endl;
	cout << "tuo" << yt.Tuo::age << endl;
	cout << "yt" << yt.age << endl;

}

int main(int argc, char **argv)
{
	test1();

	test2();
	return 0;
}
