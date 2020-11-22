#include <cstdio>
#include <cctype>
typedef long long ll;
#define root 1
#ifdef _OJ_
#define maxm 200005
#else
#define maxm 20
#endif

int n, m, totalNodes = 1;
//const int maxm = 200005;
struct node{
    ll sum;//代表该区间内所有翻过的次数
    ll tag;//代表标记
    int lc, rc;
}tree[31*maxm+1];

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

void push_down(int start, int end, int nodeId){
    int mid = (start+end)>>1;
    if(tree[nodeId].lc==0) tree[nodeId].lc = ++totalNodes;
    if(tree[nodeId].rc==0) tree[nodeId].rc = ++totalNodes;
    tree[tree[nodeId].lc].tag += tree[nodeId].tag;
    tree[tree[nodeId].rc].tag += tree[nodeId].tag;
    tree[tree[nodeId].lc].sum += tree[nodeId].tag*(mid-start+1);
    tree[tree[nodeId].rc].sum += tree[nodeId].tag*(end-mid);
    tree[nodeId].tag = 0;
}
void push_up(int nodeId){
    tree[nodeId].sum = tree[tree[nodeId].lc].sum + tree[tree[nodeId].rc].sum;
}

void flip(int i, int j, int start, int end, int nodeId){
    if(i==start and j==end){
        tree[nodeId].sum += j-i+1;
        tree[nodeId].tag++;
        return;
    }
    push_down(start, end, nodeId);
    int mid = (start+end) >> 1;
    if(i<=mid and j>mid){
        if(tree[nodeId].lc==0) tree[nodeId].lc = ++totalNodes;
        flip(i,mid,start,mid,tree[nodeId].lc);
        if(tree[nodeId].rc==0) tree[nodeId].rc = ++totalNodes;
        flip(mid+1,j,mid+1,end,tree[nodeId].rc);
    }else if(j<=mid){
        if(tree[nodeId].lc==0) tree[nodeId].lc = ++totalNodes;
        flip(i,j,start,mid,tree[nodeId].lc);
    }else{
        if(tree[nodeId].rc==0) tree[nodeId].rc = ++totalNodes;
        flip(i,j,mid+1,end,tree[nodeId].rc);
    }
    push_up(nodeId);
}

ll query(int i, int j, int start, int end, int nodeId){
    if(i==start and j==end) return tree[nodeId].sum;
    ll ans = 0;
    push_down(start, end, nodeId);
    int mid = (start+end) >> 1;
    if(i<=mid and j>mid){
        if(tree[nodeId].lc) ans += query(i,mid,start,mid,tree[nodeId].lc);
        if(tree[nodeId].rc) ans += query(mid+1,j,mid+1,end,tree[nodeId].rc);
    }else if(j<=mid){
        if(tree[nodeId].lc) ans += query(i,j,start,mid,tree[nodeId].lc);
    }else{
        if(tree[nodeId].rc) ans += query(i,j,mid+1,end,tree[nodeId].rc);
    }
    return ans;
}

int main(){
    scanf("%d%d",&n ,&m); getchar();
    char operand;
    while(m--){
        operand = getchar(); getchar();
        int i = read(), j = read();
        if(operand == 'H'){
            flip(i,j,1,n,root);
        }else{
            printf("%lld\n", query(i,j,1,n,root));
        }
    }
    return 0;
}