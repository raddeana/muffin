template<class T>
class AutoPtr {
public:
      //构造函数获得资源
      AutoPtr(T* ptr)
           :_ptr(ptr)
      {}

      //管理权转移
      AutoPtr(AutoPtr<T>& ap)   //参数不能加const
           :_ptr(ap._ptr)
      {
           ap._ptr = NULL;
      }
      AutoPtr<T>& operator=(AutoPtr<T>& ap)
      {
           if (this != &ap)
           {
                 //先释放自己的
                 delete _ptr;
                 _ptr = ap._ptr;
                 ap._ptr = NULL;
           }
           return *this;
      }
      //析构函数清理资源
      ~AutoPtr()
      {
           if (_ptr != NULL)
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
};

void TestAutoPtr () {
      AutoPtr<int> ap1(new int(10));
      AutoPtr<int> ap2(new int(20));
      ap1 = ap2;
}
