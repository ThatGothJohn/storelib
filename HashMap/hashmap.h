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
u_int64_t simple_hash(T data){
    u_int32_t a = 0xFF5242A3,b=0x123BF069,c=0xDEADBEEF; //magic constants

    auto sized_data = (u_int64_t) data;
//    int low = (int)x;
    auto low = (u_int32_t) sized_data;
//    int high = (int)(x >>> 32);
    auto high = (u_int32_t) (sized_data >> 32);
//    return (int)((a * low + b * high + c) >>> 32);
    return std::rotr((a * low + b * high + c), 32);
}

template<typename T,typename Y>
struct hashmap {
public:
    hashmap();
    explicit hashmap(size_t);
    Y& operator[](size_t);
    ~hashmap() = default;
    void put(T, Y);
    void remove(T);
private:
    Y* mem;
    size_t length;

    size_t get_index_for(T);
};

template<typename T, typename Y>
hashmap<T, Y>::hashmap(size_t len) {
    this->mem = (Y*)malloc(len * sizeof(Y));
    if (this->mem != nullptr) {
        this->length = len;
        memset(this->mem, 0, len);
    }
    else
        this->length = 0;
}

template<typename T, typename Y>
hashmap<T, Y>::hashmap() = default;

template<typename T, typename Y>
Y& hashmap<T,Y>::operator[](size_t index){
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
    auto index = this->get_index_for(key);
    this->mem[index] = data;
}

template<typename T, typename Y>
void hashmap<T, Y>::remove(T key) {
    auto index = this->get_index_for(key);
    this->mem[index] = (Y)NULL;
}

#endif //STORELIB_HASHMAP_H
