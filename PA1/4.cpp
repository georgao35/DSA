#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

char src[3200005];//初始的字符串
int n, leftId, rightId;

struct Node{
    Node* pred; 
    Node* succ;
    char value;

    Node(){}
    Node(char e, Node* pred, Node* succ):value(e), pred(pred), succ(succ) {}
    Node* insertAsPred(char e){
        Node* tmp = new Node(e, pred, this);
        pred->succ = tmp; pred = tmp;
        return tmp;
    }
    Node* insertAsSucc(char e){
        Node* tmp = new Node(e, this, succ);
        succ->pred = tmp; succ = tmp;
        return tmp;
    }
};
Node* Left, *Right;
Node* header, *trailer;

void moveRight(){}
void moveLeft(){}
void insert(){}
void del(){}
void reverse(){}
void show(){}
void init(){
    header = new Node; trailer = new Node;
    header->succ = trailer; header->pred = nullptr;
    trailer->pred = header; trailer->succ = nullptr;
    int len = strlen(src);
    for(int i=0; i<len; ++i){
        trailer->insertAsPred(src[i]);
    }
    Left = header->succ; leftId = 0;
    Right = trailer; rightId = strlen(src); 
}

int main(){
    scanf("%s",src);
    leftId = 0; rightId = strlen(src);
    init();
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