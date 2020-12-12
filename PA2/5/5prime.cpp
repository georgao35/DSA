#include <cstdlib>
#include <utility>
#include "temperature.h"
#define maxn 200005
#define root 1
#ifndef _OJ_
#include <iostream>
#include <cstring>
#include <cassert>
#define maxn 25
#endif
using namespace std;

struct xquery{
    int begin, end; int yroot;
}xtree[4*maxn];
struct yquery{
    int max, min;
    int begin, end;
};
struct site{
    int x,y; int t;
}posi[maxn];
pair<int, int> yt[maxn];//初始化y树时的数组
template <class T> class Vector{
public:
    int _size;
    T* _content;
    int _capacity;
    Vector():_size(0),_capacity(2) {
        _content = new T [_capacity];
    }
    void expand(){
        T* old_content = _content;
        _content = new T [2*_capacity];
        for(int i=0;i<_capacity;++i) _content[i] = old_content[i];
        delete [] old_content;
        _capacity *= 2;
    }
    T& operator[](int Rank){
        while(_capacity <= Rank) expand();
        return _content[Rank];
    }
};
Vector<yquery> ytrees[maxn];
int allYtrees=0;
inline int lc(int id){
    return id<<1;
}
inline int rc(int id){
    return (id<<1) | 1;
}
inline int larger(int a, int b){
    return a>b? a:b;
}
inline int smaller(int a, int b){
    return a<b? a:b;
}
inline int smallerT(int t1, int t2){
    if(t1>=0 and t2>=0) return t1>t2? t2:t1;
    if(t1==-1 and t2==-1) return -1;
    else return t1>=0? t1:t2;
}
inline int cmp(const void * a, const void * b){
    int tmpa = ((site *)a)->x, tmpb = ((site *)b)->x;
    return (tmpa>tmpb)-(tmpa<tmpb);
    // if(tmpa > tmpb) return 1;
    // else if(tmpa == tmpb) return 0;
    // else return -1;
}
inline int cmpy(const void * a, const void * b){
    int tmpa = ((pair<int,int> *)a)->first, tmpb = ((pair<int,int> *)b)->first;
    return (tmpa>tmpb)-(tmpa<tmpb);
    // if(tmpa > tmpb) return 1;
    // else if(tmpa == tmpb) return 0;
    // else return -1;
}
pair<int,int> initYQuery(int left, int right, int treeId, int nodeId){
    ytrees[treeId][nodeId].begin = yt[left].first; ytrees[treeId][nodeId].end = yt[right].first;
    if(left == right){
        ytrees[treeId][nodeId].max = ytrees[treeId][nodeId].min = yt[left].second;
        return make_pair(yt[left].second, yt[left].second);
    }
    //递归调用
    int mid = (left+right) >> 1;
    pair<int,int> a = initYQuery(left, mid, treeId, lc(nodeId)),
                  b = initYQuery(mid+1, right, treeId, rc(nodeId));
    ytrees[treeId][nodeId].max = larger(a.first, b.first);
    ytrees[treeId][nodeId].min = a.second+b.second-larger(a.second, b.second);
    return make_pair(ytrees[treeId][nodeId].max, ytrees[treeId][nodeId].min);
}

void initQuery(int left, int right, int nodeId){
    xtree[nodeId].yroot = allYtrees++;
    xtree[nodeId].begin = posi[left].x; xtree[nodeId].end = posi[right].x;
    if(left == right){
        ytrees[xtree[nodeId].yroot][root].max = ytrees[xtree[nodeId].yroot][root].min = posi[left].t;
        ytrees[xtree[nodeId].yroot][root].begin = ytrees[xtree[nodeId].yroot][root].end = posi[left].y;
        return;
    }
    //建立y树
    for(int i=0;i<=right-left;i++){
        yt[i].first = posi[i+left].y; yt[i].second = posi[i+left].t;
    }
    qsort(yt, right-left+1, sizeof(pair<int,int>), cmpy);
    initYQuery(0, right-left, xtree[nodeId].yroot, root);
    //递归调用
    int mid = (left+right)>>1;
    initQuery(left, mid, lc(nodeId)); 
    initQuery(mid+1, right, rc(nodeId));
}

void init(int n, const int *x, const int *y, const int *t){
    //xtree = new xquery[4*n+1];
    for(int i=0;i<n;i++){
        posi[i].x = x[i]; posi[i].y = y[i]; posi[i].t = t[i];
    }
    qsort(posi, n, sizeof(site), cmp);
    initQuery(0, n-1, 1);
}

pair<int,int> queryy(int y1, int y2, int nodeid, int treeid){
    Vector<yquery>& now = ytrees[treeid];
    if(y1<=now[nodeid].begin and y2>=now[nodeid].end)
        return make_pair(now[nodeid].max, now[nodeid].min);
    if(y1>now[nodeid].end or y2<now[nodeid].begin) return make_pair(-1,-1);
    int lcend = now[lc(nodeid)].end, rcbegin = now[rc(nodeid)].begin;
    pair<int,int> left(-1,-1), right(-1,-1);
    if(y1<=lcend) left = queryy(y1, smaller(y2, lcend), lc(nodeid), treeid);
    if(rcbegin<=y2) right = queryy(larger(y1, rcbegin), y2, rc(nodeid), treeid);
    return make_pair(larger(left.first,right.first), smallerT(left.second, right.second));
}

pair<int,int> queryx(int x1, int x2, int y1, int y2, int nodeid){
    if(x1 > xtree[nodeid].end or x2 < xtree[nodeid].begin) return make_pair(-1,-1);
    if(x1 <= xtree[nodeid].begin and x2 >= xtree[nodeid].end){
        return queryy(y1,y2,root,xtree[nodeid].yroot);
    }
    int lcend = xtree[lc(nodeid)].end, rcbegin = xtree[rc(nodeid)].begin;
    pair<int,int> left(-1,-1), right(-1,-1);
    if(x1<=lcend) left = queryx(x1, smaller(x2, lcend), y1, y2, lc(nodeid));
    if(x2>=rcbegin) right = queryx(larger(x1, rcbegin), x2, y1, y2, rc(nodeid));
    return make_pair(larger(left.first, right.first), smallerT(left.second, right.second));
}

void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax){
    pair<int,int> result =  queryx(x1, x2, y1, y2, root);
    *tmax = result.first; *tmin = result.second;
}

#ifndef _OJ_
int main() {
    // in case of defined(NDEBUG), do not write `assert(1 == scanf("%d", &n))'
    int res; // store the return value of `scanf'
    int n;
    res = scanf("%d", &n);
    assert(1 == res);
    assert(1 <= n && n <= 200000);

    // init stations
    int *x = new int[n], *y = new int[n];
    int *t = new int[n];
    for (int i = 0; i < n; i++) {
        long long xi, yi, ti;
        res = scanf("%lld%lld%lld", &xi, &yi, &ti);
        assert(3 == res);
        x[i] = xi;
        y[i] = yi;
        t[i] = ti;
        assert(x[i] == xi && y[i] == yi && t[i] == ti); // check overflow
        assert(t[i] >= 0);
    }
    init(n, x, y, t);

    // after init(), forbid using x, y, and t
    memset(x, 0, n * sizeof(int));
    memset(y, 0, n * sizeof(int));
    memset(t, 0, n * sizeof(int));
    delete[] x;
    delete[] y;
    delete[] t;

    // do query
    long long x1, x2, y1, y2;
    int m = 0;
    while (EOF != (res = scanf("%lld%lld%lld%lld", &x1, &x2, &y1, &y2))) {
        assert(4 == res);
        assert(x1 == (int)x1 && x2 == (int)x2 && y1 == (int)y1 && y2 == (int)y2); // check overflow
        assert(x1 <= x2 && y1 <= y2);
        int tmin, tmax;
        query(x1, x2, y1, y2, &tmin, &tmax);
        printf("%d %d\n", tmin, tmax);
        m++;
    }

    assert(1 <= m && m <= 160000);

    return 0;
}
#endif
