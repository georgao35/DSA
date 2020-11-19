#include <cstdio>
#ifdef _OJ_
#define maxn 500001
#else
#define maxn 10
#endif
#define root 1

struct listNode{
    listNode* nxt; int id;
};
struct node{
    int sum;
    int lc, rc;//向左为0
    node(int parent):sum(0),lc(0),rc(0){}
}tree[1<<20 + 44*maxn];
struct leaf{
    int sum; listNode* head;
}leaves[maxn];

int n,k;
int totalNodes = 0, totalLeaves = 0;
char src[10][65];

int getAns(int tar){

}

void insert(int now, int tar){//向第now个叶子插入tar这个属性
    leaves[now].sum++;
    
    //插入
}

void del(int now){//删除第now个叶子的记录

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
            now = tree[now].rc;
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
        now = tree[now].rc;
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
    leaves[now].sum--;
    del(now);
}

int main(){
    scanf("%d%d", &n, &k);
    for(int i=0;i<n;i++)
        scanf("%s", src[i]);
    int ans = 0;
    for(int i=1;i<=k+1;i++){
        push(i);
    }
    return 0;
}