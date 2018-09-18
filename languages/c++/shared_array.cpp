template<class T>
class SharedArray
{
public:
      SharedArray(T* ptr)
           :_ptr(ptr)
           , _pCount(new int(1))
      {}

      SharedArray(const SharedArray<T>& sa)
           :_ptr(sa._ptr)
           , _pCount(sa._pCount)
      {}

      SharedArray<T>& operator=(const SharedArray<T>& sa)
      {
           if (_ptr != sa._ptr)
           {
                 if (--(*_pCount) == 0)
                 {
                      delete[] _ptr;
                      delete _pCount;
                 }
                 _ptr = sa._ptr;
                 _pCount = sa._pCount;
                 ++(*_pCount);
           }
           return *this;
      }

      T& operator[](size_t pos)
      {
           return _ptr[pos];
      }

      ~SharedArray()
      {
           if (--(*_pCount) == 0)
           {
                 delete[] _ptr;
                 delete _pCount;
           }
      }
protected:
      T *_ptr;
      int* _pCount;
};
