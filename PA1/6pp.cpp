#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char src[4000000];//源字符串
int all = 0;//所有的结点个数
int cursor[2], cursorId[2], cursorPrev[2];//两个光标的位置（数组索引）、两个光标在字符串中的位置、光标的前缀的位置

struct Node{
    int sum;//储存结点前后结点的数组的索引值之和
    char data;//结点的值
} nodes[8000000];//用于储存所有结点的数组

int getSucc(int pred, int now){
    //返回实际索引为now的结点的后继的实际位置，pred是其前驱的
    return nodes[now].sum-pred;
}
int getPred(int succ, int now){
    //返回实际位置为now的结点的前驱的实际位置
    return nodes[now].sum-succ;
}
int insertAsPred(int now, int pred, char data){
    //作为now的直接前驱、pred的后继进行插入
    nodes[all].sum = now+pred; nodes[all].data = data;
    nodes[pred].sum += all-now;//更改前驱与后继的和
    nodes[now].sum += all-pred;
    return all++;//返回新结点的数组索引值
}

void init(){
    nodes[1].sum = 0; nodes[0].sum = 1;//nodes[1]是起点，nodes[0]是终点，方便初始化
    int l = strlen(src);
    all = 2;
    for(int i=0;i<l;i++){
        insertAsPred(0,1+i,src[i]);
    }
    cursor[0] = 2; cursorId[0] = 0; cursorPrev[0] = 1;
    cursor[1] = 0; cursorId[1] = l; cursorPrev[1] = l+1;
}
void moveRight(){
    char which; //判断左右
    which = getchar(); getchar();
    int tmp = 0;//用来代表是左右光标的变量，以便从数组中直接取出
    if(which == 'R') tmp = 1;
    if(cursor[tmp] == 0) puts("F");
    else{
        int tmp1 = cursor[tmp];
        cursor[tmp] = getSucc(cursorPrev[tmp], cursor[tmp]);//将光标赋予其后缀的值
        cursorPrev[tmp] = tmp1; 
        cursorId[tmp]++;//将光标前缀的位置放到原来光标的位置，并更新光标在字符串中的位置
        puts("T");
    }
}
void moveLeft(){//与moveRight()函数类似
    char which; which = getchar(); getchar();
    int tmp = 0;
    if(which == 'R') tmp = 1;
    if(cursorId[tmp] == 0) puts("F");
    else{
        int tmp1 = cursorPrev[tmp];
        cursorPrev[tmp] = getPred(cursor[tmp], cursorPrev[tmp]);
        cursor[tmp] = tmp1;
        cursorId[tmp]--;
        puts("T");
    }
}
void insert(){
    char which; which = getchar(); getchar();                                   //获取是左右的哪个光标
    char target; target = getchar(); getchar();//获取需要插入的字符
    int tmp = 0;
    if(which == 'R') tmp = 1;
    cursorPrev[tmp] = insertAsPred(cursorPrev[tmp],cursor[tmp], target);//将目标字符插入光标和光标前缀，并将光标前缀放置到新创建的结点上
    //当另一光标在此光标的右侧/重合时，要有相应的操作，包括更改光标在数组中的索引和在字符串中的位置等等
    if(cursor[tmp]==cursor[1-tmp]) cursorPrev[1-tmp] = cursorPrev[tmp];
    if(cursorId[1-tmp]>=cursorId[tmp]) cursorId[1-tmp]++;
    cursorId[tmp]++;
    puts("T");
}
void del(){
    char which; which = getchar(); getchar();
    int tmp = 0; if(which == 'R') tmp = 1;//获取进行操作的是哪个光标
    if(cursor[tmp] == 0) {puts("F"); return;}//如果光标已经在最右侧，将输出F，且不进行操作
    int next = getSucc(cursorPrev[tmp],cursor[tmp]);//删除当前结点
    nodes[next].sum += cursorPrev[tmp]-cursor[tmp];
    nodes[cursorPrev[tmp]].sum += next-cursor[tmp];
    if(cursor[1-tmp]==cursor[tmp]) cursor[1-tmp] = next;//若另一个光标与此光标重合，也要将另一个光标放到下一个结点
    else if(cursorPrev[1-tmp]==cursor[tmp]) cursorPrev[1-tmp] = cursorPrev[tmp];//若另一个光标在此光标的后面，
                                                                                //则要将另一个光标的前缀放到此光标前缀的位置
    if(cursorId[1-tmp]>cursorId[tmp]) cursorId[1-tmp]--;//若另一个光标在后面，则将更改其在字符串中的序号
    cursor[tmp] = next;//将光标放置在下一个结点上
    puts("T");
}
void reverse(){
    if (cursorId[0] >= cursorId[1]){ puts("F"); return; }//通过两光标在字符串中的位置来判断，若左侧光标不在右侧光标的左侧就输出错误
    nodes[cursorPrev[0]].sum += cursorPrev[1]-cursor[0];//更改各个光标和其前缀之间相连的关系：将左侧光标与右侧光标相连，左侧光标前缀与右侧光标前缀相连
    nodes[cursor[1]].sum += cursor[0]-cursorPrev[1];
    nodes[cursor[0]].sum += cursor[1]-cursorPrev[0];
    nodes[cursorPrev[1]].sum += cursorPrev[0]-cursor[1];
    int tmp = cursor[0]; cursor[0] = cursorPrev[1]; cursorPrev[1] = tmp;//将左侧光标与右侧光标前缀进行互换，便实现了反转的操作
    puts("T");
}
void show(){
    int now = nodes[1].sum, prev = 1;
    while(now){//直到当前结点为终点之前，输出当前结点代表的字符值
        putchar(nodes[now].data);
        int succ = getSucc(prev, now);
        prev = now; now = succ;
    }
    puts("");
}

int main(){
    scanf("%s", src);
    init();
    int n;
    scanf("%d", &n); getchar();
    int count = 0;
    while (n-- > 0){
        char manip;
        manip = getchar(); getchar();
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
        #ifndef _OJ_
            show();
        #endif
    }
    return 0;
}
