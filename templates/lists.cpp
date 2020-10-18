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
    int clear();//清除列表中的结点，方便析构，返回删除的结点个数(即原来的长度)
    ~List<T> ();

    T& operator[](Rank r);
    Posi(T) insertA(Posi(T) p, const T& e);//e作为p的直接后继插入
    Posi(T) insertB(Posi(T) p, const T& e);//e作为p的直接前驱插入
    Posi(T) first();
    T remove(Posi(T));
    Posi(T) find(T const& e, int n, Posi(T) p);//从p结点的n个前驱中查找
    Posi(T) find(T const& e);
    int deduplicate();//无序列表的去重操作，算法与无序向量的相同
    template <class FUN> void traverse(FUN func);//遍历
    int uniquify();//有序列表的去重操作，与向量类似，但稍有不同的是列表无法高效随机访问，因此采用从前到后的方法

    void mergeSort(Posi(T) p, int n);//对起始于p的n个元素进行排序
    void merge(Posi(T) p, int n, List<T>& l, Posi(T) q, int m);//将p开始的n个元素与l列表中q开始的m个元素进行归并
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
    int old_size = _size;
    while(0<_size)//可否删除最后一个结点？
        remove(header->succ);
    return old_size;
}

template <typename T>
List<T>::~List<T>(){
    clear();
    delete header;
    delete trailer;
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
        if(e == (p=p->pred)->data) return p;//返回了最后一个e
    }
    return nullptr;
}

template <typename T>
Posi(T) List<T>::find(const T& e){
    return find(e,_size,trailer);
}

template <typename T>
int List<T>::deduplicate(){
    int old_size = _size;
    Posi(T) p = first();
    for(Rank r = 0; p!=trailer; p=p->succ){
        if(Posi(T) q = find(p->data, r, p)) remove(q);
        else r++;//记录前面有多少个不重复的结点
    }
    return old_size-_size;
}

template <typename T> template <class FUN>
void List<T>::traverse(FUN func){
    Posi(T) p = header;
    while ((p=p->succ)!=trailer){
        func(p);
    }
}

template <typename T>
int List<T>::uniquify(){
    if(_size<2) return 0;
    int old_size = _size;//记录原来的规模
    Posi(T) p = first(), q;//从区间的开始进行查找，也是一种可以遍历整个列表的方法
    while((q=p->succ)!=trailer){//不断考察相邻的两个结点，这种高级语法
        if(p->data==q->data) remove(q);//由于向量无法做到高效的寻秩访问，因此按顺序前后移动已经是最快的选择
        else p = q;
    }
    return old_size-_size;
}

template <typename T>
void List<T>::mergeSort(Posi(T) p, int n){
    if(n<2) return;//递归基
    Posi(T) q = p; int m = n>>1;
    for(int i=0;i<m;i++) q = q->succ;
    mergeSort(p, m); mergeSort(q, n-m);
    merge(p, m, this, q, m-m);
}

template <typename T>//把所有的q放到p中去
void List<T>::merge(Posi(T) p, int n, List<T>& l, Posi(T) q, int m){
    Posi(T) pp = p->pred;
    while(0<m){
        if(0<n and (q->data>=p->data)){//p还在范围中，当q的值不小于p的值时，不进行合并，取p的后继
            p = p->succ;
            if(p == q) break;//如果p到q了，就结束了；此时因为可以相同的话就说明是一个列表中，可以跳过
            n--;
        }else{//此时如果是q小，就插入到p的前面，因为是已经搜索过的，此时的p就是正确的位置；如果是因为p走完了，那就是将所有的q都放到p的前面
            insertB(p,l.remove((q=q->succ)->pred)); m--;
        }
    }
    p = pp->succ;
}
