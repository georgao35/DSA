#include <cstdio>
#include <set>
#include <random>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

set<int> all;
const int rangeN = 1000000;
const int rangeX = 8500000;
int updated[rangeX+2] = {false};
default_random_engine e(time(nullptr));
uniform_int_distribution<int> u(0,rangeX);

void splay(){
    puts("1000000");
    int i=0;
    vector<int> fruits;
    for(;i<2*rangeN/3;i++){
        int tmp = u(e);
        while(updated[tmp]) tmp = u(e);
        updated[tmp] = true; fruits.push_back(tmp);
        sort(fruits.begin(), fruits.end());
        //putchar('A'); putchar(' '); printf("%d\n", tmp);
    }
    for(auto j=fruits.begin();j!=fruits.end();j++){
        putchar('A'); putchar(' '); printf("%d\n", *j);
    }
    while(i++ < rangeN){
        putchar('C'); putchar(' '); printf("%d\n", fruits[0]);
    }
}

void avl(){

}

int main(){
    splay();
    return 0;
}