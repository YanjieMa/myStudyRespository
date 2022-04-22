#include <iostream>
#include <string>

using namespace std;
//加号运算符重载
class Person
{
public:
	Person()
	{
		
	}
	Person(int a,int b)
	{
		this->m_a = a;
		this->m_b = b;
	}
	Person operator+(const Person &p)
	{
		Person tmp;
		cout << "成员函数实现重载" << endl;
		tmp.m_a = this->m_a + p.m_a;
		tmp.m_b = this->m_b + p.m_b;
		return tmp;
	}

public:
	int m_a;
	int m_b;
};
Person operator+(const Person &p1,const Person &p2)
{
	Person tmp;
	cout << "全局函数实现重载" << endl;
	tmp.m_a = p1.m_a + p2.m_a;
	tmp.m_b = p1.m_b + p2.m_b;
	return tmp;
}
Person operator+(const Person &pp,int val)
{
	Person tmp;
	tmp.m_a = pp.m_a + val;
	tmp.m_b = pp.m_b + val;
	return tmp;
}
void test1()
{
	Person p1(10,20);
	Person p2(100,200);
	Person p3 = p1 + p2;
	cout << "p3.m_a = " << p3.m_a << endl;
	cout << "p3.m_b = " << p3.m_b << endl;
	Person p4 = p3 + 1000;
	cout << "p4.m_a = " << p4.m_a << endl;
	cout << "p4.m_b = " << p4.m_b << endl;
}

//左移运算符的重载
class Home
{
	friend ostream & operator<<(ostream & out,Home p);
	friend istream & operator>>(istream & in ,Home &p);
public:
	Home()
	{
		this->m_a = 0;
		this->m_b = 0;
	}
	Home(int a, int b)
	{
		this->m_a = a;
		this->m_b = b;	
	}
	//前置++
	Home &operator++()
	{
		this->m_a++;
		this->m_b++;
		return *this;
	}
	//后置++
	const Home operator++(int )
	{
		Home tmp = *this;
		++(*this);
		return tmp;	
	}
	//成员函数 实现不了 我么你想要的 <<
private:
	int m_a;
	int m_b;
};
ostream & operator<<(ostream &out, Home p) //注意：在重载了后置++时，不能使用 Home &p
{
	out << "a:" << p.m_a << "\tb:" << p.m_b << "\t";
	return out;
}
void test2()
{
	Home Hm(100,200);
	cout << Hm << "end" << endl;
}

//右移运算符重载
istream &operator>>(istream &in,Home &p)
{
	in >> p.m_a >> p.m_b;
	return in;	
}
void test3()
{
	Home home(1,2);
	cin >> home;
	cout << home << endl;
}
//递增运算符重载
void test4()
{
	Home p(123,456);
	cout << ++p << endl;
	cout << p << endl;
	cout << p++ << endl;
	cout << p << endl;
}

//c++编译器至少给一个类添加4个函数
//	默认构造函数，无参，函数体为空
//	默认析构函数，无参，函数体为空
//	默认拷贝构造函数，对属性进行值拷贝
//	赋值运算符operator+ ， 对属性进行值拷贝

//赋值运算符的重载
class Test
{

public:
	Test(int val)
	{
		m_val = new int(val);	
	}
	
	//重载赋值运算符
	Test &operator=(Test &p)
	{
		if(m_val != NULL){
			delete m_val;
			m_val = NULL;
		}
		m_val = new int(*p.m_val);
		return *this;
	}

	~Test()
	{
		if(m_val != NULL){
			delete m_val;
			m_val = NULL;
		}
	}

	int *m_val;
};
void test5()
{
	Test t1(10);
	Test t2(20);
	Test t3(30);

	t1 = t2 = t3;

	cout << "t1,t2,t3\t" << *t1.m_val	<< *t2.m_val << *t3.m_val << endl;
}
//关系运算符的重载
class People
{
public:
	People(int age, string name)
	{
		this->age = age;
		this->name = name;
	}
	
	bool operator==(People &p)
	{
		if(this->age == p.age && this->name == p.name){
			return true;
		}else{
			return false;
		}
	}
	bool operator!=(People &p)
	{
		if(this->age = p.age && this->name == p.name){
			return false;
		}else{
			return true;
		}
	}
	int age;
	string name;
};
void test6()
{
	People p1(100,"ma");
	People p2(200,"li");

	if(p1 == p2){
		cout << "tong" << endl;
	}else{
		cout << " bu tong" << endl;
	}
}
//仿函数
class Add
{
public:
	int operator()(int a,int b)
	{
		return a+b;
	}
};
class Print
{
public:
	void operator()(string str)
	{
		cout << str << endl;
	}
};
void test7()
{
	Add add;
	int ret = add(10,20);
	cout << ret << endl;

	Print print;
	print("qwer");
	//匿名对象调用
	cout << Add()(100,200) << endl;	
}

int main(int argc, char **argv)
{
	cout << "*********test1**********" << endl;
	test1();	

	cout << "*********test2**********" << endl;
	test2();	

	cout << "*********test3**********" << endl;
	test3();	

	cout << "*********test4**********" << endl;
	test4();	

	cout << "*********test5**********" << endl;
	test5();	

	cout << "*********test6**********" << endl;
	test6();	

	cout << "*********test7**********" << endl;
	test7();	

	return 0;
}
