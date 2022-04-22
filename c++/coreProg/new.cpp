#include <iostream>

using namespace std;

int * test()
{
	int *p_a = new int(10);
	return p_a;
}

void test2()
{
	int *arr=new int[10];
	
	for(int i=0;i<10;i++){
		arr[i] = i;
	}
	for(int i=0;i<10;i++){
		cout << arr[i] << endl;
	}
	
	delete[] arr;
}

int main(int argc,char **argv)
{
	int *p = test();
	cout << "p=" << p << "*p=" << *p << endl;
	delete p;

	test2();
	return 0;
}
