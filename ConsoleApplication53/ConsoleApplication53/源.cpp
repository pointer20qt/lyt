
#include "iostream"
#include"memory"
#include"tool.h"
#include"string"
using namespace std;


class tool
{
public:
	int value = 0;
	tool()
	{
		cout << "���캯��" << endl;
	}
	~tool()
	{
		cout << "��������" << endl;
	}
};
void run()
{

	L_auto_ptr<tool>ptr(new tool);
	L_auto_ptr<tool>ptr2(ptr);
	L_auto_ptr<tool>ptr3;
	ptr3 = ptr2;

}
void main()
{
	tool a;
	run();


}

