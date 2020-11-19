#include <cstdio>
#define BinNodePosi(T) BinNode<T>*

template <typename T> struct
BinNode{
    BinNodePosi(T) parent, lc, rc;
    T data; int height; int size();
    BinNodePosi(T) insertAsLc(T const &);
    BinNodePosi(T) insertAsRc(T const &);
    BinNodePosi(T) succ();//在中序遍历意义下的直接后继（在搜索树中有应用
    template <typename VST> travLevel(VST &);//子树层次遍历
    template <typename VST> travPre(VST &);//子树前序遍历
    template <typename VST> travIn(VST &);//子树中序遍历
    template <typename VST> travPost(VST &);//子树后序遍历
};