#include <cstdlib>
#include <iostream>

using namespace std;
int strlen (const char * s) {	
  int i = 0;
	for(; s[i]; ++i);
	return i;
}

void strcpy (char * d, const char * s) {
	int i = 0;
	
  for( i = 0; s[i]; ++i) {
		d[i] = s[i];
  }
  
	d[i] = 0;	
}

int strcmp (const char * s1, const char * s2) {
	for (int i = 0; s1[i] && s2[i] ; ++i) {
		if (s1[i] < s2[i]) {
			return -1;
		} else if (s1[i] > s2[i]) {
			return 1;
    }
	}
  
	return 0;
}

void strcat (char * d, const char * s) {
	int len = strlen(d);
	strcpy(d + len, s);
}

class MyString {}

int CompareString (const void * e1, const void * e2) {
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
  
	if(* s1 < *s2) {
	  return -1;
	} else if(*s1 == *s2) {
	  return 0;
	} else if(*s1 > *s2) {
	  return 1;
  }
}
