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
	//�����������ͷ�ָ��
	~L_auto_ptr()
	{
		delete obj;
	}
	//����׼�ĸ��ƹ���
	L_auto_ptr(L_auto_ptr <T> & ptr):obj(ptr.release())
	{
		/*obj = ptr.obj;
		ptr.obj = nullptr;*/
	}
	//����׼�ĸ�ֵ����
	L_auto_ptr& operator=(L_auto_ptr<T>& ptr)
	{
		obj = ptr.release();
		/*delete obj;
		obj = ptr.obj;
		ptr.obj = nullptr;*/
		return *this;
	}
	//reset:�ͷ�֮ǰ��ָ�룬����µ�ָ��
	void reset(T* newptr=nullptr)
	{
		delete obj;
		ptr = newptr;
	}
	//relese:�ͷſ���Ȩ����ָ��
	T* release()
	{
		auto temp = obj;
		obj = nullptr;
		return temp;
	}
	//operator->() ģ��ָ�뷵�ط���
	T* operator->()
	{
		return obj;
	}
	T* get()
	{
		return obj;
	}

};
