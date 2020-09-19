#include <iostream>
using namespace std;

typedef int Rank;

template <class T>
class Vector{
    int _size;
    T* _content;
    int _capacity;
public:
    Vector<T>();
    Vector<T>(const Vector<T>& src);
    Vector<T>(Vector<T>&& src);

    int size();
    void expand();
    void shrink();
    void append(const T&);
    T get(Rank r);

    Rank insert(Rank r, T const & e);
    int remove(Rank lo, Rank hi);//区间删除,返回删除的个数
    T remove(Rank r);//单个删除,视为上一个区间删除的特例

    bool disordered();
    void sort();
    int deduplicate();//返回减去的数量
    void uniquify();//对有序向量的去重操作
    template<typename VST> void traverse(VST& func);//通过函数对象进行遍历

    T& operator[](int Rank);

    Rank find(const T& e, Rank lo, Rank hi);//适用于所有向量的顺序查找
    T& binSearch(const T& e, Rank lo, Rank hi);//适用于有序向量的二分查找
};

template <class T>
int Vector<T>::size(){
    return _size;
}

template <class T>
void Vector<T>::expand(){//首先进行判断，果有必要再进行扩容
    if(_size < _capacity)
        return;
    T* old_content = _content;
    _content = new T [2*_capacity];
    for(int i=0;i<_capacity;++i) _content[i] = old_content[i];
    delete [] old_content;
    _capacity *= 2;
}

template <class T>
void Vector<T>::append(const T& src){
    expand();
    _content[_size++] = src;
}

template <class T>
T Vector<T>::get(Rank i){
    if(Rank >= 0 && Rank <_size) return _content[Rank];
    throw "rank out of range";
}

template <class T>
Rank Vector<T>::insert(Rank r, const T& e){
    if(r >= 0 && r <=_size){
        expand();
        for(Rank i=_size;i>r;++i)   _content[i] = _content[i-1];
        _content[r] = e;_size++;
        return r;
    }
    throw "rank out of range";
}

template <class T>
int Vector<T>::remove(Rank lo, Rank hi){
    if(lo == hi) return 0;
    //for(Rank i = hi;i<_size;++i) _content[i-hi+lo] = _content[i];
    //_size -= hi-lo;
    while(hi<_size) _content[lo++] = _content[hi++];
    _size = lo;
    return hi-lo;
}

template <class T>
T Vector<T>::remove(Rank r){
    T tmp = _content[r];
    remove(r,r+1);
    return tmp;
}

template <class T>
T& Vector<T>::operator[](int rank){
    if(rank >= 0 && rank <_size) return _content[rank];
    throw "rank out of range";
}

template <class T>//逆序查找
Rank Vector<T>::find(const T& e, Rank lo, Rank hi){
    if(0<=lo && lo<hi && hi<_size){
        while((lo < hi--)&&(_content[hi]!=e))//选择逆向查找
        return hi;//若hi小于lo时则错误
    }
    throw "error in index";
}

template <class T>
int Vector<T>::deduplicate(){
    int old_size = _size; Rank i = 1;
    while(i<_size){
        if(find(_content,0,i)<0) i++;
        else remove(i);//因为算法是从前到后，判断前面是否有相同的，并保证前面是独一无二的，因此删除当前这一个元素可以保证正确性
    }
    return old_size-_size;
}

template <class T>
void Vector<T>::uniquify(){
    Rank i=0,j=1;
    while(j<_size){
        if(_content[j-1]!=_content[j]) _content[++i]=_content[j];
        else j++;
    }
    _size = ++i; shrink();
    return j-i;
}

template <typename T> template <typename VST>
void Vector<T>::traverse(VST& func){
    for(Rank i=0;i<_size;++i){
        func(_content[i]);
    }
}


