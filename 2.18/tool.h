#pragma once
#include"string"
#include<iostream>

namespace Liu
{
	template <class T> class  L_auto_ptr
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
		//����׼�Ŀ������ƹ���
		L_auto_ptr(L_auto_ptr <T> & ptr) :obj(ptr.release())
		{
			/*obj = ptr.obj;
			ptr.obj = nullptr;*/
		}
		//����׼�Ŀ�����ֵ����
		L_auto_ptr& operator=(L_auto_ptr<T>& ptr)
		{
			obj = ptr.release();
			/*delete obj;
			obj = ptr.obj;
			ptr.obj = nullptr;*/
			return *this;
		}
		//reset:�ͷ�֮ǰ��ָ�룬����µ�ָ��
		void reset(T* newptr)
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
		//ģ��ָ�뷵�ط���
		T& operator* ()
		{
			return *obj;
		}
	};
	template <class T> class  L_unique_ptr
	{
		T*obj = nullptr;
	public:
		L_unique_ptr(T*ptr) :obj(ptr)
		{
		}
		//��ʹ�ÿ�������
		L_unique_ptr(const T&) = delete;

		L_unique_ptr() = default;
		//�����������ͷ�ָ��
		~L_unique_ptr()
		{
			delete obj;
		}
		//���ܿ�����ֵ
		L_unique_ptr& operator=(const L_unique_ptr<T>&) = delete;
		//����׼���ƶ����ƹ���
		L_unique_ptr(L_auto_ptr <T> && ptr) :obj(ptr.release())
		{
			/*obj = ptr.obj;
			ptr.obj = nullptr;*/
		}
		//����׼���ƶ���ֵ����
		L_unique_ptr& operator=(L_auto_ptr<T>&& ptr)
		{
			obj = ptr.release();
			/*delete obj;
			obj = ptr.obj;
			ptr.obj = nullptr;*/
			return *this;
		}
		//reset:�ͷ�֮ǰ��ָ�룬����µ�ָ��
		void reset(T* newptr)
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
		//ģ��ָ�뷵�ط���
		T& operator* ()
		{
			return *obj;
		}
	};
	template<class T> class Ref
	{
		//��ǰ��Դ����
		int r_count=0;
		T* object=nullptr;
	public:
		Ref(T* target) :object(target)
		{
			++r_count;
		}
		inline void increase()
		{
			r_count++;
		}
		inline void reduce()
		{
			r_count--;
			if (r_count == 0)
			{
				delete object;
				delete this;
			}
		}
		//��ö�Ӧ�Ķ��� 
		T* get()
		{
			return object;
		}
		//��ü���
		int getcount()
		{
			return r_count;
		}

	};
	//sharedptr��Ҫ�ķ���
	template<class T> class L_sharedptr
	{
		//�洢��Դ����
		Ref<T>* ref=nullptr;
	public:
		//�޲ι���
		L_sharedptr() = default;
		//���ι���
		L_sharedptr(T* newp)
		{
			ref = new Ref<T>(newp);
		}
		//��������
		L_sharedptr(const L_sharedptr & other)
		{
			ref = other.ref;
			if (ref != nullptr)
			{
				ref->increase();
			}
		}
		//�ƶ�����
		L_sharedptr( L_sharedptr && other)
		{
			swap(ref, other.ref);
		}
		~L_sharedptr()
		{
			if (ref != nullptr)
			{
				ref->reduce();
			}
		}
		//������ֵ
		L_sharedptr& operator=(const L_sharedptr & other)
		{
			if (ref != nullptr)
			{
				ref->reduce();
			}
			ref = other.ref;
			if (ref != nullptr)
			{
				ref->increase();
			}
			return *this;
		}
		L_sharedptr& operator = (L_sharedptr && other)
		{
			if (ref != nullptr)
			{
				ref->reduce();
			}
			ref = other.ref;
			other.ref = nullptr;
			return *this;
		}
		//����
		void swap(L_sharedptr & other)
		{
			swap(ref, other.ref);
		}
		//�滻ָ������
		void reset(T *target)
		{
			if (ref != nullptr)
			{
				ref->reduce;
			}
			ref = new Ref<T>(target); 
		}
		//���ٶ���
		void reset()
		{
			if (ref != nullptr)
			{
				ref->reduce();
			}
			ref = nullptr;
		}
		//operatoe*() operator->()
		T& operator* ()
		{
			if (ref != nullptr)
			{
				return *ref->get();
			}
			else
			{
				return *(T*)nullptr;
			}
		}
		T * operator-> ()
		{
			if (ref != nullptr)
			{
				return ref->get();
			}
			else
			{
				return (T*)nullptr;
			}
		}
		//�����ָ��
		T* get()
		{
			if (ref != nullptr)
			{
				return ref->get();
			}
			else
			{
				return (T*)nullptr;
			}	
		
		}
		//�������ü���
		int use_count()
		{
			if (ref != nullptr)
			{
				return ref->getcount();
			}
			else
			{
				return 0;
			}
		}
		//�жϵ�ǰ�Ƿ�Ψһ
		bool unique()
		{
			if (ref != nullptr)
			{
				return ref->getcount()==1;
			}
			else
			{
				return false;
			}
		}
		//�жϵ�ǰ����ָ���Ƿ�Ͷ������
		operator bool()
		{
			return ref != nullptr;
		}
	};
}
	
