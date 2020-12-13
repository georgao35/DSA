#include <cstdio>
#include <iostream>
#define NodePosi(T) treeNode<T>*
enum RBcolor{Red, Black};

inline int bigger(int a,int b){ return a>b? a:b; }
#define FromParentTo(x) /*来自父亲的引用*/ \
    ( (x->pa) ? ( (x)->isLC() ? (x)->pa->lc : (x)->pa->rc ):this->_root )

template <typename T> struct treeNode{
    T data;
    NodePosi(T) pa, *lc, *rc;
    int height;
    RBcolor color;
    treeNode():pa(nullptr), lc(nullptr), rc(nullptr), height(0), color(Red){}
    treeNode(T const& e, NodePosi(T) p = nullptr, NodePosi(T) lc = nullptr, NodePosi(T) rc = nullptr,
              int h = 0, RBcolor c = Red): data(e), pa(p), lc(lc), rc(rc), height(h), color(c){
              }
    NodePosi(T) insertAsLc(T const& src){
        return lc = new treeNode(src, this);
    }
    NodePosi(T) insertAsRc(T const& src){
        return rc = new treeNode(src, this);
    }
    bool isLC(){
        if(!pa) return false;
        return this == pa->lc;
    }
    bool isRC(){
        if(!pa) return false;
        return this == pa->rc;
    }
    NodePosi(T) succ(){
        NodePosi(T) w = this;
        if(rc){
            w = rc;
            while(w->lc) w = w->lc;
        }else{
            while(w->isRC()) w = w->pa;
            w = w->pa;
        }
        return w;
    }
    NodePosi(T) prev(){
        if(!lc){    
            NodePosi(T) cur = this;
            while(cur->isLC()) cur = cur->pa;
            return cur->pa;
        }else{
            NodePosi(T) cur = lc;
            while(cur->rc) cur = cur->rc;
            return cur;
        }
    }
    bool operator< (const treeNode& b){return data < b.data;}
};
template <typename T> inline int stature(NodePosi(T) t){
    return t? t->height:-1;
}

template <typename T> inline bool AvlBalanced(NodePosi(T) t){
    return -2 < stature(t->lc)-stature(t->rc) and stature(t->lc)-stature(t->rc) < 2;
}
template <typename T> inline NodePosi(T) tallerChild(NodePosi(T) x){
    if(stature(x->lc) > stature(x->rc)) return x->lc;
    else if(stature(x->rc) > stature(x->lc)) return x->rc;
    else return x->isLC()? x->lc:x->rc;
}

template <typename T> class BST{
public:
    int _size; NodePosi(T) _root, *_hot;
    NodePosi(T) connect34(
        NodePosi(T) a, NodePosi(T) b, NodePosi(T) c,
        NodePosi(T) T0, NodePosi(T) T1, NodePosi(T) T2, NodePosi(T) T3){
        a->lc = T0; if ( T0 ) T0->pa = a;
        a->rc = T1; if ( T1 ) T1->pa = a; updateHeight ( a );
        c->lc = T2; if ( T2 ) T2->pa = c;
        c->rc = T3; if ( T3 ) T3->pa = c; updateHeight ( c );
        b->lc = a; a->pa = b;
        b->rc = c; c->pa = b; updateHeight ( b );
        return b; //该子树新的根节点
    }
    NodePosi(T) rotateAt(NodePosi(T) x){
        NodePosi(T) p = x->pa; NodePosi(T) g = p->pa;
        if(p->isLC()){
            if(x->isLC()){
                p->pa = g->pa;
                return connect34(x,p,g,x->lc,x->rc,p->rc,g->rc);
            }else{
                x->pa = g->pa;
                return connect34(p,x,g,p->lc,x->lc,x->rc,g->rc);
            }
        }else{
            if(x->isRC()){
                p->pa = g->pa;
                return connect34(g,p,x,g->lc,p->lc,x->lc,x->rc);
            }else{
                x->pa = g->pa;
                return connect34(g,x,p,g->lc,x->lc,x->rc,p->rc);
            }
        }
    }
    BST(){
        _root = nullptr; _size = 0;
    }
    int updateHeight(NodePosi(T) x){
        return x->height = bigger(stature(x->lc),stature(x->rc))+1;
    }
    void updateHeightAbove(NodePosi(T) x){
        while(x){
            updateHeight(x); x = x->pa;
        }
    }
    virtual NodePosi(T)& search(const T& target){
        if(!_root || _root->data == target){
            _hot = nullptr; return _root;
        }
        _hot = _root;
        while(true){
            NodePosi(T)& c = (target < _hot->data)? _hot->lc:_hot->rc;
            if(!c or target == c->data) return c;
            _hot = c;
        }
    }
    virtual NodePosi(T) insert(const T& target){
        NodePosi(T)& x = search(target);
        if(!x){
            x = new treeNode<T> (target, _hot);
            _size++;
            updateHeightAbove(_hot);
        }
        return x;
    }
    void removeAt(NodePosi(T)& x,NodePosi(T)& hot){
        NodePosi(T) w = x; NodePosi(T) succ = nullptr;
        if(!w->lc) succ = x = x->rc;
        else if(!w->rc) succ = x = x->lc;
        else{
            w = w->succ();
            T tmp = w->data; w->data = x->data; x->data = tmp;
            NodePosi(T) u = w->pa;
            (u==x? u->rc:u->lc) = succ = w->rc;
        }
        hot = w->pa;
        if(succ) succ->pa = hot;
    }
    virtual bool remove(const T& target){
        NodePosi(T)& w = search(target); if(!w) return false;
        removeAt(w, _hot); _size--;
        updateHeightAbove(_hot);
        return true;
    }
};

template <typename T> class AVL: public BST<T>{
public:
    virtual NodePosi(T) insert(const T& target){
        NodePosi(T)& x = this->search(target); if(x) return x;
        this->_size++; NodePosi(T) xx = x = new treeNode<T>(target, this->_hot);
        for(NodePosi(T) g = this->_hot;g;g=g->pa){
            if(!AvlBalanced(g)){
                NodePosi(T)& a = FromParentTo(g);
                a = this->rotateAt(tallerChild(tallerChild(g)));
                break;
            }else
                this->updateHeight(g);
        }
        return xx;
    }
    virtual bool remove(const T& target){
        NodePosi(T)& w = this->search(target); if(!w) return false;
        this->BST<T>::removeAt(w, this->_hot); this->_size--;
        for(NodePosi(T) p = this->_hot;p;p=p->pa){
            if(!AvlBalanced(p)){
                NodePosi(T)& a = FromParentTo(p);
                p = a = this->rotateAt(tallerChild(tallerChild(p)));
            }
            this->updateHeight(p);
        }
        return true;
    }
};
BST<int> tree;

void travPrev(NodePosi(int) now){
    if(!now) return;
    printf("%d ", now->data);
    travPrev(now->lc); travPrev(now->rc);
}
void travMid(NodePosi(int) now){
    if(!now) return;
    travMid(now->lc); printf("%d ", now->data); travMid(now->rc);
}
void travPos(NodePosi(int) now){
    if(!now) return;
    travPos(now->lc); travPos(now->rc); printf("%d ", now->data);
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        int tmp; scanf("%d",&tmp);
        tree.insert(tmp);
    }
    travPrev(tree._root);puts("");
    travMid(tree._root);puts("");
    travPos(tree._root);puts("");
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        int tmp; scanf("%d", &tmp);
        if(tree.search(tmp)){
            printf("Yes\n");
        }else printf("No\n");
    }
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        int tmp; scanf("%d", &tmp);
        if(tree.remove(tmp)) printf("%d has now been deleted.\n", tmp);
        else printf("No number!\n");
    }
    travPrev(tree._root);puts("");
    travMid(tree._root);puts("");
    travPos(tree._root);puts("");
    return 0;
}