#include <iostream>
#include <cstdio>
using namespace std;
#define Posi(T) ListNode<T>*
typedef int Rank;
//列表结点，创建了一个双向列表
template <typename T>
struct ListNode{
    T data;
    Posi(T) pred;
    Posi(T) succ;
    //构造函数
    ListNode(){}//头、尾的构造函数
    ListNode(T e, Posi(T) pred = nullptr, Posi(T) succ = nullptr): data(e), pred(pred), succ(succ){}
    //在构造好后构造中间的普通节点
    Posi(T) insertAsPred(const T& e);
    Posi(T) insertAsSucc(const T& e);
    //返回新节点的位置
};
//得益于哨兵元素的存在，所有的结点（包括首、尾）都可以同样的对待
template<typename T>
Posi(T) ListNode<T>::insertAsPred(const T& e){
    Posi(T) x = new ListNode<T> (e, pred, this);
    pred->succ = x; pred = x;
    return x;
}

template <typename T>
Posi(T) ListNode<T>::insertAsSucc(const T& e){
    Posi(T) x = new ListNode<T> (e,this,succ);
    succ->pred = x; succ = x;
    return x;
}

template <class T>
class List{
private:
    int _size;
    Posi(T) header;
    Posi(T) trailer;//头尾两个哨兵
protected:

public:
    void init();//构造列表
    void copyNodes(Posi(T) p, int n);//用已有列表进行初始化，粘贴p以后的n个结点
    int clear();//清除列表中的结点，方便析构，返回删除的结点个数
    ~List<T> ();

    T& operator[](Rank r);
    Posi(T) insertA(Posi(T) p, const T& e);//e作为p的直接后继插入
    Posi(T) insertB(Posi(T) p, const T& e);//e作为p的直接前驱插入
    Posi(T) first();
    T remove(Posi(T));
    Posi(T) find(T const& e, int n, Posi(T) p);//从p结点前n个前驱中查找
    Posi(T) find(T const& e);
};

template <typename T>
void List<T>::init(){
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->pred = nullptr; header->succ = trailer;
    trailer->pred = header; trailer->succ = nullptr;
    _size = 0;
}

template <typename T>
void List<T>::copyNodes(Posi(T)p, int n){
    init();
    while(n-- >0){
        trailer->insertAsPred(p->data);
        p = p->succ;
    }
}

template <typename T>
int List<T>::clear(){
    
}

template <typename T>
T& List<T>::operator[](Rank r){
    if(r>=0 and r<_size){
        Posi(T) node = first();
        while(r-- > 0) node = node->succ;
        return node->data;
    }
    throw "index out of range";
}

template <typename T>
Posi(T) List<T>::insertA(Posi(T) x, const T& e){
    _size++;
    return x->insertAsSucc(e);
}

template <typename T>
Posi(T) List<T>::insertB(Posi(T) x, const T& e){
    _size++;
    return x->insertAsPred(e);
}

template <typename T>
T List<T>::remove(Posi(T) p){
    T tmp = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p; _size--; return tmp;//注意长度的变化以及释放空间
}

template <typename T>
Posi(T) List<T>::find(const T& e, int n, Posi(T) p){//默认
    while(n-- > 0){
        p=p->pred;
        if(e == p->data) return p;//返回了最后一个e
    }
    return nullptr;
}

template <typename T>
Posi(T) List<T>::find(const T& e){
    return find(e,_size,trailer);
}
