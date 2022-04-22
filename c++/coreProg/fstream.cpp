#include <fstream>
#include <string.h>
#include <iostream>
#include <iomanip>
// 打开方式		解释
// ios::in		读方式打开文件
// ios::out		写方式打开
// ios::ate		初始位置在文件末尾
// ios::app		追加方式写文件
// ios::trunc	如果文件存在，先删除，再创建
// ios::binary	二进制方式		
using namespace std;

class Person{
public:
	Person(){};
	Person(string name,int age)
	{
		this->name = name;
		this->age = age;
	}
	
	string name;
	int age;
};

void writeFile()
{
	Person per("mayanjie",28);
	ofstream ofs;
	
	ofs.open("file.txt",ios::out | ios::trunc);
	if(!ofs.is_open()){
		cout << "open file.txt failed." << endl;
		return ;
	}
	ofs << setiosflags(ios::left) << setw(15) <<  "name" << setw(15) << "sex"<< setw(15) << "age" << endl;
	ofs << setiosflags(ios::right) << setw(15) <<  "ma" << setw(15) << "M" << setw(15) << "18" << endl;
	ofs << 'q' << setfill('*') << setw(5) << 'a' << setfill('*') << setw(20) << 'b' << endl;
	long pos = ofs.tellp();
	cout << "写文件的输出流位置为：" <<pos << endl;
	ofs.close();

	//写二级制文件
	ofstream ofs2;
	ofs2.open("file.txt",ios::out | ios::binary | ios::app);
	pos = ofs2.tellp();	
	cout << "写文件的输出流位置为：" <<pos << endl;
	ofs2 << endl;
	ofs2.write((const char *)&per,sizeof(per));

	pos = ofs2.tellp();
	cout << "重定位：写文件的输出流位置为：" << pos << endl;

	ofs2.close(); 
}


void readFile()
{
	ifstream ifs;
	
	ifs.open("file.txt",ios::in);
	if(!ifs.is_open()){
		cout << "open file failed" << endl;
		return ;
	}
	//方法1：	
	//当一个文件读到尾部以后，不能再用seekg移动或者定位
	char read_buf1[4];
	while(ifs >> read_buf1){			// 每次读取以空格分割
		cout << read_buf1 << endl;
	}
	long pos = ifs.tellg();
	cout << "第一次读完:输入流当前位置："<< pos << endl;
	
	ifs.seekg(1,ios::beg);//设置输出流指针到初位置
	
	pos = ifs.tellg();
	cout << "重定位：输入流当前位置："<< pos << endl;
	ifs.close();	

	
	//方法2：
	
	ifstream ifs2("file.txt",ios::in);
	char read_buf2[1024];
	while(ifs2.getline(read_buf2,sizeof(read_buf2))){	//	每次读取以回车分割
		cout << read_buf2 << endl;
	}

	pos = ifs2.tellg();
	cout << "第二次读完：输入流当前位置："<< pos << endl;
	
	ifs2.seekg(0);//设置输出流指针到初位置
	
	pos = ifs2.tellg();
	cout << "重定位：输入流当前位置："<< pos << endl;
	ifs2.close();

	//方法3：
	cout << "third" << endl;
	ifstream ifs3("file.txt",ios::in);
	string read_buf3;
	while(getline(ifs3,read_buf3)){	//	每次读取以回车分割
		cout << read_buf3 << endl;
	}

	ifs3.close();
	
	//二进制读取文件
	cout << "第四次" << endl;
	ifstream ifs4("file.txt",ios::in | ios::binary);
	Person person;
	ifs4.read((char *)&person,sizeof(Person));
	cout << person.name << " " << person.age  << endl;

	ifs4.close();	
}

int main(int argc, char **argv)
{
	writeFile();		
	readFile();	
	return 0;

}
