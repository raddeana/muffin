template<class T>
class AutoPtr
{
public:
      //构造函数获得资源
      AutoPtr(T* ptr)
           :_ptr(ptr)
           ,_owner(true)
      {}

      //管理权转移
      AutoPtr(AutoPtr<T>& ap)
           :_ptr(ap._ptr)
      {
           ap._owner = false;
           _owner = true;
      }
      AutoPtr<T>& operator=(AutoPtr<T>& ap)
      {
           if (this != &ap)
           {
                 //先释放自己的
                 delete _ptr;
                 _ptr = ap._ptr;
                 ap._owner = false;
                 _owner = true;
           }
           return *this;
      }
      //析构函数清理资源
      ~AutoPtr()
      {
           if (_owner == true)
           {
                 delete _ptr;
                 printf("0X%p\n", _ptr);
           }
      }

      //像指针一样
      T& operator*()
      {
           return *_ptr;
      }

      T* operator->()
      {
           return _ptr;
      }
protected:
      T* _ptr;
      bool _owner;
};
