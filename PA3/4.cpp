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

class LeftHeap{

};

int n, m, k, q;
int weight[maxn];

int search(int u){
    
}

int main(){
    scanf("%d%d%d%d", &n, &m, &k, &q);
    unionFind.init(n);
    for(int i=0;i<n;i++)
        scanf("%d", weight+i);
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
        }else{
            int u; scanf("%d", &u);
            printf("%d\n", search(u));
        }
    }
    
    return 0;
}