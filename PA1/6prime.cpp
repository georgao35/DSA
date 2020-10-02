#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char src[3200010];
int all=0, leftId, rightId, Left, Right, Size;

struct Node{
    int pred, succ, sum;
    char value;
    Node() {}
}nodes[7200100];
char tmp[7200100];
//作为第id项的前缀加入
int insertAsPred(char e, int id){
    nodes[all].value = e; nodes[all].succ = id; nodes[all].pred = nodes[id].pred; 
    nodes[nodes[id].pred].succ = all;
    nodes[id].pred = all;
    return all++;
}
void init(){
    all = 2;
    nodes[0].succ = 1; nodes[0].pred = -1; nodes[0].sum = nodes[0].succ+nodes[0].pred;
    nodes[1].pred = 0; nodes[1].succ = -1; nodes[1].sum = nodes[1].succ+nodes[1].pred;
    int l = strlen(src);
    for(int i=0;i<l;i++){
        insertAsPred(src[i],1);
    }
    leftId = 0; rightId = l; Left = nodes[0].succ; Right = 1; Size = l;
}
void show(){
    int now = 0;
    now = nodes[now].succ;
    while(now!=1){
        putchar(nodes[now].value);
        now = nodes[now].succ;
    }
    putchar('\n');
}

void moveRight(){
    char which; //判断左右
    scanf("%c", &which); getchar();
    switch (which)
    {
    case 'L':
        if(Left == 1) puts("F");
        else{
            Left = nodes[Left].succ;
            leftId ++;
            puts("T");
        }
        break;
    case 'R':
        if(Right == 1) puts("F");
        else{
            Right = nodes[Right].succ;
            rightId ++;
            puts("T");
        }
        break;
    default:
        break;
    }
}
void moveLeft(){
    char which; //判断左右
    scanf("%c", &which);
    getchar();
    switch (which)
    {
    case 'L':
        if (leftId == 0) puts("F");
        else{
            Left = nodes[Left].pred;
            leftId--;
            puts("T");
        }
        break;
    case 'R':
        if (rightId == 0) puts("F");
        else{
            Right = nodes[Right].pred;
            rightId--;
            puts("T");
        }
        break;
    default:
        break;
    }
}
void insert(){
    char which, target;
    scanf("%c", &which); getchar();
    scanf("%c", &target); getchar();
    switch (which)
    {
    case 'L':
        insertAsPred(target, Left);
        if (rightId >= leftId)
            rightId++;
        leftId++;
        break;
    case 'R':
        insertAsPred(target, Right);
        if (leftId >= rightId)
            leftId++;
        rightId++;
        break;
    default:
        break;
    }
    puts("T");
}
void reverse(){
    if (leftId >= rightId){ puts("F"); return;}
    int p = Left, q = nodes[Right].pred;
    int count = rightId - leftId;
    for(int i=0;i<count;i++){
        //tmp[i] = nodes[p].value; 
        p = nodes[p].succ;
    }
    puts("T");
}
void del(){
    char which;
    scanf("%c", &which); getchar();
    switch (which){
    case 'L':
        if (Left == 1) puts("F");
        else{
            nodes[nodes[Left].pred].succ = nodes[Left].succ; nodes[nodes[Left].succ].pred = nodes[Left].pred;
            Left = nodes[Left].succ;
            if (rightId == leftId) Right = Left;
            else if (rightId > leftId) rightId--;
            puts("T");
        }
        break;
    case 'R':
        if(Right == 1) puts("F");
        else{
            nodes[nodes[Right].pred].succ = nodes[Right].succ; nodes[nodes[Right].succ].pred = nodes[Right].pred;
            Right = nodes[Right].succ;
            if (rightId == leftId) Left = Right;
            else if (leftId > rightId) leftId--;
            puts("T");
        }
        break;
    default:
        break;
    }
}

int main(){
    scanf("%s", src);
    init(); int n;
    scanf("%d", &n); getchar();
    int count = 0;
    while(n-->0){
        char manip;
        scanf("%c",&manip); getchar();
        switch (manip)
        {
        case '>':
            moveRight();
            break;
        case '<':
            moveLeft();
            break;
        case 'I':
            insert();
            break;
        case 'D':
            del();
            break;
        case 'R':
            reverse();
            break;
        case 'S':
            show();
            break;
        default:
            break;
        }
    }
    return 0;
}
