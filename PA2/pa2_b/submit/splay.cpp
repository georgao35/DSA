#include <cstdio>
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
protected:
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
public:
    BST(){
        _root = nullptr; _size = 0;
    }
    ~BST(){
        release(_root);
    }
    void release(NodePosi(T) now){
        if(!now) return;
        if(now->lc) release(now->lc);
        if(now->rc) release(now->rc);
        delete now;
    }
    NodePosi(T) hot(){return _hot;}
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
            ((u==x)? u->rc:u->lc) = succ = w->rc;
        }
        hot = w->pa;
        if(succ) succ->pa = hot;
        delete w;
    }
    virtual bool remove(const T& target){
        NodePosi(T)& w = search(target); if(!w) return false;
        removeAt(w, _hot); _size--;
        updateHeightAbove(_hot);
        return true;
    }
};

template <typename T> inline void attachAsLc(NodePosi(T) pa, NodePosi(T) lc){
    pa->lc = lc; if(lc) lc->pa = pa;
}
template <typename T> inline void attachAsRc(NodePosi(T) pa, NodePosi(T) rc){
    pa->rc = rc; if(rc) rc->pa = pa;
}

template <typename T> class Splay: public BST<T>{
protected:
    NodePosi(T) splay(NodePosi(T) x){
        if(!x) return nullptr; NodePosi(T) p, *g;
        while((p = x->pa)and(g = p->pa)){
            NodePosi(T) gg = g->pa;
            if(x->isLC()){
                if(p->isLC()){
                    attachAsLc(g, p->rc); attachAsLc(p, x->rc);
                    attachAsRc(p, g); attachAsRc(x, p);
                }else{
                    attachAsLc(p, x->rc); attachAsRc(g, x->lc);
                    attachAsLc(x, g); attachAsRc(x, p);
                }
            }else{
                if(p->isRC()){
                    attachAsRc(g, p->lc); attachAsRc(p, x->lc);
                    attachAsLc(p, g); attachAsLc(x, p);
                }else{
                    attachAsLc(g, x->rc); attachAsRc(p, x->lc);
                    attachAsLc(x, p); attachAsRc(x, g);
                }
            }
            if(!gg) x->pa = nullptr;
            else{
                ( g==gg->lc? gg->lc:gg->rc) = x; x->pa = gg;
            }
            this->updateHeight(g); this->updateHeight(p); this->updateHeight(x); //更新当前的结点高度
        }
        if(p = x->pa){
            if(x->isLC()){
                attachAsLc(p, x->rc); attachAsRc(x, p);
            }else{
                attachAsRc(p, x->lc); attachAsLc(x, p);
            }
            this->updateHeight(p); this->updateHeight(x);
        }
        x->pa = nullptr;
        return x;//返回结点值，在调用处将其赋值为_root的值
    }
public:
    NodePosi(T)& search(const T& src) override {
        NodePosi(T) tar = BST<T>::search(src);
        return this->_root = splay(tar? tar:this->_hot);
    }
    NodePosi(T) insert(const T& src) override {
        if(!this->_root){
            this->_size++;
            return this->_root = new treeNode<T>(src);
        }
        NodePosi(T) tar = search(src);
        if(tar->data == src) return tar;
        this->_size++; NodePosi(T) t = this->_root;
        if(src < t->data){
            t->pa = this->_root = new treeNode<T>(src, nullptr, t->lc, t);
            if(t->lc){
                t->lc->pa = this->_root; t->lc = nullptr;
            }
        }else{
            t->pa = this->_root = new treeNode<T>(src, nullptr, t, t->rc);
            if(t->rc){
                t->rc->pa = this->_root; t->rc = nullptr;
            }
        }
        this->updateHeightAbove(t);
        return this->_root;
    }
    bool remove(const T& src) override {
        NodePosi(T) tar = search(src);
        if(!this->_root or (tar->data != src)) return false;//没查找到的标记，由于splay中的更改了，因此有两种删除失败的条件：数空和查到的不是src
        this->_size--; NodePosi(T) w = this->_root;
        if(!w->lc){//如果没有左孩子
            this->_root = this->_root->rc; if(this->_root) this->_root->pa = nullptr;
        }else if(!w->rc){//如果没有右孩子
            this->_root = this->_root->lc; if(this->_root) this->_root->pa = nullptr;
        }else{//把左右孩子合并起来：利用splay的好性质使右子树的最小值提取上来
            NodePosi(T) lsub = this->_root->lc; lsub->pa = nullptr; this->_root->lc = nullptr;
            this->_root = this->_root->rc; this->_root->pa = nullptr;
            search(w->data);
            this->_root->lc = lsub; lsub->pa = this->_root;
        }
        //释放
        if(this->_root) this->updateHeight(this->_root);
        return true;
    }
};
Splay<int> tree;

int main(){
    int n;
    scanf("%d", &n); getchar();
    char operand; int para;
    while(n--){
        operand = getchar(); getchar(); scanf("%d",&para); getchar();
        if(operand == 'A') tree.insert(para);
        else if(operand == 'B') tree.remove(para);
        else{
            NodePosi(int) tar = tree.search(para);
            if(!tar) puts("-1");
            else if(tar->data == para) printf("%d\n", para);
            else if(tree.hot()->data < para) printf("%d\n", tree.hot()->data);
            else {
                NodePosi(int) a = tree.hot()->prev();
                if(a) printf("%d\n", a->data);
                else puts("-1");
            }
        }
    }
    return 0;
}