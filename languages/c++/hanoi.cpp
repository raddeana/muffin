#include <iostream>
using namespace std;

void move(int n, char A, char B, char C);

int step;
int main () {
    int n;
    cout << "请输入block数n:" << endl;
    cin >> n;
    move(n, 'A', 'B', 'C');
    return 0;
}

void move(int n, char A, char B, char C) {
    if (n == 1) {
        step ++;
        cout<< "["<<step<<"] move 1# from "<<A<<" to "<<C<<endl;
    } else {
        move(n - 1, A, C, B);
        cout<< "[" <<step<< "]move " <<n<< "# from " <<A<< " to " <<B<<endl;
        step ++;
        move(n-1, B, A, C);
    }
}
