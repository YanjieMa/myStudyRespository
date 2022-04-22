#include <iostream>

using namespace std;
class Building;


class Goodfunc
{
public:
	Goodfunc();
	void visit();
private:
	Building * building;
};

class Building
{
	friend void goodgay(Building &build);	//全局函数做友元
	friend class Goodclass;					//类做友元
	friend void Goodfunc::visit();			//成员函数做友元
public:
	Building(){
		this->sittingRoom = "binhe sit";
		this->bedRoom = "binhe bed";
	}
public:
	string sittingRoom;
private:
	string bedRoom;
};

//1.全局函数做友元
void goodgay(Building &build)
{
	cout << "see " << build.sittingRoom << endl;
	cout << "see " << build.bedRoom << endl;
}
void test1()
{
	Building build;
	goodgay(build);
}
//2.类做友元
class Goodclass
{
public:
	Goodclass();
	void visit();	
private:
	Building *building;
};

Goodclass::Goodclass()
{
	Goodclass::building = new Building;
}
void Goodclass::visit()
{
	cout << "goodclass see " << Goodclass::building->sittingRoom << endl;
	cout << "goodclass see " << Goodclass::building->bedRoom << endl;
}
void test2()
{
	Goodclass gc;
	gc.visit();
}
//3.成员函数做友元
Goodfunc::Goodfunc()
{
	Goodfunc::building = new Building;	
}
void Goodfunc::visit()
{
	cout << "goodfunc see " << Goodfunc::building->sittingRoom << endl;
	cout << "goodfunc see " << Goodfunc::building->bedRoom << endl;
}
void test3()
{
	Goodfunc gf;
	gf.visit();
}

int main(int argc, char ** argv)
{
	test1();

	cout << "************test2************" << endl;
	test2();

	cout << "************test3************" << endl;
	test3();
	return 0;
}
