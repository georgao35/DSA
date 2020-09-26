#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char src[105];//初始的字符串
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
    Node* insertAsSucc(char e){
        Node* tmp = new Node(e, this, succ);
        succ->pred = tmp; succ = tmp;
        len++;
        return tmp;
    }
};
Node* Left, *Right;
Node* header, *trailer;

void moveRight(){
    char which;//判断左右
    scanf("%c", &which);
    switch (which)
    {
    case 'L':
        if(leftId == len)
            printf("F\n");
        else{
            Left = Left->succ;
            leftId++;
            printf("T\n");
        }
        break;
    case 'R':
        if(rightId == len)
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
    scanf("%c", &which);
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
void insert(){}
void del(){}
void reverse(){}
void show(){}
void init(){
    header = new Node; trailer = new Node;
    header->succ = trailer; header->pred = nullptr;
    trailer->pred = header; trailer->succ = nullptr;
    int l = strlen(src);
    for(int i=0; i<l; ++i){
        trailer->insertAsPred(src[i]);
    }
    Left = header->succ; leftId = 0;
    Right = trailer; rightId = strlen(src); 
}

int main(){
    scanf("%s",src);
    leftId = 0; rightId = strlen(src);
    init();
    int n;
    scanf("%d",&n);
    while(n-- > 0){
        char manip;
        scanf("%c",&manip);
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
}