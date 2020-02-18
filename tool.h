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
		//析构方法，释放指针
		~L_auto_ptr()
		{
			delete obj;
		}
		//不标准的拷贝复制构造
		L_auto_ptr(L_auto_ptr <T> & ptr) :obj(ptr.release())
		{
			/*obj = ptr.obj;
			ptr.obj = nullptr;*/
		}
		//不标准的拷贝赋值构造
		L_auto_ptr& operator=(L_auto_ptr<T>& ptr)
		{
			obj = ptr.release();
			/*delete obj;
			obj = ptr.obj;
			ptr.obj = nullptr;*/
			return *this;
		}
		//reset:释放之前的指针，获得新的指针
		void reset(T* newptr)
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
		//模拟指针返回方法
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
		//不使用拷贝构造
		L_unique_ptr(const T&) = delete;

		L_unique_ptr() = default;
		//析构方法，释放指针
		~L_unique_ptr()
		{
			delete obj;
		}
		//不能拷贝赋值
		L_unique_ptr& operator=(const L_unique_ptr<T>&) = delete;
		//不标准的移动复制构造
		L_unique_ptr(L_auto_ptr <T> && ptr) :obj(ptr.release())
		{
			/*obj = ptr.obj;
			ptr.obj = nullptr;*/
		}
		//不标准的移动赋值构造
		L_unique_ptr& operator=(L_auto_ptr<T>&& ptr)
		{
			obj = ptr.release();
			/*delete obj;
			obj = ptr.obj;
			ptr.obj = nullptr;*/
			return *this;
		}
		//reset:释放之前的指针，获得新的指针
		void reset(T* newptr)
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
		//模拟指针返回方法
		T& operator* ()
		{
			return *obj;
		}
	};
	template<class T> class Ref
	{
		//当前资源计数
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
		//获得对应的对象 
		T* get()
		{
			return object;
		}
		//获得计数
		int getcount()
		{
			return r_count;
		}

	};
	//sharedptr需要的方法
	template<class T> class L_sharedptr
	{
		//存储资源计数
		Ref<T>* ref=nullptr;
	public:
		//无参构造
		L_sharedptr() = default;
		//传参构造
		L_sharedptr(T* newp)
		{
			ref = new Ref<T>(newp);
		}
		//拷贝构造
		L_sharedptr(const L_sharedptr & other)
		{
			ref = other.ref;
			if (ref != nullptr)
			{
				ref->increase();
			}
		}
		//移动构造
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
		//拷贝赋值
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
		//交换
		void swap(L_sharedptr & other)
		{
			swap(ref, other.ref);
		}
		//替换指定对象
		void reset(T *target)
		{
			if (ref != nullptr)
			{
				ref->reduce;
			}
			ref = new Ref<T>(target); 
		}
		//销毁对象
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
		//获得裸指针
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
		//返回引用计数
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
		//判断当前是否唯一
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
		//判断当前智能指针是否和对象关联
		operator bool()
		{
			return ref != nullptr;
		}
	};
}
	
