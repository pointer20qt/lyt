#pragma once
template < class T>

class  L_auto_ptr
{
	T*obj = nullptr;
public:
	L_auto_ptr(T*ptr) :obj(ptr)
	{
	}
	L_auto_ptr() = default;
	//析构方法，释放指针
	~L_auto_ptr()
	{
		delete obj;
	}
	//不标准的复制构造
	L_auto_ptr(L_auto_ptr <T> & ptr):obj(ptr.release())
	{
		/*obj = ptr.obj;
		ptr.obj = nullptr;*/
	}
	//不标准的赋值构造
	L_auto_ptr& operator=(L_auto_ptr<T>& ptr)
	{
		obj = ptr.release();
		/*delete obj;
		obj = ptr.obj;
		ptr.obj = nullptr;*/
		return *this;
	}
	//reset:释放之前的指针，获得新的指针
	void reset(T* newptr=nullptr)
	{
		delete obj;
		ptr = newptr;
	}
	//relese:释放控制权返回指针
	T* release()
	{
		auto temp = obj;
		obj = nullptr;
		return temp;
	}
	//operator->() 模拟指针返回方法
	T* operator->()
	{
		return obj;
	}
	T* get()
	{
		return obj;
	}

};
