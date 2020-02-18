#include"stdafx.h"
#include "iostream"
#include"memory"
#include"tool.h"
#include"string"
using namespace std;
using namespace Liu;


class tool
{
public:
	int value = 0;
	tool()
	{
		cout << "构造函数" << endl;
	}
	~tool()
	{
		cout << "析构函数" << endl;
	}
};
void run()
{
	
	L_sharedptr<tool>ptr1(new tool);
	cout << "当前引用计数" << ptr1.use_count() << endl;
	L_sharedptr<tool>ptr2(ptr1);
	L_sharedptr<tool>ptr3;
	ptr3 = ptr2;
	cout << "当前引用计数" << ptr1.use_count() << endl;
	cout << "当前引用计数" << ptr2.use_count() << endl;
	cout << "当前引用计数" << ptr3.use_count() << endl;
	(*ptr2).value;
	ptr2->value;
	ptr2.reset();
}
void main()
{
	run();

}

