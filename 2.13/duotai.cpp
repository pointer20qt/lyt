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
		cout << "����ʦ��������" << endl;
	}
};
//ʵ�ֶ�̬ʵ��������ʵ������
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
		cout << schoolName << "���˹��캯��" << endl;
		master = new principal("����ʦ");
	}
	school()
	{
		cout << "����ѧУ�޲ι��캯��" << endl;
	}
	virtual	void schoolOpen()
	{
		cout<< this->schoolName<< "����ѧУ��ѧ��" << endl;
	}
	virtual void schoolOpen(int j)
	{
		for (int i = 0; i < j; i++)
		{
			cout << this->schoolName << "ѧУ��ѧ��" << endl;
		}	
	}
	//�ݹ���ó�Ա����Ŀ������췽����������Ƕ��󣬾͸���
	school(const school &p) :schoolName(p.schoolName), schoolTYpe(p.schoolTYpe), address(p.address)
	{
		//this->a = p.a;
		this->master = new principal(*p.master);
		cout <<schoolName<< "��������˿������캯��" << endl;
	}
	//���Ĭ���ƶ�����Ϳ������칦����ͬ
	school(school&& p) :schoolName(p.schoolName), schoolTYpe(p.schoolTYpe), address(p.address)
	{
		this->master = p.master;
		cout << schoolName << "����������ƶ����캯��" << endl;
		p.master = NULL;
	}
	~school()
	{
		delete master;
		cout << this->schoolName << "ѧУ��������" << endl;		
	}
};
class college : public school
{
	int b;
public:
	college() :school("����ʯ�ʹ�ѧ","��ѧ","����"){
		cout << "���컨���׶�԰��ѧ��" << endl;
	}
	void schoolOpen()
	{
		cout << "���ഺ�ﻨ������԰��ѧ��" << endl;
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