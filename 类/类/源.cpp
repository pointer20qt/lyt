#include<iostream>
#include<string>

using namespace std;

//���ǳ�Ա�ļ��� ����Ա��������Ա������
//���struct������Ĭ��˽�� structĬ�Ϲ���

class teacher
{
	string name;
public: 
	teacher(string sname)
	{
		this->name = sname;
	}
	~teacher()
	{
		cout << "����������" << endl;
	}
};
class A
{
public:
	void run2(school s)
	{
		s.schoolName = "��С��";
	}
};
class school
{
	friend class A;
	std::string schoolName;//ѧУ��
	std::string schoolType;//ѧУ���Сѧ�����С����У�
	std::string address;//ѧУ��ַ
public:
	teacher * master;

	//��������
    ~school()
	{
		delete master;
		cout << "�����ɹ�" << endl;
	}
//���캯��
	school(std::string schoolName,std::string schoolType,std::string address)
	{
		this->schoolName= schoolName;
		this->schoolType = schoolType;
		this->address = address;
		master = new teacher("������");
		cout << "����ɹ�" << endl;
	}

//Ĭ�Ϲ��칹�캯��(�����г�Ա��������乹�췽��) school() = default;
	school()
	{
		cout << "Ĭ�Ϲ���" << endl;
	}
	//Ĭ�Ͽ�������
	school(const school& p)
	{
		master = new teacher(*p.master);
     cout << "�����˿������캯��" << endl;
	}
	//�ƶ���������
	school(school&& other) :schoolType(other.schoolType), schoolName(other.schoolName), address(other.address)
	{
		cout << "�����ƶ�����" << endl;
		master = other.master;
		other.master = NULL;
	}

	//�ض���
	using EP = void(*)(int, const string &);

 //  �������캯��
	//school(const school& p) :schoolName(p.schoolName), schoolType(p.schoolType), address(p.address)
	//{
	//	cout << "�����˿������캯��" << endl;
	//}

	void schoolOpens()
	{
		cout << this->schoolName << "��ѧ��" << endl;
	 }

 };
void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
//���� 
void swap(school A, school B)
{
	school tmp = A;
	//A = B;
	//B = tmp;
	//��ֵ���� ���쿽��
	/*B = A;
	A = tmp;*/
	
}
void run(){
	school s2("����ʯ�ʹ�ѧ", "��ѧ", "����");
	school s3("��һũ�Ѵ�ѧ", "��ѧ", "����");
	swap(s2, s3);
}
school getschool()
{
	school s2("����ʯ�ʹ�ѧ", "��ѧ", "����");
	return s2;
}


int main()
{
	school s1("����ʯ�ʹ�ѧ", "��ѧ", "����");
	school s2(move(s1));


	//run();

	
	//s2->schoolOpens();
	//delete s2;
	//delete s3;
	
}


//��ʼ����װ����(c����)
/*void initschool(school *sch,string schoolName, string schoolType, string address)
{
sch->schoolName = schoolName;
sch->schoolType = schoolType;
sch->address = address;
}
int main()
{
	school *s1 = (school *)malloc(sizeof(school));
	   initschool(s1,"ָ��������","��ѵ����","����");
}*/

