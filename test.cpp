//
// Created by john on 2/10/22.
//
#include <cstdio>
#include "hashmap.h"

int main(int argc, char** argv){
    (void)argc, (void)argv;
    size_t len = 30;
    hashmap<char,size_t> b(len);

    const char wa[] = "1234uboc:{:@];[;q9uopwQWE";
    for (char ch : wa) {
        b.put(ch, 42);
    }

    for (size_t x =0;x<len;x++)
        printf("%lu\n", b[x]);

    auto w = simple_hash("oh no!");
    auto x= simple_hash(52);
    auto y = simple_hash("oh no!");
    auto z = simple_hash(0x1234FF5432198765);

    printf("\nSimple hash test: \n\"oh no!\" : %#lX \n52 : %#lX \n\"oh no!\" : %#lX \n0x1234FF5432198765 : %#lX\n%lu\n",w, x,y,z, sizeof (z));


    return 0;
}
