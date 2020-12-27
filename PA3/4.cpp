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

class LeftHeap{
public:
    Node* _root; int _size;
    LeftHeap(): _size(1){}
    int getMax(){
        return _root->weight;
    }
    int delMax(){

        return _root->weight;
    }
}heaps[maxn];

int n, m, k, q;
int weight[maxn], buffer[maxn];

template <typename T> void swap(T& a, T& b){
    T tmp = b;
    b = a;
    a = tmp;
}

Node* merge(Node* a, Node* b){
    if(!a) return b;
    if(!b) return a;
    if(a->weight < b->weight) swap(a->weight, b->weight);
    (a->rc = merge(a->rc, b)) ->pa = a;
    if(!a->lc or a->lc->npl < a->rc->npl) swap(a->lc, a->rc);
    a->npl = a->rc? 1+a->rc->npl : 1;
    return a;
}

void merge(int u, int v){
    if(!unionFind.same(u, v)){
        u = unionFind.find(u); v = unionFind.find(v);
        unionFind.merge(u,v);
        if(u == unionFind.find(u)){//u没有变
            heaps[u]._root = merge(heaps[u]._root, heaps[v]._root);
        }else{
            heaps[v]._root = merge(heaps[v]._root, heaps[u]._root);
        }
    }
}

void init(){
    for(int i=0;i<n;i++){
        heaps[i]._root = new Node(weight[i]);
    }
}

int search(int u){
    int ans = 0;
    u = unionFind.find(u);
    //如果大小较小
    int i = k;
    while (i--){
        /* code */
    }
    
    return ans;
}

int main(){
    scanf("%d%d%d%d", &n, &m, &k, &q);
    unionFind.init(n);
    for(int i=0;i<n;i++)
        scanf("%d", weight+i);
    init();
    for(int i=0;i<m;i++){
        int tmp1, tmp2;
        scanf("%d%d", &tmp1, &tmp2);
        unionFind.merge(tmp1, tmp2);
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