#include <iostream>

using namespace std;

//成员变量和成员函数分开存储
class Person
{
public:
	Person(){
		m_a = 0;
	}
	Person(int m_a){
		this->m_a = m_a;
	}
	//this指针的本质是一个指针常量，指针的指向不可修改
	//const修饰成员函数，指针指向的内存空间也不可修改
	//实质为const type *const pointer;	
	Person &personANDperson(Person p){
		this->m_a +=p.m_a;
		return *this;
	}
	
	void shouPerson() const{
		//this->m_a = 100;不可访问
		//this = NULL;	
		this->m_aa = 200;
	}
	
	void showClassName(){
		cout << "i am Person class " << endl;
	}		
	
	void func(){//函数不占对象空间，所有函数共享一个函数实例
		if(this == NULL){
			return ;
		}
		cout << "m_a = " << this->m_a << endl;
	}
	static void static_func(){//静态成员函数不占对象空间
		
	}
public:
	int m_a;//非静态成员变量占对象空间
	mutable int m_aa;
	static int m_b;//静态成员变量占对象空间
};
int Person::m_b = 200;
void test1()
{
	cout << sizeof(Person) << endl;

	Person p1(10);
	p1.personANDperson(p1).personANDperson(p1);
	cout << p1.m_a << endl;

	Person *p2 = NULL;
	p2->showClassName();
	p2->func();
}

//this指针
//this指针指向 被调用成员函数所属的对象
//在类的非静态成员函数中返回对象本身，可以使用 return *this;


//空指针可以访问成员函数 如果用到this指针需要需要加以判断保证代码的健壮性


//const修饰成员函数
//常函数 常函数内不可以修改成员属性，成员属性修改时加关键字mutable则可以修改
//常对象 常对象只能调用常函数

int main(int argc, char ** argv)
{
	cout << "*************test1**************"	<< endl;
	test1();

	return 0;
}
