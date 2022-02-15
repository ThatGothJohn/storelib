//
// Created by john on 2/10/22.
//
#include <cstdio>
#include "hashmap.h"

int main(int argc, char** argv){
    (void)argc, (void)argv;
    size_t len = 25;
    hashmap<int,int> b(len);

    const char wa[] = "1234567890-=qwertyuiop[]#asdfghjkl;'zxcvbnm,./\\`¬!£$%^&*()_+{}~:@<>?|QWERTYUIOPASDFGHJKLZXCVBNM";
    auto i = 0;
    for (char ch : wa) {
        b.put(ch, wa[sizeof(wa)-i]);
        i++;
    }
    auto count = 0;
    for (char ch : wa) {
        printf("%c : %c\n", b.get(ch), ch);
        count++;
    }
    printf("\n %u : %lu \n", count, sizeof(wa));

    auto a = b.get('A');
    printf("%c\n", a);
    b.remove('A');
    a = b.get('A');
    printf("%i\n", a);


    auto w = simple_hash("oh no!");
    auto x= simple_hash(52);
    auto y = simple_hash("oh no!");
    auto z = simple_hash(0x1234FF5432198765);

    printf("\nSimple hash test: \n\"oh no!\" : %#X \n52 : %#X \n\"oh no!\" : %#X \n0x1234FF5432198765 : %#X\n%lu\n",w, x,y,z, sizeof (z));


    return 0;
}
