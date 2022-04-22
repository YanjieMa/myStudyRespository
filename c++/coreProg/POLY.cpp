#include <iostream>

using namespace std;

//多态
//函数重载 和 运算符重载 属于 静态多态		编译阶段确定函数地址
//派生类和虚函数实现运行时多态 属于 动态多态		运行阶段确定函数地址：
//多态满足的条件
//1.有继承关系 2.子类重写父类中的虚函数
class Animal
{
public:
	virtual void speek()
	{
		cout << "animal speek" << endl;
	}
};
class Dog: public Animal
{
public:
	void speek()
	{
		cout << "dog speek" << endl;
	}
};
class Cat: public Animal
{
	void speek()
	{
		cout << "cat speek" << endl;
	}
};
void DoSpeek(Animal &p)
{
	p.speek();
}
void test1()
{
	Animal a;
	Cat cat;
	Dog dog;
	DoSpeek(a);
	DoSpeek(cat);
	DoSpeek(dog);		
}

//纯虚函数和抽象类
class MakeDrink
{
public:
	virtual void boil() = 0;
	virtual void brew() = 0;
	virtual void putCup() = 0;
	virtual void putThing() = 0;
	void makeD()
	{
		boil();
		brew();
		putCup();
		putThing();
	}
};
class MakeCoffee: public MakeDrink
{
public:
	virtual void boil()
	{
		cout << "煮咖啡水" << endl;
	}	
	virtual void brew()
	{
		cout << "冲泡咖啡" << endl;
	}
	virtual void putCup()
	{
		cout << "咖啡倒入杯中" << endl;
	}
	virtual void putThing()
	{
		cout << "加入牛奶" << endl;
	}
};
class MakeTea: public MakeDrink
{
public:
	virtual void boil()
	{
		cout << "煮茶水" << endl;
	}	
	virtual void brew()
	{
		cout << "冲泡茶叶" << endl;
	}
	virtual void putCup()
	{
		cout << "茶水倒入茶杯" << endl;
	}
	virtual void putThing()
	{
		cout << "加入枸杞" << endl;
	}
};

//业务函数
void DoDrink(MakeDrink *md)
{
	md->makeD();
	delete md;
}
void test2()
{
	DoDrink(new MakeCoffee);
	DoDrink(new MakeTea);
}
//虚析构和纯虚析构
//解决通过父类指针去释放，导致字了对象可能清理不干净，造成内存泄露的问题
//先调用Water的构造函数，再调用DrinkWater的构造函数，
//释放时 先调用DrinkWater的析构函数，再调用Water的析构函数
class Water
{
public:
	Water()
	{
		cout << "Water 构造函数调用" << endl;
	}
	virtual void drink() = 0;
	/*virtual ~Water()
	{
		cout << "Water 虚析构函数调用" << endl;
	}*/
	virtual ~Water() = 0;
};
Water::~Water()
{
	cout << "Water 纯虚析构函数调用" << endl;
}
class DrinkWater : public Water
{
public:
	DrinkWater(string name)
	{
		cout << "DrinkWater 构造函数" << endl;
		this->name = new string(name);
	}	
	virtual void drink()
	{
		cout << *name << "在喝水" << endl;
	}
	~DrinkWater()
	{
		cout << "DrinkWater析构函数" << endl;
		if(this->name != NULL){
			delete name;
			name = NULL;
		}
	}
public:
	string *name;
};
void test3()
{
	Water *water = new DrinkWater("Tom");
	water->drink();
	delete water;
}

int main(int argc, char **argv)
{
	test1();
	test2();
	test3();
	return 0;
}
