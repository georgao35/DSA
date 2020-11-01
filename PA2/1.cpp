#include <cstdio>
#include <iostream>
using namespace std;
#ifndef _OJ_
#define maxn 105
#else
#define maxn 1000005
#endif

struct Node{
    int parent, nextSibling, prevSibling, firstSon;
    int height, scale;
}nodes[maxn];

int n,m,all=0;
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
void updateHeight(int);
void updateSize(int);
void update(int);
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
    if(nodes[nodes[src].parent].firstSon == src){
        nodes[nodes[src].parent].firstSon = nodes[src].nextSibling;
        nodes[nodes[src].nextSibling].prevSibling = 0;
    }else{
        nodes[nodes[src].prevSibling].nextSibling = nodes[src].nextSibling;
        nodes[nodes[src].nextSibling].prevSibling = nodes[src].prevSibling;
    }
    while(parent){  
        nodes[parent].scale -= nodes[src].scale;
        parent = nodes[parent].parent;
    }
    parent = nodes[src].parent; int child = src;
    while(parent){
        int old_height = nodes[parent].height;
        update(parent);
        if(nodes[parent].height == old_height) break;
        parent = nodes[parent].parent;
    }
    nodes[src].parent = 0; nodes[src].prevSibling = 0; nodes[src].nextSibling = 0;
}
//移动以src为根的子树，接到tar的第rank个子树
void moveSub(int src, int tar, int rank){
    nodes[src].parent = tar;
    if(rank == 0){
        nodes[src].nextSibling = nodes[tar].firstSon;
        if(nodes[tar].firstSon) nodes[nodes[tar].firstSon].prevSibling = src;
        nodes[src].prevSibling = 0;
        nodes[tar].firstSon = src;  
    }else{
        int now = getSon(tar, rank-1);
        nodes[src].prevSibling = now;
        nodes[src].nextSibling = nodes[now].nextSibling;
        if(nodes[now].nextSibling) nodes[nodes[src].nextSibling].prevSibling = src;
        nodes[now].nextSibling = src;
    }
    int parent = tar, child = src;
    while(parent){
        nodes[parent].scale += nodes[src].scale;
        if(nodes[child].height>=nodes[parent].height) nodes[parent].height = nodes[child].height + 1;
        child = parent; parent = nodes[parent].parent;
    }
}
//维护树高和规模
int height(int id){
    if(nodes[id].firstSon==0) return nodes[id].height = 0;
    else{
        if(nodes[id].height==0) updateHeight(id);
        return nodes[id].height; 
    }
}
void updateHeight(int id){
    int max = -1; 
    for(int now = nodes[id].firstSon;now;now = nodes[now].nextSibling)
        max = max>height(now)? max:nodes[now].height;
    nodes[id].height = max+1;
}
int size(int id){
    if(nodes[id].firstSon==0) return nodes[id].scale=1;
    else{
        if(nodes[id].scale==0) updateSize(id);
        return nodes[id].scale;
    }
}
void updateSize(int id){
    int scale = 0;
    for(int now = nodes[id].firstSon;now;now = nodes[now].nextSibling)
        scale += size(now);
    nodes[id].scale = scale+1;
}
void update(int id = 1){
    updateHeight(id); updateSize(id);
}

int main(){
    n = read(); m = read();
    for(int i=1;i<=n;i++){
        int size;
        size = read();
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
    update();
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
            printf("%d\n", height(tar));
            break;
        case 2:
            tar = getNode();
            printf("%d\n", size(tar));
            break;
        default:
            break;
        }
    }
    return 0;
}