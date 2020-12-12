#include <cstdio>
#define NodePosi(T) treeNode<T>*
enum RBcolor{Red, Black};

template <typename T> struct treeNode{
    T data;
    NodePosi(T) pa, lc, rc;
    int height;
    RBcolor color;
    treeNode():pa(nullptr), lc(nullptr), rc(nullptr), height(0), color(Red){}
    treeNode( T e, NodePosi(T) p = nullptr, NodePosi(T) lc = nullptr, NodePosi(T) rc = nullptr,
              int h = 0, RBcolor c = Red): data(e), pa(p), lc(lc), rc(rc), height(h), color(c){}
    NodePosi(T) insertAsLc(const T& src){
        return lc = new treeNode(src, this);
    }
    NodePosi(T) insertAsRc(const T& src){
        return rc = new treeNode(src, this);
    }
    bool operator< (const treeNode& b){return data < b.data;}
};

template <typename T> class BST{
    int _size; NodePosi(T) _root, _hot;
public:
    virtual int updateHeight(NodePosi(T) x){

    }
    void updateHeightAbove(NodePosi(T) x){

    }
    virtual NodePosi(T)& search(const T& target){
        if(!_root || _root->data == target){
            _hot = nullptr; return _root;
        }
        _hot = _root; NodePosi(T) c=_root;
        while(true){
            
        }
    }
    virtual NodePosi(T) insert(const T& target){

    }
    virtual bool remove(const T& target){

    }
};

int main(){
    return 0;
}