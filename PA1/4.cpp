#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 10e6+5;
int n, result[maxn];//n是总共的天数，result数组是
int* x;//记录每天新增病例的个数的数组
struct Node{
    Node* pred,* succ; int data;int count;
    Node():count(1){}
};
//利用queap的数据结构，用来记录下当前天的所求最大
Node *queapH, *queapT;
//快速读入函数
inline unsigned int read(){
    unsigned int s = 0, w = 1;
    char c = getchar();
    while (!isdigit(c)){ 
        w |= c == '-'; c = getchar();
    }
    while (isdigit(c)){
        s = s * 10 + c - '0'; c = getchar();
    }
    return s * w;
}
//输出函数
inline void write(int x){
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
//将最新一天的确诊数据加入到queap中
void push(int data){
    Node* tmp1 = new Node(); tmp1->data = data;
    Node* p = queapT->pred;
    while(p->data < data and p!=queapH){ 
        tmp1->count += p->count; 
        p = p->pred;
    }
    p->succ = tmp1; tmp1->pred = p; queapT->pred = tmp1; tmp1->succ = queapT;
}
//弹出队列前面的最大值，采用类似于智能指针的计数方法，当count为0后删除当前结点
void pop(){
    if (queapH->succ->count == 1){
        queapH->succ->succ->pred = queapH;
        Node* p = queapH->succ; 
        queapH->succ = p->succ;
        delete p;
    }else
        queapH->succ->count--;
}
//初始化队列
void init(){
    queapH = new Node(); queapT = new Node();
    queapH->succ = queapT; queapT->pred = queapH; queapT->data = 0;
}
//归并排序所用的归并
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
//归并排序算法，将所有天数的数值进行排序，便于计算个数
void sort(int* data, int i, int j){
    if(j-i<2) return;
    int mid = (i+j)>>1;
    sort(data, i, mid);
    sort(data, mid, j);
    merge(data, i, mid, j);
}
//利用而二分查找查找a的位置，a的位置加一便代表了所有天中数值小于a的个数
int search(unsigned int a){
    if(a<result[0])
        return 0;
    if(result[n-1]<a)
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
    for(int i=0;i<n;++i) x[i] = read();
    init();
    int current = 0;
    for(int i=0;i<n;++i){
        unsigned int m; int from;
        m=read();
        if(i>m) from = i-m;
        else from = 0;//确定当前天所考虑到的最早的天
        for(;current<from;current++) pop();//将最早的天之前的数据弹出
        result[i] = queapH->succ->data;//获取该天的数值
        push(x[i]);//将该天的确诊数据加入到queap中
    }
    delete[] x;
    sort(result,0,n);
    int t; scanf("%d", &t);
    unsigned int p,q;
    while(t-->0){
        p = read(); q = read();
        int m = search(p), n = search(q);
        write(m); putchar(' '); write(n-m); putchar('\n');
    }
    return 0;
}