#include "kth.h"
#define maxn 500005
#define maxk 2000005

int xprime[maxn], yprime[maxn], zprime[maxn];
int m;
struct Point{
    int x, y, z;
    bool operator<(const Point& b){
        return compare(xprime[x], yprime[y], zprime[z],
                        xprime[b.x], yprime[b.y], zprime[b.z]);
    }
    bool operator<=(const Point& b){
        return 1-compare(xprime[b.x], yprime[b.y], zprime[b.z],
                         xprime[x], yprime[y], zprime[z]);
    }
};
template <class T> class Heap{
    T src[maxk*3];
    int size = 0;
public:
    void push(T x){
        int i = size++;
        while(i>0){
            int par = (i-1)>>1;
            if(src[par] <= x) break;
            src[i] = src[par];
            i = par;
        }
        src[i] = x;
    }
    T pop(){
        //最小值和在树根将要提上来的数
        T ans = src[0], x = src[--size];
        int i = 0;
        while (i*2+1<size){
            int a =i*2+1, b = i*2+2;
            if(b<size and src[b]<src[a]) a = b;
            if(x <= src[a]) break;
            src[i] = src[a];
            i = a;
        }
        src[i] = x;
        return ans;
    }
    T top(){
        return src[0];
    }
    bool empty(){
        return size == 0;
    }
};
Heap<Point> heap;

inline int cmpx(int a, int b){
    return 1-compare(b, 1, 1, a, 1, 1);
}

inline int cmpy(int a, int b){
    return 1-compare(1, b, 1, 1, a, 1);
}

inline int cmpz(int a, int b){
    return 1-compare(1, 1, b, 1, 1, a);
}

void merge(int* data, int i, int mid, int j){
    int (*cmp)(int, int);
    if(data == xprime) cmp = cmpx;
    else if(data == yprime) cmp = cmpy;
    else if(data == zprime) cmp = cmpz;

    int* a = data + i; int l1 = mid-i; int l2 = j-mid;
    int* c = data + mid;
    int* b = new int [l1];
    for(int id=0;id<l1;id++) b[id] = a[id];
    int ka=0, kb=0, kc=0;
    while(kb<l1 and kc<l2) a[ka++] = (cmp(b[kb],c[kc]))?b[kb++]:c[kc++];
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

void init(){
    for(int i=1;i<=m;i++){
        xprime[i] = i; yprime[i] = i; zprime[i] = i;
    }
    sort(xprime, 1, m+1);
    sort(yprime, 1, m+1);
    sort(zprime, 1, m+1);
}

void get_kth(int n, int k, int *x, int *y, int *z){
    m = n;
    init();
    heap.push(Point{1,1,1});
    Point tmp;
    for(int i=0;i<k;++i){
        tmp = heap.pop();
        if(tmp.z < n)
            heap.push(Point{tmp.x, tmp.y, tmp.z+1});
        if(tmp.z == 1){
            if(tmp.y < n)
                heap.push(Point{tmp.x, tmp.y+1, tmp.z});
            if(tmp.y == 1 and tmp.x < n) heap.push(Point{tmp.x+1, tmp.y, tmp.z});
        }
    }
    *x = xprime[tmp.x]; *y = yprime[tmp.y]; *z = zprime[tmp.z];
}
