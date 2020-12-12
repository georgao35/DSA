#include <cstdio>
#include <cctype>
#include <cstdlib>
typedef long long ll;
#define maxm 200005
#define root 1

int n,m,totalLeave;
struct node{
    ll tag, sum; int left, right;
}tree[31*maxm];
char operands[maxm];//记录所有操作的类型
int para[maxm][2];//记录所有操作的参数
int allPara[2*maxm];//用来排序的所有操作参数,在排序后也用作序号到实际点的转换

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
inline int lc(int l){
    return l<<1;
}
inline int rc(int l){
    return l<<1 | 1;
}
inline int cmp(const void * a, const void * b){
    return *(int*)a - *(int*)b;
}
inline void push_down(int nodeId){
    int l = lc(nodeId), r = rc(nodeId);
    tree[l].tag += tree[nodeId].tag; tree[r].tag += tree[nodeId].tag;
    tree[l].sum += tree[nodeId].tag*(tree[l].right-tree[l].left+1);
    tree[r].sum += tree[nodeId].tag*(tree[r].right-tree[r].left+1);
    tree[nodeId].tag = 0;
}
inline void push_up(int nodeId){
    tree[nodeId].sum = tree[lc(nodeId)].sum + tree[rc(nodeId)].sum;
}
void build(int i, int j, int nodeId){
    tree[nodeId].left = i? allPara[i-1] + 1:allPara[0];
    tree[nodeId].right = allPara[j];
    if(i==j){
        if(i and allPara[i]>allPara[i-1]+1){
            tree[lc(nodeId)].left = allPara[i-1]+1; tree[lc(nodeId)].right = allPara[i]-1;
            tree[rc(nodeId)].left = allPara[i]; tree[rc(nodeId)].right = allPara[i];
        }
        return;
    }
    int mid = (i+j) >> 1;
    tree[nodeId].tag = 0; tree[nodeId].sum = 0;
    build(i,mid,lc(nodeId));
    build(mid+1,j,rc(nodeId));
}

void init(){
    //读入所有的操作节点，并排序
    char operand;
    allPara[0] = 1; allPara[2*m+1] = n;
    for(int i=0;i<m;i++){
        operand = getchar(); getchar(); operands[i] = operand;
        int j = read(), k = read();
        para[i][0] = j; para[i][1] = k;
        allPara[i*2+1] = j; allPara[2*i+2] = k;
    }
    qsort(allPara+1, 2*m, sizeof(int), cmp);
    //排序、去重&构建线段树
    int i=0,j=1;
    while(j<=2*m+1){
        if(allPara[j] != allPara[j-1]) allPara[++i] = allPara[j];
        j++;
    }
    totalLeave = i+1;
    build(0,i,root);
}

void flip(int i, int j, int nodeId){
    if(i==tree[nodeId].left and j==tree[nodeId].right){
        tree[nodeId].tag++; tree[nodeId].sum += j-i+1;
        return;
    }
    push_down(nodeId);
    int mid = tree[lc(nodeId)].right;
    if(i<=mid and j>mid){
        flip(i,mid,lc(nodeId));
        flip(mid+1,j,rc(nodeId));
    }else if(j<=mid) flip(i,j,lc(nodeId));
    else flip(i,j,rc(nodeId));
    push_up(nodeId);
}

ll query(int i, int j, int nodeId){
    if(i==tree[nodeId].left and j==tree[nodeId].right) return tree[nodeId].sum;
    ll ans = 0;
    push_down(nodeId);
    int mid = tree[lc(nodeId)].right;
    if(i<=mid and j>mid){
        ans += query(i,mid,lc(nodeId));
        ans += query(mid+1,j,rc(nodeId));
    }else if(j<=mid) ans += query(i,j,lc(nodeId));
    else ans += query(i,j,rc(nodeId));
    return ans;
}

int main(){
    scanf("%d%d",&n ,&m); getchar();
    init();
    for(int i=0;i<m;i++){
        if(operands[i] == 'H'){
            flip(para[i][0], para[i][1], root);
        }else{
            printf("%lld\n", query(para[i][0], para[i][1], root));
        }
    }
    return 0;
}