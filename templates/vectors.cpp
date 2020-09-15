#include <iostream>
using namespace std;

template <class T>
class vector{
    int _size;
    T* _content;
    int _length;
public:
    void expand();
    void append();
    void deduplicate();
    void uniquify();

    T& binSearch(const T& e, int lo, int hi);
};

template <class T>
void vector<T>::expand(){
    if(_size == _length){
        
    }
}