template<class T>
class ScopedPtr
{
public:
      //RAII
      ScopedPtr(T* ptr)
           :_ptr(ptr)
      {}

      ~ScopedPtr()
      {
           if (_ptr)
           {
                 delete _ptr;
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

public:
      //将拷贝构造和赋值运算符重载声明为私有
      ScopedPtr(const ScopedPtr<T>& sp);
      ScopedPtr<T> operator=(const ScopedPtr<T>& sp);

protected:
      T* _ptr;
};

void TestScopedPtr()
{
      ScopedPtr<int> sp(new int(10));
      ScopedPtr<int> sp1(sp);
}
