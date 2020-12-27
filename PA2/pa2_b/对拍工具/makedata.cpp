#include <cstdio>
#include <set>
#include <random>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;

set<int> all;
int rangeN = 1500000;
const int rangeX = 8500000;
int updated[rangeX+2] = {false};
default_random_engine e(time(nullptr));
uniform_int_distribution<int> u(0,rangeX);

void splay2(){
    printf("%d\n", rangeN);
    int i=0;
    vector<int> fruits;
    for(;i<6*rangeN/7;i++){
        int tmp = u(e);
        while(updated[tmp]) tmp = u(e);
        updated[tmp] = true; fruits.push_back(tmp);
        
        //putchar('A'); putchar(' '); printf("%d\n", tmp);
    }
    sort(fruits.begin(), fruits.end());
    for(auto j=fruits.begin();j!=fruits.end();j++){
        putchar('A'); putchar(' '); printf("%d\n", *j);
    }
    int j=0;
    while(i++ < rangeN){
        putchar('C'); putchar(' '); printf("%d\n", fruits[u(e)%fruits.size()]);
    }
}

void splay1(){
    printf("%d\n", rangeN);
    int i=0;
    vector<int> fruits;
    for(;i<6*rangeN/7;i++){
        int tmp = u(e);
        while(updated[tmp]) tmp = u(e);
        updated[tmp] = true; fruits.push_back(tmp);
        
        //putchar('A'); putchar(' '); printf("%d\n", tmp);
    }
    sort(fruits.begin(), fruits.end());
    for(auto j=fruits.begin();j!=fruits.end();j++){
        putchar('A'); putchar(' '); printf("%d\n", *j);
    }
    int j=0;
    while(i++ < rangeN){
        putchar('C'); putchar(' '); printf("%d\n", fruits[i%5]);
    }
}

void avl(){
    rangeN = 1000000;
    printf("%d\n", rangeN);
    int i=0;
    vector<int> fruits;
    for(;i<2*rangeN/3;i++){
        int tmp = u(e);
        while(updated[tmp]) tmp = u(e);
        updated[tmp] = true; fruits.push_back(tmp);
        
        putchar('A'); putchar(' '); printf("%d\n", tmp);
    }
    int j=0;
    while(i++ < rangeN){
        int tmp = u(e);
        switch (u(e)%6){
        case 0:
        case 1:
        case 2:
            while(updated[tmp]) tmp = u(e);
            updated[tmp] = true; fruits.push_back(tmp);
            putchar('A'); putchar(' '); printf("%d\n", tmp);
            break;
        case 3:
            tmp %= fruits.size();
            putchar('B'); putchar(' '); printf("%d\n", fruits[tmp]);
            updated[fruits[tmp]] = false;
            fruits.erase(fruits.begin()+tmp);
            break;
        default:
            tmp %= fruits.size();
            putchar('C'); putchar(' '); printf("%d\n", fruits[tmp]);
            break;
        }        
    }
}

int main(){
    splay1();
    // avl();
    return 0;
}
