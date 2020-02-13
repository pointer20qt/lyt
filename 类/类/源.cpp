#include<iostream>
#include<string>

using namespace std;

//类是成员的集合 （成员方法，成员变量）
//类和struct区别：类默认私有 struct默认公有

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
		cout << "撤销刘德欣" << endl;
	}
};
class A
{
public:
	void run2(school s)
	{
		s.schoolName = "刘小美";
	}
};
class school
{
	friend class A;
	std::string schoolName;//学校名
	std::string schoolType;//学校类别（小学、初中、高中）
	std::string address;//学校地址
public:
	teacher * master;

	//析构函数
    ~school()
	{
		delete master;
		cout << "析构成功" << endl;
	}
//构造函数
	school(std::string schoolName,std::string schoolType,std::string address)
	{
		this->schoolName= schoolName;
		this->schoolType = schoolType;
		this->address = address;
		master = new teacher("刘德欣");
		cout << "构造成功" << endl;
	}

//默认构造构造函数(将所有成员对象调用其构造方法) school() = default;
	school()
	{
		cout << "默认构造" << endl;
	}
	//默认拷贝构造
	school(const school& p)
	{
		master = new teacher(*p.master);
     cout << "调用了拷贝构造函数" << endl;
	}
	//移动拷贝构造
	school(school&& other) :schoolType(other.schoolType), schoolName(other.schoolName), address(other.address)
	{
		cout << "调用移动构造" << endl;
		master = other.master;
		other.master = NULL;
	}

	//重定义
	using EP = void(*)(int, const string &);

 //  拷贝构造函数
	//school(const school& p) :schoolName(p.schoolName), schoolType(p.schoolType), address(p.address)
	//{
	//	cout << "调用了拷贝构造函数" << endl;
	//}

	void schoolOpens()
	{
		cout << this->schoolName << "开学了" << endl;
	 }

 };
void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
//拷贝 
void swap(school A, school B)
{
	school tmp = A;
	//A = B;
	//B = tmp;
	//赋值拷贝 构造拷贝
	/*B = A;
	A = tmp;*/
	
}
void run(){
	school s2("东北石油大学", "大学", "大庆");
	school s3("八一农垦大学", "大学", "大庆");
	swap(s2, s3);
}
school getschool()
{
	school s2("东北石油大学", "大学", "大庆");
	return s2;
}


int main()
{
	school s1("东北石油大学", "大学", "大庆");
	school s2(move(s1));


	//run();

	
	//s2->schoolOpens();
	//delete s2;
	//delete s3;
	
}


//初始化封装函数(c语言)
/*void initschool(school *sch,string schoolName, string schoolType, string address)
{
sch->schoolName = schoolName;
sch->schoolType = schoolType;
sch->address = address;
}
int main()
{
	school *s1 = (school *)malloc(sizeof(school));
	   initschool(s1,"指针大庆分针","培训机构","大庆");
}*/

