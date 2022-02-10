//
// Created by john on 2/10/22.
//

#ifndef STORELIB_HASHMAP_H
#define STORELIB_HASHMAP_H

#include <cstdlib>
#include <cstring>
#include <cassert>

template<typename T,typename Y>
struct hashmap {
public:
    hashmap();
    explicit hashmap(size_t);
    Y& operator[](size_t);
    ~hashmap() = default;
private:
    Y* mem;
    size_t length;
};

template<typename T, typename Y>
hashmap<T, Y>::hashmap(size_t len) {
    this->mem = (Y*)malloc(len * sizeof(Y));
    if (this->mem != nullptr) {
        this->length = len;
        memset(this->mem, 42, len);
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

#endif //STORELIB_HASHMAP_H
