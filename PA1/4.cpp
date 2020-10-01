#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 20;
int n, x[maxn], result[maxn];
int all = 2;
struct Node{
    int pred, succ; int data;
}nodes[maxn], queap[maxn];

void push(int data){
    nodes[all].data = data; nodes[all].succ = 0; nodes[all].pred = all-1;

    queap[all].data = data; queap[all].succ = 0; queap[all].pred = all-1;
    int j = all-1;
    while(queap[j].data < data){
        queap[j].data = data; j = queap[j].pred;
    }
    all++;
}
int pop(){
    nodes[1].succ = nodes[nodes[1].succ].succ;
    nodes[nodes[1].succ].pred = 1;

    int result = queap[1].data;
    queap[1].succ = queap[queap[1].succ].succ; queap[queap[1].succ].pred = 1;
    return result;
}

void quicksort(int* data, int lo, int hi){
    if(lo<hi){
        int a = data[lo];
        int i = lo, j = hi;
        while(i<j and data[i]<a) i++;
        if(i<j) data[j--] = data[i++];
        while(i<j and data[j]>a) j--;
        if(i<j) data[i++] = data[j--];
        quicksort(data,lo,i);
        quicksort(data,i+1,hi);
    }
}

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;++i) scanf("%d", x+i);
    int current = 0;
    nodes[0].data = 0; nodes[0].pred = 1; nodes[1].succ = 0;
    for(int i=0;i<n;++i){
        int m, from;
        scanf("%d", &m); from = i-m;//开始计数的序号
        for(;current<from;current++) pop();
        result[i] = queap[queap[1].succ].data;
        push(x[i]);
    }
    int t,p,q; scanf("%d", &t);
    while(t-->0){
        scanf("%d%d", &p, &q);

    }
    return 0;
}