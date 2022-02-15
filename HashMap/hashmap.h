//
// Created by john on 2/10/22.
//

#ifndef STORELIB_HASHMAP_H
#define STORELIB_HASHMAP_H

#include <cstdlib>
#include <cstring>
#include <cassert>
#include <bit>

//https://lemire.me/blog/2018/08/15/fast-strongly-universal-64-bit-hashing-everywhere/
template<typename T>
u_int32_t simple_hash(T data){
    u_int64_t a = 0x1AFF5242A3F32542,b=0x0BA18C49123BF069,c=0xDEADBEEFDEADC0D3; //magic constants

    auto sized_data = (u_int64_t) data;
//    int low = (int)x;
    auto low = (u_int32_t) sized_data;
//    int high = (int)(x >>> 32);
    auto high = (u_int32_t) (sized_data >> 32);
//    return (int)((a * low + b * high + c) >>> 32);
    return (u_int32_t)((a * low + b * high + c)>>32);
}

//a simple linear search that either returns the index of element `needle`
// in array `haystack` or returns `-1` (max unsigned int value)
template<typename T>
size_t linear_search(T needle, T* haystack, size_t haystack_len){
    for (size_t x = 0; x<haystack_len; x++)
        if (haystack[x] == needle)
            return x;
    return -1;
}

template<typename T,typename Y>
struct bucket {
    Y* data;
    T* keys;
    size_t siz;
    size_t used;
};

template<typename T,typename Y>
struct hashmap {
public:
    hashmap();
    explicit hashmap(size_t);
    bucket<T,Y>& operator[](size_t);
    ~hashmap();
    Y get(T);
    void put(T, Y);
    void remove(T);
private:

    bucket<T,Y>* mem;
    T* keys;

    size_t length{};

    size_t get_index_for(T);
};

template<typename T, typename Y>
hashmap<T, Y>::hashmap(size_t len) {
    this->mem = (bucket<T,Y>*)malloc(len * sizeof(bucket<T,Y>));
    this->keys = (T*) malloc(len * sizeof (T));
    if (this->mem != nullptr && this->keys != nullptr) {
        this->length = len;
    }
    else
        this->length = 0;
}

template<typename T, typename Y>
hashmap<T, Y>::hashmap() = default;

template<typename T, typename Y>
bucket<T,Y>& hashmap<T,Y>::operator[](size_t index){
    assert(index<this->length); //-Werror=array-bounds will catch this, but best to stay safe
    return *(this->mem + index);
}

template<typename T, typename Y>
size_t hashmap<T,Y>::get_index_for(T key){
    auto hash = simple_hash(key);
    return hash%this->length;
}

template<typename T, typename Y>
void hashmap<T, Y>::put(T key, Y data) {
    //fixme: implement resizing
    //fixme: implement resizing buckets
    //fixme: check if key already exists and overwrite value
    //fixme: fix size of hashmap so it corresponds to number of elements currently stored
    auto index = this->get_index_for(key);
    if (this->mem[index].data == nullptr){
        this->mem[index] = *(new bucket {new Y(10), new T(10), 10, 0});
    }
    assert(this->mem[index].used < this->mem[index].siz);
    auto bucket_index = this->mem[index].used;
    this->mem[index].keys[bucket_index] = key;
    this->mem[index].data[bucket_index] = data;
    this->mem[index].used++;
}

template<typename T, typename Y>
void hashmap<T, Y>::remove(T key) {
    auto index = this->get_index_for(key);
    this->mem[index] = (bucket<T,Y>) {};
}

template<typename T, typename Y>
hashmap<T, Y>::~hashmap() {
    free(this->mem);
    free(this->keys);
}

template<typename T, typename Y>
Y hashmap<T, Y>::get(T key) {
    auto key_index = this->get_index_for(key);

    auto index = linear_search(key, this->mem[key_index].keys, this->mem[key_index].siz);
    if (index > this->mem[key_index].siz)
        return -1;
    return this->mem[key_index].data[index];
}


#endif //STORELIB_HASHMAP_H
