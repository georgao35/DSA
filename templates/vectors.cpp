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

    int disordered();//返回逆序对的个数，代表了逆序的程度
    void sort();
    int deduplicate();//返回减去的数量
    int uniquify();//对有序向量的去重操作
    template<typename VST> void traverse(VST& func);//通过函数对象进行遍历

    T& operator[](int Rank);

    Rank find(const T& e, Rank lo, Rank hi);//适用于所有向量的顺序查找
    Rank binSearch(const T& e, Rank lo, Rank hi);//适用于有序向量的二分查找

    void bubbleSort(Rank lo, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    void merge(Rank lo, Rank mi, Rank hi);
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
    if(i >= 0 && i <_size) return _content[i];
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
    //for(Rank i = hi;i<_   size;++i) _content[i-hi+lo] = _content[i];
    //_size -= hi-lo;
    while(hi<_size) _content[lo++] = _content[hi++];
    _size = lo;//到哪里，lo进行了标注；同时由于++的存在，lo直接成为了哨兵
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
        while((lo < hi--)&&(_content[hi]!=e))//选择逆向查找；在比较的时候已经-1了，因此从数组取值的时候不会越界
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
int Vector<T>::uniquify(){
    Rank i=0,j=1;
    while(j<_size){
        if(_content[j-1]!=_content[j]) _content[++i]=_content[j];
        j++;
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
//约定返回的值：不大于e的最后一个元素
template <class T>
Rank Vector<T>::binSearch(const T& e, Rank lo, Rank hi){
    while(lo<hi){
        Rank mid = (lo+hi)>>1;
        e<_content[mid]? hi=mid:lo=mid+1;
    }
    return lo-1;
}

template <class T>
int Vector<T>::disordered(){
    int cnt = 0;
    for(int i=1;i<_size;++i)
        cnt += (_content[i-1]>_content[i]);//逆序则计数的高端写法
    return cnt;
}

template <class T>
void Vector<T>::bubbleSort(Rank lo, Rank hi){
    //应当有输入判断
    
}

template <class T>
void Vector<T>::mergeSort(Rank lo, Rank hi){
    if(hi-lo < 2) return; //递归基!当单位长度时已经有序
    Rank mid = (lo+hi)>>1;
    mergeSort(lo, mid);
    mergeSort(mid, hi);
    merge(lo, mid, hi);
}

template <class T>
void Vector<T>::merge(Rank lo, Rank mid, Rank hi){
    Rank i=0; T* A = _content+lo;
    int len = mid-lo;
    Rank j=0; T* B = new T [len];
    for(Rank i=0;i<len;++i) B[i] = A[i];
    Rank k=0; T* C = _content+mid;
    while(j<len and k<hi-mid)
        A[i++] = (B[j]<=C[k])? B[j++]:C[k++];
    while(j<len)//如果C先耗尽了，则将B中的
        A[i++] = B[j++];
    delete [] B;
}
