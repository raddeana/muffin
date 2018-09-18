template<class T>
class SharedPtr
{
public:
      SharedPtr(T* ptr)
           :_ptr(ptr)
           , _pCount(new int(1))
      {}

      SharedPtr(const SharedPtr<T>& ap)
           :_ptr(ap._ptr)
           , _pCount(ap._pCount)
      {
           ++(*_pCount);
      }

      SharedPtr<T>& operator=(const SharedPtr<T>& ap)
      {
           if (_ptr != ap._ptr)
           {
                 if (--(*_pCount) == 0)
                 {
                      delete _ptr;
                      delete _pCount;
                 }
                 _ptr = ap._ptr;
                 _pCount = ap._pCount;
                 ++(*_pCount);
           }
           return *this;
      }
      ~SharedPtr()
      {
           if (--(*_pCount) == 0)
           {
                 delete _ptr;
                 delete _pCount;
                 cout << "~SharedPtr()" << endl;
           }
      }

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
      int* _pCount;
};


void TestSharedPtr()
{
      SharedPtr<int> sp1(new int(10));
      SharedPtr<int> sp2(sp1);
      sp1 = sp2;
}
