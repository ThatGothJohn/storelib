//
// Created by john on 2/10/22.
//
#include <cstdio>
#include "hashmap.h"

int main(int argc, char** argv){
    (void)argc, (void)argv;
    size_t len = 10;
    hashmap<int,size_t> b(len);
    for (size_t x =0;x<len;x++)
        b[x] = x;

    for (size_t x =0;x<len;x++)
        printf("%lu\n", b[x]);

    return 0;
}
