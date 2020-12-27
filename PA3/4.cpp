#include <cstdio>
#define maxn 1000005

class UnionFind{
    int par[maxn];
    int rank[maxn];
public:
    void init(int size){
        for(int i=1;i<=size;i++){
            par[i] = i; rank[i] = 0;
        }
    }
    int find(int a){
        if(a==par[a]) return a;
        else return par[a] = find(par[a]);
    }
    void merge(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return;
        else if(rank[a]<rank[b]) 
            par[a] = b;
        else{
            par[b] = a;
            if(rank[a] == rank[b]) rank[a]++;
        }
    }
    bool same(int a,int b){
        return find(a)==find(b);
    }
}unionFind;

struct Node{
    int weight;
    Node* pa,* lc, *rc;
    int npl;
    Node(int weight): weight(weight), lc(nullptr), rc(nullptr), npl(1){}
};

template <typename T> void swap(T& a, T& b){
    T tmp = b;
    b = a;
    a = tmp;
}

Node* merge(Node* a, Node* b){//合并左氏堆
    if(!a) return b;
    if(!b) return a;
    if(a->weight > b->weight) swap(a, b);
    (a->rc = merge(a->rc, b)) ->pa = a;
    if(!a->lc or a->lc->npl < a->rc->npl) swap(a->lc, a->rc);
    a->npl = a->rc? 1+a->rc->npl : 1;
    return a;
}

class LeftHeap{
public:
    Node* _root; int _size;
    LeftHeap(): _size(1){}
    int getMin(){
        return _root->weight;
    }
    int delMin(){
        Node* left = _root->lc; if(left) left->pa = nullptr;
        Node* right = _root->rc; if(right) right->pa = nullptr;
        int tmp = _root->weight;  _size--; delete _root;
        _root = merge(left, right);
        return tmp;
    }
}heaps[maxn];

int n, m, k, q;
int weight[maxn];

void merge(int u, int v){//合并联通支
    if(!unionFind.same(u, v)){
        u = unionFind.find(u); v = unionFind.find(v);
        unionFind.merge(u,v);
        if(v == unionFind.find(v))//v没有变,将u记为v
            swap(u,v);
        heaps[u]._root = merge(heaps[u]._root, heaps[v]._root);
        heaps[u]._size += heaps[v]._size;
        while(heaps[u]._size>k)
            heaps[u].delMin();
    }
}

void init(){
    for(int i=1;i<=n;i++){
        heaps[i]._root = new Node(weight[i]);
    }
}

int search(int u){
    u = unionFind.find(u);
    if(heaps[u]._size < k) return -1;
    return heaps[u].getMin();
}

int main(){
    scanf("%d%d%d%d", &n, &m, &k, &q);
    unionFind.init(n);
    for(int i=1;i<=n;i++)
        scanf("%d", weight+i);
    init();
    for(int i=0;i<m;i++){
        int tmp1, tmp2;
        scanf("%d%d", &tmp1, &tmp2);
        merge(tmp1, tmp2);
    }
    while (q--){
        int op;
        scanf("%d", &op);
        if(op == 1){
            int u, v; scanf("%d%d", &u, &v);
            merge(u, v);
        }else{
            int u; scanf("%d", &u);
            printf("%d\n", search(u));
        }
    }
    return 0;
}