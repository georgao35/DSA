#include <cstdlib>
#include <utility>
#include "temperature.h"
#define maxn 200005
#ifndef _OJ_
#include <iostream>
#include <cstring>
#include <cassert>
#endif
using namespace std;

struct xquery{
    int begin, end; int yroot;
}xtree[4*maxn];
struct yquery{
    int max, min;
    int begin, end;
}ytree[70*maxn];
int ytnode = 0;
struct site{
    int x,y; int t;
}posi[maxn];
pair<int, int> yt[maxn];//初始化y树时的数组

inline int par(int id){
    return id >> 1;
}
inline int lc(int id){
    return id<<1;
}
inline int lc(int nodeId, int root){
    return root+lc(nodeId-root+1)-1;
}
inline int rc(int id){
    return (id<<1) | 1;
}
inline int rc(int nodeId, int root){
    return root+rc(nodeId-root+1)-1;
}
inline int cmp(const void * a, const void * b){
    int tmpa = ((site *)a)->x, tmpb = ((site *)b)->x;
    return tmpa-tmpb;
    // if(tmpa > tmpb) return 1;
    // else if(tmpa == tmpb) return 0;
    // else return -1;
}
inline int cmpy(const void * a, const void * b){
    int tmpa = ((pair<int,int> *)a)->first, tmpb = ((pair<int,int> *)b)->first;
    return tmpa-tmpb;
    // if(tmpa > tmpb) return 1;
    // else if(tmpa == tmpb) return 0;
    // else return -1;
}
inline int larger(int a, int b){
    return a>b? a:b;
}
inline int smaller(int t1, int t2){//只为温度设计
    if(t1>=0 and t2>=0) return t1>t2? t2:t1;
    if(t1==-1 and t2==-1) return -1;
    else return t1>=0? t1:t2;
}

pair<int,int> initYQuery(int low, int high, int nodeId, int root){
    if(low == high){
        ytree[nodeId].begin = yt[low].first; ytree[nodeId].end = yt[low].first;
        ytree[nodeId].max = ytree[nodeId].min = yt[low].second;
        ytnode = larger(ytnode,nodeId);
        return make_pair(ytree[nodeId].max,ytree[nodeId].max);
    }
    int mid = (low+high) >> 1;
    ytree[nodeId].begin = yt[low].first; ytree[nodeId].end = yt[high].first;
    pair<int,int> left = initYQuery(low, mid, lc(nodeId, root), root),
                    right = initYQuery(mid+1, high, rc(nodeId, root), root);
    ytree[nodeId].min = left.second + right.second - larger(left.second, right.second);
    ytree[nodeId].max = larger(left.first, right.first);
    return make_pair(ytree[nodeId].max, ytree[nodeId].min);
}

void initQuery(int left, int right, int nodeId){
    if(left == right){
        xtree[nodeId].begin = posi[left].x; xtree[nodeId].end = posi[right].x; xtree[nodeId].yroot = ++ytnode;
        ytree[xtree[nodeId].yroot].max = ytree[xtree[nodeId].yroot].min = posi[left].t;
        ytree[xtree[nodeId].yroot].begin = ytree[xtree[nodeId].yroot].end = posi[left].y;
        return;
    }
    //建立y树
    xtree[nodeId].begin = posi[left].x; xtree[nodeId].end = posi[right].x; xtree[nodeId].yroot = ++ytnode;
    for(int i=0;i<=right-left;i++){
        yt[i].first = posi[i+left].y; yt[i].second = posi[i+left].t;
    }
    qsort(yt, right-left+1, sizeof(pair<int,int>), cmpy);
    initYQuery(0, right-left, xtree[nodeId].yroot, xtree[nodeId].yroot);
    //递归调用
    int mid = (left+right) >> 1;
    initQuery(left, mid, lc(nodeId));
    initQuery(mid+1, right, rc(nodeId));
}

void init(int n, const int *x, const int *y, const int *t){
    for(int i=0;i<n;i++){
        posi[i].x = x[i]; posi[i].y = y[i]; posi[i].t = t[i];
    }
    qsort(posi, n, sizeof(site), cmp);
    initQuery(0, n-1, 1);
}

pair<int,int> yquery(int y1, int y2, int nodeId, int root){
    if(y1 <= ytree[nodeId].begin and y2 >= ytree[nodeId].end)
        return make_pair(ytree[nodeId].max, ytree[nodeId].min);
    if(y2 < ytree[nodeId].begin or y1 > ytree[nodeId].end) return make_pair(-1,-1);
    int lcBegin = ytree[lc(nodeId, root)].begin, lcEnd = ytree[lc(nodeId, root)].end,
        rcBegin = ytree[rc(nodeId, root)].begin, rcEnd = ytree[rc(nodeId, root)].end;
    pair<int,int> l(-1,-1), r(-1,-1);
    if(y1<=lcEnd) l = yquery(larger(y1,lcBegin), y2+lcEnd-larger(y2,lcEnd),lc(nodeId,root),root);
    if(rcBegin<=y2) r = yquery(larger(y1,rcBegin), y2+rcEnd-larger(y2,rcEnd), rc(nodeId,root),root);
    return make_pair(larger(l.first,r.first),smaller(l.second,r.second));
}

pair<int,int> xquery(int x1, int x2, int y1, int y2, int nodeId){
    if(x1 <= xtree[nodeId].begin and x2 >= xtree[nodeId].end)
        return yquery(y1, y2, xtree[nodeId].yroot, xtree[nodeId].yroot);
    if(x2 < xtree[nodeId].begin or x1 > xtree[nodeId].end) return make_pair(-1,-1);
    int lcBegin = xtree[lc(nodeId)].begin, lcEnd = xtree[lc(nodeId)].end, 
    rcBegin = xtree[rc(nodeId)].begin, rcEnd = xtree[rc(nodeId)].end;
    pair<int,int> l(-1,-1), r(-1,-1);
    if(x1<=lcEnd) l = xquery(larger(x1,lcBegin), x2+lcEnd-larger(x2,lcEnd), y1, y2, lc(nodeId));
    if(rcBegin<=x2) r = xquery(larger(rcBegin,x1), x2+rcEnd-larger(x2,rcEnd), y1, y2, rc(nodeId));
    return make_pair(larger(l.first,r.first),smaller(l.second,r.second));
}

void query(int x1, int x2, int y1, int y2, int *tmin, int *tmax){
    pair<int,int> a = xquery(x1,x2,y1,y2,1);
    *tmin = a.second; *tmax = a.first;
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
