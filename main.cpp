#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

long count_reverse = 0;

template <typename T>
class Vector
{
public:
    Vector();
    Vector(int Size);
    Vector(int Size, T default_value);
    ~Vector();
    Vector(const Vector &other);
    int size();
    void print();
    void reverse();
    void resize(int size);
    void resize(int size, T default_value);
    void push_back(T element);
    void pop_back();
    void push_front(T element);
    void pop_front();
    void insert(int index, T value);
    void erase(int index);
    void set();
    int bin_search_left(T element);
    int bin_search_right(T element);
    int ternary_search(T element);
    void q_sort(int b, int e);
    void merge_sort(int left_limit, int right_limit);
    void heap_sort();
    void b_min_heap();
    int get_min_heap();
    void b_max_heap();
    int get_max_heap();
    void insert_min_heap(T element);
    void insert_max_heap(T element);
    T* begin();
    T* end();
    T& operator = (const Vector &other);
    T& operator [] (const int index);


private:
    int Size;
    T* data;
    int partition(int b, int e);
    void swap(T &a, T &b);
    void inter_sort(int l, int h);
    void merge(int left_limit, int middle, int right_limit);
    void Sift_Down_min(int i);
    void Sift_Down_max(int i);
    int median(int b, int sr, int e);
};
// class create, delete, assignment
template <typename T>
Vector<T>::Vector(int Size, T default_value) {
    this->Size = Size;
    data = new T[Size];
    for (int i = 0; i < Size; i++){
        data[i] = default_value;
    }
}

template<typename T>
Vector<T>::Vector(int Size) {
    this->Size = Size;
    data = new T[Size]{};
}

template<typename T>
Vector<T>::Vector() {
    this->Size = 0;
    data = new T[0]{};
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template<typename T>
Vector<T>::Vector(const Vector &other) {
    this->Size = other.Size;
    this->data = new T[other.Size];
    for (int i = 0; i < other.Size; i++){
        this->data[i] = other.data[i];
    }
}

//operator class

template<typename T>
T &Vector<T>::operator=(const Vector &other) {
    this->Size = other.Size;
    if (this->data != nullptr){
        delete[] this->data;
    }
    this->data = new T[other.Size];
    for (int i = 0; i < other.Size; i++){
        this->data[i] = other.data[i];
    }
    return this;
}

template<typename T>
T &Vector<T>::operator[](const int index) {
    return this->data[index];
}

//iterator

template<typename T>
T *Vector<T>::end() {
    return (this->data + this->Size);
}

template<typename T>
T *Vector<T>::begin() {
    return (this->data);
}

//class methods

template<typename T>
void Vector<T>::swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void Vector<T>::reverse() {
    T temp;
    for (int i = 0; i < this->Size/2; i++){
        temp = this->data[this->Size - 1 - i];
        this->data[this->Size - 1 - i] = this->data[i];
        this->data[i] = temp;
    }
}

template<typename T>
void Vector<T>::print() {
    for (int i = 0; i < this->Size; i++){
        cout << this->data[i] << " ";
    }
}

template <typename T>
int Vector<T>::size() {
    return this->Size;
}

template<typename T>
void Vector<T>::resize(int size) {
    T *temp = new T[size]{};
    for (int i = 0; i < size; i++){
        if (this->Size == i){
            break;
        }
        temp[i] = this->data[i];
    }
    this->Size = size;
    delete[]this->data;
    this->data = temp;
}

template<typename T>
void Vector<T>::resize(int size, T default_value) {
    T *temp = new T[size]{};
    for (int i = 0; i < size; i++){
        if (this->Size == i){
            break;
        }
        temp[i] = this->data[i];
    }
    int i = 0;
    while (this->Size + i < size){
        temp[i + this->Size] = default_value;
        i++;
    }
    this->Size = size;
    delete[]this->data;
    this->data = temp;
}

template<typename T>
void Vector<T>::push_back(T element) {
    T *temp = new T[this->Size + 1]{};
    for (int i = 0; i < this->Size; i++){
        temp[i] = this->data[i];
    }
    temp[this->Size] = element;
    this->Size = this->Size + 1;
    delete[]this->data;
    this->data = temp;
}

template<typename T>
void Vector<T>::pop_back() {
    T *temp = new T[this->Size - 1]{};
    for (int i = 0; i < this->Size - 1; i++){
        temp[i] = this->data[i];
    }
    this->Size = this->Size - 1;
    delete[]this->data;
    this->data = temp;
}

template<typename T>
void Vector<T>::push_front(T element) {
    T *temp = new T[this->Size + 1]{};
    for (int i = 1; i < this->Size + 1; i++){
        temp[i] = this->data[i - 1];
    }
    temp[0] = element;
    this->Size = this->Size + 1;
    delete[]this->data;
    this->data = temp;
}

template<typename T>
void Vector<T>::pop_front() {
    T *temp = new T[this->Size - 1]{};
    for (int i = 0; i < this->Size - 1; i++){
        temp[i] = this->data[i + 1];
    }
    this->Size = this->Size - 1;
    delete[]this->data;
    this->data = temp;
}

template<typename T>
void Vector<T>::insert(int index, T value) {
    T *temp = new T[this->Size + 1]{};
    for (int i = 0; i < index; i++){
        temp[i] = this->data[i];
    }
    temp[index] = value;
    for (int i = index + 1; i < this->Size + 1; i++){
        temp[i] = this->data[i - 1];
    }
    this->Size = this->Size + 1;
    delete[]this->data;
    this->data = temp;
}

template<typename T>
void Vector<T>::erase(int index) {
    for (int i = index; i < this->Size; ++i) {
        this->data[i] = this->data[i + 1];
    }
    this->Size = this->Size - 1;
}

template<typename T>
void Vector<T>::set() {
    T *temp = new T[this->Size];
    int count = 0;
    for (int i = 0; i < this->Size; i++){
        bool f = false;
        for (int j = count - 1; j >= 0; j--){
            if (this->data[i] == temp[j]){
                f = true;
                break;
            }
        }
        if (!f){
            temp[count++] = this->data[i];
        }
    }
    delete[]this->data;
    this->data = temp;
    this->Size = count;
}

// sort

template<typename T>
void Vector<T>::q_sort(int b, int e) {
    if (b < e)
    {
        int p = partition(b, e);
        q_sort(b, p);
        q_sort(p + 1, e);
    }
}

template<typename T>
int Vector<T>::partition(int b, int e) {
    T pivot = this->data[median(b, (b+e)/2, e)];
    int f = b - 1, l = e + 1;
    while(true) {
        f++; l--;
        for(; this->data[f] < pivot; f++){}
        for(; this->data[l] > pivot; l--){}
        if (f >= l){
            return l;
        }
        swap(this->data[f], this->data[l]);
    }
}

template<typename T>
int Vector<T>::median(int b, int sr, int e) {
    if (this->data[b] > this->data[sr]) {
        if (this->data[e] > this->data[b])
            return b;
        return (this->data[sr] > this->data[e]) ? sr : e;
    }
    if (this->data[e] > this->data[sr])
        return sr;
    return (this->data[b] > this->data[e]) ? b : e;
}

template<typename T>
void Vector<T>::inter_sort(int l, int h) {
    for (int i = l + 1; i <= h; i++)
    {
        int value = this->data[i];
        int j = i;
        while (j > l && this->data[j - 1] > value)
        {
            this->data[j] = this->data[j - 1];
            j--;
        }
        this->data[j] = value;
    }
}

template<typename T>
void Vector<T>::merge_sort(int left_limit, int right_limit) {
    if (left_limit + 1 >= right_limit){
        return;
    }
    int middle = (left_limit + right_limit) / 2;
    merge_sort(left_limit, middle);
    merge_sort(middle, right_limit);
    merge(left_limit, middle, right_limit);
}

template<typename T>
void Vector<T>::merge(int left_limit, int middle, int right_limit) {
    T *temp = new T[right_limit - left_limit];
    int left = 0, right = 0;
    while (left_limit + left < middle && middle + right < right_limit){
        if (this->data[left + left_limit] <= this->data[middle + right]){
            temp[left + right] = this->data[left + left_limit];
            left++;
        }else{
            temp[left + right] = this->data[middle + right];
            right++;
            count_reverse += middle - (left_limit + left);
        }
    }
    while (left_limit + left < middle){
        temp[left + right] = this->data[left_limit + left];
        left++;
    }
    while (middle + right < right_limit){
        temp[left + right] = this->data[middle + right];
        right++;
    }
    for (int i = 0; i < right + left; i++){
        this->data[left_limit + i] = temp[i];
    }
    delete[]temp;
}

template<typename T>
void Vector<T>::heap_sort() {
    b_max_heap();
    int size = this->Size;
    for (int i = 0; i < size - 1; i++){
        this->data[size - i - 1] = get_max_heap();
    }
    this->Size = size;
}

// search

template<typename T>
int Vector<T>::bin_search_right(T element) {
    int left_limit = 0, right_limit = this->Size - 1, middle;
    while(left_limit < right_limit){
        middle = (left_limit + right_limit + 1) / 2;
        if (this->data[middle] <= element){
            left_limit = middle;
        }else{
            right_limit = middle - 1;
        }
    }
    if (this->data[left_limit] == element){
        return left_limit;
    }else{
        return -1;
    }
}

template<typename T>
int Vector<T>::bin_search_left(T element) {
    int left_limit = 0, right_limit = this->Size - 1, middle;
    while(left_limit < right_limit){
        middle = (left_limit + right_limit) / 2;
        if (this->data[middle] < element){
            left_limit = middle + 1;
        }else{
            right_limit = middle;
        }
    }
    if (this->data[right_limit] == element){
        return left_limit;
    }else{
        return -1;
    }
}

template<typename T>
int Vector<T>::ternary_search(T element) {
    int left = 0;
    int right = this->Size - 1;
    while (left <= right){
        int step = (right - left)/3;
        int bound_1 = left + step;
        int bound_2 = right - step;
        if (this->data[bound_1] == element){
            return bound_1;
        }
        if (this->data[bound_2] == element){
            return bound_2;
        }
        if (this->data[bound_1] < element && this->data[bound_2] > element){
            left = bound_1 + 1;
            right = bound_2 - 1;
        }else if (this->data[bound_1] > element){
            right = bound_1 - 1;
        }else{
            left = bound_2 + 1;
        }
    }
    return -1;
}

// heap

template<typename T>
void Vector<T>::b_min_heap() {
    for (int i = (this->Size - 1) / 2; i >= 0; i--){
        Sift_Down_min(i);
    }
}

template<typename T>
void Vector<T>::Sift_Down_min(int i) {
    int left = 2*i + 1;
    int right = 2*i + 2;
    int temp = i;
    if (left < this->Size && this->data[left] < this->data[i])
        temp = left;
    if (right < this->Size && this->data[right] < this->data[temp])
        temp = right;
    if (temp != i) {
        swap(this->data[i], this->data[temp]);
        Sift_Down_min(temp);
    }
}

template<typename T>
int Vector<T>::get_min_heap() {
    int res = this->data[0];
    this->data[0] = this->data[this->Size - 1];
    this->Size--;
    Sift_Down_min(0);
    return res;
}

template<typename T>
void Vector<T>::b_max_heap() {
    for (int i = this->Size / 2 - 1; i >= 0; i--){
        Sift_Down_max(i);
    }
}

template<typename T>
void Vector<T>::Sift_Down_max(int i){
    int left = 2*i + 1;
    int right = 2*i + 2;
    int temp = i;
    if (left < this->Size && this->data[left] > this->data[i])
        temp = left;
    if (right < this->Size && this->data[right] > this->data[temp])
        temp = right;
    if (temp != i) {
        swap(this->data[i], this->data[temp]);
        Sift_Down_max(temp);
    }
}

template<typename T>
int Vector<T>::get_max_heap() {
    int res = this->data[0];
    this->data[0] = this->data[this->Size - 1];
    this->Size--;
    Sift_Down_max(0);
    return res;
}

template<typename T>
void Vector<T>::insert_min_heap(T element) {
    this->data[0] = element;
    Sift_Down_min(0);
}

template<typename T>
void Vector<T>::insert_max_heap(T element) {
    this->data[0] = element;
    Sift_Down_max(0);
}

int main() {
    //Vector<int> a();
}
