#include <cstdio>
#include <iostream>
using namespace std;
#define maxn 1000005

struct Node{
    int parent, nextSibling, prevSibling, firstSon;
    int height, scale;
}nodes[maxn+5];
struct Stack{
    int data[maxn];
    int _top = 0;
    void clear(){_top = 0;}
    int top(){return data[_top-1];}
    void push(int tar){data[_top++] = tar;}
    void pop(){_top--;}
}s;
bool updated[maxn];

int n,m,all=0;
void updateHeight(int);
void updateSize(int);
void update(int);
inline void write(int x){
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
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
inline int larger(int a, int b){
    return a>b? a:b;
}
//找到parent的第index个孩子
int getSon(int parent, int index){
    int target = nodes[parent].firstSon;
    while(index--){
        target = nodes[target].nextSibling;
    }//注意超过的情况
    return target;
}
//从路径得到结点
int getNode(){
    int num, tmp, base = 1; num = read();
    while(num-- >0){
        tmp = read();
        int a = getSon(base, tmp);
        if(a) base = a;
        else break;
    }
    while(num-- >0) tmp = read();
    return base;
}
//将子树删除
void cut(int src){
    int parent = nodes[src].parent;
    if(nodes[parent].firstSon == src){
        nodes[parent].firstSon = nodes[src].nextSibling;
        nodes[nodes[src].nextSibling].prevSibling = 0;
    }else{
        nodes[nodes[src].prevSibling].nextSibling = nodes[src].nextSibling;
        if(nodes[src].nextSibling) nodes[nodes[src].nextSibling].prevSibling = nodes[src].prevSibling;
    }

    while(parent){  
        nodes[parent].scale -= nodes[src].scale;
        parent = nodes[parent].parent;
    }
    if(nodes[src].prevSibling) updateHeight(nodes[src].prevSibling);
    else updateHeight(nodes[src].parent);
    nodes[src].parent = 0; nodes[src].prevSibling = 0; nodes[src].nextSibling = 0;
}
//移动以src为根的子树，接到tar的第rank个子树
void moveSub(int src, int tar, int rank){
    if(rank){
        int now = getSon(tar, rank-1);
        if(nodes[now].nextSibling) nodes[nodes[now].nextSibling].prevSibling = src;
        nodes[src].nextSibling = nodes[now].nextSibling;
        nodes[src].prevSibling = now;
        nodes[now].nextSibling = src;
    }else if(rank == 0){
        nodes[src].nextSibling = nodes[tar].firstSon;
        if(nodes[tar].firstSon) nodes[nodes[tar].firstSon].prevSibling = src;
        nodes[tar].firstSon = src;
    }
    nodes[src].parent = tar; int parent = tar, child = src;
    updateHeight(src);
    while(parent){
        nodes[parent].scale += nodes[src].scale;
        parent = nodes[parent].parent;
    }
}
//维护树高和规模
void initHeight(int id){
    s.push(1);
    while(s._top){
        int a = s.top();
        if(nodes[a].firstSon==0 and nodes[a].nextSibling==0){ 
            nodes[a].height = 1; s.pop(); continue;
        }else if(nodes[a].firstSon == 0){
            if(nodes[nodes[a].nextSibling].height){ 
                nodes [a].height = nodes[nodes[a].nextSibling].height; s.pop();
            }
            else s.push(nodes[a].nextSibling);
        }else if(nodes[a].nextSibling == 0){
            if(nodes[nodes[a].firstSon].height){
                nodes[a].height = nodes[nodes[a].firstSon].height+1; s.pop();
            }
            else s.push(nodes[a].firstSon);
        }else{
            if(nodes[nodes[a].firstSon].height and nodes[nodes[a].nextSibling].height){
                nodes[a].height = larger(nodes[nodes[a].firstSon].height+1, nodes[nodes[a].nextSibling].height);
                s.pop(); continue;
            }
            if(nodes[nodes[a].firstSon].height==0) s.push(nodes[a].nextSibling);
            if(nodes[nodes[a].nextSibling].height==0) s.push(nodes[a].firstSon);
        }
    }
    s.clear();
}
void updateHeight(int id){
    int now = id;
    while(now){
        nodes[now].height = larger(nodes[nodes[now].firstSon].height+1, nodes[nodes[now].nextSibling].height);
        if(nodes[now].prevSibling == 0) now = nodes[now].parent;
        else now = nodes[now].prevSibling;
    }
}

void initSize(int id){
    s.push(1);
    int now = 0;//作用相当于队列的头，记录应该将谁的儿子推入栈
    while(s._top < n){
        int a = s.data[now];
        int son = nodes[a].firstSon;
        for(;son;son = nodes[son].nextSibling){
            if(updated[son]) continue;
            else{
                s.push(son); updated[son] = true;
            }
        }
        now++;
    }
    while(s._top){
        int a = s.top(); s.pop();
        int son = nodes[a].firstSon; nodes[a].scale = 1;
        for(;son;son = nodes[son].nextSibling)
            nodes[a].scale += nodes[son].scale;
    }
    s.clear();
}

int main(){
    n = read(); m = read();
    for(int i=1;i<=n;i++){
        int size = read();
        if(size){
            int tmp1, tmp2; 
            tmp1 = read(); nodes[tmp1].parent = i; nodes[i].firstSon = tmp1;
            for(int j=1;j<size;j++){
                tmp2 = read();
                nodes[tmp2].prevSibling = tmp1;
                nodes[tmp1].nextSibling = tmp2; nodes[tmp2].parent = i;
                tmp1 = tmp2;
            }
        }
    }
    initHeight(1); 
    initSize(1);
    int command;
    while(m--){
        command = read();
        int src, tar;
        switch (command)
        {
        case 0:
            src = getNode();
            cut(src);
            tar = getNode();
            int rank; rank = read();
            moveSub(src, tar, rank);
            break;
        case 1:
            tar = getNode();
            write(nodes[nodes[tar].firstSon].height); puts("");
            break;
        case 2:
            tar = getNode();
            write(nodes[tar].scale); puts("");
            break;
        default:
            break;
        }
    }
    return 0;
}