// Side Project1: MySTL_vector
// This is a header file to fufil some of the functions of vector<> in C++
// Written by Luke_Dong

/*
    Basic function of vector:
    1. operator[]: Access elements
    2. size: return the numbers of elements
    3. capacity:
    4. insert()
    5. push_back()
    6. pop_back()
    7. insert()

*/
#include <assert.h>
#include <string.h>
#include <iostream>

namespace hkd {

template<typename T>
class Vector {
public:
    typedef T value_type;
    typedef T* iterator;

private:
    value_type* _data;
    unsigned int _size;
    unsigned int _capacity;

public:
    // default constructor
    Vector() : _data(NULL), _size(0), _capacity(0) {}
    // copy constructor: copy the size and data from same T
    Vector(const Vector& other) {
        _size = other._size;
        _capacity = other._capacity;
        _data = new value_type[_capacity];
        // copy data
        for (int i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
    }
    // destructor
    ~Vector() {
        delete[] _data;
        _size = 0;
        _capacity = 0;
    }
    // override = ; vec1 = vec2;
    Vector operator=(const Vector& vec) {
        // 1. create a temp space for vec, becuz size maybe different.

        // this is ptr, vec is instance, &vec is the address
        if (&vec == this) return *this;
        value_type* temp = new value_type[vec._capacity];
        for (int i = 0; i < vec._size; i++) {
            temp[i] = vec._data[i];
        }
        delete[] _data;
        _data = temp;
        _size = vec._size;
        _capacity = vec._capacity;

        // this is ptr for class itself, is the house itself when walking into
        return *this;
    }
    // override []
    value_type& operator[](const size_t vecIndex) {
        // 1. usage: vec[],
        if (vecIndex > _size) {
            throw std::out_of_range("invalid index.");
        }
        return _data[vecIndex];
    }
    // override ==
    bool operator==(const Vector& vec) const {
        if (_size != vec._size) return false;
        for (int i = 0; i < _size; i++) {
            if (_data[i] != vec._data[i]) return false;
        }
        return true;
    }

    // Array operation
    iterator insert(value_type data, iterator insertIndex);
    iterator erase(iterator eraseIndex);
    void push_back(value_type data);
    void pop_back();
    // Array search operation
    iterator begin();
    iterator end();
    // Array size op
    void resize(size_t newSize, const value_type value);
    void reserve(size_t newSize);
};

template <class T>
typename Vector<T>::iterator
    Vector<T>::insert(T data, T* insertIndex) {
    // 1. usage: 
    // insertIndex is T ptr, so the index num is minus the beginning of array ptr
    size_t index = insertIndex - _data;
    if (index > _size) {
        throw std::out_of_range("invalid index.");
    }
    if (_capacity == 0) {
        _capacity = 1;
        _data = new T[1];
        _data[0] = data;
    }
    // Need more space when insert elements
    else if (_size + 1 > _capacity) {
        _capacity *= 2;
        T* temp = new T[_capacity];
        temp[index] = data;
        for (int i = 0; i < index; i++) {
            temp[i] = _data[i];
        }
        // Now temp and original vector has 1 step different
        for (int i = index; i < _size; i++) {
            temp[i + 1] = _data[i];
        }
        delete[] _data;
        _data = temp;
    }
    else {
        for (int i = _size - 1; i >= index; i--) {
            _data[i + 1] = _data[i];
        }
        _data[index] = data;
    }
    // Do not forget the size change
    _size++;
    return _data + index;
}

// erase: delete element and return next element iterator
template <class T>
typename Vector<T>::iterator
    Vector<T>::erase(T* eraseIndex) {
    size_t index = eraseIndex - _data;
    if (index > _size) {
        throw std::out_of_range("invalid index.");
    }
    if (_size == 1) {
        delete[] _data;
        _data = nullptr;
        _capacity = 0;
    }
    else {
        for (int i = _size - 1; i > index; i--) {
            _data[i - 1] = _data[i];
        }
    }
    _size--;
    return end();
}

template <class T>
void Vector<T>::push_back(T data) {
    if (_capacity == 0) {
        _data = new T[1];
        _data[0] = data;
        _capacity = 1;
    }
    else if (_size + 1 > _capacity) {
        _capacity *= 2;
        T* temp = new T[_capacity];
        memcpy(temp, _data, _size * sizeof(T));
        temp[_size] = data;
        delete[] _data;
        _data = temp;
    }
    else {
        _data[_size] = data;
    }
    _size++;
}

template <class T>
void Vector<T>::pop_back() {
    if (_size == 1) {
        ~Vector();
    }
    _size--;
}

template <class T>
typename Vector<T>::iterator
    Vector<T>::begin() {
    return _data;
}

template <class T>
typename Vector<T>::iterator
    Vector<T>::end() {
    return _data + _size;
}

template <class T>
void Vector<T>::reserve(size_t newSize) {
    // Reserve only modifies the capacity but not size or content
    _capacity = newSize;
    if (newSize > _capacity) {
        T* temp = new T[newSize];
        memcpy(temp, _data, _size * sizeof(T));
        delete[] _data;
        _data = temp;
        delete[] temp;
    }
}

template <class T>
void Vector<T>::resize(size_t newSize, const T value) {
    if (newSize > _capacity) {
        reserve(newSize);
        for (int i = _size; i < newSize; i++) {
            _data[i] = value;
        }
    }
    else {
        _size = newSize;
    }
}
}

using namespace hkd;
int main() {
    hkd::Vector<std::string> vec;
    std::string s;
    int cnt1;
    std::cin >> cnt1;
    while (cnt1-- >= 0) {
        std::cin >> s;
        vec.push_back(s);
    }
    auto it = vec.begin();
    int cnt;
    std::cin >> cnt;
    for (int i = 0; i < cnt; i++) {
        it++;
    }
    vec.erase(it);
    for (auto n : vec) {
        std::cout << n << " ";
    }
    std::cout << std::endl;

}





