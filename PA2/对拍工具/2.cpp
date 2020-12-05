#include <cstdio>
#define maxn 500001
#define root 1

struct listNode{
    listNode* nxt,* pre; int id;
    listNode(int id):id(id){}
};
struct node{
    int sum;
    int lc, rc;//向左为0
    node():sum(0),lc(0),rc(0){}
}tree[1048576 + 44*maxn];
struct leaf{
    int sum; listNode* head, *tail;
    leaf(){head = new listNode(-1); tail = new listNode(-1); head->nxt = tail; tail->pre = head;}
}leaves[maxn];

int n,k;
int totalNodes = 1, totalLeaves = 0;
char src[maxn][65];

inline void write(int x){
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

void insert(int now, int tar){//向第now个叶子插入tar
    leaves[now].sum++;
    //插入
    listNode* cur = leaves[now].tail->pre;
    cur->nxt = new listNode(tar); cur->nxt->nxt = leaves[now].tail;
    leaves[now].tail->pre = cur->nxt;
}

void del(int now){//弹出第now个叶子的记录
    leaves[now].sum--; 
    listNode* cur = leaves[now].head->nxt;
    leaves[now].head->nxt = cur->nxt; cur->nxt->pre = leaves[now].head;
    delete cur;
}

void push(int tar){
    int now = root;
    for(int i=0;i<63;i++){
        tree[now].sum++;
        int a = src[tar][i] - '0';
        if(a){
            if(tree[now].rc==0) tree[now].rc = ++totalNodes;
            now = tree[now].rc;
        }else{
            if(tree[now].lc==0) tree[now].lc = ++totalNodes;
            now = tree[now].lc;
        }
    }
    //最后一个
    tree[now].sum++;
    int a = src[tar][63] - '0';
    if(a){
        if(tree[now].rc==0) tree[now].rc = ++totalLeaves;
        now = tree[now].rc;
    }else{
        if(tree[now].lc==0) tree[now].lc = ++totalLeaves;
        now = tree[now].lc;
    }
    insert(now, tar);
}

void pop(int tar){
    int now = root;
    for(int i=0;i<64;i++){
        tree[now].sum--;
        int a = src[tar][i] - '0';
        if(a) now = tree[now].rc;
        else now = tree[now].lc;
    }
    del(now);
}

int query(int tar){//查找tar元件的最大异或
    int now = root;
    for(int i=0;i<63;i++){
        int a = src[tar][i]-'0';
        if(a){
            if(tree[tree[now].lc].sum) now = tree[now].lc;
            else now = tree[now].rc;
        }else{
            if(tree[tree[now].rc].sum) now = tree[now].rc;
            else now = tree[now].lc;
        }
    }
    int a = src[tar][63]-'0';
    if(a){
        if(leaves[tree[now].lc].sum) now = tree[now].lc;
        else now = tree[now].rc;
    }else{
        if(leaves[tree[now].rc].sum) now = tree[now].rc;
        else now = tree[now].lc;
    }
    if(leaves[now].head->nxt->id == tar) return leaves[now].head->nxt->nxt->id;
    else return leaves[now].head->nxt->id;
}

int main(){
    scanf("%d%d", &n, &k);
    for(int i=0;i<n;i++)
        scanf("%s", src[i]);
    int ans = 0;
    for(int i=0;i<=k+1;i++)
        if(i<n) push(i);
        else break;
    for(int i=0;i<n;i++){
        write(query(i)); puts("");
        if(i-k-1 >= 0) pop(i-k-1);
        if(i+k+2 < n) push(i+k+2);
    }
    return 0;
}