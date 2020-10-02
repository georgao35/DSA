#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 10e6+5;
int n, result[maxn];
int* x;
struct Node{
    Node* pred,* succ; int data;int count;
    Node():count(1){}
};

Node *queapH, *queapT;

void push(int data){
    Node* tmp1 = new Node(); tmp1->data = data;
    Node* p = queapT->pred;
    while(p->data < data and p!=queapH){ 
        tmp1->count += p->count; 
        p = p->pred;
    }
    p->succ = queapT; queapT->pred = p;
    tmp1->succ = queapT; tmp1->pred = queapT->pred;
    queapT->pred->succ = tmp1; queapT->pred = tmp1;
}
void pop(){
    if (queapH->succ->count == 1){
        queapH->succ->succ->pred = queapH;
        Node* p = queapH->succ; 
        queapH->succ = p->succ;
        delete p;
    }else
        queapH->succ->count--;
}

void init(){
    queapH = new Node(); queapT = new Node();
    queapH->succ = queapT; queapT->pred = queapH; queapT->data = 0;
}

void merge(int* data, int i, int mid, int j){
    int* a = data + i; int l1 = mid-i; int l2 = j-mid;
    int* c = data + mid;
    int* b = new int [l1];
    for(int id=0;id<l1;id++) b[id] = a[id];
    int ka=0, kb=0, kc=0;
    while(kb<l1 and kc<l2) a[ka++] = (b[kb]<=c[kc])?b[kb++]:c[kc++];
    while(kb<l1) a[ka++] = b[kb++];
    delete[] b;
}

void sort(int* data, int i, int j){
    if(j-i<2) return;
    int mid = (i+j)>>1;
    sort(data, i, mid);
    sort(data, mid, j);
    merge(data, i, mid, j);
}

int search(int a){
    if(a<result[0])
        return 0;
    if(a>result[n-1])
        return n;
    int i=0,j=n-1;
    while(j-i>4){
        int mid = (i+j)>>1;
        result[mid]<a? i=mid:j=mid;
    }
    while(i<=j && result[i]<a) i++;
    return i;
}

int main(){
    scanf("%d",&n);
    x = new int[n];
    for(int i=0;i<n;++i) scanf("%d", x+i);
    init();
    int current = 0;
    for(int i=0;i<n;++i){
        unsigned int m; int from;
        scanf("%d", &m); from = i-m;//开始计数的序号
        for(;current<from;current++) pop();
        result[i] = queapH->succ->data;
        push(x[i]);
    }
    delete[] x;
    sort(result,0,n);
    int t; scanf("%d", &t);
    unsigned int p,q;
    while(t-->0){
        scanf("%d%d", &p, &q);
        int m = search(p), n = search(q);
        printf("%d %d\n", m, n-m);
    }
    return 0;
}