#include <iostream>
using namespace std;

int main() {
    int i = 0;
    while(i++ != 0) printf("1st loop is running");
    while(++i==1)printf("2nd loop is running");
    printf("no loop");
    return 0;
}

