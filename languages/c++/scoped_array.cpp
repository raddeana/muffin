template<class T>
class ScopedArray
{
public:
      //RAII
      ScopedArray(T* ptr)
           :_ptr(ptr)
      {}

      ~ScopedArray()
      {
           if (_ptr)
           {
                 delete[] _ptr;
           }
      }

      T& operator[](size_t pos)
      {
           return _ptr[pos];
      }

public:
      ScopedArray(const ScopedArray<T>& sp);
      ScopedArray<T> operator=(const ScopedArray<T>& sp);

protected:
      T* _ptr;
};
void TestScopedArray()
{
      ScopedArray<int> sp1(new int[10]);
}
