#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace std;

char src[3200005], tmp[3200005];//初始的字符串
int leftId, rightId, len;

struct Node{
    Node* pred;
    Node* succ;
    char value;

    Node(){}
    Node(char e, Node* pred, Node* succ):value(e), pred(pred), succ(succ) {}
    Node* insertAsPred(char e){
        Node* tmp = new Node(e, pred, this);
        pred->succ = tmp; pred = tmp;
        len++;
        return tmp;
    }
};
Node* Left, *Right;
Node* header, *trailer;

void moveRight(){
    char which;//判断左右
    //scanf("%c", &which); getchar();
    cin >> which;
    switch (which)
    {
    case 'L':
        if(Left == trailer)
            printf("F\n");
        else{
            Left = Left->succ;
            leftId++;
            printf("T\n");
        }
        break;
    case 'R':
        if(Right == trailer)
            printf("F\n");
        else{
            Right = Right->succ;
            rightId++;
            printf("T\n");
        }
        break;
    default:
        break;
    }
}
void moveLeft(){
    char which;
    //scanf("%c", &which); getchar();
    cin >> which;
    switch (which)
    {
    case 'L':
        if(leftId == 0)
            printf("F\n");
        else{
            Left = Left->pred;
            leftId--;
            printf("T\n");
        }
        break;
    case 'R':
        if(rightId == 0)
            printf("F\n");
        else{
            Right = Right->pred;
            rightId--;
            printf("T\n");
        }
    default:
        break;
    }
}
void insert(){
    char which, target;
    //scanf("%c", &which); getchar();
    cin >> which;
    //scanf("%c", &target); getchar();
    cin >> target;
    switch (which)
    {
    case 'L':
        Left->insertAsPred(target);
        if(rightId >= leftId) rightId++;
        leftId ++;
        break;
    case 'R':
        Right->insertAsPred(target);
        if(leftId >= rightId) leftId++;
        rightId ++;
        break;
    default:
        break;
    }
    printf("T\n");
}
void del(){
    char which;
    //scanf("%c", &which); getchar();
    cin >> which;
    switch (which)
    {
    case 'L':
        if(Left == trailer){
            printf("F\n");
        }else{
            Node* old = Left;
            Left->pred->succ = Left->succ; Left->succ->pred = Left->pred;
            Left = Left->succ; //delete old;
            if(rightId == leftId) Right = Left;
            else if(rightId > leftId) rightId--;
            printf("T\n");
            len--;
        }
        break;
    case 'R':
        if(Right == trailer) printf("F\n");
        else{
            Node* old = Right;
            Right->pred->succ = Right->succ; Right->succ->pred = Right->pred;
            Right = Right->succ; //delete old;
            if(leftId == rightId) Left=Right;
            else if(leftId > rightId) leftId--;
            printf("T\n");
            len--;
        }
        break;
    default:
        break;
    }
}
void reverse(){
    if(leftId>=rightId) printf("F\n");
    else{
        int count = rightId-leftId;
        Node* p = Left;
        for(int i=0;i<count;i++){
            tmp[i] = p->value; p=p->succ;
        }
        p = p->pred;
        for(int i=0;i<count;i++){
            p->value = tmp[i]; p=p->pred;
        }
        printf("T\n");
    }
}
void show(){
    Node* p = header;
    p=p->succ;
    while(p!=trailer){ 
        printf("%c", p->value);
        p=p->succ;
    }/*
    for(int i=0;i<len;i++){
        printf("%c", p->value);
        p=p->succ;
    }*/
    printf("\n");
}
void init(){
    header = new Node; trailer = new Node;
    header->succ = trailer; header->pred = nullptr;
    trailer->pred = header; trailer->succ = nullptr;
    int l = strlen(src);
    for(int i=0; i<l; ++i){
        trailer->insertAsPred(src[i]);
    }
    Left = header->succ; leftId = 0;
    Right = trailer; rightId = l; 
}

int main(){
    //scanf("%s",src);
    cin >> src;
    leftId = 0; rightId = strlen(src);
    init();
    int n;
    //scanf("%d",&n); getchar();
    cin >> n;
    int count = 0;
    while(n-- > 0){
        char manip;
        cin >> manip;
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