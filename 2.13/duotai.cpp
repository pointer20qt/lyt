#include <iostream>
#include <string>
using  namespace std;
using  I = int;
typedef void(*F) (int, const std::string &);
using F = void(*)(int, const std::string &);

class principal
{
	string name;
public:
	principal(string sname)
	{
		this->name = sname;
	}
	~principal()
	{
		cout << "杨老师被析构了" << endl;
	}
};
//实现多态实现虚析构实现隐藏
class school
{
protected:
	string schoolName;
	string address;
	string schoolTYpe;
public:

	principal *master;
	school(string schoolName, string schoolTYpe, string address){
		this->schoolName = schoolName;
		this->schoolTYpe = schoolTYpe;
		this->address = address;
		cout << schoolName << "走了构造函数" << endl;
		master = new principal("杨老师");
	}
	school()
	{
		cout << "父类学校无参构造函数" << endl;
	}
	virtual	void schoolOpen()
	{
		cout<< this->schoolName<< "父类学校开学了" << endl;
	}
	virtual void schoolOpen(int j)
	{
		for (int i = 0; i < j; i++)
		{
			cout << this->schoolName << "学校开学了" << endl;
		}	
	}
	//递归调用成员对象的拷贝构造方法，如果不是对象，就复制
	school(const school &p) :schoolName(p.schoolName), schoolTYpe(p.schoolTYpe), address(p.address)
	{
		//this->a = p.a;
		this->master = new principal(*p.master);
		cout <<schoolName<< "父类调用了拷贝构造函数" << endl;
	}
	//类的默认移动构造和拷贝构造功能相同
	school(school&& p) :schoolName(p.schoolName), schoolTYpe(p.schoolTYpe), address(p.address)
	{
		this->master = p.master;
		cout << schoolName << "父类调用了移动构造函数" << endl;
		p.master = NULL;
	}
	~school()
	{
		delete master;
		cout << this->schoolName << "学校析构函数" << endl;		
	}
};
class college : public school
{
	int b;
public:
	college() :school("东北石油大学","大学","大庆"){
		cout << "春天花花幼儿园开学了" << endl;
	}
	void schoolOpen()
	{
		cout << "子类春田花花幼稚园开学了" << endl;
	}
};
void printSchool(school * s)
{
	s->schoolOpen();
}
int main()
{
	college *c=new college();
	school *s =c;
	printSchool(c);
	printSchool(s);
	//c->schoolOpen(2);
	system("pause");
}
/*class complex
{
	int real;
	int vir;
public:
	complex(int real,int vir):real(real),vir(vir){
}
	complex operator+(complex & x)
	{
		real += x.real;
		vir += x.vir;
		return complex(real,vir);
	}
	std::string toString()
	{
		char buff[50];
		sprintf(buff,"(%d+%di)",real,vir);
		return string(buff);
	}
};   */  