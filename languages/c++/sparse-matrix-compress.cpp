#include <iostream>
#include <vector>
#include <assert.h>
usingnamespace std;
template<class T>
class SparseMatrix
{
/*三元组 */
	template<class T>
	struct Trituple
	{
		Trituple() /* 给一个默认构造函数 */
		{
		}


		Trituple( size_t row, size_t col, const T & data )
			: _row( row )
			, _col( col )
			, _data( data )
		{
		}


		size_t	_row;
		size_t	_col;
		T	_data;
	};
public:
/* 稀疏矩阵的压缩存储 */
	SparseMatrix()
	{
	}


	SparseMatrix( int* arr, size_t row, size_t col, const T & invalid ) : _row( row ) , _col( col ), _invalid( invalid )
	{
		for ( int i = 0; i < row; i++ )
		{
			for ( int j = 0; j < col; ++j )
			{
				if ( arr[i * col + j] != invalid ) {                                    /* 将有效值存储在一个一维数组中 */
					_sm.push_back( Trituple<T>( i, j, arr[i * col + j] ) );               /* 将三元组的无名对象push进去 */
			  }
      }
		}
	}


/* 访问稀疏矩阵中row行col中的元素 */
	T & Acess( int row, int col )
	{
/* 1、 */


/*for(int idx = 0; idx < _sm.size(); idx++)//遍历一遍
 * {
 * if(_sm[idx]._row == row && _sm[idx]._col == col)//当前行列与我们要访问那个元素行列相同时返回这个有效值
 * return _sm[idx]._data;
 * }
 * return _invalid;*/                                                                                                                                                             /* 否则返回无效值 */
/* 2、 */
		vector<Trituple<T> >::iterator it = _sm.begin();        /* 定义一个迭代器,指向起始位置 */
		while ( it != _sm.end() )                               /* 未到最后一个元素时 */
		{
			if ( it->_row == row && it->_col == col )       /* 行列相等输出值 */
				return(it->_data);
			++it;                                           /* 迭代器向后移动 */
		}
		return(_invalid);
	}


/* 还原稀疏矩阵 */
	template<typename T>
	friend ostream & operator<<( ostream & _cout, SparseMatrix<T> & s ) /* 重载<< */
	{
		size_t idex = 0;
		for ( size_t i = 0; i < s._row; i++ )
		{
			for ( size_t j = 0; j < s._col; j++ )
			{
				if ( idex < s._sm.size() /*防止数组越界*/ && s._sm[idex]._row == i && s._sm[idex]._col == j )
				{
					_cout << s._sm[idex]._data << " ";
					++idex;
				}else
					_cout << s._invalid << " ";
			}
			_cout << endl;
		}
		return(_cout);
	}


/* 实现稀疏矩阵的逆置 时间复杂度O(M*N)(M为元素个数N为矩阵列数) */
	SparseMatrix<T> Transport()
	{
		SparseMatrix<T> sm;
		sm._row		= _col;
		sm._col		= _row;
		sm._invalid	= _invalid;
		for ( size_t i = 0; i < _col; i++ )
		{
			vector<Trituple<T> >::iterator it = _sm.begin();
			while ( it != _sm.end() )
			{
				if ( it->_col == i ) /* 从原矩阵第0列开始，将每列中的有效值依次放入新的稀疏矩阵 */
					sm._sm.push_back( Trituple<T> ( i, it->_row, it->_data ) );
				++it;
			}
		}
		return(sm);
	}


/* 实现稀疏矩阵的快速转置 时间复杂度O(N)+O(M) */
	SparseMatrix<T> FastTransport()
	{
		SparseMatrix<T> sm;
		sm._col		= _row;
		sm._row		= _col;
		sm._invalid	= _invalid;
		sm._sm.resize( _sm.size() );    /* 开辟空间 */
/* 1、统计原矩阵中每一列有多少个有效元素 */
		int* pCount = newint[_col];     /* 开辟原矩阵中列个数的空间 */
		memset( pCount, 0, _col * sizeof(pCount[0]) );
		for ( int i = 0; i < _sm.size(); i++ )
			pCount[_sm[i]._col]++;
/* 2、原矩阵每一列在新矩阵中的起始位值 */
		int* pAddr = newint[_col];
		memset( pAddr, 0, _col * sizeof(pAddr[0]) );
		for ( int i = 1 /*从1开始，第一个位置起始为0已经放入*/; i < _sm.size(); i++ )
		{
			pAddr[i] = pAddr[i - 1] + pCount[i - 1]; /* 前一个起始位值+前一列有效元素个数 */
		}
/* 3、放置元素到新空间 */
		for ( int i = 0; i < _sm.size(); i++ )
		{
			int & addr = pAddr[_sm[i]._col];
			sm._sm[addr] = Trituple<T>( _sm[i]._col, _sm[i]._row, _sm[i]._data );
			addr++;
		}
		return(sm);
	}


/* 实现稀疏矩阵的加法操作1 */
/*SparseMatrix<T> operator+(const SparseMatrix<T>& sp)
 * {
 * int i = 0, j = 0, k = 0;
 * T v;
 * SparseMatrix<T> s;
 * if(this->_col != sp._col || this->_row != sp._row)
 * exit(1);
 * s._row = sp._row;
 * s._col = sp._col;
 * s._invalid = sp._invalid;
 * while(i < this->_sm.size() && j < sp._sm.size())
 * {
 * if(this->_sm[i]._row == sp._sm[j]._row)
 * {
 * if(this->_sm[i]._col < sp._sm[j]._col)
 * {
 * s._sm.push_back(Trituple<T>(this->_sm[i]._row, this->_sm[i]._col, this->_sm[i]._data));
 * i++;
 * k++;
 * }
 * else if(this->_sm[i]._col > sp._sm[j]._col)
 * {
 * s._sm.push_back(Trituple<T>(sp._sm[j]._row, sp._sm[j]._col, sp._sm[j]._data));
 * j++;
 * k++;
 * }
 * else
 * {
 * v = this->_sm[i]._data + sp._sm[j]._data;
 * if(v)
 * {
 * s._sm.push_back(Trituple<T>(sp._sm[j]._row, sp._sm[j]._col, v));
 * k++;
 * }
 * i++;
 * j++;
 * }
 * }
 * else if(this->_sm[i]._row < sp._sm[j]._row)
 * {
 * s._sm.push_back(Trituple<T>(this->_sm[i]._row, this->_sm[i]._col, this->_sm[i]._data));
 * i++;
 * k++;
 * }
 * else
 * {
 * s._sm.push_back(Trituple<T>(sp._sm[j]._row, sp._sm[j]._col, sp._sm[j]._data));
 * j++;
 * k++;
 * }
 * }
 * return s;
 * }*/
/* 实现稀疏矩阵的加法操作2 */
	SparseMatrix<T> operator+( const SparseMatrix<T> & sp )
	{
		assert( _row == sp._row && _col == sp._col );                                           /* 检测两个相加的矩阵行列是否相等 */
		SparseMatrix<T> ret;
		ret._row	= _row;
		ret._col	= _col;
		ret._invalid	= _invalid;
		int iLidx = 0, iRidx = 0;                                                               /* 定义两个索引 */
    
		while ( iLidx < _sm.size() && iRidx < sp._sm.size() )
		{
			size_t	AddrLeft	= _sm[iLidx]._row * _col + _sm[iLidx]._col;                         /* 左边矩阵的起始位值 */
			size_t	AddrRight	= sp._sm[iRidx]._row * sp._col + sp._sm[iRidx]._col;                /* 右边矩阵起始位值 */
			if ( AddrLeft < AddrRight )                                                           /* 左<右，将左边有效值放入和矩阵中，左边的索引加加 */
			{
				ret._sm.push_back( Trituple<T>( _sm[iLidx]._row, _sm[iLidx]._col, _sm[iLidx]._data ) );
				iLidx++;
			}
			elseif( AddrLeft > AddrRight )
			{
				ret._sm.push_back( Trituple<T>( sp._sm[iRidx]._row, sp._sm[iRidx]._col, sp._sm[iRidx]._data ) );
				iRidx++;
			}else  { /* 当左边等于右边判断相加后和是否为0，不为0放入 */
				Trituple<T> temp( _sm[iLidx] );
				temp._data += sp._sm[iRidx]._data;
				if ( temp._data )
				{
					ret._sm.push_back( temp );
					iLidx++;
					iRidx++;
				}
			}
		}
    
		while (iLidx < _sm.size()) /* 左边还有剩余则放入剩余元素 */
		{
			ret._sm.push_back( Trituple<T>( _sm[iLidx]._row, _sm[iLidx]._col, _sm[iLidx]._data ) );
			iLidx++;
		}
    
		while (iRidx < sp._sm.size()) {
			ret._sm.push_back( Trituple<T>( sp._sm[iRidx]._row, sp._sm[iRidx]._col, sp._sm[iRidx]._data ) );
			iRidx++;
		}
		return(ret);
	}


private:
	size_t			_row;
	size_t			_col;
	vector<Trituple<T> >	_sm;
	T			_invalid; /* 无效值 */
};
int main()
{
	int			arr[6][5] = {
		{ 1, 0, 3, 0, 5 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 1, 0, 3, 0, 5 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 }
	};
	int			arr1[6][5] = {
		{ 1, 0, 3, 0, 5 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 2, 4, 0 },
		{ 1, 0, 3, 0, 5 },
		{ 0, 0, 0, 1, 0 },
		{ 0, 0, 0, 0, 1 }
	};
	SparseMatrix<int>	s( (int *) arr, 6, 5, 0 );
	SparseMatrix<int>	s1( (int *) arr1, 6, 5, 0 );
	cout << "访问三行四列元素" << endl;
	cout << s.Acess( 3, 4 ) << endl;
	cout << s << endl;
	cout << "快速转置" << endl;
	cout << s.FastTransport();
	cout << endl;
	cout << "矩阵s：" << endl;
	cout << s << endl;
	cout << "矩阵s1：" << endl;
	cout << s1 << endl;
	cout << "s+s1求和：" << endl;
	cout << s1 + s << endl;
	system( "pause" );
	return(0);
}
