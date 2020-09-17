#include <iostream>
using namespace std;

template <class T>
class Vector{
    int _size;
    T* _content;
    int _length;
public:
    Vector<T>();
    Vector<T>(const Vector<T>& src);
    Vector<T>(Vector<T>&& src);

    void expand();
    void append(const T&);
    void deduplicate();
    void uniquify();

    T& operator[](int rank);

    T& binSearch(const T& e, int lo, int hi);
};

template <class T>
void Vector<T>::expand(){
    if(_size < _length)
        return;
    T* old_content = _content;
    _content = new T [2*_length];
    for(int i=0;i<_length;++i) _content[i] = old_content[i];
    delete [] old_content;
    _length *= 2;
}

template <class T>
void Vector<T>::append(const T& src){
    expand();
    _content[_size++] = src;
}

template <class T>
T& Vector<T>::operator[](int rank){
    if(rank >= 0 && rank <_size) return _content[rank];
}