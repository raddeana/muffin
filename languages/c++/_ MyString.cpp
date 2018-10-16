#include <cstdlib>
#include <iostream>
using namespace std;
 
// 求字符串的长度
int strlen (const char * s) {
	int i = 0;
	for (; s[i]; ++i);

	return i;
}
 
// 拷贝字符串
void strcpy (char * d, const char * s) {
	int i = 0;
	
  for (i = 0; s[i]; ++i) {
		d[i] = s[i];
  }
  
	d[i] = 0;
}
 
// 比较字符串的字典序
int strcmp (const char * s1, const char * s2) {
	for (int i = 0; s1[i] && s2[i]; ++i) {
		if (s1[i] < s2[i]) {
			return -1;
		} else if (s1[i] > s2[i]) {
			return 1;
	  }
  }
  
	return 0;
}
 
// 拼接字符串
void strcat (char * d, const char * s) {
	int len = strlen(d);
	strcpy(d + len, s);
}
 
class MyString {
private:
	char* p;   // 字符串指针 动态分配空间
	int len;   // 字符串长度

public:
	// 字符串构造函数
	MyString (const char* a) {
		len = strlen(a);
		p = new char[len + 1];
    
		strcpy(p, a);
	}
  
  // 无参数构造函数
	MyString () {
		len = 1;
		p = new char[1];
		strcpy(p, "");
	}
  
	// 拷贝构造函数
	MyString (const MyString& a) {
		len = strlen(a.p);
		p = new char[len + 1];
		strcpy(p, a.p);
	}
  
	// 输出运算符重载
	friend ostream& operator << (ostream& o, const MyString& a) {
		o << a.p;
		return o;
	}
  
	// 赋值运算符重载
	MyString& operator = (const MyString& a) {
		if (p == a.p) {
			return *this;
		}
    
		if (p) {
			delete p;
    }

		len = strlen(a.p);
		p = new char[len + 1];
		strcpy(p, a.p);
    
		return *this;
	}
  
	// [] 运算符重载
	char& operator[] (int i) {
		return p[i];
	}

	// 字符串+的重载
	friend MyString operator + (const MyString& a, const MyString& b) {
		int l = b.len + a.len;
		char *c = new char[l + 1];
		strcpy(c, a.p);
		int i;
		int j = 0;
		
    for (i = a.len; i <= l - 1; ++i, ++j) {
			c[i] = b.p[j];
    }
    
		c[i] = 0;
		return MyString(c);
	}
  
	// 字符串+=的重载
	void operator +=(const char *a) {
		// 注意，不能直接拼接的原因是空间不够，需要先删除p
		// 申请一个更大的空间，在拼接
		int i = len;
		char *b = new char[len + 1];
		
    strcpy(b, p);
		delete p;
		
    len = len + strlen(a);
		p = new char[len + 1];
		
    strcpy(p, b);
		int j = 0;
		
    for (; i <= len - 1; i++, j++) {
			p[i] = a[j];
		}
    
		p[i] = 0;
	}
  
	// 比较字典序的重载
	friend bool operator< (const MyString& a, const MyString& b) {
		if (strcmp(b.p, a.p) == 1) {
			return 1;
		}
    
		return 0;
	}
  
	// 比较字典序的重载
	friend bool operator>(const MyString& a, const MyString& b) {
		if (strcmp(a.p, b.p) == 1) {
			return 1;
		}
    
		return 0;
	}
	
  // 比较字典序的重载
	friend bool operator == (const MyString& a, const MyString& b) {
		if (strcmp(a.p, b.p) == 0) {
			return 1;
		}
    
		return 0;
	}
  
	// ()运算符的重载，取出字典字串
	char* operator () (int a, int l) {
		char* c = new char[l + 1];
		int j = 0;
    
		for (int i = a; i<a + l; i++, j++) {
			c[j] = p[i];
		}
    
		c[j] = 0;
		return c;
	}
};
