#include <cstdio>
#include <utility>
#include <cctype>
#define mod 998244353
#define maxn 100005
#define maxm 400005
using namespace std;
typedef long long ll;

inline int read(){
    int s = 0, w = 1;
    char c = getchar();
    while (!isdigit(c)){ 
        w |= c == '-'; c = getchar();
    }
    while (isdigit(c)){
        s = s * 10 + c - '0'; c = getchar();
    }
    return s * w;
}
int m, n, q;
class UnionFind{
    int par[maxn];
public:
    void init(int size){
        for(int i=1;i<=size;i++) par[i] = i;
    }
    int find(int a){
        if(a==par[a]) return a;
        else return par[a] = find(par[a]);
    }
    void merge(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return;
        else par[a] = b;
    }
    bool same(int a,int b){
        return find(a)==find(b);
    }
}unionFind;
template <class T> class Heap{
    T src[maxm];
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
            if(src[a] >= x) break;
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
Heap<pair<ll, int> > heap;
struct Edge{
    int to,cost;
};
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
    void append(const T& src){
        if(_size == _capacity) expand();
        _content[_size++] = src;
    }
    T& operator[](int Rank){
        return _content[Rank];
    }
};

ll dis[maxn], rDis[maxn];//从起点的最短路径和从终点的最短路径
ll num[maxn], rNum[maxn];//从起点的最短路条数和从终点的最短路条数
Vector<Edge> graph[maxn];
int tmp[maxm][3];//临时储存边
void dij(){
    int src = unionFind.find(1);
    heap.push(make_pair(0,src)); num[src] = 1; dis[src] = 0;
    while(!heap.empty()){
        pair<ll, int> now = heap.pop();
        int v = unionFind.find(now.second);
        if(dis[v] < now.first) continue;
        for(int i=0;i<graph[v]._size;i++){
            Edge e = graph[v][i];
            if(dis[e.to] > dis[v]+e.cost){
                dis[e.to] = dis[v]+e.cost;
                num[e.to] = num[v];
                heap.push(make_pair(dis[e.to],e.to));
            }else if(dis[e.to] == dis[v]+e.cost){
                num[e.to] += num[v];
            }
            num[e.to] %= mod;
        }
    }
    src = unionFind.find(n);
    heap.push(make_pair(0,src)); rNum[src] = 1; rDis[src] = 0;
    while(!heap.empty()){
        pair<ll, int> now = heap.pop();
        int v = unionFind.find(now.second);
        if(rDis[v] < now.first) continue;
        for(int i=0;i<graph[v]._size;i++){
            Edge e = graph[v][i];
            if(rDis[e.to] > rDis[v]+e.cost){
                rDis[e.to] = rDis[v]+e.cost;
                rNum[e.to] = rNum[v];
                heap.push(make_pair(rDis[e.to],e.to));
            }else if(rDis[e.to] == rDis[v]+e.cost){
                rNum[e.to] += rNum[v];
            }
            rNum[e.to] %= mod;
        }
    }
}
int main(){
    n = read(); m = read();
    unionFind.init(n);
    for(int i=0;i<m;i++){
        int u,v,c;
        u = read(); v = read(); c = read();
        tmp[i][0] = u; tmp[i][1] = v; tmp[i][2] = c;
        if(c==0) unionFind.merge(u,v);
    }//初始化
    for(int i=0;i<m;i++){
        if(tmp[i][2]==0) continue;
        int u = unionFind.find(tmp[i][0]), v = unionFind.find(tmp[i][1]);
        graph[u].append({v,tmp[i][2]});
        graph[v].append({u,tmp[i][2]});
    }
    for(int i=1;i<=n;i++){ 
        dis[i] = rDis[i] = __LONG_LONG_MAX__;
        num[i] = 0; rNum[i] = 0;
    }
    dij();
    ll lengthOrigin = dis[unionFind.find(n)];
    q = read();
    int u,v,c;
    int last = unionFind.find(n);
    while (q--){
        u = read(); v = read(); c = read();
        u = unionFind.find(u), v = unionFind.find(v);
        if(dis[u]>dis[v]){
            int tmp = v; v = u; u = tmp;
        }
        ll left = dis[u], right = rDis[v];
        if(left+right+c>lengthOrigin) printf("%lld\n", num[last]);
        else if(left+right+c<lengthOrigin) 
            printf("%lld\n", num[u]*rNum[v]%mod);
        else
            printf("%lld\n", (num[last]+num[u]*rNum[v])%mod);
  
    }
    return 0;
}